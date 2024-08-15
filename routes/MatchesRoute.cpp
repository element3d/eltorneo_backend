#include "MatchesRoute.h"
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include "../managers/PQManager.h"
#include <jwt-cpp/jwt.h>

MatchesRoute* MatchesRoute::sInstance = nullptr;

MatchesRoute* MatchesRoute::Get()
{
    if (!sInstance) sInstance = new MatchesRoute();
    return sInstance;
}

std::function<void(const httplib::Request&, httplib::Response&)> MatchesRoute::GetMatches()
{
    return [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        int userId = -1;
        std::string token = req.get_header_value("Authentication");
        if (token.size())
        {
            auto decoded = jwt::decode(token);
            userId = decoded.get_payload_claim("id").as_int();
        }

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

        std::string season = req.get_param_value("season");
        season = season.substr(2);
        std::string week = req.get_param_value("week");

        // Connect to the database
        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string sql = "SELECT m.id, m.league, m.season, m.week, m.match_date, m.team1_score, m.team2_score, "
            "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
            "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "
            "COALESCE(p.team1_score, -1) AS predicted_team1_score, " // Default -1 if NULL
            "COALESCE(p.team2_score, -1) AS predicted_team2_score, " // Default -1 if NULL
            "COALESCE(p.status, -1) AS status " // Default -1 if NULL          
            "FROM matches m "
            "JOIN teams t1 ON m.team1 = t1.id "
            "JOIN teams t2 ON m.team2 = t2.id "
            "LEFT JOIN predicts p ON p.match_id = m.id AND p.user_id = " + std::to_string(userId) + " "
            "WHERE m.league = " + std::to_string(lid) + " AND m.week = " + week + " AND m.season = '" + season + "' ORDER BY m.match_date ASC;";

        PGresult* ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_TUPLES_OK) {
            fprintf(stderr, "Failed to fetch matches: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500; // Internal Server Error
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetArray();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        for (int i = 0; i < nrows; ++i)
        {
            rapidjson::Value matchObj(rapidjson::kObjectType);
            int id = atoi(PQgetvalue(ret, i, 0));
            int league = atoi(PQgetvalue(ret, i, 1));
            std::string season = PQgetvalue(ret, i, 2);
            int week = atoi(PQgetvalue(ret, i, 3));
            long long date = atoll(PQgetvalue(ret, i, 4));

            int team1Score = atol(PQgetvalue(ret, i, 5));
            int team2Score = atol(PQgetvalue(ret, i, 6));


            rapidjson::Value team1Obj(rapidjson::kObjectType);
            team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 7)), allocator);
            team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 8), allocator), allocator);
            team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 9), allocator), allocator);

            rapidjson::Value team2Obj(rapidjson::kObjectType);
            team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 10)), allocator);
            team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 11), allocator), allocator);
            team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 12), allocator), allocator);

            matchObj.AddMember("id", id, allocator);
            matchObj.AddMember("league", league, allocator);
            matchObj.AddMember("season", rapidjson::Value(season.c_str(), allocator), allocator);
            matchObj.AddMember("week", week, allocator);
            matchObj.AddMember("team1", team1Obj, allocator);
            matchObj.AddMember("team2", team2Obj, allocator);
            matchObj.AddMember("date", (double)date, allocator);
            matchObj.AddMember("team1_score", team1Score, allocator);
            matchObj.AddMember("team2_score", team2Score, allocator);

            rapidjson::Value predictObj(rapidjson::kObjectType);
            predictObj.AddMember("team1_score", atoi(PQgetvalue(ret, i, 13)), allocator);
            predictObj.AddMember("team2_score", atoi(PQgetvalue(ret, i, 14)), allocator);
            predictObj.AddMember("status", atoi(PQgetvalue(ret, i, 15)), allocator);

            // Include prediction in match object
            matchObj.AddMember("predict", predictObj, allocator);

            // Add the updated match object to the document array
            document.PushBack(matchObj, allocator);
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
#include <ctime> // Include necessary libraries

