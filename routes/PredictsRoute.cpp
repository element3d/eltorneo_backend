#include "PredictsRoute.h"
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include "../managers/PQManager.h"
#include <jwt-cpp/jwt.h>


PredictsRoute* PredictsRoute::sInstance = nullptr;

PredictsRoute* PredictsRoute::Get()
{
    if (!sInstance) sInstance = new PredictsRoute();
    return sInstance;
}


std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetUserPredict()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        std::string matchId = req.get_param_value("match_id");
        std::string season = "";
        if (req.has_param("season"))
        {
            season = req.get_param_value("season");
        }
        std::string postfix = "";
        if (season.size())
        {
            std::string currentSeason = "25/26";
            if (season != currentSeason)
            {
                std::replace(season.begin(), season.end(), '/', '_');
                postfix = "_" + season;
            }
        }

        std::string token = req.get_header_value("Authentication");
        auto decoded = jwt::decode(token);
        int userId = decoded.get_payload_claim("id").as_int();

        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string sql = "SELECT * FROM predicts" + postfix + " WHERE user_id = "
            + std::to_string(userId) + " AND match_id = "
            + matchId
            + ";";
        PGresult* ret = PQexec(pg, sql.c_str());

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
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        char* temp = (char*)calloc(4096, sizeof(char));

        for (int i = 0; i < nrows; ++i)
        {
            // Handle ID as integer
            int id = atoi(PQgetvalue(ret, i, 0)); // Convert the string from the first column to an integer
            rapidjson::Value idValue;
            idValue.SetInt(id);
            document.AddMember("id", idValue, allocator);

            int userId = atoi(PQgetvalue(ret, i, 1));
            idValue.SetInt(userId);
            document.AddMember("user_id", idValue, allocator);

            int matchId = atoi(PQgetvalue(ret, i, 2));
            idValue.SetInt(matchId);
            document.AddMember("match_id", idValue, allocator);

            int score1 = atoi(PQgetvalue(ret, i, 3));
            idValue.SetInt(score1);
            document.AddMember("team1_score", idValue, allocator);

            int score2 = atoi(PQgetvalue(ret, i, 4));
            idValue.SetInt(score2);
            document.AddMember("team2_score", idValue, allocator);

            int status = atoi(PQgetvalue(ret, i, 5));
            idValue.SetInt(status);
            document.AddMember("status", idValue, allocator);
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

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetUserBet()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        std::string matchId = req.get_param_value("match_id");
        /*std::string season = "";
        if (req.has_param("season"))
        {
            season = req.get_param_value("season");
        }*/
        std::string postfix = "";
        /*if (season.size())
        {
            std::string currentSeason = "25/26";
            if (season != currentSeason)
            {
                std::replace(season.begin(), season.end(), '/', '_');
                postfix = "_" + season;
            }
        }*/

        std::string token = req.get_header_value("Authentication");
        auto decoded = jwt::decode(token);
        int userId = decoded.get_payload_claim("id").as_int();

        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string sql = "select id, bet, amount, odd, status FROM bets" + postfix + " WHERE user_id = "
            + std::to_string(userId) + " AND match_id = "
            + matchId
            + ";";
        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch user bet: %s", PQerrorMessage(pg));
            PQclear(ret);
            res.status = 500;  // Internal Server Error
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        char* temp = (char*)calloc(4096, sizeof(char));

        for (int i = 0; i < nrows; ++i)
        {
            // Handle ID as integer
            int id = atoi(PQgetvalue(ret, i, 0)); // Convert the string from the first column to an integer
            rapidjson::Value idValue;
            idValue.SetInt(id);
            document.AddMember("id", idValue, allocator);
            document.AddMember("bet", rapidjson::Value(PQgetvalue(ret, 0, 1), allocator), allocator);
            document.AddMember("amount", atoi(PQgetvalue(ret, 0, 2)), allocator);
            document.AddMember("odd", atof(PQgetvalue(ret, 0, 3)), allocator);
            document.AddMember("status", atoi(PQgetvalue(ret, 0, 4)), allocator);
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


int getTeamId(PGconn* conn, int matchId, int teamNumber)
{
    const char* teamField = (teamNumber == 1) ? "team1" : "team2";

    char query[256];
    snprintf(query, sizeof(query), "SELECT %s FROM matches WHERE id = %d;", teamField, matchId);

    PGresult* res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        PQclear(res);
        return -1; // Indicate error
    }

    int teamId = atoi(PQgetvalue(res, 0, 0));
    PQclear(res);
    return teamId;
}

int getTeamScore(PGconn* conn, int matchId, int teamNumber)
{
    const char* teamField = (teamNumber == 1) ? "team1_score" : "team2_score";

    char query[256];
    snprintf(query, sizeof(query), "SELECT %s FROM matches WHERE id = %d;", teamField, matchId);

    PGresult* res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        PQclear(res);
        return -1; // Indicate error
    }

    int teamId = atoi(PQgetvalue(res, 0, 0));
    PQclear(res);
    return teamId;
}

long long getMatchDate(PGconn* conn, int matchId)
{
    char query[256];
    std::string sql = "select match_date from matches where id = " + std::to_string(matchId) + ";";
    PGresult* res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        PQclear(res);
        return -1; // Indicate error
    }

    long long teamId = atoll(PQgetvalue(res, 0, 0));
    PQclear(res);
    return teamId;
}


std::string getTeamName(PGconn* conn, int teamId)
{
    static char teamName[256]; // Static to return safely
    char query[256];
    snprintf(query, sizeof(query), "SELECT name FROM teams WHERE id = %d;", teamId);

    PGresult* res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        PQclear(res);
        strcpy(teamName, "Unknown"); // Indicate error
        return teamName;
    }

    strncpy(teamName, PQgetvalue(res, 0, 0), sizeof(teamName) - 1);
    teamName[sizeof(teamName) - 1] = '\0'; // Ensure null-termination
    PQclear(res);
    return teamName;
}

