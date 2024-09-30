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
        std::string sql = "SELECT m.id, m.league, m.season, m.week, m.week_type, m.match_date, m.team1_score, m.team2_score, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, "
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
            int weekType = atoi(PQgetvalue(ret, i, 4));

            long long date = atoll(PQgetvalue(ret, i, 5));

            int team1Score = atol(PQgetvalue(ret, i, 6));
            int team2Score = atol(PQgetvalue(ret, i, 7));
            int elapsed = atol(PQgetvalue(ret, i, 8));
            int team1ScoreLive = atol(PQgetvalue(ret, i, 9));
            int team2ScoreLive = atol(PQgetvalue(ret, i, 10));
            std::string status = PQgetvalue(ret, i, 11);


            rapidjson::Value team1Obj(rapidjson::kObjectType);
            team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 12)), allocator);
            team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 13), allocator), allocator);
            team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 14), allocator), allocator);

            rapidjson::Value team2Obj(rapidjson::kObjectType);
            team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 15)), allocator);
            team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 16), allocator), allocator);
            team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 17), allocator), allocator);

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
            matchObj.AddMember("elapsed", elapsed, allocator);
            matchObj.AddMember("team1_score_live", team1ScoreLive, allocator);
            matchObj.AddMember("team2_score_live", team2ScoreLive, allocator);
            matchObj.AddMember("status", rapidjson::Value(status.c_str(), allocator), allocator);

            rapidjson::Value predictObj(rapidjson::kObjectType);
            predictObj.AddMember("team1_score", atoi(PQgetvalue(ret, i, 18)), allocator);
            predictObj.AddMember("team2_score", atoi(PQgetvalue(ret, i, 19)), allocator);
            predictObj.AddMember("status", atoi(PQgetvalue(ret, i, 20)), allocator);

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