std::function<void(const httplib::Request&, httplib::Response&)> MatchesRoute::GetMatchesByDay()
{
    return [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        int userId = -1;
        std::string token = req.get_header_value("Authentication");
        if (token.size())
        {
            auto decoded = jwt::decode(token);
            userId = decoded.get_payload_claim("id").as_int();
        }

        // Extract timestamp from query parameters
        std::string timestampString = req.get_param_value("timestamp");
        long long ts = atoll(timestampString.c_str());

        // Calculate start and end of the day in milliseconds
        time_t rawtime = ts / 1000;  // Convert to seconds
        struct tm timeinfo = *localtime(&rawtime);

        // Start of day
        timeinfo.tm_hour = 0;
        timeinfo.tm_min = 0;
        timeinfo.tm_sec = 0;
        auto dayStart = std::mktime(&timeinfo) * 1000;  // Convert back to milliseconds

        // End of day
        timeinfo.tm_hour = 23;
        timeinfo.tm_min = 59;
        timeinfo.tm_sec = 59;
        auto dayEnd = std::mktime(&timeinfo) * 1000;  // Convert back to milliseconds

        // Connect to the database
        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string sql = "SELECT m.id, m.league, m.season, m.week, m.match_date, m.team1_score, m.team2_score, "
            "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
            "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "
            "COALESCE(p.team1_score, -1) AS predicted_team1_score, " // Default -1 if NULL
            "COALESCE(p.team2_score, -1) AS predicted_team2_score, " // Default -1 if NULL
            "COALESCE(p.status, -1) AS status, " // Default -1 if NULL
            "l.name AS league_name, "  // Include league name
            "l.current_week "
            "FROM matches m "
            "JOIN teams t1 ON m.team1 = t1.id "
            "JOIN teams t2 ON m.team2 = t2.id "
            "LEFT JOIN predicts p ON p.match_id = m.id AND p.user_id = " + std::to_string(userId) + " "
            "JOIN leagues l ON m.league = l.id "  // Join with leagues table
            "WHERE m.match_date >= " + std::to_string(dayStart) + " AND m.match_date <= " + std::to_string(dayEnd) + " "
            "ORDER BY m.league ASC, m.match_date ASC;";



        PGresult* ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_TUPLES_OK) {
            fprintf(stderr, "Failed to fetch matches: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500; // Internal Server Error
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetArray();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        for (int i = 0; i < nrows; ++i)
        {
            rapidjson::Value matchObj(rapidjson::kObjectType);
            int id = atoi(PQgetvalue(ret, i, 0));
            int league = atoi(PQgetvalue(ret, i, 1));
            std::string season = PQgetvalue(ret, i, 2);
            int week = atoi(PQgetvalue(ret, i, 3));
            long long date = atoll(PQgetvalue(ret, i, 4));
            int team1Score = atol(PQgetvalue(ret, i, 5));
            int team2Score = atol(PQgetvalue(ret, i, 6));
            std::string leagueName = PQgetvalue(ret, i, 16); // Assuming league_name is the last column
            int currentWeek = atol(PQgetvalue(ret, i, 17));

            rapidjson::Value team1Obj(rapidjson::kObjectType);
            team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 7)), allocator);
            team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 8), allocator), allocator);
            team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 9), allocator), allocator);

            rapidjson::Value team2Obj(rapidjson::kObjectType);
            team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 10)), allocator);
            team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 11), allocator), allocator);
            team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 12), allocator), allocator);

            matchObj.AddMember("id", id, allocator);
            matchObj.AddMember("league", league, allocator);
            matchObj.AddMember("season", rapidjson::Value(season.c_str(), allocator), allocator);
            matchObj.AddMember("week", week, allocator);
            matchObj.AddMember("team1", team1Obj, allocator);
            matchObj.AddMember("team2", team2Obj, allocator);
            matchObj.AddMember("date", (double)date, allocator);
            matchObj.AddMember("team1_score", team1Score, allocator);
            matchObj.AddMember("team2_score", team2Score, allocator);
            matchObj.AddMember("league_name", rapidjson::Value(leagueName.c_str(), allocator), allocator); // Add league name
            matchObj.AddMember("currentWeek", currentWeek, allocator);

            rapidjson::Value predictObj(rapidjson::kObjectType);
            predictObj.AddMember("team1_score", atoi(PQgetvalue(ret, i, 13)), allocator);
            predictObj.AddMember("team2_score", atoi(PQgetvalue(ret, i, 14)), allocator);
            predictObj.AddMember("status", atoi(PQgetvalue(ret, i, 15)), allocator);
            matchObj.AddMember("predict", predictObj, allocator);

            document.PushBack(matchObj, allocator);
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