std::string getTeamShortName(PGconn* conn, int teamId)
{
    static char teamName[256]; // Static to return safely
    char query[256];
    snprintf(query, sizeof(query), "SELECT short_name FROM teams WHERE id = %d;", teamId);

    PGresult* res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        PQclear(res);
        strcpy(teamName, "Unknown"); // Indicate error
        return teamName;
    }

    strncpy(teamName, PQgetvalue(res, 0, 0), sizeof(teamName) - 1);
    teamName[sizeof(teamName) - 1] = '\0'; // Ensure null-termination
    PQclear(res);
    return teamName;
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetBeatBet()
{
    return [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        std::string strPlayer = req.get_param_value("player");
        std::string strTeam = req.get_param_value("team");
        std::string strLeague = req.get_param_value("league");
        bool isHome = false;
        bool isAway = false;
        if (req.has_param("home")) 
        {
            isHome = atoi(req.get_param_value("home").c_str());
        }
        if (req.has_param("away"))
        {
            isAway = atoi(req.get_param_value("away").c_str());
        }
        

        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        rapidjson::Value predictsArray(rapidjson::kArrayType);
        PGconn* pg = ConnectionPool::Get()->getConnection();
        PGresult* ret;
        PGresult* ret2;
        int league = atoi(strLeague.c_str());
        std::string leagueCmd = league > 0 ? " AND m.league = " + std::to_string(league) + " " : "";

        int team = atoi(strTeam.c_str());;
        std::string teamCmd;
        if (team > 0) 
        {
            if (isHome)
            {
                teamCmd = " AND m.team1 = " + std::to_string(team) + " ";
            }
            else if (isAway) 
            {
                teamCmd = " AND m.team2 = " + std::to_string(team) + " ";
            }
            else 
            {
                teamCmd = " AND (m.team1 = " + std::to_string(team) + " OR m.team2 = " + std::to_string(team) + ") ";
            }
        }

        int player = atoi(strPlayer.c_str());
        std::string playerCmd = player > 0 ? " AND p.user_id = " + std::to_string(player) + " " : "";
        // get live matches
        int numLiveMatches = 0;
        {
            // Get the current timestamp in milliseconds
            auto now = std::chrono::system_clock::now();
            auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
            auto epoch = now_ms.time_since_epoch();
            auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
            long long currentTimeMs = value.count();

            std::string sqlBase = "SELECT p.*, m.id, l.id as league_id, l.name as league_name, m.season, m.week, m.match_date, "
                "m.team1_score, m.team2_score, m.week_type, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.preview, t1.id as team1_id, t1.name as team1_name, t1.short_name as team1_short_name, "
                "t2.id as team2_id, t2.name as team2_name, t2.short_name as team2_short_name, "
                "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches table
                "COALESCE(s.points, '') AS special_match_points " // Fetch title from special_matches table
                "FROM predicts p "
                "INNER JOIN matches m ON p.match_id = m.id "
                "LEFT JOIN leagues l ON m.league = l.id "
                "LEFT JOIN teams t1 ON m.team1 = t1.id "
                "LEFT JOIN teams t2 ON m.team2 = t2.id "
                "LEFT JOIN special_matches s ON s.match_id = m.id " // Join special_matches
                "WHERE m.match_date < " + std::to_string(currentTimeMs) + " AND m.team1_score = -1 and m.team2_score =  -1 and m.team1_score_live <> -1 and m.team2_score_live <> -1 and m.status <> 'PST' and p.status <> 4 "
                + leagueCmd 
                + teamCmd 
                + playerCmd +
                "ORDER BY p.id ASC "
                "LIMIT " + std::to_string(5) + ";";

            ret = PQexec(pg, sqlBase.c_str());

            if (PQresultStatus(ret) != PGRES_TUPLES_OK)
            {
                fprintf(stderr, "Failed to fetch data: %s", PQerrorMessage(pg));
                PQclear(ret);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 500;
                return;
            }

            int nrows = PQntuples(ret);
            numLiveMatches = nrows;

            // Iterate through result rows to build each prediction's JSON
            for (int i = nrows - 1; i >= 0; --i) {
                rapidjson::Value object(rapidjson::kObjectType);
                rapidjson::Value leagueObject(rapidjson::kObjectType);
                leagueObject.AddMember("id", atoi(PQgetvalue(ret, i, 7)), allocator);
                leagueObject.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 8)), allocator);
                object.AddMember("league", leagueObject, allocator);

                object.AddMember("id", atoi(PQgetvalue(ret, i, 6)), allocator);
                object.AddMember("season", rapidjson::StringRef(PQgetvalue(ret, i, 9)), allocator);
                object.AddMember("week", atoi(PQgetvalue(ret, i, 10)), allocator);
                object.AddMember("date", (double)atoll(PQgetvalue(ret, i, 11)), allocator);
                object.AddMember("team1_score", atoi(PQgetvalue(ret, i, 12)), allocator);
                object.AddMember("team2_score", atoi(PQgetvalue(ret, i, 13)), allocator);
                object.AddMember("week_type", atoi(PQgetvalue(ret, i, 14)), allocator);
                object.AddMember("elapsed", atoi(PQgetvalue(ret, i, 15)), allocator);
                object.AddMember("team1_score_live", atoi(PQgetvalue(ret, i, 16)), allocator);
                object.AddMember("team2_score_live", atoi(PQgetvalue(ret, i, 17)), allocator);
                object.AddMember("status", rapidjson::StringRef(PQgetvalue(ret, i, 18)), allocator);
                object.AddMember("is_special", atoi(PQgetvalue(ret, i, 19)), allocator);
                object.AddMember("preview", rapidjson::StringRef(PQgetvalue(ret, i, 20)), allocator);

                object.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 27), allocator), allocator);
                object.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 28), allocator), allocator);

                rapidjson::Value team1Object(rapidjson::kObjectType);
                team1Object.AddMember("id", atoi(PQgetvalue(ret, i, 21)), allocator);
                team1Object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 22)), allocator);
                team1Object.AddMember("shortName", rapidjson::StringRef(PQgetvalue(ret, i, 23)), allocator);
                object.AddMember("team1", team1Object, allocator);

                rapidjson::Value team2Object(rapidjson::kObjectType);
                team2Object.AddMember("id", atoi(PQgetvalue(ret, i, 24)), allocator);
                team2Object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 25)), allocator);
                team2Object.AddMember("shortName", rapidjson::StringRef(PQgetvalue(ret, i, 26)), allocator);
                object.AddMember("team2", team2Object, allocator);

                rapidjson::Value predict(rapidjson::kObjectType);
                predict.AddMember("id", atoi(PQgetvalue(ret, i, 0)), allocator);
                predict.AddMember("team1_score", atoi(PQgetvalue(ret, i, 3)), allocator);
                predict.AddMember("team2_score", atoi(PQgetvalue(ret, i, 4)), allocator);
                predict.AddMember("status", atoi(PQgetvalue(ret, i, 5)), allocator);
                object.AddMember("predict", predict, allocator);

                predictsArray.PushBack(object, allocator);
            }

           // PQclear(ret);
        }
        if (numLiveMatches <= 0)
        {
            // Get the current timestamp in milliseconds
            auto now = std::chrono::system_clock::now();
            auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
            auto epoch = now_ms.time_since_epoch();
            auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
            long long currentTimeMs = value.count();

            std::string sqlBase = "SELECT p.*, m.id, l.id as league_id, l.name as league_name, m.season, m.week, m.match_date, "
                "m.team1_score, m.team2_score, m.week_type, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.preview, t1.id as team1_id, t1.name as team1_name, t1.short_name as team1_short_name, "
                "t2.id as team2_id, t2.name as team2_name, t2.short_name as team2_short_name, "
                "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches table
                "COALESCE(s.points, '') AS special_match_points " // Fetch title from special_matches table
                "FROM predicts p "
                "INNER JOIN matches m ON p.match_id = m.id "
                "LEFT JOIN leagues l ON m.league = l.id "
                "LEFT JOIN teams t1 ON m.team1 = t1.id "
                "LEFT JOIN teams t2 ON m.team2 = t2.id "
                "LEFT JOIN special_matches s ON s.match_id = m.id " // Join special_matches
                "WHERE m.match_date > " + std::to_string(currentTimeMs) + " AND m.team1_score = -1 and m.team2_score =  -1 and m.status <> 'PST' and p.status <> 4 "
                + leagueCmd
                + teamCmd
                + playerCmd +
                "ORDER BY p.id ASC "
                "LIMIT " + std::to_string(5) + ";";

            ret = PQexec(pg, sqlBase.c_str());

            if (PQresultStatus(ret) != PGRES_TUPLES_OK)
            {
                fprintf(stderr, "Failed to fetch data: %s", PQerrorMessage(pg));
                PQclear(ret);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 500;
                return;
            }

            int nrows = PQntuples(ret);


            // Iterate through result rows to build each prediction's JSON
            for (int i = nrows - 1; i >= 0; --i) {
                rapidjson::Value object(rapidjson::kObjectType);
                rapidjson::Value leagueObject(rapidjson::kObjectType);
                leagueObject.AddMember("id", atoi(PQgetvalue(ret, i, 7)), allocator);
                leagueObject.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 8)), allocator);
                object.AddMember("league", leagueObject, allocator);

                object.AddMember("id", atoi(PQgetvalue(ret, i, 6)), allocator);
                object.AddMember("season", rapidjson::StringRef(PQgetvalue(ret, i, 9)), allocator);
                object.AddMember("week", atoi(PQgetvalue(ret, i, 10)), allocator);
                object.AddMember("date", (double)atoll(PQgetvalue(ret, i, 11)), allocator);
                object.AddMember("team1_score", atoi(PQgetvalue(ret, i, 12)), allocator);
                object.AddMember("team2_score", atoi(PQgetvalue(ret, i, 13)), allocator);
                object.AddMember("week_type", atoi(PQgetvalue(ret, i, 14)), allocator);
                object.AddMember("elapsed", atoi(PQgetvalue(ret, i, 15)), allocator);
                object.AddMember("team1_score_live", atoi(PQgetvalue(ret, i, 16)), allocator);
                object.AddMember("team2_score_live", atoi(PQgetvalue(ret, i, 17)), allocator);
                object.AddMember("status", rapidjson::StringRef(PQgetvalue(ret, i, 18)), allocator);
                object.AddMember("is_special", atoi(PQgetvalue(ret, i, 19)), allocator);
                object.AddMember("preview", rapidjson::StringRef(PQgetvalue(ret, i, 20)), allocator);

                object.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 27), allocator), allocator);
                object.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 28), allocator), allocator);

                rapidjson::Value team1Object(rapidjson::kObjectType);
                team1Object.AddMember("id", atoi(PQgetvalue(ret, i, 21)), allocator);
                team1Object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 22)), allocator);
                team1Object.AddMember("shortName", rapidjson::StringRef(PQgetvalue(ret, i, 23)), allocator);
                object.AddMember("team1", team1Object, allocator);

                rapidjson::Value team2Object(rapidjson::kObjectType);
                team2Object.AddMember("id", atoi(PQgetvalue(ret, i, 24)), allocator);
                team2Object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 25)), allocator);
                team2Object.AddMember("shortName", rapidjson::StringRef(PQgetvalue(ret, i, 26)), allocator);
                object.AddMember("team2", team2Object, allocator);

                rapidjson::Value predict(rapidjson::kObjectType);
                predict.AddMember("id", atoi(PQgetvalue(ret, i, 0)), allocator);
                predict.AddMember("team1_score", atoi(PQgetvalue(ret, i, 3)), allocator);
                predict.AddMember("team2_score", atoi(PQgetvalue(ret, i, 4)), allocator);
                predict.AddMember("status", atoi(PQgetvalue(ret, i, 5)), allocator);
                object.AddMember("predict", predict, allocator);

                predictsArray.PushBack(object, allocator);
            }

            // PQclear(ret);
        }

        // Get finished matches
        {
            std::string sqlBase = "SELECT p.*, m.id, l.id as league_id, l.name as league_name, m.season, m.week, m.match_date, "
                "m.team1_score, m.team2_score, m.week_type, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.preview, t1.id as team1_id, t1.name as team1_name, t1.short_name as team1_short_name, "
                "t2.id as team2_id, t2.name as team2_name, t2.short_name as team2_short_name, "
                "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches table
                "COALESCE(s.points, '') AS special_match_points " // Fetch title from special_matches table
                "FROM predicts p "
                "INNER JOIN matches m ON p.match_id = m.id "
                "LEFT JOIN leagues l ON m.league = l.id "
                "LEFT JOIN teams t1 ON m.team1 = t1.id "
                "LEFT JOIN teams t2 ON m.team2 = t2.id "
                "LEFT JOIN special_matches s ON s.match_id = m.id " // Join special_matches
                "WHERE m.team1_score <> -1 and m.team2_score <> -1 and m.team1_score_live <> -1 and m.team2_score_live <> -1 and m.status <> 'PST' and p.status <> 4 "
                + leagueCmd 
                + teamCmd
                + playerCmd +
                "ORDER BY p.id DESC "
                "LIMIT " + std::to_string(20) + ";";

            PGresult* ret = PQexec(pg, sqlBase.c_str());
            ret2 = ret;
            if (PQresultStatus(ret) != PGRES_TUPLES_OK)
            {
                fprintf(stderr, "Failed to fetch data: %s", PQerrorMessage(pg));
                PQclear(ret);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 500;
                return;
            }

            int nrows = PQntuples(ret);


            // Iterate through result rows to build each prediction's JSON
            for (int i = 0; i < nrows; ++i) {
                rapidjson::Value object(rapidjson::kObjectType);
                rapidjson::Value leagueObject(rapidjson::kObjectType);
                leagueObject.AddMember("id", atoi(PQgetvalue(ret, i, 7)), allocator);
                leagueObject.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 8)), allocator);
                object.AddMember("league", leagueObject, allocator);

                object.AddMember("id", atoi(PQgetvalue(ret, i, 6)), allocator);
                object.AddMember("season", rapidjson::StringRef(PQgetvalue(ret, i, 9)), allocator);
                object.AddMember("week", atoi(PQgetvalue(ret, i, 10)), allocator);
                object.AddMember("date", (double)atoll(PQgetvalue(ret, i, 11)), allocator);
                object.AddMember("team1_score", atoi(PQgetvalue(ret, i, 12)), allocator);
                object.AddMember("team2_score", atoi(PQgetvalue(ret, i, 13)), allocator);
                object.AddMember("week_type", atoi(PQgetvalue(ret, i, 14)), allocator);
                object.AddMember("elapsed", atoi(PQgetvalue(ret, i, 15)), allocator);
                object.AddMember("team1_score_live", atoi(PQgetvalue(ret, i, 16)), allocator);
                object.AddMember("team2_score_live", atoi(PQgetvalue(ret, i, 17)), allocator);
                object.AddMember("status", rapidjson::StringRef(PQgetvalue(ret, i, 18)), allocator);
                object.AddMember("is_special", atoi(PQgetvalue(ret, i, 19)), allocator);
                object.AddMember("preview", rapidjson::StringRef(PQgetvalue(ret, i, 20)), allocator);

                object.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 27), allocator), allocator);
                object.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 28), allocator), allocator);

                rapidjson::Value team1Object(rapidjson::kObjectType);
                team1Object.AddMember("id", atoi(PQgetvalue(ret, i, 21)), allocator);
                team1Object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 22)), allocator);
                team1Object.AddMember("shortName", rapidjson::StringRef(PQgetvalue(ret, i, 23)), allocator);
                object.AddMember("team1", team1Object, allocator);

                rapidjson::Value team2Object(rapidjson::kObjectType);
                team2Object.AddMember("id", atoi(PQgetvalue(ret, i, 24)), allocator);
                team2Object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 25)), allocator);
                team2Object.AddMember("shortName", rapidjson::StringRef(PQgetvalue(ret, i, 26)), allocator);
                object.AddMember("team2", team2Object, allocator);

                rapidjson::Value predict(rapidjson::kObjectType);
                predict.AddMember("id", atoi(PQgetvalue(ret, i, 0)), allocator);
                predict.AddMember("team1_score", atoi(PQgetvalue(ret, i, 3)), allocator);
                predict.AddMember("team2_score", atoi(PQgetvalue(ret, i, 4)), allocator);
                predict.AddMember("status", atoi(PQgetvalue(ret, i, 5)), allocator);
                object.AddMember("predict", predict, allocator);

                predictsArray.PushBack(object, allocator);
            }

        }

        document.AddMember("predicts", predictsArray, allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;
        PQclear(ret);
        PQclear(ret2);

        ConnectionPool::Get()->releaseConnection(pg);
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetUserPredicts()
{
    return [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        std::string userId = req.get_param_value("user_id");
        std::string leagueId = req.get_param_value("league_id");
        int page = std::stoi(req.get_param_value("page")) - 1;
        int limit = 20;
        int offset = page * limit;

        PGconn* pg = ConnectionPool::Get()->getConnection();
        if (!pg) 
        {
            res.status = 500;  // Internal Server Error
            return;
        }

        // SQL base string
        std::string sqlBase = "SELECT p.*, m.id, l.id as league_id, l.name as league_name, l.country as league_country, m.season, m.week, m.match_date, "
            "m.team1_score, m.team2_score, m.week_type, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.preview, m.teaser, m.play_off, " 
            "m.team1_score_90, m.team2_score_90, m.team1_score_pen, m.team2_score_pen,"
            "t1.id as team1_id, t1.name as team1_name, t1.short_name as team1_short_name, "
            "t2.id as team2_id, t2.name as team2_name, t2.short_name as team2_short_name, "
            "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches table
            "COALESCE(s.points, '') AS special_match_points " // Fetch title from special_matches table
            "FROM predicts p "
            "INNER JOIN matches m ON p.match_id = m.id "
            "LEFT JOIN leagues l ON m.league = l.id "
            "LEFT JOIN teams t1 ON m.team1 = t1.id "
            "LEFT JOIN teams t2 ON m.team2 = t2.id "
            "LEFT JOIN special_matches s ON s.match_id = m.id " // Join special_matches
            "WHERE p.user_id = " + userId +
            (leagueId != "-1" ? " AND m.league = " + leagueId : "") +
            " ORDER BY m.match_date DESC, m.id DESC "
            "LIMIT " + std::to_string(20) + " OFFSET " + std::to_string(offset) + ";";

        PGresult* ret = PQexec(pg, sqlBase.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK) 
        {
            fprintf(stderr, "Failed to fetch data: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        rapidjson::Value predictsArray(rapidjson::kArrayType);

        // Iterate through result rows to build each prediction's JSON
        for (int i = 0; i < nrows; ++i) {
            rapidjson::Value object(rapidjson::kObjectType);
            rapidjson::Value leagueObject(rapidjson::kObjectType);
            leagueObject.AddMember("id", atoi(PQgetvalue(ret, i, 7)), allocator);
            leagueObject.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 8)), allocator);
            leagueObject.AddMember("country", rapidjson::StringRef(PQgetvalue(ret, i, 9)), allocator);
            object.AddMember("league", leagueObject, allocator);

            object.AddMember("id", atoi(PQgetvalue(ret, i, 6)), allocator);
            object.AddMember("season", rapidjson::StringRef(PQgetvalue(ret, i, 10)), allocator);
            object.AddMember("week", atoi(PQgetvalue(ret, i, 11)), allocator);
            object.AddMember("date", (double)atoll(PQgetvalue(ret, i, 12)), allocator);
            object.AddMember("team1_score", atoi(PQgetvalue(ret, i, 13)), allocator);
            object.AddMember("team2_score", atoi(PQgetvalue(ret, i, 14)), allocator);
            object.AddMember("week_type", atoi(PQgetvalue(ret, i, 15)), allocator);
            object.AddMember("elapsed", atoi(PQgetvalue(ret, i, 16)), allocator);
            object.AddMember("team1_score_live", atoi(PQgetvalue(ret, i, 17)), allocator);
            object.AddMember("team2_score_live", atoi(PQgetvalue(ret, i, 18)), allocator);
            object.AddMember("status", rapidjson::StringRef(PQgetvalue(ret, i, 19)), allocator);
            object.AddMember("is_special", atoi(PQgetvalue(ret, i, 20)), allocator);
            object.AddMember("preview", rapidjson::StringRef(PQgetvalue(ret, i, 21)), allocator);
            object.AddMember("teaser", rapidjson::StringRef(PQgetvalue(ret, i, 22)), allocator);
            object.AddMember("playOff", atoi(PQgetvalue(ret, i, 23)), allocator);

            object.AddMember("team1_score_90", atoi(PQgetvalue(ret, i, 24)), allocator);
            object.AddMember("team2_score_90", atoi(PQgetvalue(ret, i, 25)), allocator);
            object.AddMember("team1_score_pen", atoi(PQgetvalue(ret, i, 26)), allocator);
            object.AddMember("team2_score_pen", atoi(PQgetvalue(ret, i, 27)), allocator);

            object.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 34), allocator), allocator);
            object.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 35), allocator), allocator);

            rapidjson::Value team1Object(rapidjson::kObjectType);
            team1Object.AddMember("id", atoi(PQgetvalue(ret, i, 28)), allocator);
            team1Object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 29)), allocator);
            team1Object.AddMember("shortName", rapidjson::StringRef(PQgetvalue(ret, i, 30)), allocator);
            object.AddMember("team1", team1Object, allocator);

            rapidjson::Value team2Object(rapidjson::kObjectType);
            team2Object.AddMember("id", atoi(PQgetvalue(ret, i, 31)), allocator);
            team2Object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 32)), allocator);
            team2Object.AddMember("shortName", rapidjson::StringRef(PQgetvalue(ret, i, 33)), allocator);
            object.AddMember("team2", team2Object, allocator);

            rapidjson::Value predict(rapidjson::kObjectType);
            predict.AddMember("id", atoi(PQgetvalue(ret, i, 0)), allocator);
            predict.AddMember("team1_score", atoi(PQgetvalue(ret, i, 3)), allocator);
            predict.AddMember("team2_score", atoi(PQgetvalue(ret, i, 4)), allocator);
            predict.AddMember("status", atoi(PQgetvalue(ret, i, 5)), allocator);
            object.AddMember("predict", predict, allocator);

            predictsArray.PushBack(object, allocator);
        }

        // Reintroducing the count queries
        auto generateCountQuery = [&](const std::string& condition) 
        {
            std::string countSql = "SELECT COUNT(*) FROM predicts p INNER JOIN matches m ON p.match_id = m.id WHERE p.user_id = " + userId;
            if (leagueId != "-1") 
            {
                countSql += " AND m.league = " + leagueId;
            }
            countSql += condition.size() ? " AND " + condition + ";" : ";";
            PGresult* countRet = PQexec(pg, countSql.c_str());

            if (PQresultStatus(countRet) != PGRES_TUPLES_OK) 
            {
                fprintf(stderr, "Failed to fetch count: %s", PQerrorMessage(pg));
                PQclear(countRet);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 500;
                return -1;  // Error code for failure
            }
            int total = atoi(PQgetvalue(countRet, 0, 0));
            PQclear(countRet);
            return total;
        };

        int totalPredicts = generateCountQuery("p.status <> 0");
        if (totalPredicts == -1) return;  // Check for errors and exit if found

        int totalScorePredicts = generateCountQuery("p.status = 2");
        if (totalScorePredicts == -1) return;  // Check for errors and exit if found

        int totalWinnerPredicts = generateCountQuery("(p.status = 2 OR p.status = 1 OR p.status = 5)");
        if (totalWinnerPredicts == -1) return;  // Check for errors and exit if found

        int totalFailPredicts = generateCountQuery("p.status = 3");
        if (totalFailPredicts == -1) return;  // Check for errors and exit if found

        int allPredicts = generateCountQuery("");
        if (allPredicts == -1) return;  // Check for errors and exit if found

        document.AddMember("totalPredicts", totalPredicts, allocator);
        document.AddMember("totalScorePredicts", totalScorePredicts, allocator);
        document.AddMember("totalWinnerPredicts", totalWinnerPredicts, allocator);
        document.AddMember("totalFailPredicts", totalFailPredicts, allocator);
        document.AddMember("allPredicts", allPredicts, allocator);

        document.AddMember("predicts", predictsArray, allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetBeatBetOfficialBets() {
    return [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        std::string userId = "25524"; // Beat Bet user id
        int page = std::stoi(req.get_param_value("page")) - 1;
        int limit = 20;
        int offset = page * limit;

        PGconn* pg = ConnectionPool::Get()->getConnection();
        if (!pg) {
            res.status = 500;  // Internal Server Error
            return;
        }

        // SQL query to fetch bets and match details
        std::string sql =
            "SELECT b.id, b.bet, b.amount, b.odd, b.status, "
            "m.id AS match_id, l.id AS league_id, l.name AS league_name, l.country AS league_country, "
            "m.season, m.week, m.match_date, m.team1_score, m.team2_score, m.week_type, m.elapsed, "
            "m.team1_score_live, m.team2_score_live, m.status AS match_status, m.is_special, m.preview, "
            "m.teaser, m.play_off, t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
            "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "
            "COALESCE(s.title, '') AS special_match_title, COALESCE(s.points, '') AS special_match_points "
            "FROM bets b "
            "INNER JOIN matches m ON b.match_id = m.id "
            "LEFT JOIN leagues l ON m.league = l.id "
            "LEFT JOIN teams t1 ON m.team1 = t1.id "
            "LEFT JOIN teams t2 ON m.team2 = t2.id "
            "LEFT JOIN special_matches s ON s.match_id = m.id "
            "WHERE b.user_id = " + userId +
            " ORDER BY m.match_date DESC, m.id DESC "
            "LIMIT " + std::to_string(limit) + " OFFSET " + std::to_string(offset) + ";";

        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK) {
            fprintf(stderr, "Failed to fetch bets: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        rapidjson::Value betsArray(rapidjson::kArrayType);

        for (int i = 0; i < nrows; ++i) {
            rapidjson::Value object(rapidjson::kObjectType);

            rapidjson::Value leagueObject(rapidjson::kObjectType);
            leagueObject.AddMember("id", atoi(PQgetvalue(ret, i, 6)), allocator);
            leagueObject.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 7)), allocator);
            leagueObject.AddMember("country", rapidjson::StringRef(PQgetvalue(ret, i, 8)), allocator);
            object.AddMember("league", leagueObject, allocator);

            object.AddMember("id", atoi(PQgetvalue(ret, i, 5)), allocator);
            object.AddMember("season", rapidjson::StringRef(PQgetvalue(ret, i, 9)), allocator);
            object.AddMember("week", atoi(PQgetvalue(ret, i, 10)), allocator);
            object.AddMember("date", (double)atoll(PQgetvalue(ret, i, 11)), allocator);
            object.AddMember("team1_score", atoi(PQgetvalue(ret, i, 12)), allocator);
            object.AddMember("team2_score", atoi(PQgetvalue(ret, i, 13)), allocator);
            object.AddMember("week_type", atoi(PQgetvalue(ret, i, 14)), allocator);
            object.AddMember("elapsed", atoi(PQgetvalue(ret, i, 15)), allocator);
            object.AddMember("team1_score_live", atoi(PQgetvalue(ret, i, 16)), allocator);
            object.AddMember("team2_score_live", atoi(PQgetvalue(ret, i, 17)), allocator);
            object.AddMember("status", rapidjson::StringRef(PQgetvalue(ret, i, 18)), allocator);
            object.AddMember("is_special", atoi(PQgetvalue(ret, i, 19)), allocator);
            object.AddMember("preview", rapidjson::StringRef(PQgetvalue(ret, i, 20)), allocator);
            object.AddMember("teaser", rapidjson::StringRef(PQgetvalue(ret, i, 21)), allocator);
            object.AddMember("playOff", atoi(PQgetvalue(ret, i, 22)), allocator);

            object.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 29), allocator), allocator);
            object.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 30), allocator), allocator);

            rapidjson::Value team1Object(rapidjson::kObjectType);
            team1Object.AddMember("id", atoi(PQgetvalue(ret, i, 23)), allocator);
            team1Object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 24)), allocator);
            team1Object.AddMember("shortName", rapidjson::StringRef(PQgetvalue(ret, i, 25)), allocator);
            object.AddMember("team1", team1Object, allocator);

            rapidjson::Value team2Object(rapidjson::kObjectType);
            team2Object.AddMember("id", atoi(PQgetvalue(ret, i, 26)), allocator);
            team2Object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 27)), allocator);
            team2Object.AddMember("shortName", rapidjson::StringRef(PQgetvalue(ret, i, 28)), allocator);
            object.AddMember("team2", team2Object, allocator);

            rapidjson::Value betObject(rapidjson::kObjectType);
            betObject.AddMember("id", atoi(PQgetvalue(ret, i, 0)), allocator);
            betObject.AddMember("bet", rapidjson::StringRef(PQgetvalue(ret, i, 1)), allocator);
            betObject.AddMember("amount", atoi(PQgetvalue(ret, i, 2)), allocator);
            betObject.AddMember("odd", atof(PQgetvalue(ret, i, 3)), allocator);
            betObject.AddMember("status", atoi(PQgetvalue(ret, i, 4)), allocator);
            object.AddMember("bet", betObject, allocator);

            betsArray.PushBack(object, allocator);
        }

        document.AddMember("bets", betsArray, allocator);

        auto generateBetCountQuery = [&](const std::string& condition)
        {
            std::string countSql = "SELECT COUNT(*) FROM bets b INNER JOIN matches m ON b.match_id = m.id WHERE b.user_id = " + userId;
            countSql += condition.size() ? " AND " + condition : "";
            return countSql;
        };

        std::string countAllBetsSql = generateBetCountQuery("");  // Count all bets
        std::string countWinBetsSql = generateBetCountQuery("b.status = 1"); // Count win bets
        std::string countLooseBetsSql = generateBetCountQuery("b.status = 2"); // Count lose bets
        std::string countTotalBetsSql = generateBetCountQuery("b.status IN (1, 2)"); // Total bets that are NOT pending

        PGresult* retAllBets = PQexec(pg, countAllBetsSql.c_str());
        PGresult* retWinBets = PQexec(pg, countWinBetsSql.c_str());
        PGresult* retLooseBets = PQexec(pg, countLooseBetsSql.c_str());
        PGresult* retTotalBets = PQexec(pg, countTotalBetsSql.c_str());

        int allBets = (PQntuples(retAllBets) > 0) ? atoi(PQgetvalue(retAllBets, 0, 0)) : 0;
        int totalWinBets = (PQntuples(retWinBets) > 0) ? atoi(PQgetvalue(retWinBets, 0, 0)) : 0;
        int totalLooseBets = (PQntuples(retLooseBets) > 0) ? atoi(PQgetvalue(retLooseBets, 0, 0)) : 0;
        int totalBets = (PQntuples(retTotalBets) > 0) ? atoi(PQgetvalue(retTotalBets, 0, 0)) : 0;

        PQclear(retAllBets);
        PQclear(retWinBets);
        PQclear(retLooseBets);
        PQclear(retTotalBets);

        document.AddMember("allBets", allBets, allocator);
        document.AddMember("totalBets", totalBets, allocator);
        document.AddMember("totalWinBets", totalWinBets, allocator);
        document.AddMember("totalLooseBets", totalLooseBets, allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetUserBets() {
    return [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        std::string userId = req.get_param_value("user_id");
        std::string leagueId = req.get_param_value("league_id");
        int page = std::stoi(req.get_param_value("page")) - 1;
        int limit = 20;
        int offset = page * limit;

        PGconn* pg = ConnectionPool::Get()->getConnection();
        if (!pg) {
            res.status = 500;  // Internal Server Error
            return;
        }

        // SQL query to fetch bets and match details
        std::string sql =
            "SELECT b.id, b.bet, b.amount, b.odd, b.status, "
            "m.id AS match_id, l.id AS league_id, l.name AS league_name, l.country AS league_country, "
            "m.season, m.week, m.match_date, m.team1_score, m.team2_score, m.week_type, m.elapsed, "
            "m.team1_score_live, m.team2_score_live, m.status AS match_status, m.is_special, m.preview, "
            "m.teaser, m.play_off, "
            "m.team1_score_90, m.team2_score_90, m.team1_score_pen, m.team2_score_pen,"
            "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
            "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "
            "COALESCE(s.title, '') AS special_match_title, COALESCE(s.points, '') AS special_match_points "
            "FROM bets b "
            "INNER JOIN matches m ON b.match_id = m.id "
            "LEFT JOIN leagues l ON m.league = l.id "
            "LEFT JOIN teams t1 ON m.team1 = t1.id "
            "LEFT JOIN teams t2 ON m.team2 = t2.id "
            "LEFT JOIN special_matches s ON s.match_id = m.id "
            "WHERE b.user_id = " + userId +
            (leagueId != "-1" ? " AND m.league = " + leagueId : "") +
            " ORDER BY m.match_date DESC, m.id DESC "
            "LIMIT " + std::to_string(limit) + " OFFSET " + std::to_string(offset) + ";";

        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK) {
            fprintf(stderr, "Failed to fetch bets: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        rapidjson::Value betsArray(rapidjson::kArrayType);

        for (int i = 0; i < nrows; ++i) {
            rapidjson::Value object(rapidjson::kObjectType);

            rapidjson::Value leagueObject(rapidjson::kObjectType);
            leagueObject.AddMember("id", atoi(PQgetvalue(ret, i, 6)), allocator);
            leagueObject.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 7)), allocator);
            leagueObject.AddMember("country", rapidjson::StringRef(PQgetvalue(ret, i, 8)), allocator);
            object.AddMember("league", leagueObject, allocator);

            object.AddMember("id", atoi(PQgetvalue(ret, i, 5)), allocator);
            object.AddMember("season", rapidjson::StringRef(PQgetvalue(ret, i, 9)), allocator);
            object.AddMember("week", atoi(PQgetvalue(ret, i, 10)), allocator);
            object.AddMember("date", (double)atoll(PQgetvalue(ret, i, 11)), allocator);
            object.AddMember("team1_score", atoi(PQgetvalue(ret, i, 12)), allocator);
            object.AddMember("team2_score", atoi(PQgetvalue(ret, i, 13)), allocator);
            object.AddMember("week_type", atoi(PQgetvalue(ret, i, 14)), allocator);
            object.AddMember("elapsed", atoi(PQgetvalue(ret, i, 15)), allocator);
            object.AddMember("team1_score_live", atoi(PQgetvalue(ret, i, 16)), allocator);
            object.AddMember("team2_score_live", atoi(PQgetvalue(ret, i, 17)), allocator);
            object.AddMember("status", rapidjson::StringRef(PQgetvalue(ret, i, 18)), allocator);
            object.AddMember("is_special", atoi(PQgetvalue(ret, i, 19)), allocator);
            object.AddMember("preview", rapidjson::StringRef(PQgetvalue(ret, i, 20)), allocator);
            object.AddMember("teaser", rapidjson::StringRef(PQgetvalue(ret, i, 21)), allocator);
            object.AddMember("playOff", atoi(PQgetvalue(ret, i, 22)), allocator);

            object.AddMember("team1_score_90", atoi(PQgetvalue(ret, i, 23)), allocator);
            object.AddMember("team2_score_90", atoi(PQgetvalue(ret, i, 24)), allocator);
            object.AddMember("team1_score_pen", atoi(PQgetvalue(ret, i, 25)), allocator);
            object.AddMember("team2_score_pen", atoi(PQgetvalue(ret, i, 26)), allocator);

            object.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 33), allocator), allocator);
            object.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 34), allocator), allocator);

            rapidjson::Value team1Object(rapidjson::kObjectType);
            team1Object.AddMember("id", atoi(PQgetvalue(ret, i, 27)), allocator);
            team1Object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 28)), allocator);
            team1Object.AddMember("shortName", rapidjson::StringRef(PQgetvalue(ret, i, 29)), allocator);
            object.AddMember("team1", team1Object, allocator);

            rapidjson::Value team2Object(rapidjson::kObjectType);
            team2Object.AddMember("id", atoi(PQgetvalue(ret, i, 30)), allocator);
            team2Object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 31)), allocator);
            team2Object.AddMember("shortName", rapidjson::StringRef(PQgetvalue(ret, i, 32)), allocator);
            object.AddMember("team2", team2Object, allocator);

            rapidjson::Value betObject(rapidjson::kObjectType);
            betObject.AddMember("id", atoi(PQgetvalue(ret, i, 0)), allocator);
            betObject.AddMember("bet", rapidjson::StringRef(PQgetvalue(ret, i, 1)), allocator);
            betObject.AddMember("amount", atoi(PQgetvalue(ret, i, 2)), allocator);
            betObject.AddMember("odd", atof(PQgetvalue(ret, i, 3)), allocator);
            betObject.AddMember("status", atoi(PQgetvalue(ret, i, 4)), allocator);
            object.AddMember("bet", betObject, allocator);

            betsArray.PushBack(object, allocator);
        }

        document.AddMember("bets", betsArray, allocator);

        auto generateBetCountQuery = [&](const std::string& condition)
        {
            std::string countSql = "SELECT COUNT(*) FROM bets b INNER JOIN matches m ON b.match_id = m.id WHERE b.user_id = " + userId;
            if (leagueId != "-1")
            {
                countSql += " AND m.league = " + leagueId;
            }
            countSql += condition.size() ? " AND " + condition : "";
            return countSql;
        };

        std::string countAllBetsSql = generateBetCountQuery("");  // Count all bets
        std::string countWinBetsSql = generateBetCountQuery("b.status = 1"); // Count win bets
        std::string countLooseBetsSql = generateBetCountQuery("b.status = 2"); // Count lose bets
        std::string countTotalBetsSql = generateBetCountQuery("b.status IN (1, 2)"); // Total bets that are NOT pending

        PGresult* retAllBets = PQexec(pg, countAllBetsSql.c_str());
        PGresult* retWinBets = PQexec(pg, countWinBetsSql.c_str());
        PGresult* retLooseBets = PQexec(pg, countLooseBetsSql.c_str());
        PGresult* retTotalBets = PQexec(pg, countTotalBetsSql.c_str());

        int allBets = (PQntuples(retAllBets) > 0) ? atoi(PQgetvalue(retAllBets, 0, 0)) : 0;
        int totalWinBets = (PQntuples(retWinBets) > 0) ? atoi(PQgetvalue(retWinBets, 0, 0)) : 0;
        int totalLooseBets = (PQntuples(retLooseBets) > 0) ? atoi(PQgetvalue(retLooseBets, 0, 0)) : 0;
        int totalBets = (PQntuples(retTotalBets) > 0) ? atoi(PQgetvalue(retTotalBets, 0, 0)) : 0;

        PQclear(retAllBets);
        PQclear(retWinBets);
        PQclear(retLooseBets);
        PQclear(retTotalBets);

        document.AddMember("allBets", allBets, allocator);
        document.AddMember("totalBets", totalBets, allocator);
        document.AddMember("totalWinBets", totalWinBets, allocator);
        document.AddMember("totalLooseBets", totalLooseBets, allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}

// Helper function to add count results to the document
void addCountToDocument(const std::string& key, const std::string& sql, PGconn* pg, rapidjson::Document& document, rapidjson::Document::AllocatorType& allocator) {
    PGresult* countRet = PQexec(pg, sql.c_str());
    if (PQresultStatus(countRet) == PGRES_TUPLES_OK) {
        int count = atoi(PQgetvalue(countRet, 0, 0));
        document.AddMember(rapidjson::StringRef(key.c_str()), count, allocator);
    }
    else {
        fprintf(stderr, "Failed to fetch count for %s: %s", key.c_str(), PQerrorMessage(pg));
    }
    PQclear(countRet);
}


std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetUserScorePredicts()
{
    return [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        std::string userId = req.get_param_value("user_id");
        std::string leagueId = req.get_param_value("league_id");
        int page = std::stoi(req.get_param_value("page")) - 1;
        int limit = 20;  // you can make this configurable if needed
        int offset = page * limit;

        PGconn* pg = ConnectionPool::Get()->getConnection();
        if (!pg) {
            res.status = 500;  // Internal Server Error
            return;
        }

        // Base SQL query
        std::string sqlBase = "SELECT p.*, m.id, l.id as league_id, l.name as league_name, m.season, m.week, m.match_date, "
            "m.team1_score, m.team2_score, m.week_type, m.is_special, t1.id as team1_id, t1.name as team1_name, t1.short_name as team1_short_name, "
            "t2.id as team2_id, t2.name as team2_name, t2.short_name as team2_short_name, "
            "COALESCE(s.title, '') AS special_match_title " // Fetch title from special_matches table
            "FROM predicts p "
            "INNER JOIN matches m ON p.match_id = m.id "
            "LEFT JOIN leagues l ON m.league = l.id "
            "LEFT JOIN teams t1 ON m.team1 = t1.id "
            "LEFT JOIN teams t2 ON m.team2 = t2.id "
            "LEFT JOIN special_matches s ON s.match_id = m.id " // Join special_matches
            "WHERE p.user_id = " + userId + " AND p.status = 2";

        if (leagueId != "-1") {
            sqlBase += " AND m.league = " + leagueId;
        }
        sqlBase += " ORDER BY m.match_date DESC, m.id DESC LIMIT " + std::to_string(limit) + " OFFSET " + std::to_string(offset) + ";";

        PGresult* ret = PQexec(pg, sqlBase.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK) {
            fprintf(stderr, "Failed to fetch data: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        rapidjson::Value predictsArray(rapidjson::kArrayType);

        for (int i = 0; i < nrows; ++i) {
            rapidjson::Value object(rapidjson::kObjectType);
            rapidjson::Value leagueObject(rapidjson::kObjectType);
            leagueObject.AddMember("id", atoi(PQgetvalue(ret, i, 7)), allocator);
            leagueObject.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 8)), allocator);
            object.AddMember("league", leagueObject, allocator);

            object.AddMember("id", atoi(PQgetvalue(ret, i, 6)), allocator);
            object.AddMember("season", rapidjson::StringRef(PQgetvalue(ret, i, 9)), allocator);
            object.AddMember("week", atoi(PQgetvalue(ret, i, 10)), allocator);
            object.AddMember("date", (double)atoll(PQgetvalue(ret, i, 11)), allocator);
            object.AddMember("team1_score", atoi(PQgetvalue(ret, i, 12)), allocator);
            object.AddMember("team2_score", atoi(PQgetvalue(ret, i, 13)), allocator);
            object.AddMember("week_type", atoi(PQgetvalue(ret, i, 14)), allocator);
            object.AddMember("is_special", atoi(PQgetvalue(ret, i, 15)), allocator);
            object.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 22), allocator), allocator);

            rapidjson::Value team1Object(rapidjson::kObjectType);
            team1Object.AddMember("id", atoi(PQgetvalue(ret, i, 16)), allocator);
            team1Object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 17)), allocator);
            team1Object.AddMember("shortName", rapidjson::StringRef(PQgetvalue(ret, i, 18)), allocator);
            object.AddMember("team1", team1Object, allocator);

            rapidjson::Value team2Object(rapidjson::kObjectType);
            team2Object.AddMember("id", atoi(PQgetvalue(ret, i, 19)), allocator);
            team2Object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 20)), allocator);
            team2Object.AddMember("shortName", rapidjson::StringRef(PQgetvalue(ret, i, 21)), allocator);
            object.AddMember("team2", team2Object, allocator);

            rapidjson::Value predict(rapidjson::kObjectType);
            predict.AddMember("id", atoi(PQgetvalue(ret, i, 0)), allocator);
            predict.AddMember("team1_score", atoi(PQgetvalue(ret, i, 3)), allocator);
            predict.AddMember("team2_score", atoi(PQgetvalue(ret, i, 4)), allocator);
            predict.AddMember("status", atoi(PQgetvalue(ret, i, 5)), allocator);
            object.AddMember("predict", predict, allocator);

            predictsArray.PushBack(object, allocator);
        }

        document.AddMember("predicts", predictsArray, allocator);

        // Generate count queries based on the same league condition
        auto generateCountQuery = [&](const std::string& condition) {
            std::string countSql = "SELECT COUNT(*) FROM predicts p INNER JOIN matches m ON p.match_id = m.id WHERE p.user_id = " + userId ;
            if (leagueId != "-1") {
                countSql += " AND m.league = " + leagueId;
            }
            countSql += " AND " + condition + ";";
            PGresult* countRet = PQexec(pg, countSql.c_str());

            if (PQresultStatus(countRet) != PGRES_TUPLES_OK) {
                fprintf(stderr, "Failed to fetch count: %s", PQerrorMessage(pg));
                PQclear(countRet);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 500;
                return -1;  // Error code for failure
            }
            int total = atoi(PQgetvalue(countRet, 0, 0));
            PQclear(countRet);
            return total;
        };

        int totalPredicts = generateCountQuery("true");
        if (totalPredicts == -1) return;  // Check for errors and exit if found

        int totalScorePredicts = generateCountQuery("p.status = 2");;  // As this query is already for status = 2

        int totalWinnerPredicts = generateCountQuery("(p.status = 1 OR p.status = 2)");
        if (totalWinnerPredicts == -1) return;  // Check for errors and exit if found

        document.AddMember("totalPredicts", totalPredicts, allocator);
        document.AddMember("totalScorePredicts", totalScorePredicts, allocator);
        document.AddMember("totalWinnerPredicts", totalWinnerPredicts, allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}


