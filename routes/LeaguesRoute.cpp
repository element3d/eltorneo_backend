#include "LeaguesRoute.h"
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include "../managers/PQManager.h"
#include "MatchesInitializer.h"

#include "League.h"
#include "Team.h"




LeaguesRoute* LeaguesRoute::sInstance = nullptr;

LeaguesRoute* LeaguesRoute::Get()
{
    if (!sInstance) sInstance = new LeaguesRoute();
    return sInstance;
}

LeaguesRoute::LeaguesRoute() 
{
    Init();
}

void LeaguesRoute::Init()
{
    PGconn* pg = ConnectionPool::Get()->getConnection();
    std::string sql = "select count(*) from leagues";
    PGresult* ret = PQexec(pg, sql.c_str());
    int numLeagues = atoi(PQgetvalue(ret, 0, 0));
    PQclear(ret);
    if (numLeagues > 0) 
    {
     

        ConnectionPool::Get()->releaseConnection(pg);
        return;
    }
    std::string leagues[] =
    {
        "Champions League",
        "Premier League",
        "LaLiga",
        "Serie A",
        "Bundesliga",
        "Ligue 1"
    };


    for (auto& league : leagues) 
    {
        std::string sql = "insert into leagues(name) values ('"
            + league + "');";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }

    MatchesInitializer::InitPremierLeagueTeams24_25(pg);
    MatchesInitializer::InitLaLigaTeams24_25(pg);
    MatchesInitializer::InitSerieATeams24_25(pg);

    MatchesInitializer::InitPremierLeague24_25(pg);
    MatchesInitializer::InitLaLiga24_25(pg);
    MatchesInitializer::InitSerieA24_25(pg);

    ConnectionPool::Get()->releaseConnection(pg);
}

std::function<void(const httplib::Request&, httplib::Response&)> LeaguesRoute::GetSettings()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");


        PGconn* pg = ConnectionPool::Get()->getConnection();
        const char* sql = "SELECT * FROM settings;";
        PGresult* ret = PQexec(pg, sql);

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch settings: %s", PQerrorMessage(pg));
            PQclear(ret);
            res.status = 500;  // Internal Server Error
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetArray();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        char* temp = (char*)calloc(4096, sizeof(char));

        for (int i = 0; i < nrows; ++i)
        {
            rapidjson::Value objValue(rapidjson::kObjectType);

            // Handle ID as integer
            int id = atoi(PQgetvalue(ret, i, 0)); // Convert the string from the first column to an integer
            rapidjson::Value idValue;
            idValue.SetInt(id);

            // Handle name as string
            strcpy(temp, PQgetvalue(ret, i, 1));
            std::string version = temp;
            rapidjson::Value versionValue;
            versionValue.SetString(version.c_str(), version.size(), allocator);

            // Add key-value pairs to the object
            objValue.AddMember("id", idValue, allocator);
            objValue.AddMember("version", versionValue, allocator);
            objValue.AddMember("enableAds", atoi(PQgetvalue(ret, i, 2)), allocator);
            objValue.AddMember("numMinAdActions", atoi(PQgetvalue(ret, i, 3)), allocator);

            // Add the object to the document array
            document.PushBack(objValue, allocator);
        }
        free(temp);

        // Assuming you convert the Document to a string and send it in the response as before
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        // You can then use `buffer.GetString()` to get the JSON string
        // And send it in the response as follows:
        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;  // OK


        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> LeaguesRoute::GetLeagues()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");


        PGconn* pg = ConnectionPool::Get()->getConnection();
        const char* sql = "SELECT * FROM leagues order by id asc;";
        PGresult* ret = PQexec(pg, sql);

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch leagues: %s", PQerrorMessage(pg));
            PQclear(ret);
            res.status = 500;  // Internal Server Error
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetArray();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        char* temp = (char*)calloc(4096, sizeof(char));

        for (int i = 0; i < nrows; ++i)
        {
            rapidjson::Value objValue(rapidjson::kObjectType);

            // Handle ID as integer
            int id = atoi(PQgetvalue(ret, i, 0)); // Convert the string from the first column to an integer
            rapidjson::Value idValue;
            idValue.SetInt(id);

            // Handle name as string
            strcpy(temp, PQgetvalue(ret, i, 1));
            std::string name = temp;
            rapidjson::Value nameValue;
            nameValue.SetString(name.c_str(), name.size(), allocator);

            // Add key-value pairs to the object
            objValue.AddMember("id", idValue, allocator);
            objValue.AddMember("name", nameValue, allocator);

            strcpy(temp, PQgetvalue(ret, i, 2));
            std::string season = temp;
            rapidjson::Value saesonValue;
            saesonValue.SetString(season.c_str(), season.size(), allocator);
            objValue.AddMember("season", saesonValue, allocator);

            int currentWeek = atoi(PQgetvalue(ret, i, 3));
            objValue.AddMember("week", currentWeek, allocator);

            int numWeeks = atoi(PQgetvalue(ret, i, 4));
            objValue.AddMember("num_weeks", numWeeks, allocator);

            // Add the object to the document array
            document.PushBack(objValue, allocator);
        }
        free(temp);

        // Assuming you convert the Document to a string and send it in the response as before
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        // You can then use `buffer.GetString()` to get the JSON string
        // And send it in the response as follows:
        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;  // OK


        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> LeaguesRoute::GetLeague()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        // Get the league ID from query string
        auto id = req.get_param_value("id");
        if (id.empty()) 
        {
            res.set_content("League ID is required", "text/plain");
            res.status = 400;  // Bad Request
            return;
        }

        // Ensure the ID is an integer
        char* end;
        long league_id = strtol(id.c_str(), &end, 10);
        if (*end) 
        {
            res.set_content("Invalid league ID", "text/plain");
            res.status = 400;  // Bad Request
            return;
        }

        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string sql = "SELECT * FROM leagues WHERE id = " + std::to_string(league_id) + ";";
        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch league: %s", PQerrorMessage(pg));
            PQclear(ret);
            res.status = 500;  // Internal Server Error
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }

        if (PQntuples(ret) == 0)
        {
            res.set_content("League not found", "text/plain");
            res.status = 404;  // Not Found
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }

        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        // Assuming ID is column 0 and name is column 1
        rapidjson::Value idValue;
        idValue.SetInt(atoi(PQgetvalue(ret, 0, 0)));

        rapidjson::Value nameValue;
        nameValue.SetString(PQgetvalue(ret, 0, 1), allocator);

        document.AddMember("id", idValue, allocator);
        document.AddMember("name", nameValue, allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;  // OK

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}



std::function<void(const httplib::Request&, httplib::Response&)> LeaguesRoute::PostLeague()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        rapidjson::Document document;
        document.Parse(req.body.c_str());
   

        std::string name = document["name"].GetString();
        using namespace std::chrono;

        std::string sql = "INSERT INTO leagues(name) VALUES('"
            + (name) + "'"
            + ");";

        PGconn* pg = ConnectionPool::Get()->getConnection();
        PGresult* ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "Failed to add league: %s", PQerrorMessage(pg));
            PQclear(ret);
            res.status = 500;
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
        res.status = 200;
    };
}