std::function<void(const httplib::Request&, httplib::Response&)> MatchesRoute::GetTeamMatches()
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

        // Extract team_id from query parameters
        std::string team_id = req.get_param_value("team_id");
        if (team_id.empty()) {
            res.set_content("Team ID is required", "text/plain");
            res.status = 400; // Bad Request
            return;
        }

        // Validate team_id
        char* end;
        long tid = strtol(team_id.c_str(), &end, 10);
        if (*end) {
            res.set_content("Invalid team ID", "text/plain");
            res.status = 400; // Bad Request
            return;
        }

        // Connect to the database
        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string sql = "SELECT m.id, m.league, l.name AS league_name, m.season, m.week, m.week_type, m.match_date, m.team1_score, m.team2_score, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, "
            "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
            "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "
            "COALESCE(p.team1_score, -1) AS predicted_team1_score, " // Default -1 if NULL
            "COALESCE(p.team2_score, -1) AS predicted_team2_score, " // Default -1 if NULL
            "COALESCE(p.status, -1) AS status " // Default -1 if NULL          
            "FROM matches m "
            "JOIN teams t1 ON m.team1 = t1.id "
            "JOIN teams t2 ON m.team2 = t2.id "
            "JOIN leagues l ON m.league = l.id "
            "LEFT JOIN predicts p ON p.match_id = m.id AND p.user_id = " + std::to_string(userId) + " "
            "WHERE (m.team1 = " + std::to_string(tid) + " OR m.team2 = " + std::to_string(tid) + ") AND m.team1_score > -1 AND m.team2_score > -1 ORDER BY m.match_date DESC;";

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

            // League object
            rapidjson::Value leagueObj(rapidjson::kObjectType);
            leagueObj.AddMember("id", atoi(PQgetvalue(ret, i, 1)), allocator);
            leagueObj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 2), allocator), allocator);

            std::string season = PQgetvalue(ret, i, 3);
            int week = atoi(PQgetvalue(ret, i, 4));
            int weekType = atoi(PQgetvalue(ret, i, 5));

            long long date = atoll(PQgetvalue(ret, i, 6));

            int team1Score = atol(PQgetvalue(ret, i, 7));
            int team2Score = atol(PQgetvalue(ret, i, 8));
            int elapsed = atol(PQgetvalue(ret, i, 9));
            int team1ScoreLive = atol(PQgetvalue(ret, i, 10));
            int team2ScoreLive = atol(PQgetvalue(ret, i, 11));
            std::string status = PQgetvalue(ret, i, 12);

            rapidjson::Value team1Obj(rapidjson::kObjectType);
            team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 13)), allocator);
            team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 14), allocator), allocator);
            team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 15), allocator), allocator);

            rapidjson::Value team2Obj(rapidjson::kObjectType);
            team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 16)), allocator);
            team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 17), allocator), allocator);
            team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 18), allocator), allocator);

            matchObj.AddMember("id", id, allocator);
            matchObj.AddMember("league", leagueObj, allocator); // Add league object
            matchObj.AddMember("season", rapidjson::Value(season.c_str(), allocator), allocator);
            matchObj.AddMember("week", week, allocator);
            matchObj.AddMember("weekType", weekType, allocator);
            matchObj.AddMember("team1", team1Obj, allocator);
            matchObj.AddMember("team2", team2Obj, allocator);
            matchObj.AddMember("date", (double)date, allocator);
            matchObj.AddMember("team1_score", team1Score, allocator);
            matchObj.AddMember("team2_score", team2Score, allocator);
            matchObj.AddMember("elapsed", elapsed, allocator);
            matchObj.AddMember("team1_score_live", team1ScoreLive, allocator);
            matchObj.AddMember("team2_score_live", team2ScoreLive, allocator);
            matchObj.AddMember("status", rapidjson::Value(status.c_str(), allocator), allocator);

            rapidjson::Value predictObj(rapidjson::kObjectType);
            predictObj.AddMember("team1_score", atoi(PQgetvalue(ret, i, 19)), allocator);
            predictObj.AddMember("team2_score", atoi(PQgetvalue(ret, i, 20)), allocator);
            predictObj.AddMember("status", atoi(PQgetvalue(ret, i, 21)), allocator);

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
        std::string sql = "SELECT m.id, m.league, m.season, m.week, m.week_type, m.match_date, m.team1_score, m.team2_score, m.elapsed, m.team1_score_live, m.team2_score_live, m.status,"
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
            int weekType = atoi(PQgetvalue(ret, i, 4));

            long long date = atoll(PQgetvalue(ret, i, 5));
            int team1Score = atol(PQgetvalue(ret, i, 6));
            int team2Score = atol(PQgetvalue(ret, i, 7));
            int elapsed = atol(PQgetvalue(ret, i, 8));
            int team1ScoreLive = atol(PQgetvalue(ret, i, 9));
            int team2ScoreLive = atol(PQgetvalue(ret, i, 10));
            std::string status = (PQgetvalue(ret, i, 11));


            std::string leagueName = PQgetvalue(ret, i, 21); // Assuming league_name is the last column
            int currentWeek = atol(PQgetvalue(ret, i, 22));

            rapidjson::Value team1Obj(rapidjson::kObjectType);
            team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 12)), allocator);
            team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 13), allocator), allocator);
            team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 14), allocator), allocator);

            rapidjson::Value team2Obj(rapidjson::kObjectType);
            team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 15)), allocator);
            team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 16), allocator), allocator);
            team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 17), allocator), allocator);

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
            matchObj.AddMember("elapsed", elapsed, allocator);
            matchObj.AddMember("team1_score_live", team1ScoreLive, allocator);
            matchObj.AddMember("team2_score_live", team2ScoreLive, allocator);
            matchObj.AddMember("status", rapidjson::Value(status.c_str(), allocator), allocator);



            matchObj.AddMember("league_name", rapidjson::Value(leagueName.c_str(), allocator), allocator); // Add league name
            matchObj.AddMember("currentWeek", currentWeek, allocator);

            rapidjson::Value predictObj(rapidjson::kObjectType);
            predictObj.AddMember("team1_score", atoi(PQgetvalue(ret, i, 18)), allocator);
            predictObj.AddMember("team2_score", atoi(PQgetvalue(ret, i, 19)), allocator);
            predictObj.AddMember("status", atoi(PQgetvalue(ret, i, 20)), allocator);
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
        std::string sql = "SELECT m.id, m.league, m.season, m.week, m.match_date, m.team1_score, m.team2_score, m.week_type, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, "
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
            "AND m.status <> 'PST' ORDER BY m.league ASC, m.match_date ASC;";

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
            int elapsed = atoi(PQgetvalue(ret, i, 8));
            int team1ScoreLive = atoi(PQgetvalue(ret, i, 9));
            int team2ScoreLive = atoi(PQgetvalue(ret, i, 10));
            std::string status = (PQgetvalue(ret, i, 11));

            std::string leagueName = PQgetvalue(ret, i, 21); // Assuming league_name is the last column
            int currentWeek = atol(PQgetvalue(ret, i, 22));

            rapidjson::Value team1Obj(rapidjson::kObjectType);
            team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 12)), allocator);
            team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 13), allocator), allocator);
            team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 14), allocator), allocator);

            rapidjson::Value team2Obj(rapidjson::kObjectType);
            team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 15)), allocator);
            team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 16), allocator), allocator);
            team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 17), allocator), allocator);

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
            matchObj.AddMember("elapsed", elapsed, allocator);
            matchObj.AddMember("team1_score_live", team1ScoreLive, allocator);
            matchObj.AddMember("team2_score_live", team2ScoreLive, allocator);
            matchObj.AddMember("status", rapidjson::Value(status.c_str(), allocator), allocator);

            matchObj.AddMember("league_name", rapidjson::Value(leagueName.c_str(), allocator), allocator); // Add league name
            matchObj.AddMember("currentWeek", currentWeek, allocator);

            rapidjson::Value predictObj(rapidjson::kObjectType);
            predictObj.AddMember("team1_score", atoi(PQgetvalue(ret, i, 18)), allocator);
            predictObj.AddMember("team2_score", atoi(PQgetvalue(ret, i, 19)), allocator);
            predictObj.AddMember("status", atoi(PQgetvalue(ret, i, 20)), allocator);
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