std::function<void(const httplib::Request&, httplib::Response&)> MatchesRoute::GetMatchesLive()
{
    return [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        int userId = -1;
        std::string token = req.get_header_value("Authentication");
        if (token.size()) {
            auto decoded = jwt::decode(token);
            userId = decoded.get_payload_claim("id").as_int();
        }

        // Get the current timestamp in milliseconds
        auto now = std::chrono::system_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto epoch = now_ms.time_since_epoch();
        auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
        long long currentTimeMs = value.count();

        // Connect to the database
        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string sql = "SELECT m.id, m.league, m.season, m.week, m.match_date, m.team1_score, m.team2_score, m.week_type, "
            "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
            "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "
            "COALESCE(p.team1_score, -1) AS predicted_team1_score, " // Default -1 if NULL
            "COALESCE(p.team2_score, -1) AS predicted_team2_score, " // Default -1 if NULL
            "COALESCE(p.status, -1) AS status, " // Default -1 if NULL
            "l.name AS league_name, "  // Include league name
            "l.current_week "
            "FROM matches m "
            "JOIN teams t1 ON m.team1 = t1.id "
            "JOIN teams t2 ON m.team2 = t2.id "
            "LEFT JOIN predicts p ON p.match_id = m.id AND p.user_id = " + std::to_string(userId) + " "
            "JOIN leagues l ON m.league = l.id "  // Join with leagues table
            "WHERE m.match_date < " + std::to_string(currentTimeMs) + " "
            "AND m.team1_score = -1 AND m.team2_score = -1 "
            "ORDER BY m.league ASC, m.match_date ASC;";

        PGresult* ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_TUPLES_OK) {
            fprintf(stderr, "Failed to fetch live matches: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500; // Internal Server Error
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetArray();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        for (int i = 0; i < nrows; ++i) 
        {
            rapidjson::Value matchObj(rapidjson::kObjectType);
            int id = atoi(PQgetvalue(ret, i, 0));
            int league = atoi(PQgetvalue(ret, i, 1));
            std::string season = PQgetvalue(ret, i, 2);
            int week = atoi(PQgetvalue(ret, i, 3));
            long long date = atoll(PQgetvalue(ret, i, 4));
            int team1Score = atol(PQgetvalue(ret, i, 5));
            int team2Score = atol(PQgetvalue(ret, i, 6));
            int weekType = atoi(PQgetvalue(ret, i, 7));
            std::string leagueName = PQgetvalue(ret, i, 17); // Assuming league_name is the last column
            int currentWeek = atol(PQgetvalue(ret, i, 18));

            rapidjson::Value team1Obj(rapidjson::kObjectType);
            team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 8)), allocator);
            team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 9), allocator), allocator);
            team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 10), allocator), allocator);

            rapidjson::Value team2Obj(rapidjson::kObjectType);
            team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 11)), allocator);
            team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 12), allocator), allocator);
            team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 13), allocator), allocator);

            matchObj.AddMember("id", id, allocator);
            matchObj.AddMember("league", league, allocator);
            matchObj.AddMember("season", rapidjson::Value(season.c_str(), allocator), allocator);
            matchObj.AddMember("week", week, allocator);
            matchObj.AddMember("team1", team1Obj, allocator);
            matchObj.AddMember("team2", team2Obj, allocator);
            matchObj.AddMember("date", (double)date, allocator);
            matchObj.AddMember("team1_score", team1Score, allocator);
            matchObj.AddMember("team2_score", team2Score, allocator);
            matchObj.AddMember("week_type", weekType, allocator);

            matchObj.AddMember("league_name", rapidjson::Value(leagueName.c_str(), allocator), allocator); // Add league name
            matchObj.AddMember("currentWeek", currentWeek, allocator);

            rapidjson::Value predictObj(rapidjson::kObjectType);
            predictObj.AddMember("team1_score", atoi(PQgetvalue(ret, i, 14)), allocator);
            predictObj.AddMember("team2_score", atoi(PQgetvalue(ret, i, 15)), allocator);
            predictObj.AddMember("status", atoi(PQgetvalue(ret, i, 16)), allocator);
            matchObj.AddMember("predict", predictObj, allocator);

            document.PushBack(matchObj, allocator);
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