std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetUserWinnerPredicts()
{
    return [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        std::string userId = req.get_param_value("user_id");
        std::string leagueId = req.get_param_value("league_id");
        int page = std::stoi(req.get_param_value("page")) - 1; // Assuming page number starts at 1 in client side
        int limit = 20; // Number of records per page
        int offset = page * limit;

        PGconn* pg = ConnectionPool::Get()->getConnection();
        if (!pg) {
            res.status = 500;  // Internal Server Error
            return;
        }

        std::string sql = "SELECT p.*, m.id, l.id as league_id, l.name as league_name, m.season, m.week, m.match_date, "
            "m.team1_score, m.team2_score, m.week_type, t1.id as team1_id, t1.name as team1_name, t1.short_name as team1_short_name, "
            "t2.id as team2_id, t2.name as team2_name, t2.short_name as team2_short_name "
            "FROM predicts p "
            "INNER JOIN matches m ON p.match_id = m.id "
            "LEFT JOIN leagues l ON m.league = l.id "
            "LEFT JOIN teams t1 ON m.team1 = t1.id "
            "LEFT JOIN teams t2 ON m.team2 = t2.id "
            "WHERE p.user_id = " + userId + " AND (p.status = 2 OR p.status = 1)";
        if (leagueId != "-1") {
            sql += " AND m.league = " + leagueId;
        }
        sql += " ORDER BY m.match_date DESC, m.id DESC LIMIT " + std::to_string(limit) + " OFFSET " + std::to_string(offset) + ";";

        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK) {
            fprintf(stderr, "Failed to fetch data: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        rapidjson::Value predictsArray(rapidjson::kArrayType);

        for (int i = 0; i < nrows; ++i) {
            rapidjson::Value object(rapidjson::kObjectType);
            rapidjson::Value leagueObject(rapidjson::kObjectType);
            leagueObject.AddMember("id", atoi(PQgetvalue(ret, i, 7)), allocator);
            leagueObject.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 8)), allocator);
            object.AddMember("league", leagueObject, allocator);

            object.AddMember("id", atoi(PQgetvalue(ret, i, 6)), allocator);
            object.AddMember("season", rapidjson::StringRef(PQgetvalue(ret, i, 9)), allocator);
            object.AddMember("week", atoi(PQgetvalue(ret, i, 10)), allocator);
            object.AddMember("date", (double)atoll(PQgetvalue(ret, i, 11)), allocator);
            object.AddMember("team1_score", atoi(PQgetvalue(ret, i, 12)), allocator);
            object.AddMember("team2_score", atoi(PQgetvalue(ret, i, 13)), allocator);
            object.AddMember("week_type", atoi(PQgetvalue(ret, i, 14)), allocator);

            rapidjson::Value team1Object(rapidjson::kObjectType);
            team1Object.AddMember("id", atoi(PQgetvalue(ret, i, 15)), allocator);
            team1Object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 16)), allocator);
            team1Object.AddMember("shortName", rapidjson::StringRef(PQgetvalue(ret, i, 17)), allocator);
            object.AddMember("team1", team1Object, allocator);

            rapidjson::Value team2Object(rapidjson::kObjectType);
            team2Object.AddMember("id", atoi(PQgetvalue(ret, i, 18)), allocator);
            team2Object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 19)), allocator);
            team2Object.AddMember("shortName", rapidjson::StringRef(PQgetvalue(ret, i, 20)), allocator);
            object.AddMember("team2", team2Object, allocator);

            rapidjson::Value predict(rapidjson::kObjectType);
            predict.AddMember("id", atoi(PQgetvalue(ret, i, 0)), allocator);
            predict.AddMember("team1_score", atoi(PQgetvalue(ret, i, 3)), allocator);
            predict.AddMember("team2_score", atoi(PQgetvalue(ret, i, 4)), allocator);
            predict.AddMember("status", atoi(PQgetvalue(ret, i, 5)), allocator);
            object.AddMember("predict", predict, allocator);

            predictsArray.PushBack(object, allocator);
        }

        document.AddMember("predicts", predictsArray, allocator);

        // Generate count queries based on the same league condition
        auto generateCountQuery = [&](const std::string& condition) {
            std::string countSql = "SELECT COUNT(*) FROM predicts p INNER JOIN matches m ON p.match_id = m.id WHERE p.user_id = " + userId;
            if (leagueId != "-1") {
                countSql += " AND m.league = " + leagueId;
            }
            countSql += " AND " + condition + ";";
            PGresult* countRet = PQexec(pg, countSql.c_str());

            if (PQresultStatus(countRet) != PGRES_TUPLES_OK) {
                fprintf(stderr, "Failed to fetch count: %s", PQerrorMessage(pg));
                PQclear(countRet);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 500;
                return -1;  // Error code for failure
            }
            int total = atoi(PQgetvalue(countRet, 0, 0));
            PQclear(countRet);
            return total;
        };

        int totalPredicts = generateCountQuery("true");
        if (totalPredicts == -1) return;  // Check for errors and exit if found

        int totalScorePredicts = generateCountQuery("p.status = 2");
        if (totalScorePredicts == -1) return;  // Check for errors and exit if found

        int totalWinnerPredicts = generateCountQuery("(p.status = 2 OR p.status = 1)");
        if (totalWinnerPredicts == -1) return;  // Check for errors and exit if found

        document.AddMember("totalPredicts", totalPredicts, allocator);
        document.AddMember("totalScorePredicts", totalScorePredicts, allocator);
        document.AddMember("totalWinnerPredicts", totalWinnerPredicts, allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}


std::string getUserName(PGconn* conn, int userId)
{
    char query[256];
    snprintf(query, sizeof(query), "SELECT name FROM users WHERE id = %d;", userId);

    PGresult* res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        PQclear(res);
        return "Unknown"; // Indicate error
    }

    std::string userName(PQgetvalue(res, 0, 0));
    PQclear(res);
    return userName;
}

std::string getUserAvatar(PGconn* conn, int userId)
{
    char query[256];
    snprintf(query, sizeof(query), "SELECT avatar FROM users WHERE id = %d;", userId);

    PGresult* res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        PQclear(res);
        return "Unknown"; // Indicate error
    }

    std::string userAvatar(PQgetvalue(res, 0, 0));
    PQclear(res);
    return userAvatar;
}

int getUserPoints(PGconn* conn, int userId)
{
    char query[256];
    snprintf(query, sizeof(query), "SELECT points FROM users WHERE id = %d;", userId);

    PGresult* res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        PQclear(res);
        return 0; // Indicate error
    }

    int points = atoi(PQgetvalue(res, 0, 0));
    PQclear(res);
    return points;
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetMatchPredicts()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        std::string matchId = req.get_param_value("match_id");
        std::string season;
        if (req.has_param("season"))
        {
            season = req.get_param_value("season");
        }
        std::string postfix = "";
        if (season.size())
        {
            std::string currentSeason = "25/26";
            if (season != currentSeason)
            {
                std::replace(season.begin(), season.end(), '/', '_');
                postfix = "_" + season;
            }
        }

        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string predictsSql = "SELECT * FROM predicts" + postfix + " WHERE status <> 4 AND match_id = " + matchId + ";";
        PGresult* predictsRet = PQexec(pg, predictsSql.c_str());

        if (PQresultStatus(predictsRet) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch predicts: %s", PQerrorMessage(pg));
            PQclear(predictsRet);
            res.status = 500;  // Internal Server Error
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }

        // Fetch predicts
        int nrows = PQntuples(predictsRet);
        rapidjson::Document document;
        rapidjson::Value predicts;
        predicts.SetArray();

        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        int numP1 = 0, numP2 = 0, numDraw = 0;

        for (int i = 0; i < nrows; ++i)
        {
            int score1 = atoi(PQgetvalue(predictsRet, i, 3));
            int score2 = atoi(PQgetvalue(predictsRet, i, 4));

            if (score1 > score2) ++numP1;
            else if (score2 > score1) ++numP2;
            else ++numDraw;
        }

        document.AddMember("numP1", numP1, allocator);
        document.AddMember("numP2", numP2, allocator);
        document.AddMember("numDraw", numDraw, allocator);
        document.AddMember("numPredicts", nrows, allocator);

        // Check for beat_bet record
        std::string beatBetSql =
            "SELECT bet, odd, status "
            "FROM bets WHERE user_id = 25524 and match_id = " + matchId + ";";
        PGresult* beatBetRet = PQexec(pg, beatBetSql.c_str());

        if (PQresultStatus(beatBetRet) == PGRES_TUPLES_OK && PQntuples(beatBetRet) > 0)
        {
            rapidjson::Value beatBet(rapidjson::kObjectType);

            rapidjson::Value v;
            v.SetString(PQgetvalue(beatBetRet, 0, 0), allocator);
            beatBet.AddMember("bet", v, allocator);
            beatBet.AddMember("odd", atof(PQgetvalue(beatBetRet, 0, 1)), allocator);
            beatBet.AddMember("status", atoi(PQgetvalue(beatBetRet, 0, 2)), allocator);

            document.AddMember("beatBetOfficial", beatBet, allocator);
        }

        // Clean up beat_bet result
        PQclear(beatBetRet);

        // Serialize JSON response
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;  // OK

        PQclear(predictsRet);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetMatchBetsSummary()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        std::string matchId = req.get_param_value("match_id");
        std::string season;
        /*if (req.has_param("season"))
        {
            season = req.get_param_value("season");
        }*/
        std::string postfix = "";
        /*if (season.size())
        {
            std::string currentSeason = "25/26";
            if (season != currentSeason)
            {
                std::replace(season.begin(), season.end(), '/', '_');
                postfix = "_" + season;
            }
        }*/

        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string predictsSql = "SELECT bet FROM bets" + postfix + " WHERE match_id = " + matchId + ";";
        PGresult* predictsRet = PQexec(pg, predictsSql.c_str());

        if (PQresultStatus(predictsRet) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch predicts: %s", PQerrorMessage(pg));
            PQclear(predictsRet);
            res.status = 500;  // Internal Server Error
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }

        // Fetch predicts
        int nrows = PQntuples(predictsRet);
        rapidjson::Document document;
        rapidjson::Value predicts;
        predicts.SetArray();

        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        int numP1 = 0, numP2 = 0, numDraw = 0;

        for (int i = 0; i < nrows; ++i)
        {
            std::string bet = (PQgetvalue(predictsRet, i, 0));

            if (bet == "w1" || bet == "x12" || bet == "x1") ++numP1;
            if (bet == "w2" || bet == "x12" || bet == "x2") ++numP2;
            if (bet == "x1" || bet == "x12" || bet == "x2" || bet == "x") ++numDraw;
        }

        document.AddMember("numP1", numP1, allocator);
        document.AddMember("numP2", numP2, allocator);
        document.AddMember("numDraw", numDraw, allocator);
        document.AddMember("numPredicts", nrows, allocator);

        // Check for beat_bet record
        // std::string beatBetSql =
        //     "SELECT ai_team, ai_type, ai_status, ls_team, ls_type, ls_percent, ls_status, "
        //     "score180_team, score180_type, score180_percent, score180_status "
        //     "FROM beat_bet WHERE match_id = " + matchId + " LIMIT 1;";
        // PGresult* beatBetRet = PQexec(pg, beatBetSql.c_str());
        // 
        // if (PQresultStatus(beatBetRet) == PGRES_TUPLES_OK && PQntuples(beatBetRet) > 0)
        // {
        //     rapidjson::Value beatBet(rapidjson::kObjectType);
        // 
        //     beatBet.AddMember("ai_team", atoi(PQgetvalue(beatBetRet, 0, 0)), allocator);
        //     beatBet.AddMember("ai_type", atoi(PQgetvalue(beatBetRet, 0, 1)), allocator);
        //     beatBet.AddMember("ai_status", atoi(PQgetvalue(beatBetRet, 0, 2)), allocator);
        //     beatBet.AddMember("ls_team", atoi(PQgetvalue(beatBetRet, 0, 3)), allocator);
        //     beatBet.AddMember("ls_type", atoi(PQgetvalue(beatBetRet, 0, 4)), allocator);
        //     beatBet.AddMember("ls_percent", atoi(PQgetvalue(beatBetRet, 0, 5)), allocator);
        //     beatBet.AddMember("ls_status", atoi(PQgetvalue(beatBetRet, 0, 6)), allocator);
        //     beatBet.AddMember("score180_team", atoi(PQgetvalue(beatBetRet, 0, 7)), allocator);
        //     beatBet.AddMember("score180_type", atoi(PQgetvalue(beatBetRet, 0, 8)), allocator);
        //     beatBet.AddMember("score180_percent", atoi(PQgetvalue(beatBetRet, 0, 9)), allocator);
        //     beatBet.AddMember("score180_status", atoi(PQgetvalue(beatBetRet, 0, 10)), allocator);
        // 
        //     document.AddMember("beatBet", beatBet, allocator);
        // }
        // 
        // // Clean up beat_bet result
        // PQclear(beatBetRet);

        // Serialize JSON response
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;  // OK

        PQclear(predictsRet);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}