std::function<void(const httplib::Request&, httplib::Response&)> MatchesRoute::GetUpcomingMatches()
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
        std::string sql = "SELECT m.id, m.league, m.season, m.week, m.match_date, m.team1_score, m.team2_score, m.week_type, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, "
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
            "WHERE m.match_date > " + std::to_string(currentTimeMs) + " "
            "ORDER BY m.match_date ASC "
            "LIMIT 10;";

        PGresult* ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_TUPLES_OK) {
            fprintf(stderr, "Failed to fetch upcoming matches: %s", PQerrorMessage(pg));
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
            int weekType = atoi(PQgetvalue(ret, i, 7)); // week_type included
            int elapsed = atoi(PQgetvalue(ret, i, 8));
            int team1ScoreLive = atoi(PQgetvalue(ret, i, 9));
            int team2ScoreLive = atoi(PQgetvalue(ret, i, 10));
            std::string status = (PQgetvalue(ret, i, 11));

            std::string leagueName = PQgetvalue(ret, i, 21); // Assuming league_name is the last column
            int currentWeek = atol(PQgetvalue(ret, i, 22));

            rapidjson::Value team1Obj(rapidjson::kObjectType);
            team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 12)), allocator);
            team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 13), allocator), allocator);
            team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 14), allocator), allocator);

            rapidjson::Value team2Obj(rapidjson::kObjectType);
            team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 15)), allocator);
            team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 16), allocator), allocator);
            team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 17), allocator), allocator);

            matchObj.AddMember("id", id, allocator);
            matchObj.AddMember("league", league, allocator);
            matchObj.AddMember("season", rapidjson::Value(season.c_str(), allocator), allocator);
            matchObj.AddMember("week", week, allocator);
            matchObj.AddMember("team1", team1Obj, allocator);
            matchObj.AddMember("team2", team2Obj, allocator);
            matchObj.AddMember("date", (double)date, allocator);
            matchObj.AddMember("team1_score", team1Score, allocator);
            matchObj.AddMember("team2_score", team2Score, allocator);
            matchObj.AddMember("week_type", weekType, allocator); // Add week_type
            matchObj.AddMember("elapsed", elapsed, allocator);
            matchObj.AddMember("team1_score_live", team1ScoreLive, allocator);
            matchObj.AddMember("team2_score_live", team2ScoreLive, allocator);
            matchObj.AddMember("status", rapidjson::Value(status.c_str(), allocator), allocator);

            matchObj.AddMember("league_name", rapidjson::Value(leagueName.c_str(), allocator), allocator); // Add league name
            matchObj.AddMember("currentWeek", currentWeek, allocator);

            rapidjson::Value predictObj(rapidjson::kObjectType);
            predictObj.AddMember("team1_score", atoi(PQgetvalue(ret, i, 18)), allocator);
            predictObj.AddMember("team2_score", atoi(PQgetvalue(ret, i, 19)), allocator);
            predictObj.AddMember("status", atoi(PQgetvalue(ret, i, 20)), allocator);
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