std::function<void(const httplib::Request&, httplib::Response&)> MatchesRoute::GetMatch()
{
    return [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        // Extract league_id from query parameters
        std::string matchId = req.get_param_value("match_id");
       

    
        // Connect to the database
        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string sql = "SELECT m.id, m.league, m.season, m.week, m.match_date, m.team1_score, m.team2_score, m.week_type, "
            "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
            "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "
            "p.team1_score AS predicted_team1_score, p.team2_score AS predicted_team2_score, p.status, "
            "l.name AS league_name, "  // Include league name
            "l.current_week "
            "FROM matches m "
            "JOIN teams t1 ON m.team1 = t1.id "
            "JOIN teams t2 ON m.team2 = t2.id "
            "LEFT JOIN predicts p ON p.match_id = m.id "
            "JOIN leagues l ON m.league = l.id " // Join with leagues table
            "WHERE m.id = " + matchId + ";";

        PGresult* ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_TUPLES_OK) {
            fprintf(stderr, "Failed to fetch matches: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500; // Internal Server Error
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetArray();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        for (int i = 0; i < nrows; ++i)
        {
            rapidjson::Value matchObj(rapidjson::kObjectType);
            int id = atoi(PQgetvalue(ret, i, 0));
            int league = atoi(PQgetvalue(ret, i, 1));
            std::string season = PQgetvalue(ret, i, 2);
            int week = atoi(PQgetvalue(ret, i, 3));
            long long date = atoll(PQgetvalue(ret, i, 4));
            int team1Score = atol(PQgetvalue(ret, i, 5));
            int team2Score = atol(PQgetvalue(ret, i, 6));
            int weekType = atol(PQgetvalue(ret, i, 7));

            std::string leagueName = PQgetvalue(ret, i, 17);

            rapidjson::Value team1Obj(rapidjson::kObjectType);
            team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 8)), allocator);
            team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 9), allocator), allocator);
            team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 10), allocator), allocator);

            rapidjson::Value team2Obj(rapidjson::kObjectType);
            team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 11)), allocator);
            team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 12), allocator), allocator);
            team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 13), allocator), allocator);

            matchObj.AddMember("id", id, allocator);
            matchObj.AddMember("league", league, allocator);
            matchObj.AddMember("season", rapidjson::Value(season.c_str(), allocator), allocator);
            matchObj.AddMember("week", week, allocator);
            matchObj.AddMember("weekType", weekType, allocator);

            matchObj.AddMember("team1", team1Obj, allocator);
            matchObj.AddMember("team2", team2Obj, allocator);
            matchObj.AddMember("date", (double)date, allocator);
            matchObj.AddMember("team1_score", team1Score, allocator);
            matchObj.AddMember("team2_score", team2Score, allocator);
            matchObj.AddMember("leagueName", rapidjson::Value(leagueName.c_str(), allocator), allocator);
            matchObj.AddMember("currentWeek", atoi(PQgetvalue(ret, i, 18)), allocator); // Add current_week

            rapidjson::Value predictObj(rapidjson::kObjectType);
            predictObj.AddMember("team1_score", atoi(PQgetvalue(ret, i, 14)), allocator);
            predictObj.AddMember("team2_score", atoi(PQgetvalue(ret, i, 15)), allocator);
            predictObj.AddMember("status", atoi(PQgetvalue(ret, i, 16)), allocator);

            // Include prediction in match object
            matchObj.AddMember("predict", predictObj, allocator);

            document.PushBack(matchObj, allocator);
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

