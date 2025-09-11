#include "MatchesRoute.h"
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include "../managers/PQManager.h"
#include <jwt-cpp/jwt.h>
#include "../managers/MatchesManager.h"

MatchesRoute* MatchesRoute::sInstance = nullptr;

static std::string ReadFile(const std::string& filename)
{
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

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
        if (league_id.empty()) 
        {
            res.set_content("League ID is required", "text/plain");
            res.status = 400; // Bad Request
            return;
        }

        // Validate league_id
        char* end;
        long lid = strtol(league_id.c_str(), &end, 10);
        if (*end) 
        {
            res.set_content("Invalid league ID", "text/plain");
            res.status = 400; // Bad Request
            return;
        }

        std::string season = req.get_param_value("season");
        season = season.substr(2);
        std::string week = req.get_param_value("week");
        std::string lang = "en";
        if (req.has_param("lang")) lang = req.get_param_value("lang");
        std::string game = "eltorneo";
        if (req.has_param("game")) 
        {
            std::string g = req.get_param_value("game");
            if (g == "beatbet") game = g;
            if (g == "fireball") game = g;
        }

        PGconn* pg = ConnectionPool::Get()->getConnection();
        rapidjson::Document document;
        bool ok = false;
        if (game == "beatbet") 
        {
            ok = MatchesManager::GetLeagueMatchesWithBets(pg, userId, lid, season, week, lang, document);
        }
        else if (game == "fireball")
        {
            ok = MatchesManager::GetLeagueMatchesWithFireball(pg, userId, lid, season, week, lang, document);
        }
        else 
        {
            ok = MatchesManager::GetLeagueMatchesWithPredicts(pg, userId, lid, season, week, lang, document);
        }

        if (!ok) 
        {
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;

        ConnectionPool::Get()->releaseConnection(pg);
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> MatchesRoute::GetTrailers()
{
    return [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        rapidjson::Document d;
        d.SetArray();

        rapidjson::Value title;

        rapidjson::Value t1;
        t1.SetObject();
        title.SetString("Lamine Yamal", d.GetAllocator());
        t1.AddMember("title", title, d.GetAllocator());

        title.SetString("The Amazing Spider-Man", d.GetAllocator());
        t1.AddMember("subtitle", title, d.GetAllocator());

        title.SetString("w6kDZYXL94w", d.GetAllocator());
        t1.AddMember("video", title, d.GetAllocator());

        title.SetString("spider_man", d.GetAllocator());
        t1.AddMember("image", title, d.GetAllocator());

        rapidjson::Value t2;
        t2.SetObject();
        title.SetString("Erling Haaland", d.GetAllocator());
        t2.AddMember("title", title, d.GetAllocator());

        title.SetString("Dead Men Tell No Tales", d.GetAllocator());
        t2.AddMember("subtitle", title, d.GetAllocator());

        title.SetString("AMZyXoQtlM8", d.GetAllocator());
        t2.AddMember("video", title, d.GetAllocator());

        title.SetString("dead_men_tell", d.GetAllocator());
        t2.AddMember("image", title, d.GetAllocator());

        rapidjson::Value t3;
        t3.SetObject();
        title.SetString("Real Madrid", d.GetAllocator());
        t3.AddMember("title", title, d.GetAllocator());

        title.SetString("Teenage Mutant Ninja Turtles", d.GetAllocator());
        t3.AddMember("subtitle", title, d.GetAllocator());

        title.SetString("I3I7uDpDLtw", d.GetAllocator());
        t3.AddMember("video", title, d.GetAllocator());

        title.SetString("tmnt", d.GetAllocator());
        t3.AddMember("image", title, d.GetAllocator());

        rapidjson::Value t4;
        t4.SetObject();
        title.SetString("Mohamed Salah", d.GetAllocator());
        t4.AddMember("title", title, d.GetAllocator());

        title.SetString("Deadpool", d.GetAllocator());
        t4.AddMember("subtitle", title, d.GetAllocator());

        title.SetString("WMap1blJ5e4", d.GetAllocator());
        t4.AddMember("video", title, d.GetAllocator());

        title.SetString("deadpool", d.GetAllocator());
        t4.AddMember("image", title, d.GetAllocator());

        rapidjson::Value t5;
        t5.SetObject();
        title.SetString("Champions League", d.GetAllocator());
        t5.AddMember("title", title, d.GetAllocator());

        title.SetString("Mortal Kombat", d.GetAllocator());
        t5.AddMember("subtitle", title, d.GetAllocator());

        title.SetString("XxAlZ1BdZJc", d.GetAllocator());
        t5.AddMember("video", title, d.GetAllocator());

        title.SetString("mortal_kombat", d.GetAllocator());
        t5.AddMember("image", title, d.GetAllocator());

        rapidjson::Value t6;
        t6.SetObject();
        title.SetString("Robert Lewandowski", d.GetAllocator());
        t6.AddMember("title", title, d.GetAllocator());

        title.SetString("Devil May Cry", d.GetAllocator());
        t6.AddMember("subtitle", title, d.GetAllocator());

        title.SetString("x7WG8lvW6TM", d.GetAllocator());
        t6.AddMember("video", title, d.GetAllocator());

        title.SetString("dmc", d.GetAllocator());
        t6.AddMember("image", title, d.GetAllocator());

        d.PushBack(t6, d.GetAllocator());
        d.PushBack(t5, d.GetAllocator());
        d.PushBack(t4, d.GetAllocator());
        d.PushBack(t1, d.GetAllocator());
        d.PushBack(t2, d.GetAllocator());
        d.PushBack(t3, d.GetAllocator());

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        d.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200; // OK
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
        if (team_id.empty()) 
        {
            res.set_content("Team ID is required", "text/plain");
            res.status = 400; // Bad Request
            return;
        }

        std::string game = "eltorneo";
        if (req.has_param("game"))
        {
            std::string g = req.get_param_value("game");
            if (g == "beatbet") game = g;
            if (g == "fireball") game = g;
        }

        // Validate team_id
        char* end;
        long tid = strtol(team_id.c_str(), &end, 10);
        if (*end) 
        {
            res.set_content("Invalid team ID", "text/plain");
            res.status = 400; // Bad Request
            return;
        }

        // Connect to the database
        PGconn* pg = ConnectionPool::Get()->getConnection();
        
        bool ok;
        rapidjson::Document document;
        if (game == "beatbet")
        {
            ok = MatchesManager::GetMatchesTeamWithBets(pg, userId, tid, document);
        }
        else if (game == "fireball")
        {
            ok = MatchesManager::GetMatchesTeamWithFireball(pg, userId, tid, document);
        }
        else 
        {
            ok = MatchesManager::GetMatchesTeamWithPredicts(pg, userId, tid, document);
        }
        
        if (!ok) 
        {
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500; // Internal Server Error
            return;
        }

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200; // OK

        ConnectionPool::Get()->releaseConnection(pg);
    };
}

bool FillTeamSquds(PGconn* pg, long tid, rapidjson::Value& document, rapidjson::Document::AllocatorType& allocator)
{
    std::string sql = "SELECT id, name, age, number, position, photo, api_id FROM team_players WHERE team_id = " + std::to_string(tid) 
        + " ORDER BY position;";
    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Failed to fetch matches: %s", PQerrorMessage(pg));
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
        return false;
    }

    int nrows = PQntuples(ret);
    for (int i = 0; i < nrows; ++i)
    {
        rapidjson::Value matchObj(rapidjson::kObjectType);
        matchObj.AddMember("id", atoi(PQgetvalue(ret, i, 0)), allocator);
        matchObj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 1), allocator), allocator);
        matchObj.AddMember("age", atoi(PQgetvalue(ret, i, 2)), allocator);
        matchObj.AddMember("number", atoi(PQgetvalue(ret, i, 3)), allocator);
        matchObj.AddMember("position", rapidjson::Value(PQgetvalue(ret, i, 4), allocator), allocator);
        matchObj.AddMember("photo", rapidjson::Value(PQgetvalue(ret, i, 5), allocator), allocator);
        std::string playerApiId = (PQgetvalue(ret, i, 6));
        matchObj.AddMember("apiId", atoi(PQgetvalue(ret, i, 6)), allocator);
        sql = "SELECT player_api_id, league_id, games, rating, goals, assists FROM player_stats WHERE team_id = "
            + std::to_string(tid) + " AND player_api_id = " + playerApiId + ";";
        PGresult* statRet = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_TUPLES_OK) 
        {
            fprintf(stderr, "Failed to player stats: %s", PQerrorMessage(pg));
            PQclear(statRet);
            ConnectionPool::Get()->releaseConnection(pg);
            document.PushBack(matchObj, allocator);
            continue;
        }
        int nStats = PQntuples(statRet);
        rapidjson::Value stats;
        stats.SetArray();
        for (int s = 0; s < nStats; ++s)
        {   
            rapidjson::Value statObj;
            statObj.SetObject();
            statObj.AddMember("playerApiId", atoi(PQgetvalue(statRet, s, 0)), allocator);
            statObj.AddMember("leagueId", atoi(PQgetvalue(statRet, s, 1)), allocator);
            statObj.AddMember("games", atoi(PQgetvalue(statRet, s, 2)), allocator);
            statObj.AddMember("rating", rapidjson::Value(PQgetvalue(statRet, s, 3), allocator), allocator);
            statObj.AddMember("goals", atoi(PQgetvalue(statRet, s, 4)), allocator);
            statObj.AddMember("assists", atoi(PQgetvalue(statRet, s, 5)), allocator);
            stats.PushBack(statObj, allocator);
        }
        matchObj.AddMember("stats", stats, allocator);
        PQclear(statRet);
        document.PushBack(matchObj, allocator);
    }
    PQclear(ret);

    return true;
}