std::function<void(const httplib::Request&, httplib::Response&)> MatchesRoute::GetMatchStatistics()
{
    return [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        auto matchId = req.get_param_value("match_id");
        PGconn* pg = ConnectionPool::Get()->getConnection();

        std::string sql = "SELECT * FROM match_stats WHERE match_id = " + (matchId) + ";";
        PGresult* ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_TUPLES_OK) 
        {
            fprintf(stderr, "Failed to fetch match stats: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        for (int i = 0; i < nrows; ++i)
        {
            int id = atoi(PQgetvalue(ret, i, 0));
            std::string shotsOnTarget = PQgetvalue(ret, i, 2);
            std::string shotsOffTarget = PQgetvalue(ret, i, 3);
            std::string blocked = PQgetvalue(ret, i, 4);
            std::string fouls = PQgetvalue(ret, i, 5);
            std::string corners = PQgetvalue(ret, i, 6);
            std::string offsides = PQgetvalue(ret, i, 7);
            std::string possession = PQgetvalue(ret, i, 8);
            std::string saves = PQgetvalue(ret, i, 9);

            document.AddMember("shotsOnTarget", rapidjson::Value(shotsOnTarget.c_str(), allocator), allocator);
            document.AddMember("shotsOffTarget", rapidjson::Value(shotsOffTarget.c_str(), allocator), allocator);
            document.AddMember("blockedShots", rapidjson::Value(blocked.c_str(), allocator), allocator);
            document.AddMember("fouls", rapidjson::Value(fouls.c_str(), allocator), allocator);
            document.AddMember("corners", rapidjson::Value(corners.c_str(), allocator), allocator);
            document.AddMember("offsides", rapidjson::Value(offsides.c_str(), allocator), allocator);
            document.AddMember("possession", rapidjson::Value(possession.c_str(), allocator), allocator);
            document.AddMember("saves", rapidjson::Value(saves.c_str(), allocator), allocator);

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

std::function<void(const httplib::Request&, httplib::Response&)> MatchesRoute::GetMatchEvents()
{
    return [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        auto matchId = req.get_param_value("match_id");
        PGconn* pg = ConnectionPool::Get()->getConnection();

        std::string sql = "SELECT * FROM events WHERE match_id = " + (matchId)+" order by elapsed asc;";
        PGresult* ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch match stats: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetArray();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    
        for (int i = 0; i < nrows; ++i)
        {
            rapidjson::Value eValue;
            eValue.SetObject();

            int id = atoi(PQgetvalue(ret, i, 0));
            int elapsed = atoi(PQgetvalue(ret, i, 2));
            int extra = atoi(PQgetvalue(ret, i, 3));
            int team = atoi(PQgetvalue(ret, i, 4));
            std::string player = (PQgetvalue(ret, i, 5));
            std::string assist = (PQgetvalue(ret, i, 6));
            std::string type = (PQgetvalue(ret, i, 7));
            std::string detail = (PQgetvalue(ret, i, 8));

            eValue.AddMember("elapsed", elapsed, allocator);
            eValue.AddMember("extra", extra, allocator);
            eValue.AddMember("team", team, allocator);
            eValue.AddMember("player", rapidjson::Value(player.c_str(), allocator), allocator);
            eValue.AddMember("assist", rapidjson::Value(assist.c_str(), allocator), allocator);
            eValue.AddMember("type", rapidjson::Value(type.c_str(), allocator), allocator);
            eValue.AddMember("detail", rapidjson::Value(detail.c_str(), allocator), allocator);
            document.PushBack(eValue, allocator);
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

std::function<void(const httplib::Request&, httplib::Response&)> MatchesRoute::GetMatchLineups()
{
    return [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        // Parse match_id from the request
        auto matchId = req.get_param_value("match_id");
        PGconn* pg = ConnectionPool::Get()->getConnection();

        // Query the database for the lineups
        std::string sql = "SELECT formation1, player_color1, player_ncolor1, player_bcolor1, "
            "gk_color1, gk_ncolor1, gk_bcolor1, formation2, player_color2, player_ncolor2, "
            "player_bcolor2, gk_color2, gk_ncolor2, gk_bcolor2, coach1, coach2 "
            "FROM lineups WHERE match_id = " + matchId + ";";

        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK) {
            // Handle error
            std::cerr << "Error executing SQL: " << PQerrorMessage(pg) << std::endl;
            res.status = 500; // Internal Server Error
            ConnectionPool::Get()->releaseConnection(pg);
            PQclear(ret);
            return;
        }

        // Assuming only one row is returned for a match_id
        int rows = PQntuples(ret);
        if (rows == 0) {
            res.status = 404; // Not Found
            res.set_content("Match lineups not found", "text/plain");
            ConnectionPool::Get()->releaseConnection(pg);
            PQclear(ret);
            return;
        }

        // Construct the JSON response
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        rapidjson::Value team1(rapidjson::kObjectType);
        rapidjson::Value team2(rapidjson::kObjectType);
        // Create a rapidjson::Value from the char* returned by PQgetvalue
        rapidjson::Value formation1(PQgetvalue(ret, 0, 0), allocator);
        rapidjson::Value player_color1(PQgetvalue(ret, 0, 1), allocator);
        rapidjson::Value player_ncolor1(PQgetvalue(ret, 0, 2), allocator);
        rapidjson::Value player_bcolor1(PQgetvalue(ret, 0, 3), allocator);
        rapidjson::Value gk_color1(PQgetvalue(ret, 0, 4), allocator);
        rapidjson::Value gk_ncolor1(PQgetvalue(ret, 0, 5), allocator);
        rapidjson::Value gk_bcolor1(PQgetvalue(ret, 0, 6), allocator);

        rapidjson::Value formation2(PQgetvalue(ret, 0, 7), allocator);
        rapidjson::Value player_color2(PQgetvalue(ret, 0, 8), allocator);
        rapidjson::Value player_ncolor2(PQgetvalue(ret, 0, 9), allocator);
        rapidjson::Value player_bcolor2(PQgetvalue(ret, 0, 10), allocator);
        rapidjson::Value gk_color2(PQgetvalue(ret, 0, 11), allocator);
        rapidjson::Value gk_ncolor2(PQgetvalue(ret, 0, 12), allocator);
        rapidjson::Value gk_bcolor2(PQgetvalue(ret, 0, 13), allocator);

        rapidjson::Value coach1(PQgetvalue(ret, 0, 14), allocator);
        rapidjson::Value coach2(PQgetvalue(ret, 0, 15), allocator);

        // Add them to the JSON objects
        team1.AddMember("formation", formation1, allocator);
        team1.AddMember("player_color", player_color1, allocator);
        team1.AddMember("player_ncolor", player_ncolor1, allocator);
        team1.AddMember("player_bcolor", player_bcolor1, allocator);
        team1.AddMember("gk_color", gk_color1, allocator);
        team1.AddMember("gk_ncolor", gk_ncolor1, allocator);
        team1.AddMember("gk_bcolor", gk_bcolor1, allocator);
        team1.AddMember("coach", coach1, allocator);

        team2.AddMember("formation", formation2, allocator);
        team2.AddMember("player_color", player_color2, allocator);
        team2.AddMember("player_ncolor", player_ncolor2, allocator);
        team2.AddMember("player_bcolor", player_bcolor2, allocator);
        team2.AddMember("gk_color", gk_color2, allocator);
        team2.AddMember("gk_ncolor", gk_ncolor2, allocator);
        team2.AddMember("gk_bcolor", gk_bcolor2, allocator);
        team2.AddMember("coach", coach2, allocator);

        // Query players for both teams
        std::string sqlPlayers = "SELECT name, number, grid, start11, team, pos FROM lineups_players WHERE lineup IN "
            "(SELECT id FROM lineups WHERE match_id = " + matchId + ");";

        PGresult* retPlayers = PQexec(pg, sqlPlayers.c_str());

        if (PQresultStatus(retPlayers) != PGRES_TUPLES_OK) {
            // Handle error
            std::cerr << "Error executing SQL for players: " << PQerrorMessage(pg) << std::endl;
            res.status = 500;
            ConnectionPool::Get()->releaseConnection(pg);
            PQclear(retPlayers);
            return;
        }

        int playerRows = PQntuples(retPlayers);
        rapidjson::Value team1Players(rapidjson::kArrayType);
        rapidjson::Value team2Players(rapidjson::kArrayType);

        for (int i = 0; i < playerRows; ++i) {
            rapidjson::Value player(rapidjson::kObjectType);
            player.AddMember("name", rapidjson::Value(PQgetvalue(retPlayers, i, 0), allocator), allocator);
            player.AddMember("number", std::stoi(PQgetvalue(retPlayers, i, 1)), allocator);
            player.AddMember("grid", rapidjson::Value(PQgetvalue(retPlayers, i, 2), allocator), allocator);
            player.AddMember("start11", std::stoi(PQgetvalue(retPlayers, i, 3)), allocator);
            player.AddMember("pos", rapidjson::Value(PQgetvalue(retPlayers, i, 5), allocator), allocator);

            int team = std::stoi(PQgetvalue(retPlayers, i, 4));
            if (team == 1) {
                team1Players.PushBack(player, allocator);
            }
            else {
                team2Players.PushBack(player, allocator);
            }

        }

        // Add players to the teams
        team1.AddMember("players", team1Players, allocator);
        team2.AddMember("players", team2Players, allocator);

        // Add both teams to the document
        document.AddMember("team1", team1, allocator);
        document.AddMember("team2", team2, allocator);

        // Convert the document to a JSON string
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        // Send the JSON response
        res.set_content(buffer.GetString(), "application/json");
        res.status = 200; // OK

        // Clean up
        PQclear(ret);
        PQclear(retPlayers);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}




std::function<void(const httplib::Request&, httplib::Response&)> MatchesRoute::GetMatchHeader()
{
    return [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        auto matchId = req.get_param_value("match_id");
        PGconn* pg = ConnectionPool::Get()->getConnection();
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        {
            std::string sql = "SELECT id FROM match_stats WHERE match_id = " + (matchId)+";";
            PGresult* ret = PQexec(pg, sql.c_str());
            if (PQresultStatus(ret) != PGRES_TUPLES_OK)
            {
                fprintf(stderr, "Failed to fetch match stats: %s", PQerrorMessage(pg));
                PQclear(ret);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 500;
                return;
            }

            int nrows = PQntuples(ret);
            document.AddMember("statistics", nrows, allocator);
            PQclear(ret);
        }
        {
            std::string sql = "SELECT id FROM events WHERE match_id = " + (matchId) + ";";
            PGresult* ret = PQexec(pg, sql.c_str());
            if (PQresultStatus(ret) != PGRES_TUPLES_OK)
            {
                fprintf(stderr, "Failed to fetch match events: %s", PQerrorMessage(pg));
                PQclear(ret);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 500;
                return;
            }

            int nrows = PQntuples(ret);
            document.AddMember("events", int(nrows > 0), allocator);
            PQclear(ret);
        }
        {
            std::string sql = "SELECT id FROM lineups WHERE match_id = " + (matchId)+";";
            PGresult* ret = PQexec(pg, sql.c_str());
            if (PQresultStatus(ret) != PGRES_TUPLES_OK)
            {
                fprintf(stderr, "Failed to fetch match events: %s", PQerrorMessage(pg));
                PQclear(ret);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 500;
                return;
            }

            int nrows = PQntuples(ret);
            document.AddMember("lineups", int(nrows > 0), allocator);
            PQclear(ret);
        }

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200; // OK

        ConnectionPool::Get()->releaseConnection(pg);
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> MatchesRoute::GetMatchLive()
{
    return [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        auto matchId = req.get_param_value("match_id");
        PGconn* pg = ConnectionPool::Get()->getConnection();
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        {
            std::string sql = "SELECT id, elapsed, team1_score_live, team2_score_live, status FROM matches WHERE id = " + (matchId)+";";
            PGresult* ret = PQexec(pg, sql.c_str());
            if (PQresultStatus(ret) != PGRES_TUPLES_OK)
            {
                fprintf(stderr, "Failed to fetch match stats: %s", PQerrorMessage(pg));
                PQclear(ret);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 500;
                return;
            }

            int nrows = PQntuples(ret);

            for (int i = 0; i < nrows; ++i)
            {
                int id = atoi(PQgetvalue(ret, i, 0));
                int elapsed = atoi(PQgetvalue(ret, i, 1));
                int team1ScoreLive = atoi(PQgetvalue(ret, i, 2));
                int team2ScoreLive = atoi(PQgetvalue(ret, i, 3));
                std::string status = PQgetvalue(ret, i, 4);

                document.AddMember("id", id, allocator);
                document.AddMember("elapsed", elapsed, allocator);
                document.AddMember("team1_score_live", team1ScoreLive, allocator);
                document.AddMember("team2_score_live", team2ScoreLive, allocator);
                document.AddMember("status", rapidjson::Value(status.c_str(), allocator), allocator);
                break;
            }

            PQclear(ret);
        }
        

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200; // OK

        ConnectionPool::Get()->releaseConnection(pg);
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> MatchesRoute::GetMatch()
{
    return [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        // Extract match_id from query parameters
        std::string matchId = req.get_param_value("match_id");

        // Connect to the database
        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string sql = "SELECT m.id, m.league, m.season, m.week, m.match_date, m.team1_score, m.team2_score, m.week_type, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, "
            "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
            "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "
            "lt1.league_index AS team1_league_index, lt1.group_index AS team1_group_index, "  // Add league_index and group_index for team1
            "lt2.league_index AS team2_league_index, lt2.group_index AS team2_group_index, "  // Add league_index and group_index for team2
            "l.name AS league_name, "
            "l.current_week "
            "FROM matches m "
            "JOIN teams t1 ON m.team1 = t1.id "
            "JOIN teams t2 ON m.team2 = t2.id "
            "JOIN leagues l ON m.league = l.id "
            "JOIN leagues_teams lt1 ON lt1.team_id = t1.id AND lt1.league_id = l.id "  // Join leagues_teams for team1
            "JOIN leagues_teams lt2 ON lt2.team_id = t2.id AND lt2.league_id = l.id "  // Join leagues_teams for team2
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
            int elapsed = atol(PQgetvalue(ret, i, 8));
            int team1ScoreLive = atol(PQgetvalue(ret, i, 9));
            int team2ScoreLive = atol(PQgetvalue(ret, i, 10));
            std::string status = PQgetvalue(ret, i, 11);

            std::string leagueName = PQgetvalue(ret, i, 22);

            // Team 1 object
            rapidjson::Value team1Obj(rapidjson::kObjectType);
            team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 12)), allocator);
            team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 13), allocator), allocator);
            team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 14), allocator), allocator);
            team1Obj.AddMember("league_index", atoi(PQgetvalue(ret, i, 18)), allocator);  // Add league_index for team1
            team1Obj.AddMember("group_index", atoi(PQgetvalue(ret, i, 19)), allocator);  // Add group_index for team1

            // Team 2 object
            rapidjson::Value team2Obj(rapidjson::kObjectType);
            team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 15)), allocator);
            team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 16), allocator), allocator);
            team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 17), allocator), allocator);
            team2Obj.AddMember("league_index", atoi(PQgetvalue(ret, i, 20)), allocator);  // Add league_index for team2
            team2Obj.AddMember("group_index", atoi(PQgetvalue(ret, i, 21)), allocator);  // Add group_index for team2

            matchObj.AddMember("id", id, allocator);
            matchObj.AddMember("league", league, allocator);
            matchObj.AddMember("season", rapidjson::Value(season.c_str(), allocator), allocator);
            matchObj.AddMember("week", week, allocator);
            matchObj.AddMember("weekType", weekType, allocator);
            matchObj.AddMember("elapsed", elapsed, allocator);
            matchObj.AddMember("team1_score_live", team1ScoreLive, allocator);
            matchObj.AddMember("team2_score_live", team2ScoreLive, allocator);
            matchObj.AddMember("status", rapidjson::Value(status.c_str(), allocator), allocator);

            matchObj.AddMember("team1", team1Obj, allocator);
            matchObj.AddMember("team2", team2Obj, allocator);
            matchObj.AddMember("date", (double)date, allocator);
            matchObj.AddMember("team1_score", team1Score, allocator);
            matchObj.AddMember("team2_score", team2Score, allocator);
            matchObj.AddMember("leagueName", rapidjson::Value(leagueName.c_str(), allocator), allocator);
            matchObj.AddMember("currentWeek", atoi(PQgetvalue(ret, i, 23)), allocator); // Add current_week

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



