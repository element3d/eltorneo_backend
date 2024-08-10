#include "TeamsRoute.h"
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include "../managers/PQManager.h"

TeamsRoute* TeamsRoute::sInstance = nullptr;

TeamsRoute* TeamsRoute::Get()
{
    if (!sInstance) sInstance = new TeamsRoute();
    return sInstance;
}

std::function<void(const httplib::Request&, httplib::Response&)> TeamsRoute::GetTeams()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        // Extract league_id from query parameters
        std::string league_id = req.get_param_value("league_id");
        if (league_id.empty()) {
            res.set_content("League ID is required", "text/plain");
            res.status = 400; // Bad Request
            return;
        }

        // Validate league_id
        char* end;
        long lid = strtol(league_id.c_str(), &end, 10);
        if (*end) {
            res.set_content("Invalid league ID", "text/plain");
            res.status = 400; // Bad Request
            return;
        }

        // Connect to the database
        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string sql = "SELECT teams.id, teams.name, teams.short_name FROM teams "
            "JOIN leagues_teams ON teams.id = leagues_teams.team_id "
            "WHERE leagues_teams.league_id = " + std::to_string(lid) + ";";

        PGresult* ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_TUPLES_OK) {
            fprintf(stderr, "Failed to fetch teams: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500; // Internal Server Error
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetArray();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        for (int i = 0; i < nrows; ++i) {
            rapidjson::Value teamObj(rapidjson::kObjectType);
            int team_id = atoi(PQgetvalue(ret, i, 0));
            std::string team_name = PQgetvalue(ret, i, 1);
            std::string short_name = PQgetvalue(ret, i, 2);

            teamObj.AddMember("id", team_id, allocator);
            teamObj.AddMember("name", rapidjson::Value(team_name.c_str(), allocator), allocator);
            teamObj.AddMember("shortName", rapidjson::Value(short_name.c_str(), allocator), allocator);

            document.PushBack(teamObj, allocator);
        }

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200; // OK

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}


std::function<void(const httplib::Request&, httplib::Response&)> TeamsRoute::PostTeam()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "POST");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        rapidjson::Document document;
        document.Parse(req.body.c_str());
        if (!document.HasMember("name") || !document["name"].IsString()) 
        {
            res.set_content("Invalid input: name is required", "text/plain");
            res.status = 400; // Bad Request
            return;
        }
        std::string name = document["name"].GetString();

        // Connect to the database
        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string sql = "INSERT INTO teams(name) VALUES('" + name + "') RETURNING id;";

        // Execute the insert and capture the team ID
        PGresult* ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_TUPLES_OK) 
        {
            fprintf(stderr, "Failed to add team: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500; // Internal Server Error
            return;
        }

        // Get the new team ID from the query result
        int teamId = atoi(PQgetvalue(ret, 0, 0));
        PQclear(ret);

        // Check if leagueId is provided and is valid
        if (document.HasMember("leagueId") && document["leagueId"].IsInt()) 
        {
            int leagueId = document["leagueId"].GetInt();

            sql = "INSERT INTO leagues_teams(league_id, team_id) VALUES("
                + std::to_string(leagueId) + ", "
                + std::to_string(teamId) + ");";

            ret = PQexec(pg, sql.c_str());
            if (PQresultStatus(ret) != PGRES_COMMAND_OK) 
            {
                fprintf(stderr, "Failed to link team to league: %s", PQerrorMessage(pg));
                PQclear(ret);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 500; // Internal Server Error
                return;
            }
            PQclear(ret);
        }

        ConnectionPool::Get()->releaseConnection(pg);
        res.status = 201; // Created
        res.set_content("{\"message\": \"Team added successfully\", \"teamId\": " + std::to_string(teamId) + "}", "application/json");
    };
}