bool FillTeamPlayers(PGconn* pg, long tid, const std::string& position, rapidjson::Value& document, rapidjson::Document::AllocatorType& allocator)
{
    std::vector<std::string> positions;
    std::stringstream ss(position);
    std::string item;

    while (std::getline(ss, item, ',')) 
    {
        if (item == "GK") positions.push_back("'Goalkeeper'");
        else if (item == "DF") positions.push_back("'Defender'");
        else if (item == "MF") positions.push_back("'Midfielder'");
        else if (item == "FW") positions.push_back("'Attacker'");
    }

    std::string sql = "SELECT id, name, age, number, position, photo, api_id FROM team_players WHERE team_id = "
        + std::to_string(tid);
    if (!positions.empty()) {
        sql += " AND position IN (";
        for (size_t i = 0; i < positions.size(); ++i) {
            sql += positions[i];
            if (i != positions.size() - 1) sql += ",";
        }
        sql += ")";
    }
    sql += " ORDER BY position;";

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK) 
    {
        fprintf(stderr, "Failed to fetch team players: %s", PQerrorMessage(pg));
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
        return false;
    }

    int nrows = PQntuples(ret);
    for (int i = 0; i < nrows; ++i)
    {
        rapidjson::Value matchObj(rapidjson::kObjectType);
        matchObj.AddMember("id", atoi(PQgetvalue(ret, i, 0)), allocator);
        matchObj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 1), allocator), allocator);
        matchObj.AddMember("age", atoi(PQgetvalue(ret, i, 2)), allocator);
        matchObj.AddMember("number", atoi(PQgetvalue(ret, i, 3)), allocator);
        matchObj.AddMember("position", rapidjson::Value(PQgetvalue(ret, i, 4), allocator), allocator);
        matchObj.AddMember("photo", rapidjson::Value(PQgetvalue(ret, i, 5), allocator), allocator);
        std::string playerApiId = (PQgetvalue(ret, i, 6));
        matchObj.AddMember("apiId", atoi(PQgetvalue(ret, i, 6)), allocator);
        sql = "SELECT player_api_id, league_id, games, rating, goals, assists FROM player_stats WHERE team_id = "
            + std::to_string(tid) + " AND player_api_id = " + playerApiId + ";";
        PGresult* statRet = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to get player stats: %s", PQerrorMessage(pg));
            PQclear(statRet);
            ConnectionPool::Get()->releaseConnection(pg);
            document.PushBack(matchObj, allocator);
            continue;
        }
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
 
        matchObj.AddMember("games", games, allocator);
        matchObj.AddMember("goals", goals, allocator);
        matchObj.AddMember("assists", assists, allocator);
        matchObj.AddMember("rating", rating, allocator);
        matchObj.AddMember("teamId", tid, allocator);

        PQclear(statRet);
        document.PushBack(matchObj, allocator);
    }
    PQclear(ret);

    return true;
}