std::function<void(const httplib::Request&, httplib::Response&)> MatchesRoute::PostMatch()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "POST");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        rapidjson::Document document;
        document.Parse(req.body.c_str());

        int league = document["league"].GetInt();
        std::string season = "24/25";
        int week = document["week"].GetInt();
        int team1 = document["team1"].GetInt();
        int team2 = document["team2"].GetInt();
        long long date = document["date"].GetDouble();


        // Connect to the database
        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string sql = "INSERT INTO matches(league, season, week, team1, team2, match_date) VALUES("
            + std::to_string(league) + ", '"
            + season + "', "
            + std::to_string(week) + ", "
            + std::to_string(team1) + ", "
            + std::to_string(team2) + ", "
            + std::to_string(date) +
            +")";

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

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
        res.status = 201; // Created
    };
      
}

enum class EPredictStatus
{
    Pending,
    WinnerPredicted,
    ScorePredicted,
    Failed
};

std::function<void(const httplib::Request&, httplib::Response&)> MatchesRoute::EditMatch()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "POST");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        std::string matchId = req.get_param_value("match_id");

        rapidjson::Document document;
        document.Parse(req.body.c_str());
        
        int team1 = document["team1_score"].GetInt();
        int team2 = document["team2_score"].GetInt();
        long long date = document["date"].GetDouble();


        // Connect to the database
        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string sql = "update matches set team1_score = "
            + std::to_string(team1) + ", "
            + "team2_score = " + std::to_string(team2) + ", "
            + "match_date = " + std::to_string(date) +
            +" where id = " + (matchId) + ";";

        // Execute the insert and capture the team ID
        PGresult* ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "Failed to edit team: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500; // Internal Server Error
            return;
        }
        PQclear(ret);

        if (team1 >= 0 && team2 >= 0)
        {
            sql = "select * from predicts where match_id = " + matchId + ";";
            ret = PQexec(pg, sql.c_str());

            int nrows = PQntuples(ret);

            for (int i = 0; i < nrows; ++i)
            {

                int id = atoi(PQgetvalue(ret, i, 0));
                int userId = atoi(PQgetvalue(ret, i, 1));
                int mId = atoi(PQgetvalue(ret, i, 2));
                int t1score = atoi(PQgetvalue(ret, i, 3));
                int t2score = atoi(PQgetvalue(ret, i, 4));
                EPredictStatus predictStatus = (EPredictStatus)atoi(PQgetvalue(ret, i, 5));
                if (predictStatus != EPredictStatus::Pending) continue;

                int points = 0;
                EPredictStatus status = EPredictStatus::Pending;
                if (team1 == t1score && team2 == t2score)
                {
                    points = 3;
                    status = EPredictStatus::ScorePredicted;
                }
                else 
                {
                    if (team1 > team2 && t1score > t2score)
                    {
                        points = 1;
                        status = EPredictStatus::WinnerPredicted;
                    }
                    else if (team1 < team2 && t1score < t2score)
                    {
                        points = 1;
                        status = EPredictStatus::WinnerPredicted;
                    }
                    else if (team1 == team2 && t1score == t2score)
                    {
                        points = 1;
                        status = EPredictStatus::WinnerPredicted;
                    }
                    else
                    {
                        points = -1;
                        status = EPredictStatus::Failed;
                    }
                }

                {
                    sql = "update users set points = points + " + std::to_string(points) + " where id = " + std::to_string(userId) + ";";
                    PGresult* updateRet = PQexec(pg, sql.c_str());
                    PQclear(updateRet);
                }

                {
                    sql = "update predicts set status = " + std::to_string(int(status)) + " where id = " + std::to_string(id) + ";";
                    PGresult* updateRet = PQexec(pg, sql.c_str());
                    PQclear(updateRet);
                }
            }
            PQclear(ret);
        }

        ConnectionPool::Get()->releaseConnection(pg);
        res.status = 201; // Created
    };

}