#include "CachedTable.h"
std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetMatchPredictsTop3()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        std::string matchId = req.get_param_value("match_id");std::string season = "";
        if (req.has_param("season"))
        {
            season = req.get_param_value("season");
            if (season == "undefined") season = "";
        }
        std::string postfix = "";
        if (season.size())
        {
            std::string currentSeason = "25/26";
            if (season != currentSeason)
            {
                std::replace(season.begin(), season.end(), '/', '_');
                postfix = "_" + season;
            }
        }

        PGconn* pg = ConnectionPool::Get()->getConnection();
        // Join the predicts with users table and order by points descending, limit to 3
        std::string sql = "SELECT p.*, u.name, u.avatar, u.points" + postfix +", u.league, u.balance, "
            "COALESCE(fu.points, -1) AS fireball_points "
            "FROM predicts" + postfix + " p "
            "JOIN users u ON p.user_id = u.id "
            "LEFT JOIN fireball_users fu ON fu.user_id = u.id "
            "WHERE p.status <> 4 and p.match_id = " + matchId + " "
            "ORDER BY u.points" + postfix + " DESC LIMIT 20;";
        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch top predicts: %s", PQerrorMessage(pg));
            PQclear(ret);
            res.status = 500;  // Internal Server Error
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        rapidjson::Value predicts;
        predicts.SetArray();

        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

     //   if (!mCachedTable.size()) CacheTable();
        for (int i = 0; i < nrows; ++i)
        {
            rapidjson::Value object;
            object.SetObject();

            // Construct JSON object per predict
            int id = atoi(PQgetvalue(ret, i, 0));
            int userId = atoi(PQgetvalue(ret, i, 1));
            int matchId = atoi(PQgetvalue(ret, i, 2));
            int score1 = atoi(PQgetvalue(ret, i, 3));
            int score2 = atoi(PQgetvalue(ret, i, 4));
            int status = atoi(PQgetvalue(ret, i, 5));
            std::string userName = PQgetvalue(ret, i, 6);
            std::string userAvatar = PQgetvalue(ret, i, 7);
            int points = atoi(PQgetvalue(ret, i, 8));
            int league = atoi(PQgetvalue(ret, i, 9));
            float balance = atof(PQgetvalue(ret, i, 10));
            int fireballPoints = atoi(PQgetvalue(ret, i, 11));

            // Add user info and position to the JSON object
            rapidjson::Value userObject;
            userObject.SetObject();
            userObject.AddMember("id", userId, allocator);
            rapidjson::Value nameVal;
            nameVal.SetString(userName.c_str(), allocator);
            userObject.AddMember("name", nameVal, allocator);
            nameVal.SetString(userAvatar.c_str(), allocator);
            userObject.AddMember("avatar", nameVal, allocator);
            userObject.AddMember("points", points, allocator);
            userObject.AddMember("league", league, allocator);
            userObject.AddMember("balance", balance, allocator);
            userObject.AddMember("fireballPoints", fireballPoints, allocator);

            int posi = CachedTable::Get()->GetPosition(userId, league);
            userObject.AddMember("position", posi, allocator);

            int bbPos = CachedTable::Get()->GetBeatBetPosition(userId);
            userObject.AddMember("beatBetPosition", bbPos, allocator);

            int fbPos = CachedTable::Get()->GetFireballPosition(userId);
            userObject.AddMember("fireballPosition", fbPos, allocator);

            {
                std::string awardsQuery = "SELECT place, season, league FROM awards WHERE user_id = " + std::to_string(userId) + ";";
                PGresult* awardsRes = PQexec(pg, awardsQuery.c_str());

                if (PQresultStatus(awardsRes) != PGRES_TUPLES_OK)
                {
                    fprintf(stderr, "Failed to fetch awards: %s", PQerrorMessage(pg));
                    PQclear(awardsRes);
                }
                else
                {
                    int awardCount = PQntuples(awardsRes);
                    rapidjson::Value awards(rapidjson::kArrayType);

                    for (int j = 0; j < awardCount; ++j)
                    {
                        rapidjson::Value awardObj(rapidjson::kObjectType);

                        int place = atoi(PQgetvalue(awardsRes, j, 0));
                        char* season = PQgetvalue(awardsRes, j, 1);
                        int league = atoi(PQgetvalue(awardsRes, j, 2));

                        awardObj.AddMember("place", place, allocator);

                        rapidjson::Value seasonVal;
                        seasonVal.SetString(season, allocator);
                        awardObj.AddMember("season", seasonVal, allocator);
                        awardObj.AddMember("league", league, allocator);

                        awards.PushBack(awardObj, allocator);
                    }

                    userObject.AddMember("awards", awards, allocator);
                    PQclear(awardsRes);
                }

            }


           /* int pos = -1;
            auto it = std::find(mCachedTable.begin(), mCachedTable.end(), userId);

            if (it != mCachedTable.end()) 
            {
                // If the element is found, calculate the index
                int index = std::distance(mCachedTable.begin(), it);
                pos = index + 1;
            }

            userObject.AddMember("position", pos, allocator);  // Add position based on loop index
            */
            object.AddMember("id", id, allocator);
            object.AddMember("user", userObject, allocator);
            object.AddMember("match_id", matchId, allocator);
            object.AddMember("team1_score", score1, allocator);
            object.AddMember("team2_score", score2, allocator);
            object.AddMember("status", status, allocator);

            predicts.PushBack(object, allocator);
        }

        document.AddMember("predicts", predicts, allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;  // OK

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetMatchPredictsTop20V2()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        std::string matchId = req.get_param_value("match_id");std::string season = "";
        if (req.has_param("season"))
        {
            season = req.get_param_value("season");
            if (season == "undefined") season = "";
        }
        std::string postfix = "";
        if (season.size())
        {
            std::string currentSeason = "25/26";
            if (season != currentSeason)
            {
                std::replace(season.begin(), season.end(), '/', '_');
                postfix = "_" + season;
            }
        }

        PGconn* pg = ConnectionPool::Get()->getConnection();
        // Join the predicts with users table and order by points descending, limit to 3
        std::string sql = "SELECT p.*, u.name, u.avatar, u.points" + postfix + ", u.clear_balance, "
            "u.eltorneo_position, u.eltorneo_league, "
            "u.beat_bet_position, u.beat_bet_league, "
            "fu.position, fu.league, "
            "cu.position, cu.league, "
            "COALESCE(fu.points, -1) AS fireball_points, "
            "COALESCE(cu.points, -1) AS career_points "
            "FROM predicts" + postfix + " p "
            "JOIN users u ON p.user_id = u.id "
            "LEFT JOIN fireball_users fu ON fu.user_id = u.id "
            "LEFT JOIN career_users cu ON cu.user_id = u.id "
            "WHERE p.status <> 4 and p.match_id = " + matchId + " "
            "ORDER BY u.points" + postfix + " DESC LIMIT 20;";
        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch top predicts: %s", PQerrorMessage(pg));
            PQclear(ret);
            res.status = 500;  // Internal Server Error
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        rapidjson::Value predicts;
        predicts.SetArray();

        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        //   if (!mCachedTable.size()) CacheTable();
        for (int i = 0; i < nrows; ++i)
        {
            rapidjson::Value object;
            object.SetObject();

            // Construct JSON object per predict
            int id = atoi(PQgetvalue(ret, i, 0));
            int userId = atoi(PQgetvalue(ret, i, 1));
            int matchId = atoi(PQgetvalue(ret, i, 2));
            int score1 = atoi(PQgetvalue(ret, i, 3));
            int score2 = atoi(PQgetvalue(ret, i, 4));
            int status = atoi(PQgetvalue(ret, i, 5));
            std::string userName = PQgetvalue(ret, i, 6);
            std::string userAvatar = PQgetvalue(ret, i, 7);
            int points = atoi(PQgetvalue(ret, i, 8));
            float balance = atof(PQgetvalue(ret, i, 9));

            float elTorneoLeague = atoi(PQgetvalue(ret, i, 11));
            if (elTorneoLeague < 1) elTorneoLeague = -1;
            float elTorneoPosition = elTorneoLeague >= 1 ? atoi(PQgetvalue(ret, i, 10)) - (elTorneoLeague - 1) * 20 : -1;

            float beatBetLeague = atoi(PQgetvalue(ret, i, 13));
            if (beatBetLeague < 1) beatBetLeague = -1;
            float beatBetPosition = beatBetLeague >= 1 ? atoi(PQgetvalue(ret, i, 12)) - (beatBetLeague - 1) * 20 : -1;

            float fireballLeague = atoi(PQgetvalue(ret, i, 15));
            if (fireballLeague < 1) fireballLeague = -1;
            float fireballPosition = fireballLeague >= 1 ? atoi(PQgetvalue(ret, i, 14)) - (fireballLeague - 1) * 20 : -1;

            float careerLeague = atoi(PQgetvalue(ret, i, 17));
            if (careerLeague < 1) careerLeague = -1;
            float careerPosition = careerLeague >= 1 ? atoi(PQgetvalue(ret, i, 16)) - (careerLeague - 1) * 20 : -1;

            int fireballPoints = atoi(PQgetvalue(ret, i, 18));
            int careerPoints = atoi(PQgetvalue(ret, i, 19));

            // Add user info and position to the JSON object
            rapidjson::Value userObject;
            userObject.SetObject();
            userObject.AddMember("id", userId, allocator);
            rapidjson::Value nameVal;
            nameVal.SetString(userName.c_str(), allocator);
            userObject.AddMember("name", nameVal, allocator);
            nameVal.SetString(userAvatar.c_str(), allocator);
            userObject.AddMember("avatar", nameVal, allocator);
            userObject.AddMember("points", points, allocator);
            userObject.AddMember("balance", balance, allocator);
            userObject.AddMember("elTorneoLeague",   elTorneoLeague, allocator);
            userObject.AddMember("elTorneoPosition", elTorneoPosition, allocator);
            userObject.AddMember("beatBetLeague",   beatBetLeague, allocator);
            userObject.AddMember("beatBetPosition", beatBetPosition, allocator);
            userObject.AddMember("fireballLeague",   fireballLeague, allocator);
            userObject.AddMember("fireballPosition", fireballPosition, allocator);
            userObject.AddMember("careerLeague",   careerLeague, allocator);
            userObject.AddMember("careerPosition", careerPosition, allocator);

            userObject.AddMember("fireballPoints", fireballPoints, allocator);
            userObject.AddMember("careerPoints", careerPoints, allocator);

            {
                std::string awardsQuery = "SELECT place, season, league FROM awards WHERE user_id = " + std::to_string(userId) + ";";
                PGresult* awardsRes = PQexec(pg, awardsQuery.c_str());

                if (PQresultStatus(awardsRes) != PGRES_TUPLES_OK)
                {
                    fprintf(stderr, "Failed to fetch awards: %s", PQerrorMessage(pg));
                    PQclear(awardsRes);
                }
                else
                {
                    int awardCount = PQntuples(awardsRes);
                    rapidjson::Value awards(rapidjson::kArrayType);

                    for (int j = 0; j < awardCount; ++j)
                    {
                        rapidjson::Value awardObj(rapidjson::kObjectType);

                        int place = atoi(PQgetvalue(awardsRes, j, 0));
                        char* season = PQgetvalue(awardsRes, j, 1);
                        int league = atoi(PQgetvalue(awardsRes, j, 2));

                        awardObj.AddMember("place", place, allocator);

                        rapidjson::Value seasonVal;
                        seasonVal.SetString(season, allocator);
                        awardObj.AddMember("season", seasonVal, allocator);
                        awardObj.AddMember("league", league, allocator);

                        awards.PushBack(awardObj, allocator);
                    }

                    userObject.AddMember("awards", awards, allocator);
                    PQclear(awardsRes);
                }

            }

            object.AddMember("id", id, allocator);
            object.AddMember("user", userObject, allocator);
            object.AddMember("match_id", matchId, allocator);
            object.AddMember("team1_score", score1, allocator);
            object.AddMember("team2_score", score2, allocator);
            object.AddMember("status", status, allocator);

            predicts.PushBack(object, allocator);
        }

        document.AddMember("predicts", predicts, allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;  // OK

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}


std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetMatchBetsTop20()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        std::string matchId = req.get_param_value("match_id");std::string season = "";
        /*if (req.has_param("season"))
        {
            season = req.get_param_value("season");
        }*/
        std::string postfix = "";
        /*if (season.size())
        {
            std::string currentSeason = "25/26";
            if (season != currentSeason)
            {
                std::replace(season.begin(), season.end(), '/', '_');
                postfix = "_" + season;
            }
        }*/

        PGconn* pg = ConnectionPool::Get()->getConnection();
        // Join the predicts with users table and order by points descending, limit to 3
        std::string sql = "SELECT b.*, u.name, u.avatar, u.points" + postfix + ", u.league, u.balance, "
            "COALESCE(fu.points, -1) AS fireball_points "
            "FROM bets" + postfix + " b "
            "JOIN users u ON b.user_id = u.id "
            "LEFT JOIN fireball_users fu ON fu.user_id = u.id "
            "WHERE b.match_id = " + matchId + " "
            "ORDER BY u.balance" + postfix + " DESC LIMIT 20;";
        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch top 20 bets: %s", PQerrorMessage(pg));
            PQclear(ret);
            res.status = 500;  // Internal Server Error
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        rapidjson::Value predicts;
        predicts.SetArray();

        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        for (int i = 0; i < nrows; ++i)
        {
            rapidjson::Value object;
            object.SetObject();

            // Construct JSON object per predict
            int id = atoi(PQgetvalue(ret, i, 0));
            int userId = atoi(PQgetvalue(ret, i, 1));
            int matchId = atoi(PQgetvalue(ret, i, 2));
            std::string bet = (PQgetvalue(ret, i, 3));
            int amount = atoi(PQgetvalue(ret, i, 4));
            float odd = atof(PQgetvalue(ret, i, 5));
            int status = atoi(PQgetvalue(ret, i, 6));

            std::string userName = PQgetvalue(ret, i, 7);
            std::string userAvatar = PQgetvalue(ret, i, 8);
            int points = atoi(PQgetvalue(ret, i, 9));
            int league = atoi(PQgetvalue(ret, i, 10));
            float balance = atof(PQgetvalue(ret, i, 11));
            int fireballPoints = atoi(PQgetvalue(ret, i, 12));

            // Add user info and position to the JSON object
            rapidjson::Value userObject;
            userObject.SetObject();
            userObject.AddMember("id", userId, allocator);
            rapidjson::Value nameVal;
            nameVal.SetString(userName.c_str(), allocator);
            userObject.AddMember("name", nameVal, allocator);
            nameVal.SetString(userAvatar.c_str(), allocator);
            userObject.AddMember("avatar", nameVal, allocator);
            userObject.AddMember("points", points, allocator);
            userObject.AddMember("league", league, allocator);
            userObject.AddMember("balance", balance, allocator);
            userObject.AddMember("fireballPoints", fireballPoints, allocator);

            int posi = CachedTable::Get()->GetPosition(userId, league);
            userObject.AddMember("position", posi, allocator);

            int bbPos = CachedTable::Get()->GetBeatBetPosition(userId);
            userObject.AddMember("beatBetPosition", bbPos, allocator);

            int fbPos = CachedTable::Get()->GetFireballPosition(userId);
            userObject.AddMember("fireballPosition", fbPos, allocator);

            {
                std::string awardsQuery = "SELECT place, season, league FROM awards WHERE user_id = " + std::to_string(userId) + ";";
                PGresult* awardsRes = PQexec(pg, awardsQuery.c_str());

                if (PQresultStatus(awardsRes) != PGRES_TUPLES_OK)
                {
                    fprintf(stderr, "Failed to fetch awards: %s", PQerrorMessage(pg));
                    PQclear(awardsRes);
                }
                else
                {
                    int awardCount = PQntuples(awardsRes);
                    rapidjson::Value awards(rapidjson::kArrayType);

                    for (int j = 0; j < awardCount; ++j)
                    {
                        rapidjson::Value awardObj(rapidjson::kObjectType);

                        int place = atoi(PQgetvalue(awardsRes, j, 0));
                        char* season = PQgetvalue(awardsRes, j, 1);
                        int league = atoi(PQgetvalue(awardsRes, j, 2));

                        awardObj.AddMember("place", place, allocator);

                        rapidjson::Value seasonVal;
                        seasonVal.SetString(season, allocator);
                        awardObj.AddMember("season", seasonVal, allocator);
                        awardObj.AddMember("league", league, allocator);

                        awards.PushBack(awardObj, allocator);
                    }

                    userObject.AddMember("awards", awards, allocator);
                    PQclear(awardsRes);
                }

            }

            object.AddMember("id", id, allocator);
            object.AddMember("user", userObject, allocator);
            object.AddMember("match_id", matchId, allocator);
            rapidjson::Value betVal;
            betVal.SetString(bet.c_str(), allocator);
            object.AddMember("bet", betVal, allocator);
            object.AddMember("amount", amount, allocator);
            object.AddMember("odd", odd, allocator);
            object.AddMember("status", status, allocator);

            predicts.PushBack(object, allocator);
        }

        document.AddMember("predicts", predicts, allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;  // OK

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetMatchBetsTop20V2()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        std::string matchId = req.get_param_value("match_id");std::string season = "";
        /*if (req.has_param("season"))
        {
            season = req.get_param_value("season");
        }*/
        std::string postfix = "";
        /*if (season.size())
        {
            std::string currentSeason = "25/26";
            if (season != currentSeason)
            {
                std::replace(season.begin(), season.end(), '/', '_');
                postfix = "_" + season;
            }
        }*/

        PGconn* pg = ConnectionPool::Get()->getConnection();
        // Join the predicts with users table and order by points descending, limit to 3
        std::string sql = "SELECT b.*, u.name, u.avatar, u.points" + postfix + ", u.clear_balance, "
            "u.eltorneo_league, u.eltorneo_position, "
            "u.beat_bet_league, u.beat_bet_position, "
            "fu.league, fu.position, "
            "cu.league, cu.position, "
            "COALESCE(fu.points, -1) AS fireball_points, "
            "COALESCE(cu.points, -1) AS career_points "
            "FROM bets" + postfix + " b "
            "JOIN users u ON b.user_id = u.id "
            "LEFT JOIN fireball_users fu ON fu.user_id = u.id "
            "LEFT JOIN career_users cu ON cu.user_id = u.id "
            "WHERE b.match_id = " + matchId + " "
            "ORDER BY u.clear_balance" + postfix + " DESC LIMIT 20;";
        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch top 20 bets: %s", PQerrorMessage(pg));
            PQclear(ret);
            res.status = 500;  // Internal Server Error
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        rapidjson::Value predicts;
        predicts.SetArray();

        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        for (int i = 0; i < nrows; ++i)
        {
            rapidjson::Value object;
            object.SetObject();

            // Construct JSON object per predict
            int id = atoi(PQgetvalue(ret, i, 0));
            int userId = atoi(PQgetvalue(ret, i, 1));
            int matchId = atoi(PQgetvalue(ret, i, 2));
            std::string bet = (PQgetvalue(ret, i, 3));
            int amount = atoi(PQgetvalue(ret, i, 4));
            float odd = atof(PQgetvalue(ret, i, 5));
            int status = atoi(PQgetvalue(ret, i, 6));

            std::string userName = PQgetvalue(ret, i, 7);
            std::string userAvatar = PQgetvalue(ret, i, 8);
            int points = atoi(PQgetvalue(ret, i, 9));
            float balance = atof(PQgetvalue(ret, i, 10));

            int elTorneoLeague = atoi(PQgetvalue(ret, i, 11));
            if (elTorneoLeague < 1) elTorneoLeague = -1;
            int elTorneoPosition = elTorneoLeague >= 1 ? atoi(PQgetvalue(ret, i, 12)) - (elTorneoLeague - 1) * 20 : -1;

            int beatBetLeague = atoi(PQgetvalue(ret, i, 13));
            if (beatBetLeague < 1) beatBetLeague = -1;
            int beatBetPosition = beatBetLeague >= 1 ? atoi(PQgetvalue(ret, i, 14)) - (beatBetLeague - 1) * 20 : -1;

            int fireballLeague = atoi(PQgetvalue(ret, i, 15));
            if (fireballLeague < 1) fireballLeague = -1;
            int fireballPosition = fireballLeague >=1 ? atoi(PQgetvalue(ret, i, 16)) - (fireballLeague - 1) * 20 : -1;

            int careerLeague = atoi(PQgetvalue(ret, i, 17));
            if (careerLeague < 1) careerLeague = -1;
            int careerPosition = careerLeague >= 1 ? atoi(PQgetvalue(ret, i, 18)) - (careerLeague - 1) * 20 : -1;


            int fireballPoints = atoi(PQgetvalue(ret, i, 19));
            int careerPoints = atoi(PQgetvalue(ret, i, 20));

            // Add user info and position to the JSON object
            rapidjson::Value userObject;
            userObject.SetObject();
            userObject.AddMember("id", userId, allocator);
            rapidjson::Value nameVal;
            nameVal.SetString(userName.c_str(), allocator);
            userObject.AddMember("name", nameVal, allocator);
            nameVal.SetString(userAvatar.c_str(), allocator);
            userObject.AddMember("avatar", nameVal, allocator);
            userObject.AddMember("points", points, allocator);
            userObject.AddMember("balance", balance, allocator);
            userObject.AddMember("fireballPoints", fireballPoints, allocator);
            userObject.AddMember("careerPoints", careerPoints, allocator);

            userObject.AddMember("elTorneoLeague", elTorneoLeague, allocator);
            userObject.AddMember("elTorneoPosition", elTorneoPosition, allocator);
            userObject.AddMember("beatBetLeague", beatBetLeague, allocator);
            userObject.AddMember("beatBetPosition", beatBetPosition, allocator);
            userObject.AddMember("fireballLeague",   fireballLeague, allocator);
            userObject.AddMember("fireballPosition", fireballPosition, allocator);
            userObject.AddMember("careerLeague", careerLeague, allocator);
            userObject.AddMember("careerPosition", careerPosition, allocator);
            {
                std::string awardsQuery = "SELECT place, season, league FROM awards WHERE user_id = " + std::to_string(userId) + ";";
                PGresult* awardsRes = PQexec(pg, awardsQuery.c_str());

                if (PQresultStatus(awardsRes) != PGRES_TUPLES_OK)
                {
                    fprintf(stderr, "Failed to fetch awards: %s", PQerrorMessage(pg));
                    PQclear(awardsRes);
                }
                else
                {
                    int awardCount = PQntuples(awardsRes);
                    rapidjson::Value awards(rapidjson::kArrayType);

                    for (int j = 0; j < awardCount; ++j)
                    {
                        rapidjson::Value awardObj(rapidjson::kObjectType);

                        int place = atoi(PQgetvalue(awardsRes, j, 0));
                        char* season = PQgetvalue(awardsRes, j, 1);
                        int league = atoi(PQgetvalue(awardsRes, j, 2));

                        awardObj.AddMember("place", place, allocator);

                        rapidjson::Value seasonVal;
                        seasonVal.SetString(season, allocator);
                        awardObj.AddMember("season", seasonVal, allocator);
                        awardObj.AddMember("league", league, allocator);

                        awards.PushBack(awardObj, allocator);
                    }

                    userObject.AddMember("awards", awards, allocator);
                    PQclear(awardsRes);
                }

            }

            object.AddMember("id", id, allocator);
            object.AddMember("user", userObject, allocator);
            object.AddMember("match_id", matchId, allocator);
            rapidjson::Value betVal;
            betVal.SetString(bet.c_str(), allocator);
            object.AddMember("bet", betVal, allocator);
            object.AddMember("amount", amount, allocator);
            object.AddMember("odd", odd, allocator);
            object.AddMember("status", status, allocator);

            predicts.PushBack(object, allocator);
        }

        document.AddMember("predicts", predicts, allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;  // OK

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}


#include "CachedTable.h"
std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetTableByPoints()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        // Get the 'page' query parameter, default to 1 if not provided
        int page = 1;
        int league = 1;
        std::string season = "25_26";
        if (req.has_param("page")) 
        {
            page = std::stoi(req.get_param_value("page"));
            page = std::max(page, 1);
        }
        if (req.has_param("league")) 
        {
            league = std::stoi(req.get_param_value("league"));
        }
        if (req.has_param("season")) 
        {
            season = req.get_param_value("season");
            std::replace(season.begin(), season.end(), '/', '_');
            if (season == "undefined") season = "25_26";
        }

        int limit = 20; // Number of users per page
        int offset = (page - 1) * limit; // Calculate the offset based on the page

        PGconn* pg = ConnectionPool::Get()->getConnection();
        if (!pg) 
        {
            res.status = 500;  // Internal Server Error
            return;
        }

        std::string predictsTableName = "predicts";
        std::string pointsColName = "u.points";
        std::string leagueColName = "u.league";

        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        long long timestamp = ms.count();
        long long ten_days_ms = 20LL * 24 * 60 * 60 * 1000;
        long long tsDiff = timestamp - ten_days_ms;

        std::string currentSeason = "25_26";
        bool isCurrentSeason = true;
        if (season != currentSeason) 
        {
            isCurrentSeason = false;
            predictsTableName += "_" + season;
            pointsColName += "_" + season;
            leagueColName += "_" + season;
            tsDiff = 0;
        }

        // SQL query
        std::string sql =
            "SELECT u.id, u.name, u.avatar, "
            + pointsColName + " AS user_points, "
            + leagueColName + ", "
            "u.balance, COUNT(p.id) AS total_predictions, "
            "COALESCE(fu.points, -1) AS fireball_points, "
            "COALESCE(cu.points, -1) AS career_points "
            "FROM users u "
            "INNER JOIN " + predictsTableName + " p ON u.id = p.user_id "
            "LEFT JOIN fireball_users fu ON fu.user_id = u.id "
            "LEFT JOIN career_users cu ON cu.user_id = u.id "
            "WHERE p.status != 4 "
         + (!isCurrentSeason ? "AND " + leagueColName + " = " + std::to_string(league) + " " : "") +
            "AND u.last_predict_ts >= " + std::to_string(tsDiff) + " "
            "GROUP BY u.id, u.name, u.avatar, " + pointsColName + ", "
            + leagueColName + ", u.balance, fu.points, cu.points "
            "HAVING COUNT(p.id) > 0 "
            "ORDER BY " + pointsColName + " DESC, total_predictions DESC, u.id ASC "
            "LIMIT " + std::to_string(limit) + " OFFSET " + std::to_string(offset) + ";";


        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK) 
        {
            fprintf(stderr, "Failed to fetch table by points: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetArray();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
     //   if (page == 1 && league == 1) mCachedTable.clear();
        for (int i = 0; i < nrows; ++i) {
            int id = atoi(PQgetvalue(ret, i, 0));
            rapidjson::Value object(rapidjson::kObjectType);
            object.AddMember("id",id , allocator);
            object.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 1), allocator), allocator);
            object.AddMember("avatar", rapidjson::Value(PQgetvalue(ret, i, 2), allocator), allocator);
            object.AddMember("predictions", atoi(PQgetvalue(ret, i, 3)), allocator);
            object.AddMember("league", atoi(PQgetvalue(ret, i, 4)), allocator);
            object.AddMember("balance", atof(PQgetvalue(ret, i, 5)), allocator);
            object.AddMember("totalPredictions", atoi(PQgetvalue(ret, i, 6)), allocator);  // Include the count of predictions
            object.AddMember("fireballPoints", atoi(PQgetvalue(ret, i, 7)), allocator);
            object.AddMember("careerPoints", atoi(PQgetvalue(ret, i, 8)), allocator);

            int pos = CachedTable::Get()->GetPosition(id, league);
            object.AddMember("position", pos, allocator);
            int beatBetPos = CachedTable::Get()->GetBeatBetPosition(id);
            object.AddMember("beatBetPosition", beatBetPos, allocator);
            int fireballPos = CachedTable::Get()->GetFireballPosition(id);
            object.AddMember("fireballPosition", fireballPos, allocator);
            int careerPos = CachedTable::Get()->GetCareerPosition(id);
            object.AddMember("careerPosition", careerPos, allocator);

            {
                std::string awardsQuery = "SELECT place, season, league FROM awards WHERE user_id = " + std::to_string(id) + ";";
                PGresult* awardsRes = PQexec(pg, awardsQuery.c_str());

                if (PQresultStatus(awardsRes) != PGRES_TUPLES_OK)
                {
                    fprintf(stderr, "Failed to fetch awards: %s", PQerrorMessage(pg));
                    PQclear(awardsRes);
                }
                else
                {
                    int awardCount = PQntuples(awardsRes);
                    rapidjson::Value awards(rapidjson::kArrayType);

                    for (int j = 0; j < awardCount; ++j)
                    {
                        rapidjson::Value awardObj(rapidjson::kObjectType);

                        int place = atoi(PQgetvalue(awardsRes, j, 0));
                        char* season = PQgetvalue(awardsRes, j, 1);
                        int league = atoi(PQgetvalue(awardsRes, j, 2));

                        awardObj.AddMember("place", place, allocator);

                        rapidjson::Value seasonVal;
                        seasonVal.SetString(season, allocator);
                        awardObj.AddMember("season", seasonVal, allocator);
                        awardObj.AddMember("league", league, allocator);

                        awards.PushBack(awardObj, allocator);
                    }

                    object.AddMember("awards", awards, allocator);
                    PQclear(awardsRes);
                }

            }

            document.PushBack(object, allocator);

           // if (page == 1 && league == 1) mCachedTable.push_back(id);
        }

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetElTorneoTable()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        // Get the 'page' query parameter, default to 1 if not provided
        int page = 1;
        int league = 1;
        std::string season = "25_26";
        if (req.has_param("page"))
        {
            page = std::stoi(req.get_param_value("page"));
            page = std::max(page, 1);
        }
        if (req.has_param("league"))
        {
            league = std::stoi(req.get_param_value("league"));
        }
        if (req.has_param("season"))
        {
            season = req.get_param_value("season");
            std::replace(season.begin(), season.end(), '/', '_');
            if (season == "undefined") season = "25_26";
        }

        int limit = 20; // Number of users per page
        int offset = (page - 1) * limit; // Calculate the offset based on the page

        PGconn* pg = ConnectionPool::Get()->getConnection();
        if (!pg)
        {
            res.status = 500;
            return;
        }

        std::string predictsTableName = "predicts";
        std::string pointsColName = "u.points";
        std::string leagueColName = "u.eltorneo_league";

        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        long long timestamp = ms.count();
        long long ten_days_ms = 20LL * 24 * 60 * 60 * 1000;
        long long tsDiff = timestamp - ten_days_ms;

        std::string currentSeason = "25_26";
        bool isCurrentSeason = true;
        if (season != currentSeason)
        {
            isCurrentSeason = false;
            predictsTableName += "_" + season;
            pointsColName += "_" + season;
            leagueColName += "_" + season;
            tsDiff = 0;
        }

        // SQL query
        std::string sql =
            "SELECT u.id, u.name, u.avatar, "
            + pointsColName + " AS user_points, "
            + leagueColName + ", "
            "u.clear_balance, u.eltorneo_position, COUNT(p.id) AS total_predictions, "
            "u.beat_bet_league, u.beat_bet_position, "
            "fu.league, fu.position, "
            "cu.league, cu.position, "
            "COALESCE(fu.points, -1) AS fireball_points, "
            "COALESCE(cu.points, -1) AS career_points "
            "FROM users u "
            "INNER JOIN " + predictsTableName + " p ON u.id = p.user_id "
            "LEFT JOIN fireball_users fu ON fu.user_id = u.id "
            "LEFT JOIN career_users cu ON cu.user_id = u.id "
            "WHERE p.status != 4 "
            "AND " + leagueColName + " = " + std::to_string(league) + " "
            "AND u.last_predict_ts >= " + std::to_string(tsDiff) + " "
            "GROUP BY u.id, u.name, u.avatar, " + pointsColName + ", "
            + leagueColName + ", u.clear_balance, fu.points, cu.points, fu.league, fu.position, cu.league, cu.position "
            "HAVING COUNT(p.id) > 0 "
            "ORDER BY " + pointsColName + " DESC, total_predictions DESC, u.id ASC "
            "LIMIT " + std::to_string(limit) + " OFFSET " + std::to_string(offset) + ";";


        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch table by points: %s", PQerrorMessage(pg));
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
            int id = atoi(PQgetvalue(ret, i, 0));
            rapidjson::Value object(rapidjson::kObjectType);
            object.AddMember("id", id, allocator);
            object.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 1), allocator), allocator);
            object.AddMember("avatar", rapidjson::Value(PQgetvalue(ret, i, 2), allocator), allocator);
            object.AddMember("predictions", atoi(PQgetvalue(ret, i, 3)), allocator);
            object.AddMember("balance", atof(PQgetvalue(ret, i, 5)), allocator);

            int elTorneoLeague = atoi(PQgetvalue(ret, i, 4));
            if (elTorneoLeague < 1) elTorneoLeague = -1;
            object.AddMember("elTorneoLeague", elTorneoLeague, allocator);
            int elTorneoPosition = elTorneoLeague >= 1 ? atoi(PQgetvalue(ret, i, 6)) - (elTorneoLeague - 1) * 20 : -1;
            object.AddMember("elTorneoPosition", elTorneoPosition, allocator);
            object.AddMember("totalPredictions", atoi(PQgetvalue(ret, i, 7)), allocator);
            
            int beatBetLeague = atoi(PQgetvalue(ret, i, 8));
            if (beatBetLeague < 1) beatBetLeague = -1;
            int beatBetPosition = beatBetLeague >= 1 ? atoi(PQgetvalue(ret, i, 9)) - (beatBetLeague - 1) * 20 : -1;
            object.AddMember("beatBetLeague", beatBetLeague, allocator);
            object.AddMember("beatBetPosition", beatBetPosition, allocator);

            int fireballLeague = atoi(PQgetvalue(ret, i, 10));
            if (fireballLeague < 1) fireballLeague = -1;
            int fireballPosition = fireballLeague >= 1 ? atoi(PQgetvalue(ret, i, 11)) - (fireballLeague - 1) * 20 : -1;
            object.AddMember("fireballLeague", fireballLeague, allocator);
            object.AddMember("fireballPosition", fireballPosition, allocator);

            int careerLeague = atoi(PQgetvalue(ret, i, 12));
            if (careerLeague < 1) careerLeague = -1;
            int careerPosition = careerLeague >= 1 ? atoi(PQgetvalue(ret, i, 13)) - (careerLeague - 1) * 20 : -1;
            object.AddMember("careerLeague", careerLeague, allocator);
            object.AddMember("careerPosition", careerPosition, allocator);

            object.AddMember("fireballPoints", atoi(PQgetvalue(ret, i, 14)), allocator);
            object.AddMember("careerPoints", atoi(PQgetvalue(ret, i, 15)), allocator);

            {
                std::string awardsQuery = "SELECT place, season, league FROM awards WHERE user_id = " + std::to_string(id) + ";";
                PGresult* awardsRes = PQexec(pg, awardsQuery.c_str());

                if (PQresultStatus(awardsRes) != PGRES_TUPLES_OK)
                {
                    fprintf(stderr, "Failed to fetch awards: %s", PQerrorMessage(pg));
                    PQclear(awardsRes);
                }
                else
                {
                    int awardCount = PQntuples(awardsRes);
                    rapidjson::Value awards(rapidjson::kArrayType);

                    for (int j = 0; j < awardCount; ++j)
                    {
                        rapidjson::Value awardObj(rapidjson::kObjectType);

                        int place = atoi(PQgetvalue(awardsRes, j, 0));
                        char* season = PQgetvalue(awardsRes, j, 1);
                        int league = atoi(PQgetvalue(awardsRes, j, 2));

                        awardObj.AddMember("place", place, allocator);

                        rapidjson::Value seasonVal;
                        seasonVal.SetString(season, allocator);
                        awardObj.AddMember("season", seasonVal, allocator);
                        awardObj.AddMember("league", league, allocator);

                        awards.PushBack(awardObj, allocator);
                    }

                    object.AddMember("awards", awards, allocator);
                    PQclear(awardsRes);
                }

            }

            document.PushBack(object, allocator);
        }

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}