std::function<void(const httplib::Request&, httplib::Response&)> MatchesRoute::EditMatch()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "POST");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        std::string matchId = req.get_param_value("match_id");

        rapidjson::Document document;
        document.Parse(req.body.c_str());

        int team1Score = document["team1_score"].GetInt();
        int team2Score = document["team2_score"].GetInt();
        long long date = document["date"].GetDouble();

        // Connect to the database
        PGconn* pg = ConnectionPool::Get()->getConnection();

        // Get team IDs from the match record
        std::string sql = "SELECT team1, team2, league, season FROM matches WHERE id = " + matchId + ";";
        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK || PQntuples(ret) == 0)
        {
            fprintf(stderr, "Failed to get match: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500; // Internal Server Error
            return;
        }

        int team1 = atoi(PQgetvalue(ret, 0, 0));
        int team2 = atoi(PQgetvalue(ret, 0, 1));
        int league = atoi(PQgetvalue(ret, 0, 2));
        std::string season = PQgetvalue(ret, 0, 3);

        PQclear(ret);

        // Update the match record in the database
        sql = "UPDATE matches SET team1_score = " + std::to_string(team1Score) + ", "
            + "team2_score = " + std::to_string(team2Score) + ", "
            + "match_date = " + std::to_string(date) + " "
            + "WHERE id = " + matchId + ";";
        ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "Failed to update match: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500; // Internal Server Error
            return;
        }
        PQclear(ret);

        
        // Update predictions (if necessary)
        if (team1Score >= 0 && team2Score >= 0)
        {
            // Update the league table for both teams
            auto updateLeagueTable = [&](int team, int goalsFor, int goalsAgainst, int points) {
                sql = "UPDATE tables SET "
                    "matches_played = matches_played + 1, "
                    "goals_f = goals_f + " + std::to_string(goalsFor) + ", "
                    "goals_a = goals_a + " + std::to_string(goalsAgainst) + ", "
                    "points = points + " + std::to_string(points) + " "
                    "WHERE team_id = " + std::to_string(team) + " AND league_id = " + std::to_string(league) + " AND season = '" + season + "'" + ";";
                PGresult* updateRet = PQexec(pg, sql.c_str());
                PQclear(updateRet);
            };

            // Determine points to assign
            int pointsForTeam1 = 0;
            int pointsForTeam2 = 0;

            if (team1Score > team2Score) {
                pointsForTeam1 = 3; // Team 1 wins
            }
            else if (team1Score < team2Score) {
                pointsForTeam2 = 3; // Team 2 wins
            }
            else {
                pointsForTeam1 = 1; // Draw
                pointsForTeam2 = 1; // Draw
            }

            // Update league table for both teams
            updateLeagueTable(team1, team1Score, team2Score, pointsForTeam1);
            updateLeagueTable(team2, team2Score, team1Score, pointsForTeam2);


            sql = "SELECT * FROM predicts WHERE match_id = " + matchId + ";";
            ret = PQexec(pg, sql.c_str());

            int nrows = PQntuples(ret);

            for (int i = 0; i < nrows; ++i)
            {
                int id = atoi(PQgetvalue(ret, i, 0));
                int userId = atoi(PQgetvalue(ret, i, 1));
                int t1score = atoi(PQgetvalue(ret, i, 3));
                int t2score = atoi(PQgetvalue(ret, i, 4));
                EPredictStatus predictStatus = (EPredictStatus)atoi(PQgetvalue(ret, i, 5));
                if (predictStatus != EPredictStatus::Pending) continue;

                int points = 0;
                EPredictStatus status = EPredictStatus::Pending;
                if (team1Score == t1score && team2Score == t2score)
                {
                    points = 3;
                    status = EPredictStatus::ScorePredicted;
                }
                else
                {
                    if ((team1Score > team2Score && t1score > t2score) ||
                        (team1Score < team2Score && t1score < t2score) ||
                        (team1Score == team2Score && t1score == t2score))
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

                sql = "UPDATE users SET points = GREATEST(0, points + " + std::to_string(points) + ") WHERE id = " + std::to_string(userId) + ";";
                PGresult* updateRet = PQexec(pg, sql.c_str());
                PQclear(updateRet);

                sql = "UPDATE predicts SET status = " + std::to_string(int(status)) + " WHERE id = " + std::to_string(id) + ";";
                updateRet = PQexec(pg, sql.c_str());
                PQclear(updateRet);
            }
            PQclear(ret);
        }

        ConnectionPool::Get()->releaseConnection(pg);
        res.status = 201; // Created
    };
}
