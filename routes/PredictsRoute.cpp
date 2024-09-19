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


        std::string token = req.get_header_value("Authentication");
        auto decoded = jwt::decode(token);
        int userId = decoded.get_payload_claim("id").as_int();

        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string sql = "SELECT * FROM predicts WHERE user_id = "
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
        if (!pg) {
            res.status = 500;  // Internal Server Error
            return;
        }

        // SQL base string
        std::string sqlBase = "SELECT p.*, m.id, l.id as league_id, l.name as league_name, m.season, m.week, m.match_date, "
            "m.team1_score, m.team2_score, m.week_type, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, t1.id as team1_id, t1.name as team1_name, t1.short_name as team1_short_name, "
            "t2.id as team2_id, t2.name as team2_name, t2.short_name as team2_short_name "
            "FROM predicts p "
            "INNER JOIN matches m ON p.match_id = m.id "
            "LEFT JOIN leagues l ON m.league = l.id "
            "LEFT JOIN teams t1 ON m.team1 = t1.id "
            "LEFT JOIN teams t2 ON m.team2 = t2.id "
            "WHERE p.user_id = " + userId +
            (leagueId != "-1" ? " AND m.league = " + leagueId : "") +
            " ORDER BY m.match_date DESC, m.id DESC "
            "LIMIT " + std::to_string(20) + " OFFSET " + std::to_string(offset) + ";";

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

            rapidjson::Value team1Object(rapidjson::kObjectType);
            team1Object.AddMember("id", atoi(PQgetvalue(ret, i, 19)), allocator);
            team1Object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 20)), allocator);
            team1Object.AddMember("shortName", rapidjson::StringRef(PQgetvalue(ret, i, 21)), allocator);
            object.AddMember("team1", team1Object, allocator);

            rapidjson::Value team2Object(rapidjson::kObjectType);
            team2Object.AddMember("id", atoi(PQgetvalue(ret, i, 22)), allocator);
            team2Object.AddMember("name", rapidjson::StringRef(PQgetvalue(ret, i, 23)), allocator);
            team2Object.AddMember("shortName", rapidjson::StringRef(PQgetvalue(ret, i, 24)), allocator);
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

        int totalPredicts = generateCountQuery("p.status <> 0");
        if (totalPredicts == -1) return;  // Check for errors and exit if found

        int totalScorePredicts = generateCountQuery("p.status = 2");
        if (totalScorePredicts == -1) return;  // Check for errors and exit if found

        int totalWinnerPredicts = generateCountQuery("(p.status = 2 OR p.status = 1)");
        if (totalWinnerPredicts == -1) return;  // Check for errors and exit if found

        document.AddMember("totalPredicts", totalPredicts, allocator);
        document.AddMember("totalScorePredicts", totalScorePredicts, allocator);
        document.AddMember("totalWinnerPredicts", totalWinnerPredicts, allocator);

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
            "m.team1_score, m.team2_score, m.week_type, t1.id as team1_id, t1.name as team1_name, t1.short_name as team1_short_name, "
            "t2.id as team2_id, t2.name as team2_name, t2.short_name as team2_short_name "
            "FROM predicts p "
            "INNER JOIN matches m ON p.match_id = m.id "
            "LEFT JOIN leagues l ON m.league = l.id "
            "LEFT JOIN teams t1 ON m.team1 = t1.id "
            "LEFT JOIN teams t2 ON m.team2 = t2.id "
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

        std::string userId = req.get_param_value("match_id");

        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string sql = "SELECT * FROM predicts WHERE match_id = "
            + userId +
            +";";
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
        rapidjson::Value predicts;
        predicts.SetArray();

        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        char* temp = (char*)calloc(4096, sizeof(char));

        int numP1 = 0;
        int numP2 = 0;
        int numDraw = 0;

        for (int i = 0; i < nrows; ++i)
        {
            /*rapidjson::Value object;
            object.SetObject();

            // Handle ID as integer
            int id = atoi(PQgetvalue(ret, i, 0)); // Convert the string from the first column to an integer
            rapidjson::Value idValue;
            idValue.SetInt(id);
            object.AddMember("id", idValue, allocator);

            int userId = atoi(PQgetvalue(ret, i, 1));
            std::string userName = getUserName(pg, userId);
            std::string userAvatar = getUserAvatar(pg, userId);
            int points = getUserPoints(pg, userId);

            // Create user object
            rapidjson::Value userObject;
            userObject.SetObject();
            rapidjson::Value userIdValue;
            userIdValue.SetInt(userId);
            userObject.AddMember("id", userIdValue, allocator);

            rapidjson::Value userNameValue;
            userNameValue.SetString(userName.c_str(), allocator);
            userObject.AddMember("name", userNameValue, allocator);*/

            //rapidjson::Value userAvatarValue;
            //userAvatarValue.SetString(userAvatar.c_str(), allocator);
            //userObject.AddMember("avatar", userAvatarValue, allocator);

            //userObject.AddMember("points", points, allocator);

            // Add user object to the main JSON object
            //object.AddMember("user", userObject, allocator);

            //int matchId = atoi(PQgetvalue(ret, i, 2));
            //idValue.SetInt(matchId);
            //object.AddMember("match_id", idValue, allocator);

            int score1 = atoi(PQgetvalue(ret, i, 3));
            //idValue.SetInt(score1);
            //object.AddMember("team1_score", idValue, allocator);

            int score2 = atoi(PQgetvalue(ret, i, 4));
            // idValue.SetInt(score2);
            // object.AddMember("team2_score", idValue, allocator);

            // int status = atoi(PQgetvalue(ret, i, 5));
            // idValue.SetInt(status);
            // object.AddMember("status", idValue, allocator);

            if (score1 > score2) ++numP1;
            else if (score2 > score1) ++numP2;
            else ++numDraw;

          //  predicts.PushBack(object, allocator);
        }
        free(temp);

     //   document.AddMember("predicts", predicts, allocator);
        document.AddMember("numP1", numP1, allocator);
        document.AddMember("numP2", numP2, allocator);
        document.AddMember("numDraw", numDraw, allocator);
        document.AddMember("numPredicts", nrows, allocator);


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

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetMatchPredictsTop3()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        std::string matchId = req.get_param_value("match_id");

        PGconn* pg = ConnectionPool::Get()->getConnection();
        // Join the predicts with users table and order by points descending, limit to 3
        std::string sql = "SELECT p.*, u.name, u.avatar, u.points FROM predicts p "
            "JOIN users u ON p.user_id = u.id "
            "WHERE p.match_id = " + matchId + " "
            "ORDER BY u.points DESC LIMIT 20;";
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

        if (!mCachedTable.size()) CacheTable();
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

            int pos = -1;
            auto it = std::find(mCachedTable.begin(), mCachedTable.end(), userId);

            if (it != mCachedTable.end()) 
            {
                // If the element is found, calculate the index
                int index = std::distance(mCachedTable.begin(), it);
                pos = index + 1;
            }

            userObject.AddMember("position", pos, allocator);  // Add position based on loop index

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