std::function<void(const httplib::Request&, httplib::Response&)> MatchesRoute::GetTeam()
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
        if (team_id.empty()) 
        {
            res.set_content("Team ID is required", "text/plain");
            res.status = 400; // Bad Request
            return;
        }

        // Validate team_id
        char* end;
        long tid = strtol(team_id.c_str(), &end, 10);
        if (*end) 
        {
            res.set_content("Invalid team ID", "text/plain");
            res.status = 400; // Bad Request
            return;
        }

        std::string game = "eltorneo";
        if (req.has_param("game"))
        {
            std::string g = req.get_param_value("game");
            if (g == "beatbet") game = g;
            if (g == "fireball") game = g;
        }

        // Connect to the database
        PGconn* pg = ConnectionPool::Get()->getConnection();
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Value vMatches(rapidjson::kArrayType);
        vMatches.SetArray();
        if (game == "beatbet") 
        {
            MatchesManager::FillTeamMatchesWithBets(pg, userId, tid, vMatches, document.GetAllocator(), ETeamMatch::Upcoming);
            MatchesManager::FillTeamMatchesWithBets(pg, userId, tid, vMatches, document.GetAllocator(), ETeamMatch::Live);
            MatchesManager::FillTeamMatchesWithBets(pg, userId, tid, vMatches, document.GetAllocator(), ETeamMatch::Finished);
        }
        else if (game == "fireball")
        {
            MatchesManager::FillTeamMatchesWithFireball(pg, userId, tid, vMatches, document.GetAllocator(), ETeamMatch::Upcoming);
            MatchesManager::FillTeamMatchesWithFireball(pg, userId, tid, vMatches, document.GetAllocator(), ETeamMatch::Live);
            MatchesManager::FillTeamMatchesWithFireball(pg, userId, tid, vMatches, document.GetAllocator(), ETeamMatch::Finished);
        }
        else 
        {
            MatchesManager::FillTeamMatchesWithPredicts(pg, userId, tid, vMatches, document.GetAllocator(), ETeamMatch::Upcoming);
            MatchesManager::FillTeamMatchesWithPredicts(pg, userId, tid, vMatches, document.GetAllocator(), ETeamMatch::Live);
            MatchesManager::FillTeamMatchesWithPredicts(pg, userId, tid, vMatches, document.GetAllocator(), ETeamMatch::Finished);
        }
        
        document.AddMember("matches", vMatches, document.GetAllocator());

        rapidjson::Value vPlayers(rapidjson::kArrayType);
        vPlayers.SetArray();
        FillTeamSquds(pg, tid, vPlayers, document.GetAllocator());
        document.AddMember("squad", vPlayers, document.GetAllocator());

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200; // OK

        ConnectionPool::Get()->releaseConnection(pg);
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> MatchesRoute::GetTeamPlayers()
{
    return [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        // Extract team_id from query parameters
        std::string team_id = req.get_param_value("team_id");
        if (team_id.empty())
        {
            res.set_content("Team ID is required", "text/plain");
            res.status = 400; // Bad Request
            return;
        }

        // Validate team_id
        char* end;
        long tid = strtol(team_id.c_str(), &end, 10);
        if (*end)
        {
            res.set_content("Invalid team ID", "text/plain");
            res.status = 400; // Bad Request
            return;
        }

        std::string position;
        if (req.has_param("position"))
        {
            position = req.get_param_value("position");
        }

        // Connect to the database
        PGconn* pg = ConnectionPool::Get()->getConnection();
        rapidjson::Document document;
        document.SetObject();
       
        rapidjson::Value vPlayers(rapidjson::kArrayType);
        vPlayers.SetArray();
        FillTeamPlayers(pg, tid, position, vPlayers, document.GetAllocator());
        document.AddMember("players", vPlayers, document.GetAllocator());

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200; // OK

        ConnectionPool::Get()->releaseConnection(pg);
    };
}