std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetBeatBetTable()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        // Get the 'page' query parameter, default to 1 if not provided
        int page = 1;
        int league = 1;
     //   std::string season = "25_26";
        if (req.has_param("page")) 
        {
            page = std::stoi(req.get_param_value("page"));
            page = std::max(page, 1);
        }
        if (req.has_param("league")) 
        {
            league = std::stoi(req.get_param_value("league"));
        }
      /*  if (req.has_param("season")) {
            season = req.get_param_value("season");
            std::replace(season.begin(), season.end(), '/', '_');
        }*/

        int limit = 20; // Number of users per page
        int offset = (page - 1) * limit; // Calculate the offset based on the page

        PGconn* pg = ConnectionPool::Get()->getConnection();
        if (!pg) 
        {
            res.status = 500;  // Internal Server Error
            return;
        }

        std::string predictsTableName = "bets";
        std::string pointsColName = "u.balance";
        std::string leagueColName = "u.league";

       /* std::string currentSeason = "25_26";
        if (season != currentSeason)
        {
            predictsTableName += "_" + season;
            pointsColName += "_" + season;
            leagueColName += "_" + season;
        }*/

        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        long long timestamp = ms.count();
        long long ten_days_ms = 20LL * 24 * 60 * 60 * 1000;

        // Updated SQL query to join users with predicts, count the total number of predictions per user, and paginate
        std::string sql =
            "SELECT u.id, u.name, u.avatar, u.points, u.league, u.balance, "
            "COUNT(p.id) AS total_predictions, "
            "COALESCE(fu.points, -1) AS fireball_points, "
            "COALESCE(cu.points, -1) AS career_points "
            "FROM users u "
            "INNER JOIN " + predictsTableName + " p ON u.id = p.user_id "
            "LEFT JOIN fireball_users fu ON fu.user_id = u.id "
            "LEFT JOIN career_users cu ON cu.user_id = u.id "
            "WHERE u.last_bet_ts >= " + std::to_string(timestamp - ten_days_ms) + " "
            "GROUP BY u.id, u.name, u.avatar, u.points, u.league, u.balance, fu.points, cu.points "
            "HAVING COUNT(p.id) > 0 "
            "ORDER BY " + pointsColName + " DESC, total_predictions DESC, u.id ASC "
            "LIMIT " + std::to_string(limit) + " OFFSET " + std::to_string(offset) + ";";


        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK) 
        {
            fprintf(stderr, "Failed to fetch bets table: %s", PQerrorMessage(pg));
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
            int id = atoi(PQgetvalue(ret, i, 0));
            rapidjson::Value object(rapidjson::kObjectType);
            object.AddMember("id", id, allocator);
            object.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 1), allocator), allocator);
            object.AddMember("avatar", rapidjson::Value(PQgetvalue(ret, i, 2), allocator), allocator);
            object.AddMember("predictions", atoi(PQgetvalue(ret, i, 3)), allocator);
            object.AddMember("league", atoi(PQgetvalue(ret, i, 4)), allocator);
            object.AddMember("balance", atof(PQgetvalue(ret, i, 5)), allocator);
            object.AddMember("totalPredictions", atoi(PQgetvalue(ret, i, 6)), allocator);  // Include the count of predictions
            object.AddMember("fireballPoints", atoi(PQgetvalue(ret, i, 7)), allocator);
            object.AddMember("careerPoints", atoi(PQgetvalue(ret, i, 8)), allocator);

            int pos = CachedTable::Get()->GetPosition(id, league);
            object.AddMember("position", pos, allocator);
            int beatBetPos = CachedTable::Get()->GetBeatBetPosition(id);
            object.AddMember("beatBetPosition", beatBetPos, allocator);
            int fbPos = CachedTable::Get()->GetFireballPosition(id);
            object.AddMember("fireballPosition", fbPos, allocator);
            int cPos = CachedTable::Get()->GetCareerPosition(id);
            object.AddMember("careerPosition", cPos, allocator);

           {
                std::string awardsQuery = "SELECT place, season, league FROM awards WHERE user_id = " + std::to_string(id) + ";";
                PGresult* awardsRes = PQexec(pg, awardsQuery.c_str());

                if (PQresultStatus(awardsRes) != PGRES_TUPLES_OK)
                {
                    fprintf(stderr, "Failed to fetch awards: %s", PQerrorMessage(pg));
                    PQclear(awardsRes);
                }
                else
                {
                    int awardCount = PQntuples(awardsRes);
                    rapidjson::Value awards(rapidjson::kArrayType);

                    for (int j = 0; j < awardCount; ++j)
                    {
                        rapidjson::Value awardObj(rapidjson::kObjectType);

                        int place = atoi(PQgetvalue(awardsRes, j, 0));
                        char* season = PQgetvalue(awardsRes, j, 1);
                        int league = atoi(PQgetvalue(awardsRes, j, 2));

                        awardObj.AddMember("place", place, allocator);

                        rapidjson::Value seasonVal;
                        seasonVal.SetString(season, allocator);
                        awardObj.AddMember("season", seasonVal, allocator);
                        awardObj.AddMember("league", league, allocator);

                        awards.PushBack(awardObj, allocator);
                    }

                    object.AddMember("awards", awards, allocator);
                    PQclear(awardsRes);
                }

            }
            
            document.PushBack(object, allocator);

            // if (page == 1 && league == 1) mCachedTable.push_back(id);
        }

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetBeatBetTableV2()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        // Get the 'page' query parameter, default to 1 if not provided
        int page = 1;
        int league = 1;
        //   std::string season = "25_26";
        if (req.has_param("page"))
        {
            page = std::stoi(req.get_param_value("page"));
            page = std::max(page, 1);
        }
        if (req.has_param("league"))
        {
            league = std::stoi(req.get_param_value("league"));
        }
        /*  if (req.has_param("season")) {
              season = req.get_param_value("season");
              std::replace(season.begin(), season.end(), '/', '_');
          }*/

        int limit = 20; // Number of users per page
        int offset = (page - 1) * limit; // Calculate the offset based on the page

        PGconn* pg = ConnectionPool::Get()->getConnection();
        if (!pg)
        {
            res.status = 500;  // Internal Server Error
            return;
        }

        std::string predictsTableName = "bets";

        /* std::string currentSeason = "25_26";
         if (season != currentSeason)
         {
             predictsTableName += "_" + season;
         }*/

        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        long long timestamp = ms.count();
        long long ten_days_ms = 20LL * 24 * 60 * 60 * 1000;

        // Updated SQL query to join users with predicts, count the total number of predictions per user, and paginate
        std::string sql =
            "SELECT u.id, u.name, u.avatar, u.points, u.clear_balance, "
            "u.eltorneo_league, u.eltorneo_position, "
            "u.beat_bet_league, u.beat_bet_position, "
            "fu.league, fu.position, "
            "cu.league, cu.position, "
            "COUNT(p.id) AS total_predictions, "
            "COALESCE(fu.points, -1) AS fireball_points, "
            "COALESCE(cu.points, -1) AS career_points "
            "FROM users u "
            "INNER JOIN " + predictsTableName + " p ON u.id = p.user_id "
            "LEFT JOIN fireball_users fu ON fu.user_id = u.id "
            "LEFT JOIN career_users cu ON cu.user_id = u.id "
            "WHERE u.last_bet_ts >= " + std::to_string(timestamp - ten_days_ms) + " "
            "AND u.beat_bet_league = " + std::to_string(league) + " "
            "GROUP BY u.id, u.name, u.avatar, u.points, u.beat_bet_league, u.clear_balance, "
            "fu.points, cu.points, fu.league, fu.position, cu.league, cu.position "
            "HAVING COUNT(p.id) > 0 "
            "ORDER BY u.clear_balance DESC, total_predictions DESC, u.id ASC "
            "LIMIT " + std::to_string(limit) + " OFFSET " + std::to_string(offset) + ";";


        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch bets table V2: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Value table;
        table.SetArray();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        for (int i = 0; i < nrows; ++i)
        {
            int id = atoi(PQgetvalue(ret, i, 0));
            rapidjson::Value object(rapidjson::kObjectType);
            object.AddMember("id", id, allocator);
            object.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 1), allocator), allocator);
            object.AddMember("avatar", rapidjson::Value(PQgetvalue(ret, i, 2), allocator), allocator);
            object.AddMember("predictions", atoi(PQgetvalue(ret, i, 3)), allocator);
            object.AddMember("balance", atof(PQgetvalue(ret, i, 4)), allocator);

            int elTorneoLeague = atoi(PQgetvalue(ret, i, 5));
            if (elTorneoLeague < 1) elTorneoLeague = -1;
            int elTorneoPosition = elTorneoLeague >= 1 ? atoi(PQgetvalue(ret, i, 6)) - (elTorneoLeague - 1) * 20 : -1;
            object.AddMember("elTorneoLeague", elTorneoLeague, allocator);
            object.AddMember("elTorneoPosition", elTorneoPosition, allocator);

            int beatBetLeague = atoi(PQgetvalue(ret, i, 7));
            if (beatBetLeague < 1) beatBetLeague = -1;
            int beatBetPosition = beatBetLeague >= 1 ? atoi(PQgetvalue(ret, i, 8)) - (beatBetLeague - 1) * 20 : -1;
            object.AddMember("beatBetLeague", beatBetLeague, allocator);
            object.AddMember("beatBetPosition", beatBetPosition, allocator);

            int fireballLeague = atoi(PQgetvalue(ret, i, 9));
            if (fireballLeague < 1) fireballLeague = -1;
            int fireballPosition = fireballLeague >= 1 ? atoi(PQgetvalue(ret, i, 10)) - (fireballLeague - 1) * 20 : -1;
            object.AddMember("fireballLeague", fireballLeague, allocator);
            object.AddMember("fireballPosition", fireballPosition, allocator);

            int careerLeague = atoi(PQgetvalue(ret, i, 11));
            if (careerLeague < 1) careerLeague = -1;
            int careerPosition = careerLeague >= 1 ? atoi(PQgetvalue(ret, i, 12)) - (careerLeague - 1) * 20 : -1;
            object.AddMember("careerLeague", careerLeague, allocator);
            object.AddMember("careerPosition", careerPosition, allocator);

            object.AddMember("totalPredictions", atoi(PQgetvalue(ret, i, 13)), allocator);  // Include the count of predictions
            object.AddMember("fireballPoints", atoi(PQgetvalue(ret, i, 14)), allocator);
            object.AddMember("careerPoints", atoi(PQgetvalue(ret, i, 15)), allocator);

            {
                std::string awardsQuery = "SELECT place, season, league FROM awards WHERE user_id = " + std::to_string(id) + ";";
                PGresult* awardsRes = PQexec(pg, awardsQuery.c_str());

                if (PQresultStatus(awardsRes) != PGRES_TUPLES_OK)
                {
                    fprintf(stderr, "Failed to fetch awards: %s", PQerrorMessage(pg));
                    PQclear(awardsRes);
                }
                else
                {
                    int awardCount = PQntuples(awardsRes);
                    rapidjson::Value awards(rapidjson::kArrayType);

                    for (int j = 0; j < awardCount; ++j)
                    {
                        rapidjson::Value awardObj(rapidjson::kObjectType);

                        int place = atoi(PQgetvalue(awardsRes, j, 0));
                        char* season = PQgetvalue(awardsRes, j, 1);
                        int league = atoi(PQgetvalue(awardsRes, j, 2));

                        awardObj.AddMember("place", place, allocator);

                        rapidjson::Value seasonVal;
                        seasonVal.SetString(season, allocator);
                        awardObj.AddMember("season", seasonVal, allocator);
                        awardObj.AddMember("league", league, allocator);

                        awards.PushBack(awardObj, allocator);
                    }

                    object.AddMember("awards", awards, allocator);
                    PQclear(awardsRes);
                }

            }

            table.PushBack(object, allocator);

            // if (page == 1 && league == 1) mCachedTable.push_back(id);
        }
        document.AddMember("table", table, allocator);

        sql =
            "SELECT COUNT(*) AS total_users "
            "FROM ( "
            "    SELECT u.id "
            "    FROM users u "
            "    INNER JOIN " + predictsTableName + " p ON u.id = p.user_id "
            "    WHERE u.last_bet_ts >= " + std::to_string(timestamp - ten_days_ms) + " "
            "    GROUP BY u.id "
            "    HAVING COUNT(p.id) > 0 "
            ") AS subquery;";
        PGresult* totalRet = PQexec(pg, sql.c_str());
        int totalUsers = atoi(PQgetvalue(totalRet, 0, 0));
        document.AddMember("numUsers", totalUsers, allocator);
        PQclear(totalRet);
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}


std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetTableByScore()
{
    return [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        PGconn* pg = ConnectionPool::Get()->getConnection();
        if (!pg)
        {
            res.status = 500;  // Internal Server Error
            return;
        }

        std::string league_id = req.get_param_value("league_id");
        int lid = std::stoi(league_id);  // Convert league_id to integer

        // Base SQL
        std::string sql = "SELECT u.id, u.name, u.avatar, "
            "SUM(CASE WHEN p.status = 2 THEN 1 ELSE 0 END) AS status_2_count, "
            "COUNT(p.*) AS total_predictions, "
            "ROUND((CAST(SUM(CASE WHEN p.status = 2 THEN 1 ELSE 0 END) AS DECIMAL) / COUNT(p.*)) * 100, 2) AS success_rate "
            "FROM predicts p "
            "JOIN users u ON p.user_id = u.id "
            "JOIN matches m ON p.match_id = m.id ";

        // Adding league filter if league_id is greater than 1
        if (lid >= 1) 
        {
            sql += "WHERE m.league = " + std::to_string(lid) + " ";
        }

        sql += "GROUP BY u.id, u.name, u.avatar "
            "ORDER BY success_rate DESC, status_2_count DESC "
            "LIMIT 20;";

        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK) 
        {
            fprintf(stderr, "Failed to fetch user predictions: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetArray();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        for (int i = 0; i < nrows; ++i) {
            rapidjson::Value object(rapidjson::kObjectType);
            object.AddMember("user_id", atoi(PQgetvalue(ret, i, 0)), allocator);
            object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 1)), allocator);
            object.AddMember("avatar", rapidjson::StringRef(PQgetvalue(ret, i, 2)), allocator);
            object.AddMember("predictions", atoi(PQgetvalue(ret, i, 3)), allocator);
            object.AddMember("totalPredictions", atoi(PQgetvalue(ret, i, 4)), allocator);
            object.AddMember("rate", atof(PQgetvalue(ret, i, 5)), allocator);

            document.PushBack(object, allocator);
        }

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}