void PredictsRoute::CacheTable()
{
    std::string sql = "SELECT u.id, u.name, u.avatar, u.points, COUNT(p.id) AS total_predictions FROM users u INNER JOIN predicts p ON u.id = p.user_id GROUP BY u.id, u.name, u.avatar, u.points HAVING COUNT(p.id) > 0 ORDER BY u.points DESC, total_predictions DESC LIMIT 20;";

    PGconn* pg = ConnectionPool::Get()->getConnection();
    PGresult* ret = PQexec(pg, sql.c_str());

    if (PQresultStatus(ret) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Failed to fetch data: %s", PQerrorMessage(pg));
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
        return;
    }

    int nrows = PQntuples(ret);
    mCachedTable.clear();
    for (int i = 0; i < nrows; ++i) 
    {
        mCachedTable.push_back(atoi(PQgetvalue(ret, i, 0)));
    }
    PQclear(ret);
    ConnectionPool::Get()->releaseConnection(pg);
}

std::function<void(const httplib::Request&, httplib::Response&)> PredictsRoute::GetTableByPoints()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        // Get the 'page' query parameter, default to 1 if not provided
        int page = 1;
        if (req.has_param("page")) {
            page = std::stoi(req.get_param_value("page"));
        }

        int limit = 20; // Number of users per page
        int offset = (page - 1) * limit; // Calculate the offset based on the page

        PGconn* pg = ConnectionPool::Get()->getConnection();
        if (!pg) {
            res.status = 500;  // Internal Server Error
            return;
        }

        // Updated SQL query to join users with predicts, count the total number of predictions per user, and paginate
        std::string sql = "SELECT u.id, u.name, u.avatar, u.points, COUNT(p.id) AS total_predictions "
            "FROM users u "
            "INNER JOIN predicts p ON u.id = p.user_id "
            "GROUP BY u.id, u.name, u.avatar, u.points "
            "HAVING COUNT(p.id) > 0 "
            "ORDER BY u.points DESC, total_predictions DESC, u.id ASC "  // Added u.id to ensure stable ordering
            "LIMIT " + std::to_string(limit) + " OFFSET " + std::to_string(offset) + ";";


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
        document.SetArray();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        if (page == 1) mCachedTable.clear();
        for (int i = 0; i < nrows; ++i) {
            rapidjson::Value object(rapidjson::kObjectType);
            object.AddMember("id", atoi(PQgetvalue(ret, i, 0)), allocator);
            object.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 1), allocator), allocator);
            object.AddMember("avatar", rapidjson::Value(PQgetvalue(ret, i, 2), allocator), allocator);
            object.AddMember("predictions", atoi(PQgetvalue(ret, i, 3)), allocator);
            object.AddMember("totalPredictions", atoi(PQgetvalue(ret, i, 4)), allocator);  // Include the count of predictions

            document.PushBack(object, allocator);

            if (page == 1) mCachedTable.push_back(atoi(PQgetvalue(ret, i, 0)));
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
        if (lid >= 1) {
            sql += "WHERE m.league = " + std::to_string(lid) + " ";
        }

        sql += "GROUP BY u.id, u.name, u.avatar "
            "ORDER BY success_rate DESC, status_2_count DESC "
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
        std::string sql = "INSERT INTO predicts(user_id, match_id, team1_score, team2_score, status) VALUES("
            + std::to_string(userId) + ", "
            + std::to_string(matchId) + ", "
            + std::to_string(team1) + ", "
            + std::to_string(team2) + ", "
            + "0"
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