std::function<void(const httplib::Request&, httplib::Response&)> MatchesRoute::GetMatchPlayers()
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

        std::string team1_id = req.get_param_value("team1_id");
        std::string team2_id = req.get_param_value("team2_id");

        int t1id = atoi(team1_id.c_str());
        int t2id = atoi(team2_id.c_str());

        PGconn* pg = ConnectionPool::Get()->getConnection();
        rapidjson::Document document;
        document.SetObject();

        {
            rapidjson::Value vPlayers(rapidjson::kArrayType);
            vPlayers.SetArray();
            FillTeamSquds(pg, t1id, vPlayers, document.GetAllocator());
            document.AddMember("team1Players", vPlayers, document.GetAllocator());
        }

        {
            rapidjson::Value vPlayers(rapidjson::kArrayType);
            vPlayers.SetArray();
            FillTeamSquds(pg, t2id, vPlayers, document.GetAllocator());
            document.AddMember("team2Players", vPlayers, document.GetAllocator());
        }
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200; // OK

        ConnectionPool::Get()->releaseConnection(pg);
    };
}


static int getRandomNumber(int n) 
{
    return rand() % n;
}

std::function<void(const httplib::Request&, httplib::Response&)> MatchesRoute::GetSpecialMatch()
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

        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string sql = "SELECT sm.* "
            "FROM special_matches sm "
            "JOIN matches m ON sm.match_id = m.id "
            "WHERE m.match_date > EXTRACT(EPOCH FROM NOW()) * 1000;"; // Compare match_date with the current time (in milliseconds)
           
        PGresult* ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch matches: %s", PQerrorMessage(pg));
            PQclear(ret);
            res.set_content("[]", "application/json");
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }
        int nm = PQntuples(ret);
        if (nm <= 0) 
        {
            fprintf(stderr, "Failed to fetch matches: %s", PQerrorMessage(pg));
            PQclear(ret);
            res.set_content("[]", "application/json");
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }

        int matchId = -1;
        std::string title;
        std::string stadium;
        std::string points;

        for (int i = 0; i < nm; ++i)
        {
            int id = atoi(PQgetvalue(ret, i, 0));
            std::string tt = PQgetvalue(ret, i, 1);
            std::string ss = PQgetvalue(ret, i, 2);
            int mid = atoi(PQgetvalue(ret, i, 3));
            std::string pp = PQgetvalue(ret, i, 4);


            // If user exists, check if they have predicted this match
            if (userId > 0)
            {
                std::string sql = "SELECT id FROM predicts WHERE user_id = "
                    + std::to_string(userId) + " AND match_id = " + std::to_string(mid) + ";";
                PGresult* predRet = PQexec(pg, sql.c_str());
                int n = PQntuples(predRet);
                PQclear(predRet);

                if (n > 0)
                {
                    continue;
                }
            }
           
            matchId = mid;
            title = tt;
            stadium = ss;
            points = pp;
        }
        
        if (matchId == -1) 
        {
            PQclear(ret);
            res.set_content("[]", "application/json");
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 200;
            return; // User has already predicted, return empty
        }

        // Fetch match details from matches and teams table
        sql = R"(
            SELECT m.id, m.league, m.week, m.week_type, m.match_date, m.is_special, t1.id, t1.name, t1.short_name, 
                   t2.id, t2.name, t2.short_name, l.name AS league_name, m.teaser, m.season 
            FROM matches m
            JOIN teams t1 ON m.team1 = t1.id
            JOIN teams t2 ON m.team2 = t2.id
            JOIN leagues l ON m.league = l.id
            WHERE m.id = )" + std::to_string(matchId) + ";";

        PGresult* matchRet = PQexec(pg, sql.c_str());
        if (PQresultStatus(matchRet) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch match details: %s", PQerrorMessage(pg));
            PQclear(matchRet);
            PQclear(ret);
            res.set_content("[]", "application/json");
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }

        int match_id = atoi(PQgetvalue(matchRet, 0, 0));
        int league_id = atoi(PQgetvalue(matchRet, 0, 1));
        int week = atoi(PQgetvalue(matchRet, 0, 2));
        int weekType = atoi(PQgetvalue(matchRet, 0, 3));
        int64_t matchDate = atoll(PQgetvalue(matchRet, 0, 4));
        int isSpecial = atoi(PQgetvalue(matchRet, 0, 5));

        // Prepare the JSON response
        rapidjson::Document document;
        document.SetObject();
        auto& allocator = document.GetAllocator();

        rapidjson::Value matchObject;
        matchObject.SetObject();
        matchObject.AddMember("id", match_id, allocator);
        matchObject.AddMember("league", league_id, allocator);
        matchObject.AddMember("week", week, allocator);
        matchObject.AddMember("weekType", weekType, allocator);
        matchObject.AddMember("date", matchDate, allocator);
        matchObject.AddMember("is_special", isSpecial, allocator);

        // Team 1 details
        rapidjson::Value team1Object;
        team1Object.SetObject();
        team1Object.AddMember("id", atoi(PQgetvalue(matchRet, 0, 6)), allocator);
        team1Object.AddMember("name", rapidjson::Value(PQgetvalue(matchRet, 0, 7), allocator), allocator);
        team1Object.AddMember("shortName", rapidjson::Value(PQgetvalue(matchRet, 0, 8), allocator), allocator);

        // Team 2 details
        rapidjson::Value team2Object;
        team2Object.SetObject();
        team2Object.AddMember("id", atoi(PQgetvalue(matchRet, 0, 9)), allocator);
        team2Object.AddMember("name", rapidjson::Value(PQgetvalue(matchRet, 0, 10), allocator), allocator);
        team2Object.AddMember("shortName", rapidjson::Value(PQgetvalue(matchRet, 0, 11), allocator), allocator);

        matchObject.AddMember("team1", team1Object, allocator);
        matchObject.AddMember("team2", team2Object, allocator);
        matchObject.AddMember("leagueName", rapidjson::Value(PQgetvalue(matchRet, 0, 12), allocator), allocator);
        matchObject.AddMember("teaser", rapidjson::Value(PQgetvalue(matchRet, 0, 13), allocator), allocator);
        matchObject.AddMember("season", rapidjson::Value(PQgetvalue(matchRet, 0, 14), allocator), allocator);

        // Title and Stadium
        rapidjson::Value v;
        v.SetString(title.c_str(), allocator);
        document.AddMember("title", v, allocator);

        v.SetString(stadium.c_str(), allocator);
        std::string translatedTitle = "";
        document.AddMember("stadium", v, allocator);

        rapidjson::Value vv;
        vv.SetString(points.c_str(), allocator);
        matchObject.AddMember("special_match_points", vv, allocator);
        document.AddMember("match", matchObject, allocator);

        {
            std::string filename = "data/special.json";
            std::string jsonString = ReadFile(filename);
            rapidjson::Document d;
            d.Parse(jsonString.c_str());
            std::string lang = req.get_param_value("lang");
            translatedTitle = d[lang.c_str()][title.c_str()].GetString();
        }
        v.SetString(translatedTitle.c_str(), allocator);
        document.AddMember("translatedTitle", v, allocator);

        // Convert to JSON string and return
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;

        PQclear(matchRet);
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

        std::string game = "eltorneo";
        if (req.has_param("game"))
        {
            std::string g = req.get_param_value("game");
            if (g == "beatbet") game = g;
            if (g == "fireball") game = g;
        }

        std::string lang = "en";
        if (req.has_param("lang")) lang = req.get_param_value("lang");

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
        rapidjson::Document document;
        bool ok;
        if (game == "beatbet")
        {
            ok = MatchesManager::GetMatchesByDateWithBets(pg, userId, dayStart, dayEnd, lang, document);
        }
        else if (game == "fireball")
        {
            ok = MatchesManager::GetMatchesByDateWithFireball(pg, userId, dayStart, dayEnd, lang, document);
        }
        else 
        {
            ok = MatchesManager::GetMatchesByDateWithPredicts(pg, userId, dayStart, dayEnd, lang, document);
        }

        if (!ok) 
        {
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500; // Internal Server Error
            return;
        }

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200; // OK

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
        if (token.size()) 
        {
            auto decoded = jwt::decode(token);
            userId = decoded.get_payload_claim("id").as_int();
        }

        std::string game = "eltorneo";
        if (req.has_param("game"))
        {
            std::string g = req.get_param_value("game");
            if (g == "beatbet") game = g;
            else if (g == "fireball") game = g;
        }

        // Get the current timestamp in milliseconds
        auto now = std::chrono::system_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto epoch = now_ms.time_since_epoch();
        auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
        long long currentTimeMs = value.count();

        // Connect to the database
        PGconn* pg = ConnectionPool::Get()->getConnection();
     
        rapidjson::Document document;
        bool ok;
        if (game == "beatbet") 
        {
            ok = MatchesManager::GetMatchesLiveWithBets(pg, userId, currentTimeMs, document);
        }
        else if (game == "fireball")
        {
            ok = MatchesManager::GetMatchesLiveWithFireball(pg, userId, currentTimeMs, document);
        }
        else 
        {
            ok = MatchesManager::GetMatchesLiveWithPredicts(pg, userId, currentTimeMs, document);
        }
        if (!ok) 
        {
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500; // Internal Server Error
            return;
        }

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200; // OK

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
        if (token.size()) 
        {
            auto decoded = jwt::decode(token);
            userId = decoded.get_payload_claim("id").as_int();
        }

        std::string game = "eltorneo";
        if (req.has_param("game"))
        {
            std::string g = req.get_param_value("game");
            if (g == "beatbet") game = g;
            else if (g == "fireball") game = g;
        }

        // Get the current timestamp in milliseconds
        auto now = std::chrono::system_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto epoch = now_ms.time_since_epoch();
        auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
        long long currentTimeMs = value.count();

        // Connect to the database
        PGconn* pg = ConnectionPool::Get()->getConnection();
       
        bool ok;
        rapidjson::Document document;
        if (game == "beatbet") 
        {
            ok = MatchesManager::GetMatchesUpcomingWithBets(pg, userId, currentTimeMs, document);
        }
        else if (game == "fireball")
        {
            ok = MatchesManager::GetMatchesUpcomingWithFireball(pg, userId, currentTimeMs, document);
        }
        else
        {
            ok = MatchesManager::GetMatchesUpcomingWithPredicts(pg, userId, currentTimeMs, document);
        }
        if (!ok)
        {
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500; // Internal Server Error
            return;
        }

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200; // OK

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
            std::string comments = (PQgetvalue(ret, i, 9));

            eValue.AddMember("elapsed", elapsed, allocator);
            eValue.AddMember("extra", extra, allocator);
            eValue.AddMember("team", team, allocator);
            eValue.AddMember("player", rapidjson::Value(player.c_str(), allocator), allocator);
            eValue.AddMember("assist", rapidjson::Value(assist.c_str(), allocator), allocator);
            eValue.AddMember("type", rapidjson::Value(type.c_str(), allocator), allocator);
            eValue.AddMember("detail", rapidjson::Value(detail.c_str(), allocator), allocator);
            eValue.AddMember("comments", rapidjson::Value(comments.c_str(), allocator), allocator);
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