std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetTableByWinner()
{
    return [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        PGconn* pg = ConnectionPool::Get()->getConnection();
        if (!pg) {
            res.status = 500;  // Internal Server Error
            return;
        }

        std::string league_id = req.get_param_value("league_id");
        int lid = std::stoi(league_id);  // Convert league_id to integer

        // Base SQL
        std::string sql = "SELECT u.id, u.name, u.avatar, "
            "SUM(CASE WHEN p.status = 1 OR p.status = 2 THEN 1 ELSE 0 END) AS successful_count, "
            "COUNT(p.*) AS total_predictions, "
            "ROUND((CAST(SUM(CASE WHEN p.status = 1 OR p.status = 2 THEN 1 ELSE 0 END) AS DECIMAL) / COUNT(p.*)) * 100, 2) AS success_rate "
            "FROM predicts p "
            "JOIN users u ON p.user_id = u.id "
            "JOIN matches m ON p.match_id = m.id ";

        // Adding league filter if league_id is greater than 1
        if (lid >= 1) {
            sql += "WHERE m.league = " + std::to_string(lid) + " ";
        }

        sql += "GROUP BY u.id, u.name, u.avatar "
            "ORDER BY success_rate DESC, successful_count DESC "
            "LIMIT 20;";

        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK) {
            fprintf(stderr, "Failed to fetch user predictions: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetArray();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        for (int i = 0; i < nrows; ++i) {
            rapidjson::Value object(rapidjson::kObjectType);
            object.AddMember("user_id", atoi(PQgetvalue(ret, i, 0)), allocator);
            object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 1)), allocator);
            object.AddMember("avatar", rapidjson::StringRef(PQgetvalue(ret, i, 2)), allocator);
            object.AddMember("predictions", atoi(PQgetvalue(ret, i, 3)), allocator);
            object.AddMember("totalPredictions", atoi(PQgetvalue(ret, i, 4)), allocator);
            object.AddMember("rate", atof(PQgetvalue(ret, i, 5)), allocator);

            document.PushBack(object, allocator);
        }

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::PostBet()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "POST");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        rapidjson::Document document;
        document.Parse(req.body.c_str());

        std::string token = req.get_header_value("Authentication");
        if (!token.size())
        {
            res.status = 500; // Internal Server Error
            return;
        }

        auto decoded = jwt::decode(token);
        int userId = decoded.get_payload_claim("id").as_int();

        int matchId = document["match"].GetInt();
        std::string bet = document["bet"].GetString();
        int amount = document["amount"].GetInt();
        float odd;

        // Connect to the database
        PGconn* pg = ConnectionPool::Get()->getConnection();
        {
            std::string sql = "select id from bets where user_id = "
                + std::to_string(userId) + " AND match_id = " + std::to_string(matchId) + ";";
            PGresult* ret = PQexec(pg, sql.c_str());
            if (PQresultStatus(ret) != PGRES_TUPLES_OK && PQresultStatus(ret) != PGRES_COMMAND_OK)
            {
                fprintf(stderr, "Failed to get bet: %s", PQerrorMessage(pg));
                PQclear(ret);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 500; // Internal Server Error
                return;
            }

            int n = PQntuples(ret);
            if (n > 0)
            {
                fprintf(stderr, "Failed to add user Bet: Exists! %s\n", PQerrorMessage(pg));
                PQclear(ret);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 500; // Internal Server Error
                return;
            }
            PQclear(ret);
        }

        {
            std::string sql = "SELECT " + bet + " FROM odds WHERE match_id = " +
                std::to_string(matchId) + ";";

            PGresult* ret = PQexec(pg, sql.c_str());
            if (PQresultStatus(ret) != PGRES_TUPLES_OK && PQresultStatus(ret) != PGRES_COMMAND_OK)
            {
                fprintf(stderr, "Failed to get bet odd: %s", PQerrorMessage(pg));
                PQclear(ret);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 500; // Internal Server Error
                return;
            }

            odd = atof(PQgetvalue(ret, 0, 0));
            PQclear(ret);
        }

        int isSpecial = false;
        {
            std::string sql = "SELECT is_special FROM matches WHERE id = " + std::to_string(matchId) + ";";
            PGresult* specialRet = PQexec(pg, sql.c_str());
            isSpecial = atoi(PQgetvalue(specialRet, 0, 0));
            PQclear(specialRet);
        }

        if (!isSpecial)
        {
            amount = std::max(10, amount);
            amount = std::min(20, amount);
        }
        else
        {
            amount = 20;
        }

        std::string sql = "INSERT INTO bets(user_id, match_id, bet, amount, odd, status) VALUES("
            + std::to_string(userId) + ", "
            + std::to_string(matchId) + ", '"
            + bet + "', "
            + std::to_string(amount) + ", "
            + std::to_string(odd) + ", "
            + "0"
            + ") RETURNING id";  // Return the inserted ID

        // Execute the insert and capture the inserted predict ID
        PGresult* ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_TUPLES_OK && PQresultStatus(ret) != PGRES_COMMAND_OK) 
        {
            fprintf(stderr, "Failed to add bet: %s\n", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500; // Internal Server Error
            return;
        }

        {
            sql = "UPDATE USERS SET balance = balance - " + std::to_string(amount)
                + " WHERE id = " + std::to_string(userId) + ";";

            PGresult* amountRet = PQexec(pg, sql.c_str());
            if (PQresultStatus(amountRet) != PGRES_TUPLES_OK && PQresultStatus(amountRet) != PGRES_COMMAND_OK) 
            {
                fprintf(stderr, "Failed to add amount: %s", PQerrorMessage(pg));
                PQclear(amountRet);
                PQclear(ret);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 500; // Internal Server Error
                return;
            }
            PQclear(amountRet);
        }
        {
            auto now = std::chrono::system_clock::now();
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
            long long timestamp = ms.count();
            sql = "UPDATE users SET last_bet_ts = " + std::to_string(timestamp) + " WHERE id = " + std::to_string(userId) + ";";
            PGresult* tsRet = PQexec(pg, sql.c_str());
            PQclear(tsRet);
        }

        // Get the inserted ID
        int insertedId = std::stoi(PQgetvalue(ret, 0, 0));

        // Clear result and release connection
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);

        // Create a JSON response with the inserted ID
        rapidjson::Document responseDoc;
        responseDoc.SetObject();
        responseDoc.AddMember("bet_id", insertedId, responseDoc.GetAllocator());

        // Convert the document to a string
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        responseDoc.Accept(writer);

        // Send response
        res.set_content(buffer.GetString(), "application/json");
        res.status = 201; // Created
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::PostPredict()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "POST");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        rapidjson::Document document;
        document.Parse(req.body.c_str());

        std::string token = req.get_header_value("Authentication");
        auto decoded = jwt::decode(token);
        int userId = decoded.get_payload_claim("id").as_int();

        int matchId = document["match"].GetInt();
        int team1 = document["team1_score"].GetInt();
        int team2 = document["team2_score"].GetInt();

        // Connect to the database
        PGconn* pg = ConnectionPool::Get()->getConnection();
        {
            std::string sql = "select id from predicts where user_id = "
                + std::to_string(userId) + " AND match_id = " + std::to_string(matchId) + ";";
            PGresult* ret = PQexec(pg, sql.c_str());
            if (PQresultStatus(ret) != PGRES_TUPLES_OK && PQresultStatus(ret) != PGRES_COMMAND_OK) 
            {
                fprintf(stderr, "Failed to add predict: %s\n", PQerrorMessage(pg));
                PQclear(ret);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 500; // Internal Server Error
                return;
            }

            int n = PQntuples(ret);
            if (n > 0) 
            {
                fprintf(stderr, "Failed to add predict: Exists! UserId = %i, MatchId = %i %s\n", userId, matchId, PQerrorMessage(pg));
                PQclear(ret);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 500; // Internal Server Error
                return;
            }
        }
        if ((team1 == 1 && team2 == 2) || (team1 == 2 && team2 == 1))
        {
            std::string sql = "SELECT "
                "CAST(COUNT(*) FILTER (WHERE (team1_score = 1 AND team2_score = 2) OR (team1_score = 2 AND team2_score = 1)) AS float) / "
                "NULLIF(COUNT(*), 0) AS ratio "
                "FROM predicts "
                "WHERE user_id = " + std::to_string(userId) + ";";

            PGresult* ret = PQexec(pg, sql.c_str());
            const char* val = PQgetvalue(ret, 0, 0);
            float ratio = 0.0f;
            if (val && strlen(val) > 0) 
                ratio = std::stof(val);  // Safe to convert
            else 
                ratio = 0.0f;  // Or you could set it to NAN, etc.
            if (ratio > 0.6f) 
            {
                PQclear(ret);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 403; 
                return;
            }
        }
        std::string sql = "INSERT INTO predicts(user_id, match_id, team1_score, team2_score, status) VALUES("
            + std::to_string(userId) + ", "
            + std::to_string(matchId) + ", "
            + std::to_string(team1) + ", "
            + std::to_string(team2) + ", "
            + "0"
            + ") RETURNING id";  // Return the inserted ID

        // Execute the insert and capture the inserted predict ID
        PGresult* ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_TUPLES_OK && PQresultStatus(ret) != PGRES_COMMAND_OK) {
            fprintf(stderr, "Failed to add predict: %s\n", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500; // Internal Server Error
            return;
        }

        {
            auto now = std::chrono::system_clock::now();
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
            long long timestamp = ms.count();
            sql = "UPDATE users SET last_predict_ts = " + std::to_string(timestamp) + " WHERE id = " + std::to_string(userId) + ";";
            PGresult* tsRet = PQexec(pg, sql.c_str());
            PQclear(tsRet);
        }

        // Get the inserted ID
        int insertedId = std::stoi(PQgetvalue(ret, 0, 0));

        // Clear result and release connection
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);

        // Create a JSON response with the inserted ID
        rapidjson::Document responseDoc;
        responseDoc.SetObject();
        responseDoc.AddMember("predict_id", insertedId, responseDoc.GetAllocator());

        // Convert the document to a string
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        responseDoc.Accept(writer);

        // Send response
        res.set_content(buffer.GetString(), "application/json");
        res.status = 201; // Created
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::DeleteBet()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "DELETE");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        std::string token = req.get_header_value("Authentication");
        auto decoded = jwt::decode(token);
        int userId = decoded.get_payload_claim("id").as_int();
        std::string betId = req.get_param_value("bet_id");

        std::string sql = "SELECT amount, match_id FROM bets WHERE user_id = " + std::to_string(userId)
            + " AND id = " + betId + ";";
        PGconn* pg = ConnectionPool::Get()->getConnection();
        PGresult* ret = PQexec(pg, sql.c_str());
        int amount = atoi(PQgetvalue(ret, 0, 0));
        int matchId = atoi(PQgetvalue(ret, 0, 1));

        PQclear(ret);

        {
            sql = "UPDATE users set balance = balance + " + std::to_string(amount) + " WHERE id = " + std::to_string(userId) + ";";
            ret = PQexec(pg, sql.c_str());
            PQclear(ret);
        }

        sql = "DELETE FROM bets WHERE user_id = " + std::to_string(userId)
            + " AND id = " + betId + ";";
        ret = PQexec(pg, sql.c_str());
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
        res.status = 200;
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::EditPredict()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "POST");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        rapidjson::Document document;
        document.Parse(req.body.c_str());

        std::string token = req.get_header_value("Authentication");
        auto decoded = jwt::decode(token);
        int userId = decoded.get_payload_claim("id").as_int();
        if (!document.HasMember("predict"))
        {
            res.status = 500; // Internal Server Error
            return;
        }
        int predictId = document["predict"].GetInt();
        int team1 = document["team1_score"].GetInt();
        int team2 = document["team2_score"].GetInt();

        PGconn* pg = ConnectionPool::Get()->getConnection();
        if ((team1 == 1 && team2 == 2) || (team1 == 2 && team2 == 1))
        {
            std::string sql = "SELECT "
                "CAST(COUNT(*) FILTER (WHERE (team1_score = 1 AND team2_score = 2) OR (team1_score = 2 AND team2_score = 1)) AS float) / "
                "NULLIF(COUNT(*), 0) AS ratio "
                "FROM predicts "
                "WHERE user_id = " + std::to_string(userId) + ";";

            PGresult* ret = PQexec(pg, sql.c_str());
            const char* val = PQgetvalue(ret, 0, 0);
            float ratio = 0.0f;
            if (val && strlen(val) > 0)
                ratio = std::stof(val);  // Safe to convert
            else
                ratio = 0.0f;  // Or you could set it to NAN, etc.
            if (ratio > 0.6f)
            {
                PQclear(ret);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 403;
                return;
            }

        }

        // Connect to the database
        std::string sql = "UPDATE predicts set team1_score = " + std::to_string(team1)
            + ", team2_score = " + std::to_string(team2)
            + " WHERE id = " + std::to_string(predictId)
            + " AND user_id = " + std::to_string(userId)
            + ";";

        // Execute the insert and capture the team ID
        PGresult* ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_COMMAND_OK)
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

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::PostFireballPredict()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "POST");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        rapidjson::Document document;
        document.Parse(req.body.c_str());

        std::string token = req.get_header_value("Authentication");
        auto decoded = jwt::decode(token);
        int userId = decoded.get_payload_claim("id").as_int();

        int matchId = document["matchId"].GetInt();
        int teamId = document["teamId"].GetInt();
        int playerApiId = document["playerApiId"].GetInt();
        std::string playerName = document["playerName"].GetString();
        std::string playerPhoto = document["playerPhoto"].GetString();

        // Connect to the database
        PGconn* pg = ConnectionPool::Get()->getConnection();
        {
            std::string sql = "select id from fireball_predicts where user_id = "
                + std::to_string(userId) + " AND match_id = " + std::to_string(matchId) + ";";
            PGresult* ret = PQexec(pg, sql.c_str());
            if (PQresultStatus(ret) != PGRES_TUPLES_OK && PQresultStatus(ret) != PGRES_COMMAND_OK)
            {
                fprintf(stderr, "Failed to add fireball predict: Option 1: %s\n", PQerrorMessage(pg));
                PQclear(ret);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 500; // Internal Server Error
                return;
            }

            int n = PQntuples(ret);
            if (n > 0)
            {
                fprintf(stderr, "Failed to add fireball predict: Option 2: %s\n", PQerrorMessage(pg));
                PQclear(ret);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 500; // Internal Server Error
                return;
            }
        }
       
        std::string sql = "INSERT INTO fireball_predicts(user_id, match_id, team_id, player_api_id, player_name, player_photo) VALUES("
            + std::to_string(userId) + ", "
            + std::to_string(matchId) + ", "
            + std::to_string(teamId) + ", "
            + std::to_string(playerApiId) + ", '"
            + playerName + "', '" 
            + playerPhoto + "' "
            + ") RETURNING id";  // Return the inserted ID

        // Execute the insert and capture the inserted predict ID
        PGresult* ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_TUPLES_OK && PQresultStatus(ret) != PGRES_COMMAND_OK) 
        {
            fprintf(stderr, "Failed to add fireball predict: Option 3: %s\n", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500; // Internal Server Error
            return;
        }

        {
            auto now = std::chrono::system_clock::now();
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
            long long timestamp = ms.count();
            sql = "UPDATE fireball_users SET last_predict_ts = " + std::to_string(timestamp) + " WHERE user_id = " + std::to_string(userId) + ";";
            PGresult* tsRet = PQexec(pg, sql.c_str());
            PQclear(tsRet);
        }

        {
            std::string sql =
                "INSERT INTO fireball_users (user_id) VALUES (" + std::to_string(userId) + ") "
                "ON CONFLICT (user_id) DO NOTHING;";
            PGresult* tsRet = PQexec(pg, sql.c_str());
            PQclear(tsRet);
        }

        // Get the inserted ID
        int insertedId = std::stoi(PQgetvalue(ret, 0, 0));

        // Clear result and release connection
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);

        // Create a JSON response with the inserted ID
        rapidjson::Document responseDoc;
        responseDoc.SetObject();
        responseDoc.AddMember("predict_id", insertedId, responseDoc.GetAllocator());

        // Convert the document to a string
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        responseDoc.Accept(writer);

        // Send response
        res.set_content(buffer.GetString(), "application/json");
        res.status = 201; // Created
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetUserFireballPredict()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        std::string matchId = req.get_param_value("match_id");
        std::string season = "";
        /*if (req.has_param("season"))
        {
            season = req.get_param_value("season");
        }*/
        std::string postfix = "";
        /*if (season.size())
        {
            std::string currentSeason = "25/26";
            if (season != currentSeason)
            {
                std::replace(season.begin(), season.end(), '/', '_');
                postfix = "_" + season;
            }
        }*/

        std::string token = req.get_header_value("Authentication");
        auto decoded = jwt::decode(token);
        int userId = decoded.get_payload_claim("id").as_int();

        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string sql = "SELECT * FROM fireball_predicts" + postfix + " WHERE user_id = "
            + std::to_string(userId) + " AND match_id = "
            + matchId
            + ";";
        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch user fireball predict: %s", PQerrorMessage(pg));
            PQclear(ret);
            res.status = 500;  // Internal Server Error
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        char* temp = (char*)calloc(4096, sizeof(char));

        for (int i = 0; i < nrows; ++i)
        {
            // Handle ID as integer
            int id = atoi(PQgetvalue(ret, i, 0)); // Convert the string from the first column to an integer
            rapidjson::Value idValue;
            idValue.SetInt(id);
            document.AddMember("id", idValue, allocator);

            int userId = atoi(PQgetvalue(ret, i, 1));
            idValue.SetInt(userId);
            document.AddMember("user_id", idValue, allocator);

            int matchId = atoi(PQgetvalue(ret, i, 2));
            idValue.SetInt(matchId);
            document.AddMember("match_id", idValue, allocator);

            int teamId = atoi(PQgetvalue(ret, i, 3));
            idValue.SetInt(teamId);
            document.AddMember("team_id", idValue, allocator);

            int player_api_id = atoi(PQgetvalue(ret, i, 4));
            idValue.SetInt(player_api_id);
            document.AddMember("player_api_id", idValue, allocator);

            std::string playerName = (PQgetvalue(ret, i, 5));
            idValue.SetString(playerName.c_str(), allocator);
            document.AddMember("player_name", idValue, allocator);

            std::string playerPhoto = (PQgetvalue(ret, i, 6));
            idValue.SetString(playerPhoto.c_str(), allocator);
            document.AddMember("player_photo", idValue, allocator);

            int goals = atoi(PQgetvalue(ret, i, 7));
            idValue.SetInt(goals);
            document.AddMember("goals", idValue, allocator);

            int status = atoi(PQgetvalue(ret, i, 8));
            idValue.SetInt(status);
            document.AddMember("status", idValue, allocator);
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

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetMatchFireballTop20()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        std::string matchId = req.get_param_value("match_id");std::string season = "";
        /*if (req.has_param("season"))
        {
            season = req.get_param_value("season");
        }*/
        std::string postfix = "";
        /*if (season.size())
        {
            std::string currentSeason = "25/26";
            if (season != currentSeason)
            {
                std::replace(season.begin(), season.end(), '/', '_');
                postfix = "_" + season;
            }
        }*/

        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string sql = "SELECT p.*, u.name, u.avatar, fu.points, u.points, u.balance, u.league FROM fireball_predicts p "
            "JOIN users u ON p.user_id = u.id "
            "JOIN fireball_users fu ON p.user_id = fu.user_id "
            "WHERE p.match_id = " + matchId + " "
            "ORDER BY fu.points DESC LIMIT 20;";
        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch top fireball predicts: %s", PQerrorMessage(pg));
            PQclear(ret);
            res.status = 500;  // Internal Server Error
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        rapidjson::Value predicts;
        predicts.SetArray();

        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        for (int i = 0; i < nrows; ++i)
        {
            rapidjson::Value object;
            object.SetObject();

            int id = atoi(PQgetvalue(ret, i, 0));
            int userId = atoi(PQgetvalue(ret, i, 1));
            int matchId = atoi(PQgetvalue(ret, i, 2));
            int teamId = atoi(PQgetvalue(ret, i, 3));
            int playerApiId = atoi(PQgetvalue(ret, i, 4));
            std::string playerName = PQgetvalue(ret, i, 5);
            std::string playerPhoto = PQgetvalue(ret, i, 6);
            int goals = atoi(PQgetvalue(ret, i, 7));
            int status = atoi(PQgetvalue(ret, i, 8));

            std::string userName = PQgetvalue(ret, i, 9);
            std::string userAvatar = PQgetvalue(ret, i, 10);

            int fireballPoints = atoi(PQgetvalue(ret, i, 11));
            int points = atoi(PQgetvalue(ret, i, 12));
            float balance = atof(PQgetvalue(ret, i, 13));
            int league = atoi(PQgetvalue(ret, i, 14));

            // Add user info and position to the JSON object
            rapidjson::Value userObject;
            userObject.SetObject();
            userObject.AddMember("id", userId, allocator);
            rapidjson::Value nameVal;
            nameVal.SetString(userName.c_str(), allocator);
            userObject.AddMember("name", nameVal, allocator);
            nameVal.SetString(userAvatar.c_str(), allocator);
            userObject.AddMember("avatar", nameVal, allocator);
            userObject.AddMember("fireballPoints", fireballPoints, allocator);
            userObject.AddMember("points", points, allocator);
            userObject.AddMember("balance", balance, allocator);

            int posi = CachedTable::Get()->GetFireballPosition(userId);
            userObject.AddMember("fireballPosition", posi, allocator);

            int pos = CachedTable::Get()->GetPosition(userId, league);
            userObject.AddMember("position", pos, allocator);

            int bbpos = CachedTable::Get()->GetBeatBetPosition(userId);
            userObject.AddMember("beatBetPosition", bbpos, allocator);

            {
                std::string awardsQuery = "SELECT place, season, league FROM awards WHERE user_id = " + std::to_string(userId) + ";";
                PGresult* awardsRes = PQexec(pg, awardsQuery.c_str());

                if (PQresultStatus(awardsRes) != PGRES_TUPLES_OK)
                {
                    fprintf(stderr, "Failed to fetch awards: %s", PQerrorMessage(pg));
                    PQclear(awardsRes);
                }
                else
                {
                    int awardCount = PQntuples(awardsRes);
                    rapidjson::Value awards(rapidjson::kArrayType);

                    for (int j = 0; j < awardCount; ++j)
                    {
                        rapidjson::Value awardObj(rapidjson::kObjectType);

                        int place = atoi(PQgetvalue(awardsRes, j, 0));
                        char* season = PQgetvalue(awardsRes, j, 1);
                        int league = atoi(PQgetvalue(awardsRes, j, 2));

                        awardObj.AddMember("place", place, allocator);

                        rapidjson::Value seasonVal;
                        seasonVal.SetString(season, allocator);
                        awardObj.AddMember("season", seasonVal, allocator);
                        awardObj.AddMember("league", league, allocator);

                        awards.PushBack(awardObj, allocator);
                    }

                    userObject.AddMember("awards", awards, allocator);
                    PQclear(awardsRes);
                }
            }

            object.AddMember("id", id, allocator);
            object.AddMember("user", userObject, allocator);
            object.AddMember("match_id", matchId, allocator);
            object.AddMember("team_id", teamId, allocator);
            object.AddMember("player_api_id", playerApiId, allocator);
            rapidjson::Value sVal;
            sVal.SetString(playerName.c_str(), allocator);
            object.AddMember("player_name", sVal, allocator);
            sVal.SetString(playerPhoto.c_str(), allocator);
            object.AddMember("player_photo", sVal, allocator);
            object.AddMember("goals", goals, allocator);
            object.AddMember("status", status, allocator);

            predicts.PushBack(object, allocator);
        }

        document.AddMember("predicts", predicts, allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;  // OK

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetMatchFireballTop20V2()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        std::string matchId = req.get_param_value("match_id");std::string season = "";
        /*if (req.has_param("season"))
        {
            season = req.get_param_value("season");
        }*/
        std::string postfix = "";
        /*if (season.size())
        {
            std::string currentSeason = "25/26";
            if (season != currentSeason)
            {
                std::replace(season.begin(), season.end(), '/', '_');
                postfix = "_" + season;
            }
        }*/

        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string sql = "SELECT p.*, u.name, u.avatar, fu.points, u.points, u.clear_balance, "
            "u.eltorneo_league, u.eltorneo_position, "
            "u.beat_bet_league, u.beat_bet_position, "
            "fu.league, fu.position, "
            "cu.league, cu.position "
            "FROM fireball_predicts p "
            "JOIN users u ON p.user_id = u.id "
            "JOIN fireball_users fu ON p.user_id = fu.user_id "
            "LEFT JOIN career_users cu ON cu.user_id = u.id "
            "WHERE p.match_id = " + matchId + " "
            "ORDER BY fu.points DESC LIMIT 20;";
        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch top fireball predicts: %s", PQerrorMessage(pg));
            PQclear(ret);
            res.status = 500;  // Internal Server Error
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        rapidjson::Value predicts;
        predicts.SetArray();

        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        for (int i = 0; i < nrows; ++i)
        {
            rapidjson::Value object;
            object.SetObject();

            int id = atoi(PQgetvalue(ret, i, 0));
            int userId = atoi(PQgetvalue(ret, i, 1));
            int matchId = atoi(PQgetvalue(ret, i, 2));
            int teamId = atoi(PQgetvalue(ret, i, 3));
            int playerApiId = atoi(PQgetvalue(ret, i, 4));
            std::string playerName = PQgetvalue(ret, i, 5);
            std::string playerPhoto = PQgetvalue(ret, i, 6);
            int goals = atoi(PQgetvalue(ret, i, 7));
            int status = atoi(PQgetvalue(ret, i, 8));

            std::string userName = PQgetvalue(ret, i, 9);
            std::string userAvatar = PQgetvalue(ret, i, 10);

            int fireballPoints = atoi(PQgetvalue(ret, i, 11));
            int points = atoi(PQgetvalue(ret, i, 12));
            float balance = atof(PQgetvalue(ret, i, 13));

            int elTorneoLeague = atoi(PQgetvalue(ret, i, 14));
            if (elTorneoLeague < 1) elTorneoLeague = -1;
            int elTorneoPosition = elTorneoLeague >= 1 ? atoi(PQgetvalue(ret, i, 15)) - (elTorneoLeague - 1) * 20 : -1;

            int beatBetLeague = atoi(PQgetvalue(ret, i, 16));
            if (beatBetLeague < 1) beatBetLeague = -1;
            int beatBetPosition = beatBetLeague >= 1 ? atoi(PQgetvalue(ret, i, 17)) - (beatBetLeague - 1) * 20 : -1;

            int fireballLeague = atoi(PQgetvalue(ret, i, 18));
            if (fireballLeague < 1) fireballLeague = -1;
            int fireballPosition = fireballLeague >= 1 ? atoi(PQgetvalue(ret, i, 19)) - (fireballLeague - 1) * 20 : -1;

            int careerLeague = atoi(PQgetvalue(ret, i, 20));
            if (careerLeague < 1) careerLeague = -1;
            int careerPosition = careerLeague >= 1 ? atoi(PQgetvalue(ret, i, 21)) - (careerLeague - 1) * 20 : -1;

            // Add user info and position to the JSON object
            rapidjson::Value userObject;
            userObject.SetObject();
            userObject.AddMember("id", userId, allocator);
            rapidjson::Value nameVal;
            nameVal.SetString(userName.c_str(), allocator);
            userObject.AddMember("name", nameVal, allocator);
            nameVal.SetString(userAvatar.c_str(), allocator);
            userObject.AddMember("avatar", nameVal, allocator);
            userObject.AddMember("fireballPoints", fireballPoints, allocator);
            userObject.AddMember("points", points, allocator);
            userObject.AddMember("balance", balance, allocator);

            userObject.AddMember("elTorneoLeague", elTorneoLeague, allocator);
            userObject.AddMember("elTorneoPosition", elTorneoPosition, allocator);
            userObject.AddMember("beatBetLeague", beatBetLeague, allocator);
            userObject.AddMember("beatBetPosition", beatBetPosition, allocator);
            userObject.AddMember("fireballLeague", fireballLeague, allocator);
            userObject.AddMember("fireballPosition", fireballPosition, allocator);
            userObject.AddMember("careerLeague",   careerLeague, allocator);
            userObject.AddMember("careerPosition", careerPosition, allocator);
            {
                std::string awardsQuery = "SELECT place, season, league FROM awards WHERE user_id = " + std::to_string(userId) + ";";
                PGresult* awardsRes = PQexec(pg, awardsQuery.c_str());

                if (PQresultStatus(awardsRes) != PGRES_TUPLES_OK)
                {
                    fprintf(stderr, "Failed to fetch awards: %s", PQerrorMessage(pg));
                    PQclear(awardsRes);
                }
                else
                {
                    int awardCount = PQntuples(awardsRes);
                    rapidjson::Value awards(rapidjson::kArrayType);

                    for (int j = 0; j < awardCount; ++j)
                    {
                        rapidjson::Value awardObj(rapidjson::kObjectType);

                        int place = atoi(PQgetvalue(awardsRes, j, 0));
                        char* season = PQgetvalue(awardsRes, j, 1);
                        int league = atoi(PQgetvalue(awardsRes, j, 2));

                        awardObj.AddMember("place", place, allocator);

                        rapidjson::Value seasonVal;
                        seasonVal.SetString(season, allocator);
                        awardObj.AddMember("season", seasonVal, allocator);
                        awardObj.AddMember("league", league, allocator);

                        awards.PushBack(awardObj, allocator);
                    }

                    userObject.AddMember("awards", awards, allocator);
                    PQclear(awardsRes);
                }
            }

            object.AddMember("id", id, allocator);
            object.AddMember("user", userObject, allocator);
            object.AddMember("match_id", matchId, allocator);
            object.AddMember("team_id", teamId, allocator);
            object.AddMember("player_api_id", playerApiId, allocator);
            rapidjson::Value sVal;
            sVal.SetString(playerName.c_str(), allocator);
            object.AddMember("player_name", sVal, allocator);
            sVal.SetString(playerPhoto.c_str(), allocator);
            object.AddMember("player_photo", sVal, allocator);
            object.AddMember("goals", goals, allocator);
            object.AddMember("status", status, allocator);

            predicts.PushBack(object, allocator);
        }

        document.AddMember("predicts", predicts, allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;  // OK

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}


std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetMatchFireballSummary()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        std::string matchId = req.get_param_value("match_id");
        std::string season;
        if (req.has_param("season"))
        {
            season = req.get_param_value("season");
        }
        std::string postfix = "";
        if (season.size())
        {
            std::string currentSeason = "25/26";
            if (season != currentSeason)
            {
                std::replace(season.begin(), season.end(), '/', '_');
                postfix = "_" + season;
            }
        }

        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string predictsSql =
            "SELECT player_api_id, "
            "       team_id, "
            "       MIN(player_name) AS player_name, "
            "       MIN(player_photo) AS player_photo, "
            "       COUNT(*) AS predict_count, "
            "       SUM(COUNT(*)) OVER () AS total_predicts "
            "FROM fireball_predicts "
            "WHERE match_id = " + matchId + " "
            "GROUP BY player_api_id, team_id "
            "ORDER BY predict_count DESC "
            "LIMIT 2;";
        PGresult* predictsRet = PQexec(pg, predictsSql.c_str());

        if (PQresultStatus(predictsRet) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch fireball summary: %s", PQerrorMessage(pg));
            PQclear(predictsRet);
            res.status = 500;  // Internal Server Error
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }

        // Fetch predicts
        int nrows = PQntuples(predictsRet);
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        if (nrows > 0) 
        {
            if (nrows >= 1) 
            {
                int playerApiId = atoi(PQgetvalue(predictsRet, 0, 0));
                int teamId = atoi(PQgetvalue(predictsRet, 0, 1));
                std::string playerName = PQgetvalue(predictsRet, 0, 2);
                std::string playerPhoto = PQgetvalue(predictsRet, 0, 3);
                int playerPredictCount = atoi(PQgetvalue(predictsRet, 0, 4));
                int totalCount = atoi(PQgetvalue(predictsRet, 0, 5));

                rapidjson::Value player1Val;
                player1Val.SetObject();
                player1Val.AddMember("player_api_id", playerApiId, allocator);
                player1Val.AddMember("team_id", teamId, allocator);
                rapidjson::Value strVal;
                strVal.SetString(playerName.c_str(), allocator);
                player1Val.AddMember("player_name", strVal, allocator);
                strVal.SetString(playerPhoto.c_str(), allocator);
                player1Val.AddMember("player_photo", strVal, allocator);
                player1Val.AddMember("count", playerPredictCount, allocator);

                document.AddMember("total_predicts", totalCount, allocator);
                document.AddMember("player1", player1Val, allocator);
            }
            if (nrows == 2)
            {
                int playerApiId = atoi(PQgetvalue(predictsRet, 1, 0));
                int teamId = atoi(PQgetvalue(predictsRet, 1, 1));
                std::string playerName = PQgetvalue(predictsRet, 1, 2);
                std::string playerPhoto = PQgetvalue(predictsRet, 1, 3);
                int playerPredictCount = atoi(PQgetvalue(predictsRet, 1, 4));
                int totalCount = atoi(PQgetvalue(predictsRet, 1, 5));

                rapidjson::Value player2Val;
                player2Val.SetObject();
                player2Val.AddMember("player_api_id", playerApiId, allocator);
                player2Val.AddMember("team_id", teamId, allocator);
                rapidjson::Value strVal;
                strVal.SetString(playerName.c_str(), allocator);
                player2Val.AddMember("player_name", strVal, allocator);
                strVal.SetString(playerPhoto.c_str(), allocator);
                player2Val.AddMember("player_photo", strVal, allocator);
                player2Val.AddMember("count", playerPredictCount, allocator);
                document.AddMember("player2", player2Val, allocator);
            }
        }
        else 
        {
            document.AddMember("total_predicts", 0, allocator);
        }
        // Serialize JSON response
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;  // OK

        PQclear(predictsRet);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetFireballTable()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        // Get the 'page' query parameter, default to 1 if not provided
        int page = 1;
        int league = 1;
        //   std::string season = "25_26";
        if (req.has_param("page")) 
        {
            page = std::stoi(req.get_param_value("page"));
        }
        if (req.has_param("league")) 
        {
            league = std::stoi(req.get_param_value("league"));
        }
        /*  if (req.has_param("season")) {
              season = req.get_param_value("season");
              std::replace(season.begin(), season.end(), '/', '_');
          }*/

        int limit = 20; // Number of users per page
        int offset = (page - 1) * limit; // Calculate the offset based on the page

        PGconn* pg = ConnectionPool::Get()->getConnection();
        if (!pg) 
        {
            res.status = 500;  // Internal Server Error
            return;
        }

        std::string predictsTableName = "fireball_predicts";
        std::string pointsColName = "fu.points";
        std::string leagueColName = "u.league";

        /* std::string currentSeason = "25_26";
         if (season != currentSeason)
         {
             predictsTableName += "_" + season;
             pointsColName += "_" + season;
             leagueColName += "_" + season;
         }*/

        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        long long timestamp = ms.count();
        long long ten_days_ms = 20LL * 24 * 60 * 60 * 1000;

        // Updated SQL query to join users with predicts, count the total number of predictions per user, and paginate
        std::string sql = "SELECT u.id, u.name, u.avatar, fu.points, COUNT(p.id) AS total_predictions, u.points, u.balance, u.league, "
            "COALESCE(cu.points, -1) AS career_points "
            "FROM users u "
            "INNER JOIN " + predictsTableName + " p ON u.id = p.user_id "
            "INNER JOIN fireball_users fu ON u.id = fu.user_id "
            "LEFT JOIN career_users cu ON cu.user_id = u.id "
            "WHERE fu.last_predict_ts >= " + std::to_string(timestamp - ten_days_ms) + " "
            " GROUP BY u.id, u.name, u.avatar, " + pointsColName + ", cu.points, cu.league "
            "HAVING COUNT(p.id) > 0 "
            "ORDER BY " + pointsColName + " DESC, total_predictions DESC, u.id ASC "
            "LIMIT " + std::to_string(limit) + " OFFSET " + std::to_string(offset) + ";";

        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK) 
        {
            fprintf(stderr, "Failed to fetch fireball table: %s", PQerrorMessage(pg));
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
            int id = atoi(PQgetvalue(ret, i, 0));
            rapidjson::Value object(rapidjson::kObjectType);
            object.AddMember("id", id, allocator);
            object.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 1), allocator), allocator);
            object.AddMember("avatar", rapidjson::Value(PQgetvalue(ret, i, 2), allocator), allocator);
            object.AddMember("fireballPoints", atoi(PQgetvalue(ret, i, 3)), allocator);
            object.AddMember("totalPredictions", atoi(PQgetvalue(ret, i, 4)), allocator);
            object.AddMember("predictions", atoi(PQgetvalue(ret, i, 5)), allocator);
            object.AddMember("balance", atof(PQgetvalue(ret, i, 6)), allocator);
            int league = atoi(PQgetvalue(ret, i, 7));
            object.AddMember("league", league, allocator);
            object.AddMember("careerPoints", atoi(PQgetvalue(ret, i, 8)), allocator);

            int pos = CachedTable::Get()->GetPosition(id, league);
            object.AddMember("position", pos, allocator);
            int bbpos = CachedTable::Get()->GetBeatBetPosition(id);
            object.AddMember("beatBetPosition", bbpos, allocator);
            int fbpos = CachedTable::Get()->GetFireballPosition(id);
            object.AddMember("fireballPosition", fbpos, allocator);
            int cpos = CachedTable::Get()->GetCareerPosition(id);
            object.AddMember("careerPosition", cpos, allocator);

            {
                std::string awardsQuery = "SELECT place, season, league FROM awards WHERE user_id = " + std::to_string(id) + ";";
                PGresult* awardsRes = PQexec(pg, awardsQuery.c_str());

                if (PQresultStatus(awardsRes) != PGRES_TUPLES_OK)
                {
                    fprintf(stderr, "Failed to fetch awards: %s", PQerrorMessage(pg));
                    PQclear(awardsRes);
                }
                else
                {
                    int awardCount = PQntuples(awardsRes);
                    rapidjson::Value awards(rapidjson::kArrayType);

                    for (int j = 0; j < awardCount; ++j)
                    {
                        rapidjson::Value awardObj(rapidjson::kObjectType);

                        int place = atoi(PQgetvalue(awardsRes, j, 0));
                        char* season = PQgetvalue(awardsRes, j, 1);
                        int league = atoi(PQgetvalue(awardsRes, j, 2));

                        awardObj.AddMember("place", place, allocator);

                        rapidjson::Value seasonVal;
                        seasonVal.SetString(season, allocator);
                        awardObj.AddMember("season", seasonVal, allocator);
                        awardObj.AddMember("league", league, allocator);

                        awards.PushBack(awardObj, allocator);
                    }

                    object.AddMember("awards", awards, allocator);
                    PQclear(awardsRes);
                }

            }

            document.PushBack(object, allocator);
        }

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetFireballTableV2()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        // Get the 'page' query parameter, default to 1 if not provided
        int page = 1;
        int league = 1;
        //   std::string season = "25_26";
        if (req.has_param("page"))
        {
            page = std::stoi(req.get_param_value("page"));
        }
        if (req.has_param("league"))
        {
            league = std::stoi(req.get_param_value("league"));
        }
        /*  if (req.has_param("season")) {
              season = req.get_param_value("season");
              std::replace(season.begin(), season.end(), '/', '_');
          }*/

        int limit = 20; // Number of users per page
        int offset = (page - 1) * limit; // Calculate the offset based on the page

        PGconn* pg = ConnectionPool::Get()->getConnection();
        if (!pg)
        {
            res.status = 500;  // Internal Server Error
            return;
        }

        std::string predictsTableName = "fireball_predicts";
        std::string pointsColName = "fu.points";
        std::string leagueColName = "fu.league";

        /* std::string currentSeason = "25_26";
         if (season != currentSeason)
         {
             predictsTableName += "_" + season;
             pointsColName += "_" + season;
             leagueColName += "_" + season;
         }*/

        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        long long timestamp = ms.count();
        long long ten_days_ms = 20LL * 24 * 60 * 60 * 1000;

        // Updated SQL query to join users with predicts, count the total number of predictions per user, and paginate
        std::string sql = "SELECT u.id, u.name, u.avatar, fu.points, COUNT(p.id) AS total_predictions, u.points, u.clear_balance, "
            "u.eltorneo_league, u.eltorneo_position, "
            "u.beat_bet_league, u.beat_bet_position, "
            "fu.league, fu.position, "
            "cu.league, cu.position, "
            "COALESCE(cu.points, -1) AS career_points "
            "FROM users u "
            "INNER JOIN " + predictsTableName + " p ON u.id = p.user_id "
            "INNER JOIN fireball_users fu ON u.id = fu.user_id "
            "LEFT JOIN career_users cu ON cu.user_id = u.id "
            "WHERE fu.last_predict_ts >= " + std::to_string(timestamp - ten_days_ms) + " "
            "AND " + leagueColName + " = " + std::to_string(league) + " "
            " GROUP BY u.id, u.name, u.avatar, " + pointsColName + ", cu.points, fu.league, fu.position, cu.league, cu.position "
            "HAVING COUNT(p.id) > 0 "
            "ORDER BY " + pointsColName + " DESC, total_predictions DESC, u.id ASC "
            "LIMIT " + std::to_string(limit) + " OFFSET " + std::to_string(offset) + ";";

        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch fireball table: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Value table;
        table.SetArray();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        for (int i = 0; i < nrows; ++i)
        {
            int id = atoi(PQgetvalue(ret, i, 0));
            rapidjson::Value object(rapidjson::kObjectType);
            object.AddMember("id", id, allocator);
            object.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 1), allocator), allocator);
            object.AddMember("avatar", rapidjson::Value(PQgetvalue(ret, i, 2), allocator), allocator);
            object.AddMember("fireballPoints", atoi(PQgetvalue(ret, i, 3)), allocator);
            object.AddMember("totalPredictions", atoi(PQgetvalue(ret, i, 4)), allocator);
            object.AddMember("predictions", atoi(PQgetvalue(ret, i, 5)), allocator);
            object.AddMember("balance", atof(PQgetvalue(ret, i, 6)), allocator);

            int elTorneoLeague = atoi(PQgetvalue(ret, i, 7));
            if (elTorneoLeague < 1) elTorneoLeague = -1;
            object.AddMember("elTorneoLeague", elTorneoLeague, allocator);
            int elTorneoPosition = elTorneoLeague >= 1 ? atoi(PQgetvalue(ret, i, 8)) - (elTorneoLeague - 1) * 20 : -1;
            object.AddMember("elTorneoPosition", elTorneoPosition, allocator);
          
            int beatBetLeague = atoi(PQgetvalue(ret, i, 9));
            if (beatBetLeague < 1) beatBetLeague = -1;
            object.AddMember("beatBetLeague", beatBetLeague, allocator);
            int beatBetPosition = beatBetLeague >= 1 ? atoi(PQgetvalue(ret, i, 10)) - (beatBetLeague - 1) * 20 : -1;
            object.AddMember("beatBetPosition", beatBetPosition, allocator);

            int fireballLeague = atoi(PQgetvalue(ret, i, 11));
            if (fireballLeague < 1) fireballLeague = -1;
            object.AddMember("fireballLeague", fireballLeague, allocator);
            int fireballPosition = fireballLeague >= 1 ? atoi(PQgetvalue(ret, i, 12)) - (fireballLeague - 1) * 20 : -1;
            object.AddMember("fireballPosition", fireballPosition, allocator);

            int careerLeague = atoi(PQgetvalue(ret, i, 13));
            if (careerLeague < 1) careerLeague = -1;
            object.AddMember("careerLeague", careerLeague, allocator);
            int careerPosition = careerLeague >= 1 ? atoi(PQgetvalue(ret, i, 14)) - (careerLeague - 1) * 20 : -1;
            object.AddMember("careerPosition", careerPosition, allocator);

            object.AddMember("careerPoints", atoi(PQgetvalue(ret, i, 15)), allocator);

            {
                std::string awardsQuery = "SELECT place, season, league FROM awards WHERE user_id = " + std::to_string(id) + ";";
                PGresult* awardsRes = PQexec(pg, awardsQuery.c_str());

                if (PQresultStatus(awardsRes) != PGRES_TUPLES_OK)
                {
                    fprintf(stderr, "Failed to fetch awards: %s", PQerrorMessage(pg));
                    PQclear(awardsRes);
                }
                else
                {
                    int awardCount = PQntuples(awardsRes);
                    rapidjson::Value awards(rapidjson::kArrayType);

                    for (int j = 0; j < awardCount; ++j)
                    {
                        rapidjson::Value awardObj(rapidjson::kObjectType);

                        int place = atoi(PQgetvalue(awardsRes, j, 0));
                        char* season = PQgetvalue(awardsRes, j, 1);
                        int league = atoi(PQgetvalue(awardsRes, j, 2));

                        awardObj.AddMember("place", place, allocator);

                        rapidjson::Value seasonVal;
                        seasonVal.SetString(season, allocator);
                        awardObj.AddMember("season", seasonVal, allocator);
                        awardObj.AddMember("league", league, allocator);

                        awards.PushBack(awardObj, allocator);
                    }

                    object.AddMember("awards", awards, allocator);
                    PQclear(awardsRes);
                }

            }

            table.PushBack(object, allocator);
        }

        sql =
            "SELECT COUNT(*) AS total_users "
            "FROM ( "
            "    SELECT u.id "
            "    FROM users u "
            "    INNER JOIN " + predictsTableName + " p ON u.id = p.user_id "
            "    INNER JOIN fireball_users fu ON u.id = fu.user_id "
            "    WHERE fu.last_predict_ts >= " + std::to_string(timestamp - ten_days_ms) + " "
            "    GROUP BY u.id "
            "    HAVING COUNT(p.id) > 0 "
            ") AS subquery;";
        PGresult* totalRet = PQexec(pg, sql.c_str());
        int totalUsers = atoi(PQgetvalue(totalRet, 0, 0));
        document.AddMember("numUsers", totalUsers, allocator);
        PQclear(totalRet);

        document.AddMember("table", table, allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}