std::function<void(const httplib::Request&, httplib::Response&)> MatchesRoute::GetMatchOdds()
{
    return [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        auto matchId = req.get_param_value("match_id");
        std::string token = req.get_header_value("Authentication");
        int userId = -1;

        if (!token.empty()) {
            auto decoded = jwt::decode(token);
            userId = decoded.get_payload_claim("id").as_int();
        }

        PGconn* pg = ConnectionPool::Get()->getConnection();

        // SQL query to get odds
        std::string sql = "SELECT * FROM odds WHERE match_id = " + matchId + ";";
        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK) {
            fprintf(stderr, "Failed to fetch match odds: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        for (int i = 0; i < nrows; ++i) {
            float w1 = atof(PQgetvalue(ret, i, 2));
            float x = atof(PQgetvalue(ret, i, 3));
            float w2 = atof(PQgetvalue(ret, i, 4));
            float x1 = atof(PQgetvalue(ret, i, 5));
            float x12 = atof(PQgetvalue(ret, i, 6));
            float x2 = atof(PQgetvalue(ret, i, 7));

            document.AddMember("w1", w1, allocator);
            document.AddMember("x", x, allocator);
            document.AddMember("w2", w2, allocator);
            document.AddMember("x1", x1, allocator);
            document.AddMember("x12", x12, allocator);
            document.AddMember("x2", x2, allocator);
        }

        PQclear(ret); // Free result after processing odds

        // If user is authenticated, fetch their bet for this match
        if (userId != -1) {
            std::string betSql = "SELECT id, bet, amount, odd, status FROM bets WHERE user_id = " +
                std::to_string(userId) + " AND match_id = " + matchId + " LIMIT 1;";
            PGresult* betResult = PQexec(pg, betSql.c_str());

            if (PQresultStatus(betResult) == PGRES_TUPLES_OK && PQntuples(betResult) > 0) {
                rapidjson::Value betObject(rapidjson::kObjectType);
                betObject.AddMember("id", atoi(PQgetvalue(betResult, 0, 0)), allocator);
                betObject.AddMember("bet", rapidjson::Value(PQgetvalue(betResult, 0, 1), allocator), allocator);
                betObject.AddMember("amount", atoi(PQgetvalue(betResult, 0, 2)), allocator);
                betObject.AddMember("odd", atof(PQgetvalue(betResult, 0, 3)), allocator);
                betObject.AddMember("status", atoi(PQgetvalue(betResult, 0, 4)), allocator);

                document.AddMember("bet", betObject, allocator);
            }

            PQclear(betResult); // Free result after processing bet
        }

        ConnectionPool::Get()->releaseConnection(pg);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;
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
            "player_bcolor2, gk_color2, gk_ncolor2, gk_bcolor2, coach1, coach2, coach1_photo, coach2_photo, coach1_api_id, coach2_api_id "
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

        rapidjson::Value coach1Photo(PQgetvalue(ret, 0, 16), allocator);
        rapidjson::Value coach2Photo(PQgetvalue(ret, 0, 17), allocator);

        rapidjson::Value coach1ApiId(PQgetvalue(ret, 0, 18), allocator);
        rapidjson::Value coach2ApiId(PQgetvalue(ret, 0, 19), allocator);

        // Add them to the JSON objects
        team1.AddMember("formation", formation1, allocator);
        team1.AddMember("player_color", player_color1, allocator);
        team1.AddMember("player_ncolor", player_ncolor1, allocator);
        team1.AddMember("player_bcolor", player_bcolor1, allocator);
        team1.AddMember("gk_color", gk_color1, allocator);
        team1.AddMember("gk_ncolor", gk_ncolor1, allocator);
        team1.AddMember("gk_bcolor", gk_bcolor1, allocator);
        team1.AddMember("coach", coach1, allocator);
        team1.AddMember("coachPhoto", coach1Photo, allocator);
        team1.AddMember("coachApiId", coach1ApiId, allocator);

        team2.AddMember("formation", formation2, allocator);
        team2.AddMember("player_color", player_color2, allocator);
        team2.AddMember("player_ncolor", player_ncolor2, allocator);
        team2.AddMember("player_bcolor", player_bcolor2, allocator);
        team2.AddMember("gk_color", gk_color2, allocator);
        team2.AddMember("gk_ncolor", gk_ncolor2, allocator);
        team2.AddMember("gk_bcolor", gk_bcolor2, allocator);
        team2.AddMember("coach", coach2, allocator);
        team2.AddMember("coachPhoto", coach2Photo, allocator);
        team2.AddMember("coachApiId", coach2ApiId, allocator);

        // Query players for both teams
        std::string sqlPlayers = "SELECT name, number, grid, start11, team, pos, api_id FROM lineups_players WHERE lineup IN "
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

        for (int i = 0; i < playerRows; ++i) 
        {
            rapidjson::Value player(rapidjson::kObjectType);
            player.AddMember("name", rapidjson::Value(PQgetvalue(retPlayers, i, 0), allocator), allocator);
            player.AddMember("number", std::stoi(PQgetvalue(retPlayers, i, 1)), allocator);
            player.AddMember("grid", rapidjson::Value(PQgetvalue(retPlayers, i, 2), allocator), allocator);
            player.AddMember("start11", std::stoi(PQgetvalue(retPlayers, i, 3)), allocator);
            player.AddMember("pos", rapidjson::Value(PQgetvalue(retPlayers, i, 5), allocator), allocator);
            int playerApiId = std::stoi(PQgetvalue(retPlayers, i, 6));
            player.AddMember("apiId", playerApiId, allocator);

            std::string playerStatsSql = "SELECT rating, goals, assists, yellow, red, minutes FROM match_players WHERE api_id = "
                + std::to_string(playerApiId) + " AND match_id = " + matchId + ";";

            PGresult* statsRes = PQexec(pg, playerStatsSql.c_str());
            if (PQresultStatus(statsRes) == PGRES_TUPLES_OK && PQntuples(statsRes) > 0)
            {
                player.AddMember("rating", std::stod(PQgetvalue(statsRes, 0, 0)), allocator);
                player.AddMember("goals", std::stoi(PQgetvalue(statsRes, 0, 1)), allocator);
                player.AddMember("assists", std::stoi(PQgetvalue(statsRes, 0, 2)), allocator);
                player.AddMember("yellow", std::stoi(PQgetvalue(statsRes, 0, 3)), allocator);
                player.AddMember("red", std::stoi(PQgetvalue(statsRes, 0, 4)), allocator);
                player.AddMember("minutes", std::stoi(PQgetvalue(statsRes, 0, 5)), allocator);
            }
            else
            {
                // Default values if no stats yet
                player.AddMember("rating", 0.0, allocator);
                player.AddMember("goals", 0, allocator);
                player.AddMember("assists", 0, allocator);
                player.AddMember("yellow", 0, allocator);
                player.AddMember("red", 0, allocator);
                player.AddMember("minutes", 0, allocator);
            }
            PQclear(statsRes);

            int team = std::stoi(PQgetvalue(retPlayers, i, 4));
            if (team == 1)
            {
                team1Players.PushBack(player, allocator);
            }
            else
            {
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
        {
            std::string sql = "SELECT id FROM odds WHERE match_id = " + (matchId)+";";
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
            document.AddMember("odds", int(nrows > 0), allocator);
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
        std::string sql = "SELECT m.id, m.league, m.season, m.week, m.match_date, m.team1_score, m.team2_score, m.week_type, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.preview, m.teaser, m.play_off, m.team1_score_90, m.team2_score_90, m.team1_score_pen, m.team2_score_pen, "
            "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, t1.venue AS team1_venue, t1.players_ready as team1_players_ready, "
            "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, t2.venue AS team2_venue, t2.players_ready as team2_players_ready, "
            "lt1.league_index AS team1_league_index, lt1.group_index AS team1_group_index, "  // Add league_index and group_index for team1
            "lt2.league_index AS team2_league_index, lt2.group_index AS team2_group_index, "  // Add league_index and group_index for team2
            "l.name AS league_name, "
            "l.country AS league_country, "
            "l.current_week, "
            "COALESCE(s.points, '') AS special_match_points, "
            "COALESCE(s.title, '') AS special_match_title "
            "FROM matches m "
            "JOIN teams t1 ON m.team1 = t1.id "
            "JOIN teams t2 ON m.team2 = t2.id "
            "JOIN leagues l ON m.league = l.id "
            "JOIN leagues_teams lt1 ON lt1.team_id = t1.id AND lt1.league_id = l.id "  // Join leagues_teams for team1
            "JOIN leagues_teams lt2 ON lt2.team_id = t2.id AND lt2.league_id = l.id "  // Join leagues_teams for team2
            "LEFT JOIN special_matches s ON s.match_id = m.id " // Join special_matches
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
            int isSpecial = atol(PQgetvalue(ret, i, 12));
            std::string preview = PQgetvalue(ret, i, 13);
            std::string teaser = PQgetvalue(ret, i, 14);
            int playOff = atoi(PQgetvalue(ret, i, 15));
            int team1Score90 = atoi(PQgetvalue(ret, i, 16));
            int team2Score90 = atoi(PQgetvalue(ret, i, 17));
            int team1ScorePen = atoi(PQgetvalue(ret, i, 18));
            int team2ScorePen = atoi(PQgetvalue(ret, i, 19));

            std::string leagueName = PQgetvalue(ret, i, 34);
            std::string leagueCountry = PQgetvalue(ret, i, 35);

            std::string points = PQgetvalue(ret, i, 37);
            std::string smTitle = PQgetvalue(ret, i, 38);

            // Team 1 object
            rapidjson::Value team1Obj(rapidjson::kObjectType);
            team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 20)), allocator);
            team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 21), allocator), allocator);
            team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 22), allocator), allocator);
            team1Obj.AddMember("venue", rapidjson::Value(PQgetvalue(ret, i, 23), allocator), allocator);
            team1Obj.AddMember("playersReady", atoi(PQgetvalue(ret, i, 24)), allocator);
            team1Obj.AddMember("league_index", atoi(PQgetvalue(ret, i, 30)), allocator);  // Add league_index for team1
            team1Obj.AddMember("group_index", atoi(PQgetvalue(ret, i, 31)), allocator);  // Add group_index for team1

            // Team 2 object
            rapidjson::Value team2Obj(rapidjson::kObjectType);
            team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 25)), allocator);
            team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 26), allocator), allocator);
            team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 27), allocator), allocator);
            team2Obj.AddMember("venue", rapidjson::Value(PQgetvalue(ret, i, 28), allocator), allocator);
            team2Obj.AddMember("playersReady", atoi(PQgetvalue(ret, i, 29)), allocator);
            team2Obj.AddMember("league_index", atoi(PQgetvalue(ret, i, 32)), allocator);  // Add league_index for team2
            team2Obj.AddMember("group_index", atoi(PQgetvalue(ret, i, 33)), allocator);  // Add group_index for team2

            matchObj.AddMember("id", id, allocator);
            matchObj.AddMember("league", league, allocator);
            matchObj.AddMember("season", rapidjson::Value(season.c_str(), allocator), allocator);
            matchObj.AddMember("week", week, allocator);
            matchObj.AddMember("weekType", weekType, allocator);
            matchObj.AddMember("elapsed", elapsed, allocator);
            matchObj.AddMember("team1_score_live", team1ScoreLive, allocator);
            matchObj.AddMember("team2_score_live", team2ScoreLive, allocator);
            matchObj.AddMember("status", rapidjson::Value(status.c_str(), allocator), allocator);
            matchObj.AddMember("is_special", isSpecial, allocator);
            matchObj.AddMember("preview", rapidjson::Value(preview.c_str(), allocator), allocator);
            matchObj.AddMember("teaser", rapidjson::Value(teaser.c_str(), allocator), allocator);
            matchObj.AddMember("playOff", playOff, allocator);

            matchObj.AddMember("team1", team1Obj, allocator);
            matchObj.AddMember("team2", team2Obj, allocator);
            matchObj.AddMember("date", (double)date, allocator);
            matchObj.AddMember("team1_score", team1Score, allocator);
            matchObj.AddMember("team2_score", team2Score, allocator);
            matchObj.AddMember("team1_score_90", team1Score90, allocator);
            matchObj.AddMember("team2_score_90", team2Score90, allocator);
            matchObj.AddMember("team1_score_pen", team1ScorePen, allocator);
            matchObj.AddMember("team2_score_pen", team2ScorePen, allocator);
            matchObj.AddMember("leagueName", rapidjson::Value(leagueName.c_str(), allocator), allocator);
            matchObj.AddMember("league_country", rapidjson::Value(leagueCountry.c_str(), allocator), allocator);
            matchObj.AddMember("currentWeek", atoi(PQgetvalue(ret, i, 36)), allocator); // Add current_week            matchObj.AddMember("leagueName", rapidjson::Value(leagueName.c_str(), allocator), allocator);
            matchObj.AddMember("special_match_points", rapidjson::Value(points.c_str(), allocator), allocator);
            matchObj.AddMember("special_match_title", rapidjson::Value(smTitle.c_str(), allocator), allocator);

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

static std::vector<int> splitPoints(const std::string& str, char delimiter) {
    std::vector<int> tokens;
    std::stringstream ss(str);  // Create a string stream from the input string
    std::string item;

    // Extract each part of the string separated by the delimiter
    while (std::getline(ss, item, delimiter)) {
        tokens.push_back(std::stoi(item));  // Convert to int and add to the vector
    }

    return tokens;
}

std::function<void(const httplib::Request&, httplib::Response&)> MatchesRoute::EditMatchPreview()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "POST");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        std::string matchId = req.get_param_value("match_id");
        rapidjson::Document document;
        document.Parse(req.body.c_str());

        std::string preview = document["preview"].GetString();
        const std::string sql = "UPDATE matches SET preview = '"
            + preview + "' WHERE id = " + matchId + ";";

        PGconn* pg = ConnectionPool::Get()->getConnection();
        PGresult* ret = PQexec(pg, sql.c_str());
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
        std::string sql = "SELECT team1, team2, league, season, is_special FROM matches WHERE id = " + matchId + ";";
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
        int isSpecial = atoi(PQgetvalue(ret, 0, 4));

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

            if (team1Score > team2Score) 
            {
                pointsForTeam1 = 3; // Team 1 wins
            }
            else if (team1Score < team2Score) 
            {
                pointsForTeam2 = 3; // Team 2 wins
            }
            else 
            {
                pointsForTeam1 = 1; // Draw
                pointsForTeam2 = 1; // Draw
            }

            // Update league table for both teams
            updateLeagueTable(team1, team1Score, team2Score, pointsForTeam1);
            updateLeagueTable(team2, team2Score, team1Score, pointsForTeam2);


            sql = "SELECT * FROM predicts WHERE match_id = " + matchId + ";";
            ret = PQexec(pg, sql.c_str());

            std::vector<int> specialPoints;
            bool isQuest = false;
            if (isSpecial)
            {
                std::string sql = "SELECT points, title FROM special_matches where match_id = " + matchId + ";";
                PGresult* ret = PQexec(pg, sql.c_str());
                std::string pp = PQgetvalue(ret, 0, 0);
                std::string tt = PQgetvalue(ret, 0, 1);
                isQuest = tt == "quest";
                specialPoints = splitPoints(pp, ':');
                PQclear(ret);
            }

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
                    points = isSpecial ? specialPoints[0] : 3;
                    status = EPredictStatus::ScorePredicted;
                }
                else
                {
                    int actualDiff = team1Score - team2Score;
                    int predictedDiff = t1score - t2score;

                    if ((team1Score > team2Score && t1score > t2score) ||
                        (team1Score < team2Score && t1score < t2score) ||
                        (team1Score == team2Score && t1score == t2score))
                    {
                        if (actualDiff == predictedDiff)
                        {
                            // Correct goal difference
                            points = isSpecial ? specialPoints[1] : 2;
                            status = EPredictStatus::DiffPredicted;
                        }
                        else
                        {
                            // Only winner predicted
                            points = isSpecial ? specialPoints[1] : 1;
                            status = EPredictStatus::WinnerPredicted;
                        }
                    }
                    else
                    {
                        points = isSpecial ? specialPoints[2] : -1;
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

            // Quest remove points
            if (isQuest)
            {
                sql =
                    "UPDATE users "
                    "SET points = GREATEST(0, points - 3) "
                    "WHERE id NOT IN (SELECT user_id FROM predicts WHERE match_id = " + (matchId) + ");";
                PGresult* pret = PQexec(pg, sql.c_str());
                PQclear(pret);

                // Insert empty predictions for users who didn't predict the match
                sql =
                    "INSERT INTO predicts (user_id, match_id, team1_score, team2_score, status) "
                    "SELECT id, " + (matchId) + ", 0, 0, 4 "
                    "FROM users "
                    "WHERE id NOT IN (SELECT user_id FROM predicts WHERE match_id = " + (matchId) + ");";
                pret = PQexec(pg, sql.c_str());
                PQclear(pret);
            }
        }

        ConnectionPool::Get()->releaseConnection(pg);
        res.status = 201; // Created
    };
}