std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetUserFireballPredicts() {
    return [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        std::string userId = req.get_param_value("user_id");
        std::string leagueId = req.get_param_value("league_id");
        int page = std::stoi(req.get_param_value("page")) - 1;
        int limit = 20;
        int offset = page * limit;

        PGconn* pg = ConnectionPool::Get()->getConnection();
        if (!pg) 
        {
            res.status = 500;  // Internal Server Error
            return;
        }

        // SQL query to fetch bets and match details
        std::string sql =
            "SELECT fp.id, fp.team_id, fp.player_api_id, fp.player_name, fp.player_photo, fp.goals, fp.status, "
            "m.id AS match_id, l.id AS league_id, l.name AS league_name, l.country AS league_country, "
            "m.season, m.week, m.match_date, m.team1_score, m.team2_score, m.week_type, m.elapsed, "
            "m.team1_score_live, m.team2_score_live, m.status AS match_status, m.is_special, m.preview, "
            "m.teaser, m.play_off, "
            "m.team1_score_90, m.team2_score_90, m.team1_score_pen, m.team2_score_pen,"
            "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
            "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "
            "COALESCE(s.title, '') AS special_match_title, COALESCE(s.points, '') AS special_match_points "
            "FROM fireball_predicts fp "
            "INNER JOIN matches m ON fp.match_id = m.id "
            "LEFT JOIN leagues l ON m.league = l.id "
            "LEFT JOIN teams t1 ON m.team1 = t1.id "
            "LEFT JOIN teams t2 ON m.team2 = t2.id "
            "LEFT JOIN special_matches s ON s.match_id = m.id "
            "WHERE fp.user_id = " + userId +
            (leagueId != "-1" ? " AND m.league = " + leagueId : "") +
            " ORDER BY m.match_date DESC, m.id DESC "
            "LIMIT " + std::to_string(limit) + " OFFSET " + std::to_string(offset) + ";";

        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK) 
        {
            fprintf(stderr, "Failed to fetch user fireball predicts: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        rapidjson::Value betsArray(rapidjson::kArrayType);

        for (int i = 0; i < nrows; ++i) {
            rapidjson::Value object(rapidjson::kObjectType);

            rapidjson::Value leagueObject(rapidjson::kObjectType);
            leagueObject.AddMember("id", atoi(PQgetvalue(ret, i, 8)), allocator);
            leagueObject.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 9)), allocator);
            leagueObject.AddMember("country", rapidjson::StringRef(PQgetvalue(ret, i, 10)), allocator);
            object.AddMember("league", leagueObject, allocator);

            object.AddMember("id", atoi(PQgetvalue(ret, i, 7)), allocator);
            object.AddMember("season", rapidjson::StringRef(PQgetvalue(ret, i, 11)), allocator);
            object.AddMember("week", atoi(PQgetvalue(ret, i, 12)), allocator);
            object.AddMember("date", (double)atoll(PQgetvalue(ret, i, 13)), allocator);
            object.AddMember("team1_score", atoi(PQgetvalue(ret, i, 14)), allocator);
            object.AddMember("team2_score", atoi(PQgetvalue(ret, i, 15)), allocator);
            object.AddMember("week_type", atoi(PQgetvalue(ret, i, 16)), allocator);
            object.AddMember("elapsed", atoi(PQgetvalue(ret, i, 17)), allocator);
            object.AddMember("team1_score_live", atoi(PQgetvalue(ret, i, 18)), allocator);
            object.AddMember("team2_score_live", atoi(PQgetvalue(ret, i, 19)), allocator);
            object.AddMember("status", rapidjson::StringRef(PQgetvalue(ret, i, 20)), allocator);
            object.AddMember("is_special", atoi(PQgetvalue(ret, i, 21)), allocator);
            object.AddMember("preview", rapidjson::StringRef(PQgetvalue(ret, i, 22)), allocator);
            object.AddMember("teaser", rapidjson::StringRef(PQgetvalue(ret, i, 23)), allocator);
            object.AddMember("playOff", atoi(PQgetvalue(ret, i, 24)), allocator);

            object.AddMember("team1_score_90", atoi(PQgetvalue(ret, i, 25)), allocator);
            object.AddMember("team2_score_90", atoi(PQgetvalue(ret, i, 26)), allocator);
            object.AddMember("team1_score_pen", atoi(PQgetvalue(ret, i, 27)), allocator);
            object.AddMember("team2_score_pen", atoi(PQgetvalue(ret, i, 28)), allocator);

            object.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 35), allocator), allocator);
            object.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 36), allocator), allocator);

            rapidjson::Value team1Object(rapidjson::kObjectType);
            team1Object.AddMember("id", atoi(PQgetvalue(ret, i, 29)), allocator);
            team1Object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 30)), allocator);
            team1Object.AddMember("shortName", rapidjson::StringRef(PQgetvalue(ret, i, 31)), allocator);
            object.AddMember("team1", team1Object, allocator);

            rapidjson::Value team2Object(rapidjson::kObjectType);
            team2Object.AddMember("id", atoi(PQgetvalue(ret, i, 32)), allocator);
            team2Object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 33)), allocator);
            team2Object.AddMember("shortName", rapidjson::StringRef(PQgetvalue(ret, i, 34)), allocator);
            object.AddMember("team2", team2Object, allocator);

            rapidjson::Value predictObj(rapidjson::kObjectType);
            predictObj.AddMember("id", atoi(PQgetvalue(ret, i, 0)), allocator);
            predictObj.AddMember("team_id", atoi(PQgetvalue(ret, i, 1)), allocator);
            predictObj.AddMember("player_api_id", atoi(PQgetvalue(ret, i, 2)), allocator);
            predictObj.AddMember("player_name", rapidjson::Value(PQgetvalue(ret, i, 3), allocator), allocator);
            predictObj.AddMember("player_photo", rapidjson::Value(PQgetvalue(ret, i, 4), allocator), allocator);
            predictObj.AddMember("goals", atoi(PQgetvalue(ret, i, 5)), allocator);
            predictObj.AddMember("status", atoi(PQgetvalue(ret, i, 6)), allocator);
            object.AddMember("fireballPredict", predictObj, allocator);

            betsArray.PushBack(object, allocator);
        }

        document.AddMember("predicts", betsArray, allocator);

        auto generateBetCountQuery = [&](const std::string& condition)
        {
            std::string countSql = "SELECT COUNT(*) FROM fireball_predicts fp INNER JOIN matches m ON fp.match_id = m.id WHERE fp.user_id = " + userId;
            if (leagueId != "-1")
            {
                countSql += " AND m.league = " + leagueId;
            }
            countSql += condition.size() ? " AND " + condition : "";
            return countSql;
        };

        std::string countAllBetsSql = generateBetCountQuery("");  // Count all bets
        std::string countWinBetsSql = generateBetCountQuery("fp.status IN (1, 2, 3)"); // Count win bets
        std::string countLooseBetsSql = generateBetCountQuery("fp.status IN (-1, 4)"); // Count lose bets
        std::string countTotalBetsSql = generateBetCountQuery("fp.status <> 0"); // Total bets that are NOT pending

        PGresult* retAllBets = PQexec(pg, countAllBetsSql.c_str());
        PGresult* retWinBets = PQexec(pg, countWinBetsSql.c_str());
        PGresult* retLooseBets = PQexec(pg, countLooseBetsSql.c_str());
        PGresult* retTotalBets = PQexec(pg, countTotalBetsSql.c_str());

        int allBets = (PQntuples(retAllBets) > 0) ? atoi(PQgetvalue(retAllBets, 0, 0)) : 0;
        int totalWinBets = (PQntuples(retWinBets) > 0) ? atoi(PQgetvalue(retWinBets, 0, 0)) : 0;
        int totalLooseBets = (PQntuples(retLooseBets) > 0) ? atoi(PQgetvalue(retLooseBets, 0, 0)) : 0;
        int totalBets = (PQntuples(retTotalBets) > 0) ? atoi(PQgetvalue(retTotalBets, 0, 0)) : 0;

        PQclear(retAllBets);
        PQclear(retWinBets);
        PQclear(retLooseBets);
        PQclear(retTotalBets);

        document.AddMember("allPredicts", allBets, allocator);
        document.AddMember("totalPredicts", totalBets, allocator);
        document.AddMember("totalWinPredicts", totalWinBets, allocator);
        document.AddMember("totalLoosePredicts", totalLooseBets, allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::DeleteFireballPredict()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "DELETE");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        std::string token = req.get_header_value("Authentication");
        auto decoded = jwt::decode(token);
        int userId = decoded.get_payload_claim("id").as_int();
        std::string id = req.get_param_value("id");

        std::string sql = "DELETE FROM fireball_predicts WHERE user_id = " + std::to_string(userId)
            + " AND id = " + id + ";";
        PGconn* pg = ConnectionPool::Get()->getConnection();
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
        res.status = 200;
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::PostCareerSave()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "POST");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        rapidjson::Document document;
        document.Parse(req.body.c_str());

        std::string token = req.get_header_value("Authentication");
        auto decoded = jwt::decode(token);

        int userId = decoded.get_payload_claim("id").as_int();
        std::string formation = document["formation"].GetString();
        int hasTransfer = document["hasTransfer"].GetInt();
        int numTransfers = hasTransfer ? 1 : 0;
        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        long long timestamp = ms.count();
        long long weekLaterTs = timestamp + 7LL * 24 * 60 * 60 * 1000;

        PGconn* pg = ConnectionPool::Get()->getConnection();
        {
            std::string sql =
                "INSERT INTO career_users (user_id, formation, next_transfer_ts, num_transfers) VALUES ("
                + std::to_string(userId) + ", '" + formation + "', "
                + std::to_string(weekLaterTs) + ", "
                + std::to_string(numTransfers) + ") "
                "ON CONFLICT (user_id) DO UPDATE SET "
                "formation = EXCLUDED.formation, "
                "num_transfers = EXCLUDED.num_transfers;";

            PGresult* ret = PQexec(pg, sql.c_str());
            if (PQresultStatus(ret) != PGRES_TUPLES_OK && PQresultStatus(ret) != PGRES_COMMAND_OK)
            {
                fprintf(stderr, "Failed to add career user: %s\n", PQerrorMessage(pg));
                PQclear(ret);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 500; // Internal Server Error
                return;
            }
            PQclear(ret);
        }

        {
            std::string sql = "DELETE FROM career_players WHERE user_id = " + std::to_string(userId) + ";";
            PGresult* ret = PQexec(pg, sql.c_str());
            PQclear(ret);
        }

        rapidjson::Value& players = document["players"];
        for (rapidjson::SizeType i = 0; i < players.Size(); i++)
        {
            rapidjson::Value& player = players[i];
            int playerApiId = player["apiId"].GetInt();
            std::string playerName = player["name"].GetString();
            int number = player["number"].GetInt();
            std::string grid = player["grid"].GetString();
            std::string pos = player["position"].GetString();
            int start11 = player["start11"].GetBool();
            int team = player["teamId"].GetInt();

            std::string sql = "INSERT INTO career_players (user_id, name, number, grid, start11, team, pos, api_id) VALUES ("
                + std::to_string(userId) + ", '"
                + playerName + "', "
                + std::to_string(number) + ", '"
                + grid + "', "
                + std::to_string(start11) + ", "
                + std::to_string(team) + ", '"
                + pos + "', "
                + std::to_string(playerApiId) + ");";
                
            PGresult* ret = PQexec(pg, sql.c_str());
            if (PQresultStatus(ret) != PGRES_TUPLES_OK && PQresultStatus(ret) != PGRES_COMMAND_OK)
            {
                fprintf(stderr, "Failed to add career players: %s\n", PQerrorMessage(pg));
                PQclear(ret);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 500; // Internal Server Error
                return;
            }
            PQclear(ret);
        }

        ConnectionPool::Get()->releaseConnection(pg);

        // Send response
        res.status = 201; // Created
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetCareerPlayers()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        int userId = -1;
        if (req.has_param("user_id")) 
        {
            userId = atoi(req.get_param_value("user_id").c_str());
        }
        if (userId == -1) 
        {
            fprintf(stderr, "Failed to fetch career players no user_id\n");
            res.status = 500;  // Internal Server Error
            return;
        }

        bool isMe = false;
        std::string token = req.get_header_value("Authentication");
        if (token.size() && token != "null")
        {
            auto decoded = jwt::decode(token);
            int myId = decoded.get_payload_claim("id").as_int();
            isMe = myId == userId;
        }



        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string sql = "SELECT formation, points, num_transfers, next_transfer_ts FROM career_users WHERE user_id = "
            + std::to_string(userId) + ";";
        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch user career: %s", PQerrorMessage(pg));
            PQclear(ret);
            res.status = 500;  // Internal Server Error
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }

        int nrows = PQntuples(ret);
        if (nrows <= 0) 
        {
            // fprintf(stderr, "Failed to fetch user career: %s", PQerrorMessage(pg));
            PQclear(ret);
            res.status = 500;  // Internal Server Error
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }
        std::string formation = PQgetvalue(ret, 0, 0);
        int points = atoi(PQgetvalue(ret, 0, 1));
        int numTransfers = atoi(PQgetvalue(ret, 0, 2));
        long long nextTransferTs = atoll(PQgetvalue(ret, 0, 3));

        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        rapidjson::Value v;
        v.SetString(formation.c_str(), formation.size(), allocator);
        document.AddMember("formation", v, allocator);
        document.AddMember("points", points, allocator);
        document.AddMember("numTransfers", numTransfers, allocator);
        document.AddMember("nextTransferTs", (double)nextTransferTs, allocator);

        if (!isMe)
        {
            sql =
                "SELECT cp.*, t.short_name, t.name, t.players_ready "
                "FROM career_players cp "
                "JOIN teams t ON cp.team = t.id "
                "WHERE cp.user_id = " + std::to_string(userId) + " ORDER BY grid;";
        }
        else 
        {
            auto now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            auto twoHoursAgo = now - 2 * 60 * 60 * 1000; // 2 hours in ms

            sql =
                "SELECT cp.*, t.short_name, t.name, t.players_ready, "
                "m.id AS live_match_id "
                "FROM career_players cp "
                "JOIN teams t ON cp.team = t.id "
                "LEFT JOIN matches m ON ("
                "    (m.team1 = t.id OR m.team2 = t.id) "
                "    AND m.match_date BETWEEN " + std::to_string(twoHoursAgo) +
                " AND " + std::to_string(now) +
                ") "
                "WHERE cp.user_id = " + std::to_string(userId) +
                " ORDER BY grid;";
        }

        PGresult* retPlayers = PQexec(pg, sql.c_str());
        if (PQresultStatus(retPlayers) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch user career players: %s", PQerrorMessage(pg));
            PQclear(ret);
            PQclear(retPlayers);
            res.status = 500;  // Internal Server Error
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }

        rapidjson::Value players;
        players.SetArray();
        nrows = PQntuples(retPlayers);
        for (int i = 0; i < nrows; ++i)
        {
            rapidjson::Value player;
            player.SetObject();

            int id = atoi(PQgetvalue(retPlayers, i, 0));
            rapidjson::Value idValue;
            player.AddMember("id", id, allocator);

            std::string name = (PQgetvalue(retPlayers, i, 2));
            idValue.SetString(name.c_str(), name.size(), allocator);
            player.AddMember("name", idValue, allocator);

            int number = atoi(PQgetvalue(retPlayers, i, 3));
            player.AddMember("number", number, allocator);

            std::string grid = (PQgetvalue(retPlayers, i, 4));
            idValue.SetString(grid.c_str(), grid.size(), allocator);
            player.AddMember("grid", idValue, allocator);

            int start11 = atoi(PQgetvalue(retPlayers, i, 5));
            player.AddMember("start11", (bool)start11, allocator);

            int team = atoi(PQgetvalue(retPlayers, i, 6));
            player.AddMember("teamId", team, allocator);

            std::string pos = (PQgetvalue(retPlayers, i, 7));
            idValue.SetString(pos.c_str(), pos.size(), allocator);
            player.AddMember("position", idValue, allocator);

            int apiId = atoi(PQgetvalue(retPlayers, i, 8));
            player.AddMember("apiId", apiId, allocator);

            std::string teamShortName = (PQgetvalue(retPlayers, i, 9));
            idValue.SetString(teamShortName.c_str(), teamShortName.size(), allocator);
            player.AddMember("teamShortName", idValue, allocator);

            std::string teamName = (PQgetvalue(retPlayers, i, 10));
            idValue.SetString(teamName.c_str(), teamName.size(), allocator);
            player.AddMember("teamName", idValue, allocator);

            int teamPlayersReady = atoi(PQgetvalue(retPlayers, i, 11));
            player.AddMember("teamPlayersReady", teamPlayersReady, allocator);

            int matchId = -1;
            if (isMe) 
            {         
                matchId = atoi(PQgetvalue(retPlayers, i, 12));
            }
            player.AddMember("matchId", matchId, allocator);

            {
                std::string sql = "SELECT player_api_id, league_id, games, rating, goals, assists FROM player_stats WHERE team_id = "
                    + std::to_string(team) + " AND player_api_id = " + std::to_string(apiId) + ";";
                PGresult* statRet = PQexec(pg, sql.c_str());
                if (PQresultStatus(ret) != PGRES_TUPLES_OK)
                {
                    fprintf(stderr, "Failed to get player stats: %s", PQerrorMessage(pg));
                    PQclear(statRet);
                }
                else
                {
                    int nStats = PQntuples(statRet);
                    rapidjson::Value stats;
                    stats.SetArray();
                    int games = 0;
                    float rating = 0;
                    int goals = 0;
                    int assists = 0;
                    int numStats = 0;
                    for (int s = 0; s < nStats; ++s)
                    {
                        int g = atoi(PQgetvalue(statRet, s, 2));
                        if (!g) continue;

                        ++numStats;
                        games += g;
                        goals += atoi(PQgetvalue(statRet, s, 4));
                        assists += atoi(PQgetvalue(statRet, s, 5));
                        rating += atof(PQgetvalue(statRet, s, 3));
                    }
                    if (numStats > 0)
                        rating = rating / numStats;

                    player.AddMember("games", games, allocator);
                    player.AddMember("goals", goals, allocator);
                    player.AddMember("assists", assists, allocator);
                    player.AddMember("rating", rating, allocator);
                    PQclear(statRet);
                }
            }

            players.PushBack(player, allocator);
        }
        document.AddMember("players", players, allocator);

        // Assuming you convert the Document to a string and send it in the response as before
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        // You can then use `buffer.GetString()` to get the JSON string
        // And send it in the response as follows:
        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;  // OK


        PQclear(ret);
        PQclear(retPlayers);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetCareerTableV2()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        // Get the 'page' query parameter, default to 1 if not provided
        int page = 1;
        int league = 1;
        //   std::string season = "25_26";
        if (req.has_param("page"))
        {
            page = std::stoi(req.get_param_value("page"));
        }
        if (req.has_param("league"))
        {
            league = std::stoi(req.get_param_value("league"));
        }
        /*  if (req.has_param("season")) {
              season = req.get_param_value("season");
              std::replace(season.begin(), season.end(), '/', '_');
          }*/

        int limit = 20; // Number of users per page
        int offset = (page - 1) * limit; // Calculate the offset based on the page

        PGconn* pg = ConnectionPool::Get()->getConnection();
        if (!pg)
        {
            res.status = 500;  // Internal Server Error
            return;
        }

        std::string pointsColName = "cu.points";
        std::string leagueColName = "cu.league";

        /* std::string currentSeason = "25_26";
         if (season != currentSeason)
         {
             predictsTableName += "_" + season;
             pointsColName += "_" + season;
             leagueColName += "_" + season;
         }*/

        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        long long timestamp = ms.count();
        long long ten_days_ms = 20LL * 24 * 60 * 60 * 1000;

        // Updated SQL query to join users with predicts, count the total number of predictions per user, and paginate
        std::string sql = "SELECT u.id, u.name, u.avatar, u.points, u.clear_balance, fu.points, cu.points, "
            "u.eltorneo_league, u.eltorneo_position, "
            "u.beat_bet_league, u.beat_bet_position, "
            "fu.league, fu.position, "
            "cu.league, cu.position "
            "FROM users u "
            "INNER JOIN career_users cu ON u.id = cu.user_id "
            "LEFT JOIN fireball_users fu ON fu.user_id = u.id "
            "WHERE " + leagueColName + " = " + std::to_string(league) + " "
            " GROUP BY u.id, u.name, u.avatar, " + pointsColName + ", fu.points, fu.league, fu.position, cu.points, cu.league, cu.position "
            "ORDER BY " + pointsColName + " DESC, u.id ASC "
            "LIMIT " + std::to_string(limit) + " OFFSET " + std::to_string(offset) + ";";

        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch career table: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Value table;
        table.SetArray();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        for (int i = 0; i < nrows; ++i)
        {
            int id = atoi(PQgetvalue(ret, i, 0));
            rapidjson::Value object(rapidjson::kObjectType);
            object.AddMember("id", id, allocator);
            object.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 1), allocator), allocator);
            object.AddMember("avatar", rapidjson::Value(PQgetvalue(ret, i, 2), allocator), allocator);
            object.AddMember("predictions", atoi(PQgetvalue(ret, i, 3)), allocator);
            object.AddMember("balance", atof(PQgetvalue(ret, i, 4)), allocator);
            object.AddMember("fireballPoints", atoi(PQgetvalue(ret, i, 5)), allocator);
            object.AddMember("careerPoints", atoi(PQgetvalue(ret, i, 6)), allocator);

            int elTorneoLeague = atoi(PQgetvalue(ret, i, 7));
            if (elTorneoLeague < 1) elTorneoLeague = -1;
            int elTorneoPosition = elTorneoLeague >= 1 ? atoi(PQgetvalue(ret, i, 8)) - (elTorneoLeague - 1) * 20 : -1;
            object.AddMember("elTorneoLeague", elTorneoLeague, allocator);
            object.AddMember("elTorneoPosition", elTorneoPosition, allocator);

            int beatBetLeague = atoi(PQgetvalue(ret, i, 9));
            if (beatBetLeague < 1) beatBetLeague = -1;
            int beatBetPosition = beatBetLeague >= 1 ? atoi(PQgetvalue(ret, i, 10)) - (beatBetLeague - 1) * 20 : -1;
            object.AddMember("beatBetLeague", beatBetLeague, allocator);
            object.AddMember("beatBetPosition", beatBetPosition, allocator);

            int fireballLeague = atoi(PQgetvalue(ret, i, 11));
            if (fireballLeague < 1) fireballLeague = -1;
            int fireballPosition = fireballLeague >= 1 ? atoi(PQgetvalue(ret, i, 12)) - (fireballLeague - 1) * 20 : -1;
            object.AddMember("fireballLeague", fireballLeague, allocator);
            object.AddMember("fireballPosition", fireballPosition, allocator);

            int careerLeague = atoi(PQgetvalue(ret, i, 13));
            if (careerLeague < 1) careerLeague = -1;
            int careerPosition = careerLeague >= 1 ? atoi(PQgetvalue(ret, i, 14)) - (careerLeague - 1) * 20 : -1;
            object.AddMember("careerLeague", careerLeague, allocator);
            object.AddMember("careerPosition", careerPosition, allocator);

            {
                std::string awardsQuery = "SELECT place, season, league FROM awards WHERE user_id = " + std::to_string(id) + ";";
                PGresult* awardsRes = PQexec(pg, awardsQuery.c_str());

                if (PQresultStatus(awardsRes) != PGRES_TUPLES_OK)
                {
                    fprintf(stderr, "Failed to fetch awards: %s", PQerrorMessage(pg));
                    PQclear(awardsRes);
                }
                else
                {
                    int awardCount = PQntuples(awardsRes);
                    rapidjson::Value awards(rapidjson::kArrayType);

                    for (int j = 0; j < awardCount; ++j)
                    {
                        rapidjson::Value awardObj(rapidjson::kObjectType);

                        int place = atoi(PQgetvalue(awardsRes, j, 0));
                        char* season = PQgetvalue(awardsRes, j, 1);
                        int league = atoi(PQgetvalue(awardsRes, j, 2));

                        awardObj.AddMember("place", place, allocator);

                        rapidjson::Value seasonVal;
                        seasonVal.SetString(season, allocator);
                        awardObj.AddMember("season", seasonVal, allocator);
                        awardObj.AddMember("league", league, allocator);

                        awards.PushBack(awardObj, allocator);
                    }

                    object.AddMember("awards", awards, allocator);
                    PQclear(awardsRes);
                }

            }

            table.PushBack(object, allocator);
        }

        sql =
            "SELECT COUNT(*) AS total_users "
            "FROM ( "
            "    SELECT u.id "
            "    FROM users u "
            "    INNER JOIN career_users cu ON u.id = cu.user_id "
            "    GROUP BY u.id "
            ") AS subquery;";
        PGresult* totalRet = PQexec(pg, sql.c_str());
        int totalUsers = atoi(PQgetvalue(totalRet, 0, 0));
        document.AddMember("numUsers", totalUsers, allocator);
        PQclear(totalRet);

        document.AddMember("table", table, allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetUserCareerPredicts() {
    return [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        std::string userId = req.get_param_value("user_id");
        std::string leagueId = req.get_param_value("league_id");
        int page = std::stoi(req.get_param_value("page")) - 1;
        int limit = 20;
        int offset = page * limit;

        PGconn* pg = ConnectionPool::Get()->getConnection();
        if (!pg)
        {
            res.status = 500;  // Internal Server Error
            return;
        }

        // SQL query to fetch bets and match details
        std::string sql =
            "SELECT cp.id, cp.user_id, cp.match_id, cp.player_api_id, cp.minutes, cp.goals, cp.assists, cp.yellow_cards, cp.red_cards, cp.goals_a, cp.pen_saved, cp.pen_missed, cp.points, cp.player_name, cp.player_pos, cp.team_id, "
            "m.id AS match_id, l.id AS league_id, l.name AS league_name, l.country AS league_country, "
            "m.season, m.week, m.match_date, m.team1_score, m.team2_score, m.week_type, m.elapsed, "
            "m.team1_score_live, m.team2_score_live, m.status AS match_status, m.is_special, m.preview, "
            "m.teaser, m.play_off, "
            "m.team1_score_90, m.team2_score_90, m.team1_score_pen, m.team2_score_pen,"
            "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
            "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "
            "COALESCE(s.title, '') AS special_match_title, COALESCE(s.points, '') AS special_match_points "
            "FROM career_predicts cp "
            "INNER JOIN matches m ON cp.match_id = m.id "
            "LEFT JOIN leagues l ON m.league = l.id "
            "LEFT JOIN teams t1 ON m.team1 = t1.id "
            "LEFT JOIN teams t2 ON m.team2 = t2.id "
            "LEFT JOIN special_matches s ON s.match_id = m.id "
            "WHERE cp.user_id = " + userId +
            (leagueId != "-1" ? " AND m.league = " + leagueId : "") +
            " ORDER BY m.match_date DESC, m.id DESC "
            "LIMIT " + std::to_string(limit) + " OFFSET " + std::to_string(offset) + ";";

        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch user fireball predicts: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        rapidjson::Value betsArray(rapidjson::kArrayType);

        for (int i = 0; i < nrows; ++i) {
            rapidjson::Value object(rapidjson::kObjectType);

            rapidjson::Value leagueObject(rapidjson::kObjectType);
            leagueObject.AddMember("id", atoi(PQgetvalue(ret, i, 17)), allocator);
            leagueObject.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 18)), allocator);
            leagueObject.AddMember("country", rapidjson::StringRef(PQgetvalue(ret, i, 19)), allocator);
            object.AddMember("league", leagueObject, allocator);

            object.AddMember("id", atoi(PQgetvalue(ret, i, 16)), allocator);
            object.AddMember("season", rapidjson::StringRef(PQgetvalue(ret, i, 20)), allocator);
            object.AddMember("week", atoi(PQgetvalue(ret, i, 21)), allocator);
            object.AddMember("date", (double)atoll(PQgetvalue(ret, i, 22)), allocator);
            object.AddMember("team1_score", atoi(PQgetvalue(ret, i, 23)), allocator);
            object.AddMember("team2_score", atoi(PQgetvalue(ret, i, 24)), allocator);
            object.AddMember("week_type", atoi(PQgetvalue(ret, i, 25)), allocator);
            object.AddMember("elapsed", atoi(PQgetvalue(ret, i, 26)), allocator);
            object.AddMember("team1_score_live", atoi(PQgetvalue(ret, i, 27)), allocator);
            object.AddMember("team2_score_live", atoi(PQgetvalue(ret, i, 28)), allocator);
            object.AddMember("status", rapidjson::StringRef(PQgetvalue(ret, i, 29)), allocator);
            object.AddMember("is_special", atoi(PQgetvalue(ret, i, 30)), allocator);
            object.AddMember("preview", rapidjson::StringRef(PQgetvalue(ret, i, 31)), allocator);
            object.AddMember("teaser", rapidjson::StringRef(PQgetvalue(ret, i, 32)), allocator);
            object.AddMember("playOff", atoi(PQgetvalue(ret, i, 33)), allocator);

            object.AddMember("team1_score_90", atoi(PQgetvalue(ret, i, 34)), allocator);
            object.AddMember("team2_score_90", atoi(PQgetvalue(ret, i, 35)), allocator);
            object.AddMember("team1_score_pen", atoi(PQgetvalue(ret, i, 36)), allocator);
            object.AddMember("team2_score_pen", atoi(PQgetvalue(ret, i, 37)), allocator);

            object.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 44), allocator), allocator);
            object.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 45), allocator), allocator);

            rapidjson::Value team1Object(rapidjson::kObjectType);
            team1Object.AddMember("id", atoi(PQgetvalue(ret, i, 38)), allocator);
            team1Object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 39)), allocator);
            team1Object.AddMember("shortName", rapidjson::StringRef(PQgetvalue(ret, i, 40)), allocator);
            object.AddMember("team1", team1Object, allocator);

            rapidjson::Value team2Object(rapidjson::kObjectType);
            team2Object.AddMember("id", atoi(PQgetvalue(ret, i, 41)), allocator);
            team2Object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 42)), allocator);
            team2Object.AddMember("shortName", rapidjson::StringRef(PQgetvalue(ret, i, 43)), allocator);
            object.AddMember("team2", team2Object, allocator);

            rapidjson::Value predictObj(rapidjson::kObjectType);
            predictObj.AddMember("id", atoi(PQgetvalue(ret, i, 0)), allocator);
            predictObj.AddMember("user_id", atoi(PQgetvalue(ret, i, 1)), allocator);
            predictObj.AddMember("match_id", atoi(PQgetvalue(ret, i, 2)), allocator);
            predictObj.AddMember("player_api_id", atoi(PQgetvalue(ret, i, 3)), allocator);
            predictObj.AddMember("minutes", atoi(PQgetvalue(ret, i, 4)), allocator);
            predictObj.AddMember("goals", atoi(PQgetvalue(ret, i, 5)), allocator);
            predictObj.AddMember("assists", atoi(PQgetvalue(ret, i, 6)), allocator);
            predictObj.AddMember("yellow_cards", atoi(PQgetvalue(ret, i, 7)), allocator);
            predictObj.AddMember("red_cards", atoi(PQgetvalue(ret, i, 8)), allocator);
            predictObj.AddMember("goals_a", atoi(PQgetvalue(ret, i, 9)), allocator);
            predictObj.AddMember("pen_saved", atoi(PQgetvalue(ret, i, 10)), allocator);
            predictObj.AddMember("pen_missed", atoi(PQgetvalue(ret, i, 11)), allocator);
            predictObj.AddMember("points", atoi(PQgetvalue(ret, i, 12)), allocator);
            predictObj.AddMember("player_name", rapidjson::StringRef(PQgetvalue(ret, i, 13)), allocator);
            predictObj.AddMember("player_pos", rapidjson::StringRef(PQgetvalue(ret, i, 14)), allocator);
            predictObj.AddMember("team_id", atoi(PQgetvalue(ret, i, 15)), allocator);

            object.AddMember("careerPredict", predictObj, allocator);

            betsArray.PushBack(object, allocator);
        }

        document.AddMember("predicts", betsArray, allocator);

        auto generateBetCountQuery = [&](const std::string& condition)
        {
            std::string countSql = "SELECT COUNT(*) FROM career_predicts cp INNER JOIN matches m ON cp.match_id = m.id WHERE cp.user_id = " + userId;
            if (leagueId != "-1")
            {
                countSql += " AND m.league = " + leagueId;
            }
            countSql += condition.size() ? " AND " + condition : "";
            return countSql;
        };

        std::string countAllBetsSql = generateBetCountQuery("");
        PGresult* retAllBets = PQexec(pg, countAllBetsSql.c_str());
        int allBets = (PQntuples(retAllBets) > 0) ? atoi(PQgetvalue(retAllBets, 0, 0)) : 0;
        PQclear(retAllBets);
        document.AddMember("allPredicts", allBets, allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}
