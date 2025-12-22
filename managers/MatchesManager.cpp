#include "MatchesManager.h"
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>

static std::string ReadFile(const std::string& filename)
{
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool MatchesManager::GetLeagueMatchesWithPredicts(PGconn* pg,
    int userId,
    int lid,
    const std::string& season,
    const std::string& week,
    const std::string& lang,
    rapidjson::Document& document)
{
    std::string currentSeason = "25/26";
    std::string postfix = "";
    std::string ss = season;
    if (ss != currentSeason)
    {
        std::replace(ss.begin(), ss.end(), '/', '_');
        postfix = "_" + ss;
    }

    std::string sql = "SELECT m.id, m.league, m.season, m.week, m.week_type, m.match_date, m.team1_score, m.team2_score, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.preview, m.teaser, m.play_off, "
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "
        "COALESCE(p.team1_score, -1) AS predicted_team1_score, " // Default -1 if NULL
        "COALESCE(p.team2_score, -1) AS predicted_team2_score, " // Default -1 if NULL
        "COALESCE(p.status, -1) AS status, " // Default -1 if NULL
        "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches table
        "COALESCE(s.stadium, '') AS special_match_stadium, "
        "COALESCE(s.points, '') AS special_match_points "
        "FROM matches m "
        "JOIN leagues l ON m.league = l.id "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "LEFT JOIN predicts" + postfix + " p ON p.match_id = m.id AND p.user_id = " + std::to_string(userId) + " "
        "LEFT JOIN special_matches s ON s.match_id = m.id " // Join special_matches
        "WHERE m.league = " + std::to_string(lid) + " AND m.week = " + week + " AND m.season = l.current_season "
        "ORDER BY m.match_date ASC;";

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch matches: %s", PQerrorMessage(pg));
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
        // res.status = 500; // Internal Server Error
        return false;
    }

    int nrows = PQntuples(ret);
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
        int isSpecial = atoi(PQgetvalue(ret, i, 12));
        std::string preview = PQgetvalue(ret, i, 13);
        std::string teaser = PQgetvalue(ret, i, 14);
        int playOff = atoi(PQgetvalue(ret, i, 15));


        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 16)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 17), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 18), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 19)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 20), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 21), allocator), allocator);

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
        matchObj.AddMember("is_special", isSpecial, allocator);
        matchObj.AddMember("preview", rapidjson::Value(preview.c_str(), allocator), allocator);
        matchObj.AddMember("teaser", rapidjson::Value(teaser.c_str(), allocator), allocator);
        matchObj.AddMember("playOff", playOff, allocator);

        std::string title = PQgetvalue(ret, i, 25);
        std::string translatedTitle;
        if (isSpecial)
        {
            std::string filename = "data/special.json";
            std::string jsonString = ReadFile(filename);
            rapidjson::Document d;
            d.Parse(jsonString.c_str());
            std::string l = "en";
            if (lang.size()) l = lang;
            translatedTitle = d[l.c_str()][title.c_str()].GetString();
        }
        matchObj.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 25), allocator), allocator);
        matchObj.AddMember("special_match_stadium", rapidjson::Value(PQgetvalue(ret, i, 26), allocator), allocator);
        matchObj.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 27), allocator), allocator);

        rapidjson::Value v;
        v.SetString(translatedTitle.c_str(), allocator);
        matchObj.AddMember("special_match_tr_title", v, allocator);

        rapidjson::Value predictObj(rapidjson::kObjectType);
        predictObj.AddMember("team1_score", atoi(PQgetvalue(ret, i, 22)), allocator);
        predictObj.AddMember("team2_score", atoi(PQgetvalue(ret, i, 23)), allocator);
        predictObj.AddMember("status", atoi(PQgetvalue(ret, i, 24)), allocator);

        // Include prediction in match object
        matchObj.AddMember("predict", predictObj, allocator);

        // Add the updated match object to the document array
        document.PushBack(matchObj, allocator);
    }

    PQclear(ret);
    return true;
}

bool MatchesManager::GetLeagueMatchesWithBets(PGconn* pg,
    int userId,
    int lid,
    const std::string& season,
    const std::string& week,
    const std::string& lang,
    rapidjson::Document& document)
{
    std::string currentSeason = "25/26";
    std::string postfix = "";
    std::string ss = season;
    if (ss != currentSeason)
    {
        std::replace(ss.begin(), ss.end(), '/', '_');
        postfix = "_" + ss;
    }

    std::string sql =
        "SELECT m.id, m.league, m.season, m.week, m.week_type, m.match_date, "
        "m.team1_score, m.team2_score, m.elapsed, m.team1_score_live, m.team2_score_live, "
        "m.status, m.is_special, m.preview, m.teaser, m.play_off, "
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "

        // user bet fields (default values if no bet)
        "COALESCE(b.id, -1) AS bet_id, "
        "COALESCE(b.bet, '') AS bet, "
        "COALESCE(b.amount, 0) AS bet_amount, "
        "COALESCE(b.odd, 0.0) AS bet_odd, "
        "COALESCE(b.status, -1) AS bet_status, "

        "COALESCE(s.title, '') AS special_match_title, "
        "COALESCE(s.stadium, '') AS special_match_stadium, "
        "COALESCE(s.points, '') AS special_match_points "

        "FROM matches m "
        "JOIN leagues l ON m.league = l.id "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "LEFT JOIN bets b ON b.match_id = m.id AND b.user_id = " + std::to_string(userId) + " "
        "LEFT JOIN special_matches s ON s.match_id = m.id "
        "WHERE m.league = " + std::to_string(lid) + " AND m.week = " + week + " AND m.season = l.current_season "
        "ORDER BY m.match_date ASC;";

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch matches with bets: %s", PQerrorMessage(pg));
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
        return false;
    }

    int nrows = PQntuples(ret);
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
        int isSpecial = atoi(PQgetvalue(ret, i, 12));
        std::string preview = PQgetvalue(ret, i, 13);
        std::string teaser = PQgetvalue(ret, i, 14);
        int playOff = atoi(PQgetvalue(ret, i, 15));

        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 16)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 17), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 18), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 19)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 20), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 21), allocator), allocator);

        // Add match data
        matchObj.AddMember("id", id, allocator);
        matchObj.AddMember("league", league, allocator);
        matchObj.AddMember("season", rapidjson::Value(season.c_str(), allocator), allocator);
        matchObj.AddMember("week", week, allocator);
        matchObj.AddMember("weekType", weekType, allocator);
        matchObj.AddMember("date", (double)date, allocator);
        matchObj.AddMember("team1_score", team1Score, allocator);
        matchObj.AddMember("team2_score", team2Score, allocator);
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

        // Special match translations
        std::string title = PQgetvalue(ret, i, 27);
        std::string translatedTitle;
        if (isSpecial)
        {
            std::string filename = "data/special.json";
            std::string jsonString = ReadFile(filename);
            rapidjson::Document d;
            d.Parse(jsonString.c_str());
            std::string l = lang.size() ? lang : "en";
            translatedTitle = d[l.c_str()][title.c_str()].GetString();
        }
        matchObj.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 27), allocator), allocator);
        matchObj.AddMember("special_match_stadium", rapidjson::Value(PQgetvalue(ret, i, 28), allocator), allocator);
        matchObj.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 29), allocator), allocator);

        rapidjson::Value v;
        v.SetString(translatedTitle.c_str(), allocator);
        matchObj.AddMember("special_match_tr_title", v, allocator);

        // Add bet object
        rapidjson::Value betObj(rapidjson::kObjectType);
        betObj.AddMember("id", atoi(PQgetvalue(ret, i, 22)), allocator);
        betObj.AddMember("bet", rapidjson::Value(PQgetvalue(ret, i, 23), allocator), allocator);
        betObj.AddMember("amount", atoi(PQgetvalue(ret, i, 24)), allocator);
        betObj.AddMember("odd", atof(PQgetvalue(ret, i, 25)), allocator);
        betObj.AddMember("status", atoi(PQgetvalue(ret, i, 26)), allocator);

        matchObj.AddMember("bet", betObj, allocator);

        document.PushBack(matchObj, allocator);
    }

    PQclear(ret);
    return true;
}

bool MatchesManager::GetLeagueMatchesWithFireball(PGconn* pg,
    int userId,
    int lid,
    const std::string& season,
    const std::string& week,
    const std::string& lang,
    rapidjson::Document& document)
{
    std::string currentSeason = "25/26";
    std::string postfix = "";
    std::string ss = season;
    if (ss != currentSeason)
    {
        std::replace(ss.begin(), ss.end(), '/', '_');
        postfix = "_" + ss;
    }

    std::string sql =
        "SELECT m.id, m.league, m.season, m.week, m.week_type, m.match_date, "
        "m.team1_score, m.team2_score, m.elapsed, m.team1_score_live, m.team2_score_live, "
        "m.status, m.is_special, m.preview, m.teaser, m.play_off, "
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "

        // user bet fields (default values if no bet)
        "COALESCE(fp.id, -1) AS fp_id, "
        "COALESCE(fp.team_id, -1) AS fp_team_id, "
        "COALESCE(fp.player_api_id, -1) AS fp_player_api_id, "
        "COALESCE(fp.player_name, '') AS fp_player_name, "
        "COALESCE(fp.player_photo, '') AS fp_player_photo, "
        "COALESCE(fp.goals, 0) AS fp_goals, "
        "COALESCE(fp.status, -2) AS fp_status, "

        "COALESCE(s.title, '') AS special_match_title, "
        "COALESCE(s.stadium, '') AS special_match_stadium, "
        "COALESCE(s.points, '') AS special_match_points "

        "FROM matches m "
        "JOIN leagues l ON m.league = l.id "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "LEFT JOIN fireball_predicts fp ON fp.match_id = m.id AND fp.user_id = " + std::to_string(userId) + " "
        "LEFT JOIN special_matches s ON s.match_id = m.id "
        "WHERE m.league = " + std::to_string(lid) + " AND m.week = " + week + " AND m.season = l.current_season "
        "ORDER BY m.match_date ASC;";

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch matches with bets: %s", PQerrorMessage(pg));
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
        return false;
    }

    int nrows = PQntuples(ret);
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
        int isSpecial = atoi(PQgetvalue(ret, i, 12));
        std::string preview = PQgetvalue(ret, i, 13);
        std::string teaser = PQgetvalue(ret, i, 14);
        int playOff = atoi(PQgetvalue(ret, i, 15));

        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 16)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 17), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 18), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 19)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 20), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 21), allocator), allocator);

        // Add match data
        matchObj.AddMember("id", id, allocator);
        matchObj.AddMember("league", league, allocator);
        matchObj.AddMember("season", rapidjson::Value(season.c_str(), allocator), allocator);
        matchObj.AddMember("week", week, allocator);
        matchObj.AddMember("weekType", weekType, allocator);
        matchObj.AddMember("date", (double)date, allocator);
        matchObj.AddMember("team1_score", team1Score, allocator);
        matchObj.AddMember("team2_score", team2Score, allocator);
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

        // Special match translations
        std::string title = PQgetvalue(ret, i, 29);
        std::string translatedTitle;
        if (isSpecial)
        {
            std::string filename = "data/special.json";
            std::string jsonString = ReadFile(filename);
            rapidjson::Document d;
            d.Parse(jsonString.c_str());
            std::string l = lang.size() ? lang : "en";
            translatedTitle = d[l.c_str()][title.c_str()].GetString();
        }
        matchObj.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 29), allocator), allocator);
        matchObj.AddMember("special_match_stadium", rapidjson::Value(PQgetvalue(ret, i, 30), allocator), allocator);
        matchObj.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 31), allocator), allocator);

        rapidjson::Value v;
        v.SetString(translatedTitle.c_str(), allocator);
        matchObj.AddMember("special_match_tr_title", v, allocator);

        // Add bet object
        rapidjson::Value predictObj(rapidjson::kObjectType);
        predictObj.AddMember("id", atoi(PQgetvalue(ret, i, 22)), allocator);
        predictObj.AddMember("team_id", atoi(PQgetvalue(ret, i, 23)), allocator);
        predictObj.AddMember("player_api_id", atoi(PQgetvalue(ret, i, 24)), allocator);
        predictObj.AddMember("player_name", rapidjson::Value(PQgetvalue(ret, i, 25), allocator), allocator);
        predictObj.AddMember("player_photo", rapidjson::Value(PQgetvalue(ret, i, 26), allocator), allocator);
        predictObj.AddMember("goals", atoi(PQgetvalue(ret, i, 27)), allocator);
        predictObj.AddMember("status", atoi(PQgetvalue(ret, i, 28)), allocator);

        matchObj.AddMember("fireballPredict", predictObj, allocator);

        document.PushBack(matchObj, allocator);
    }

    PQclear(ret);
    return true;
}

bool MatchesManager::GetLeagueMatchesWithCareer(PGconn* pg,
    int userId,
    int lid,
    const std::string& season,
    const std::string& week,
    const std::string& lang,
    rapidjson::Document& document)
{
    std::string currentSeason = "25/26";
    std::string postfix = "";
    std::string ss = season;
    if (ss != currentSeason)
    {
        std::replace(ss.begin(), ss.end(), '/', '_');
        postfix = "_" + ss;
    }

    std::string sql =
        "SELECT m.id, m.league, m.season, m.week, m.week_type, m.match_date, "
        "m.team1_score, m.team2_score, m.elapsed, m.team1_score_live, m.team2_score_live, "
        "m.status, m.is_special, m.preview, m.teaser, m.play_off, "
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "

        "COALESCE(s.title, '') AS special_match_title, "
        "COALESCE(s.stadium, '') AS special_match_stadium, "
        "COALESCE(s.points, '') AS special_match_points "

        "FROM matches m "
        "JOIN leagues l ON m.league = l.id "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "LEFT JOIN special_matches s ON s.match_id = m.id "
        "WHERE m.league = " + std::to_string(lid) + " AND m.week = " + week + " AND m.season = l.current_season "
        "ORDER BY m.match_date ASC;";

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch matches with bets: %s", PQerrorMessage(pg));
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
        return false;
    }

    int nrows = PQntuples(ret);
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
        int isSpecial = atoi(PQgetvalue(ret, i, 12));
        std::string preview = PQgetvalue(ret, i, 13);
        std::string teaser = PQgetvalue(ret, i, 14);
        int playOff = atoi(PQgetvalue(ret, i, 15));

        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 16)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 17), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 18), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 19)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 20), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 21), allocator), allocator);

        // Add match data
        matchObj.AddMember("id", id, allocator);
        matchObj.AddMember("league", league, allocator);
        matchObj.AddMember("season", rapidjson::Value(season.c_str(), allocator), allocator);
        matchObj.AddMember("week", week, allocator);
        matchObj.AddMember("weekType", weekType, allocator);
        matchObj.AddMember("date", (double)date, allocator);
        matchObj.AddMember("team1_score", team1Score, allocator);
        matchObj.AddMember("team2_score", team2Score, allocator);
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

        // Special match translations
        std::string title = PQgetvalue(ret, i, 22);
        std::string translatedTitle;
        if (isSpecial)
        {
            std::string filename = "data/special.json";
            std::string jsonString = ReadFile(filename);
            rapidjson::Document d;
            d.Parse(jsonString.c_str());
            std::string l = lang.size() ? lang : "en";
            translatedTitle = d[l.c_str()][title.c_str()].GetString();
        }
        matchObj.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 22), allocator), allocator);
        matchObj.AddMember("special_match_stadium", rapidjson::Value(PQgetvalue(ret, i, 23), allocator), allocator);
        matchObj.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 24), allocator), allocator);

        rapidjson::Value v;
        v.SetString(translatedTitle.c_str(), allocator);
        matchObj.AddMember("special_match_tr_title", v, allocator);

        document.PushBack(matchObj, allocator);
    }

    PQclear(ret);
    return true;
}

bool MatchesManager::GetMatchesByDateWithPredicts(PGconn* pg,
    int userId,
    long long dayStart,
    long long dayEnd,
    const std::string& lang,
    rapidjson::Document& document
)
{
    std::string sql = "SELECT m.id, m.league, m.season, m.week, m.week_type, m.match_date, m.team1_score, m.team2_score, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.preview, m.teaser, m.play_off, m.team1_score_90, m.team2_score_90, m.team1_score_pen, m.team2_score_pen,"
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "
        "COALESCE(p.team1_score, -1) AS predicted_team1_score, " // Default -1 if NULL
        "COALESCE(p.team2_score, -1) AS predicted_team2_score, " // Default -1 if NULL
        "COALESCE(p.status, -1) AS status, " // Default -1 if NULL
        "l.name AS league_name, "  // Include league name
        "l.country AS league_country, "  // Include league name
        "l.current_week, "

        "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches 
        "COALESCE(s.stadium, '') AS special_match_stadium, " // Fetch title from special_matches table
        "COALESCE(s.points, '') AS special_match_points "
        
        "FROM matches m "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "LEFT JOIN predicts p ON p.match_id = m.id AND p.user_id = " + std::to_string(userId) + " "
        "JOIN leagues l ON m.league = l.id "  // Join with leagues table
        "LEFT JOIN special_matches s ON s.match_id = m.id " // Join special_matches
        "WHERE m.match_date >= " + std::to_string(dayStart) + " AND m.match_date <= " + std::to_string(dayEnd) + " "
        "ORDER BY m.league ASC, m.match_date ASC, m.id ASC;";

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK) 
    {
        fprintf(stderr, "Failed to get matches by day with predicts: %s", PQerrorMessage(pg));
        PQclear(ret);
        return false;
    }

    int nrows = PQntuples(ret);
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
        int isSpecial = atol(PQgetvalue(ret, i, 12));
        std::string preview = (PQgetvalue(ret, i, 13));
        std::string teaser = (PQgetvalue(ret, i, 14));
        int isPlayOff = atol(PQgetvalue(ret, i, 15));

        int team1Score90 = atoi(PQgetvalue(ret, i, 16));
        int team2Score90 = atoi(PQgetvalue(ret, i, 17));
        int team1ScorePen = atoi(PQgetvalue(ret, i, 18));
        int team2ScorePen = atoi(PQgetvalue(ret, i, 19));

        std::string leagueName = PQgetvalue(ret, i, 29); // Assuming league_name is the last column
        std::string leagueCountry = PQgetvalue(ret, i, 30); // Assuming league_name is the last column
        int currentWeek = atol(PQgetvalue(ret, i, 31));

        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 20)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 21), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 22), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 23)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 24), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 25), allocator), allocator);

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
        matchObj.AddMember("team1_score_90", team1Score90, allocator);
        matchObj.AddMember("team2_score_90", team2Score90, allocator);
        matchObj.AddMember("team1_score_pen", team1ScorePen, allocator);
        matchObj.AddMember("team2_score_pen", team2ScorePen, allocator);
        matchObj.AddMember("status", rapidjson::Value(status.c_str(), allocator), allocator);
        matchObj.AddMember("is_special", isSpecial, allocator);
        matchObj.AddMember("preview", rapidjson::Value(preview.c_str(), allocator), allocator);
        matchObj.AddMember("teaser", rapidjson::Value(teaser.c_str(), allocator), allocator);
        matchObj.AddMember("playOff", isPlayOff, allocator);

        matchObj.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 32), allocator), allocator);
        matchObj.AddMember("special_match_stadium", rapidjson::Value(PQgetvalue(ret, i, 33), allocator), allocator);
        matchObj.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 34), allocator), allocator);

        std::string title = PQgetvalue(ret, i, 32);
        std::string translatedTitle;
        if (isSpecial)
        {
            std::string filename = "data/special.json";
            std::string jsonString = ReadFile(filename);
            rapidjson::Document d;
            d.Parse(jsonString.c_str());
            std::string l = lang.size() ? lang : "en";
            translatedTitle = d[l.c_str()][title.c_str()].GetString();
        }
        rapidjson::Value v;
        v.SetString(translatedTitle.c_str(), allocator);
        matchObj.AddMember("special_match_tr_title", v, allocator);

        matchObj.AddMember("league_name", rapidjson::Value(leagueName.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("league_country", rapidjson::Value(leagueCountry.c_str(), allocator), allocator); // Add league country
        matchObj.AddMember("currentWeek", currentWeek, allocator);

        rapidjson::Value predictObj(rapidjson::kObjectType);
        predictObj.AddMember("team1_score", atoi(PQgetvalue(ret, i, 26)), allocator);
        predictObj.AddMember("team2_score", atoi(PQgetvalue(ret, i, 27)), allocator);
        predictObj.AddMember("status", atoi(PQgetvalue(ret, i, 28)), allocator);
        matchObj.AddMember("predict", predictObj, allocator);

        document.PushBack(matchObj, allocator);
    }
    PQclear(ret);
    return true;
}

bool MatchesManager::GetMatchesByDateWithBets(PGconn* pg,
    int userId,
    long long dayStart,
    long long dayEnd,
    const std::string& lang,
    rapidjson::Document& document
)
{
    std::string sql = "SELECT m.id, m.league, m.season, m.week, m.week_type, m.match_date, m.team1_score, m.team2_score, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.preview, m.teaser, m.play_off, "
        "m.team1_score_90, m.team2_score_90, m.team1_score_pen, m.team2_score_pen,"
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "
       
        // user bet fields (default values if no bet)
        "COALESCE(b.id, -1) AS bet_id, "
        "COALESCE(b.bet, '') AS bet, "
        "COALESCE(b.amount, 0) AS bet_amount, "
        "COALESCE(b.odd, 0.0) AS bet_odd, "
        "COALESCE(b.status, -1) AS bet_status, "
       
        "l.name AS league_name, "  // Include league name
        "l.country AS league_country, "  // Include league name
        "l.current_week, "

        "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches 
        "COALESCE(s.stadium, '') AS special_match_stadium, " // Fetch title from special_matches table
        "COALESCE(s.points, '') AS special_match_points "

        "FROM matches m "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "LEFT JOIN bets b ON b.match_id = m.id AND b.user_id = " + std::to_string(userId) + " "
        "JOIN leagues l ON m.league = l.id "  // Join with leagues table
        "LEFT JOIN special_matches s ON s.match_id = m.id " // Join special_matches
        "WHERE m.match_date >= " + std::to_string(dayStart) + " AND m.match_date <= " + std::to_string(dayEnd) + " "
        "ORDER BY m.league ASC, m.match_date ASC, m.id ASC;";

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to get matches by day with predicts: %s", PQerrorMessage(pg));
        PQclear(ret);
        return false;
    }

    int nrows = PQntuples(ret);
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
        int isSpecial = atol(PQgetvalue(ret, i, 12));
        std::string preview = (PQgetvalue(ret, i, 13));
        std::string teaser = (PQgetvalue(ret, i, 14));
        int isPlayOff = atol(PQgetvalue(ret, i, 15));

        int team1Score90 = atoi(PQgetvalue(ret, i, 16));
        int team2Score90 = atoi(PQgetvalue(ret, i, 17));
        int team1ScorePen = atoi(PQgetvalue(ret, i, 18));
        int team2ScorePen = atoi(PQgetvalue(ret, i, 19));

        std::string leagueName = PQgetvalue(ret, i, 31); // Assuming league_name is the last column
        std::string leagueCountry = PQgetvalue(ret, i, 32); // Assuming league_name is the last column
        int currentWeek = atol(PQgetvalue(ret, i, 33));

        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 20)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 21), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 22), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 23)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 24), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 25), allocator), allocator);

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
        matchObj.AddMember("team1_score_90", team1Score90, allocator);
        matchObj.AddMember("team2_score_90", team2Score90, allocator);
        matchObj.AddMember("team1_score_pen", team1ScorePen, allocator);
        matchObj.AddMember("team2_score_pen", team2ScorePen, allocator);
        matchObj.AddMember("status", rapidjson::Value(status.c_str(), allocator), allocator);
        matchObj.AddMember("is_special", isSpecial, allocator);
        matchObj.AddMember("preview", rapidjson::Value(preview.c_str(), allocator), allocator);
        matchObj.AddMember("teaser", rapidjson::Value(teaser.c_str(), allocator), allocator);
        matchObj.AddMember("playOff", isPlayOff, allocator);

        matchObj.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 34), allocator), allocator);
        matchObj.AddMember("special_match_stadium", rapidjson::Value(PQgetvalue(ret, i, 35), allocator), allocator);
        matchObj.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 36), allocator), allocator);

        std::string title = PQgetvalue(ret, i, 34);
        std::string translatedTitle;
        if (isSpecial)
        {
            std::string filename = "data/special.json";
            std::string jsonString = ReadFile(filename);
            rapidjson::Document d;
            d.Parse(jsonString.c_str());
            std::string l = lang.size() ? lang : "en";
            translatedTitle = d[l.c_str()][title.c_str()].GetString();
        }
        rapidjson::Value v;
        v.SetString(translatedTitle.c_str(), allocator);
        matchObj.AddMember("special_match_tr_title", v, allocator);

        matchObj.AddMember("league_name", rapidjson::Value(leagueName.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("league_country", rapidjson::Value(leagueCountry.c_str(), allocator), allocator); // Add league country
        matchObj.AddMember("currentWeek", currentWeek, allocator);

        // Add bet object
        rapidjson::Value betObj(rapidjson::kObjectType);
        betObj.AddMember("id", atoi(PQgetvalue(ret, i, 26)), allocator);
        betObj.AddMember("bet", rapidjson::Value(PQgetvalue(ret, i, 27), allocator), allocator);
        betObj.AddMember("amount", atoi(PQgetvalue(ret, i, 28)), allocator);
        betObj.AddMember("odd", atof(PQgetvalue(ret, i, 29)), allocator);
        betObj.AddMember("status", atoi(PQgetvalue(ret, i, 30)), allocator);

        matchObj.AddMember("bet", betObj, allocator);
        document.PushBack(matchObj, allocator);
    }
    PQclear(ret);
    return true;
}

bool MatchesManager::GetMatchesByDateWithFireball(PGconn* pg,
    int userId,
    long long dayStart,
    long long dayEnd,
    const std::string& lang,
    rapidjson::Document& document
)
{
    std::string sql = "SELECT m.id, m.league, m.season, m.week, m.week_type, m.match_date, m.team1_score, m.team2_score, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.preview, m.teaser, m.play_off, "
        "m.team1_score_90, m.team2_score_90, m.team1_score_pen, m.team2_score_pen,"
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "

        // user bet fields (default values if no bet)
        "COALESCE(fp.id, -1) AS fp_id, "
        "COALESCE(fp.team_id, -1) AS fp_team_id, "
        "COALESCE(fp.player_api_id, -1) AS fp_player_api_id, "
        "COALESCE(fp.player_name, '') AS fp_player_name, "
        "COALESCE(fp.player_photo, '') AS fp_player_photo, "
        "COALESCE(fp.goals, 0) AS fp_goals, "
        "COALESCE(fp.status, -2) AS fp_status, "

        "l.name AS league_name, "  // Include league name
        "l.country AS league_country, "  // Include league name
        "l.current_week, "

        "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches 
        "COALESCE(s.stadium, '') AS special_match_stadium, " // Fetch title from special_matches table
        "COALESCE(s.points, '') AS special_match_points "

        "FROM matches m "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "LEFT JOIN fireball_predicts fp ON fp.match_id = m.id AND fp.user_id = " + std::to_string(userId) + " "
        "JOIN leagues l ON m.league = l.id "  // Join with leagues table
        "LEFT JOIN special_matches s ON s.match_id = m.id " // Join special_matches
        "WHERE m.match_date >= " + std::to_string(dayStart) + " AND m.match_date <= " + std::to_string(dayEnd) + " "
        "ORDER BY m.league ASC, m.match_date ASC, m.id ASC;";

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to get matches by day with predicts: %s", PQerrorMessage(pg));
        PQclear(ret);
        return false;
    }

    int nrows = PQntuples(ret);
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
        int isSpecial = atol(PQgetvalue(ret, i, 12));
        std::string preview = (PQgetvalue(ret, i, 13));
        std::string teaser = (PQgetvalue(ret, i, 14));
        int isPlayOff = atol(PQgetvalue(ret, i, 15));

        int team1Score90 = atoi(PQgetvalue(ret, i, 16));
        int team2Score90 = atoi(PQgetvalue(ret, i, 17));
        int team1ScorePen = atoi(PQgetvalue(ret, i, 18));
        int team2ScorePen = atoi(PQgetvalue(ret, i, 19));

        std::string leagueName = PQgetvalue(ret, i, 33); // Assuming league_name is the last column
        std::string leagueCountry = PQgetvalue(ret, i, 34); // Assuming league_name is the last column
        int currentWeek = atol(PQgetvalue(ret, i, 35));

        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 20)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 21), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 22), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 23)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 24), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 25), allocator), allocator);

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
        matchObj.AddMember("team1_score_90", team1Score90, allocator);
        matchObj.AddMember("team2_score_90", team2Score90, allocator);
        matchObj.AddMember("team1_score_pen", team1ScorePen, allocator);
        matchObj.AddMember("team2_score_pen", team2ScorePen, allocator);
        matchObj.AddMember("status", rapidjson::Value(status.c_str(), allocator), allocator);
        matchObj.AddMember("is_special", isSpecial, allocator);
        matchObj.AddMember("preview", rapidjson::Value(preview.c_str(), allocator), allocator);
        matchObj.AddMember("teaser", rapidjson::Value(teaser.c_str(), allocator), allocator);
        matchObj.AddMember("playOff", isPlayOff, allocator);

        matchObj.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 36), allocator), allocator);
        matchObj.AddMember("special_match_stadium", rapidjson::Value(PQgetvalue(ret, i, 37), allocator), allocator);
        matchObj.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 38), allocator), allocator);

        std::string title = PQgetvalue(ret, i, 36);
        std::string translatedTitle;
        if (isSpecial)
        {
            std::string filename = "data/special.json";
            std::string jsonString = ReadFile(filename);
            rapidjson::Document d;
            d.Parse(jsonString.c_str());
            std::string l = lang.size() ? lang : "en";
            translatedTitle = d[l.c_str()][title.c_str()].GetString();
        }
        rapidjson::Value v;
        v.SetString(translatedTitle.c_str(), allocator);
        matchObj.AddMember("special_match_tr_title", v, allocator);

        matchObj.AddMember("league_name", rapidjson::Value(leagueName.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("league_country", rapidjson::Value(leagueCountry.c_str(), allocator), allocator); // Add league country
        matchObj.AddMember("currentWeek", currentWeek, allocator);

        // Add bet object
        rapidjson::Value predictObj(rapidjson::kObjectType);
        predictObj.AddMember("id", atoi(PQgetvalue(ret, i, 26)), allocator);
        predictObj.AddMember("team_id", atoi(PQgetvalue(ret, i, 27)), allocator);
        predictObj.AddMember("player_api_id", atoi(PQgetvalue(ret, i, 28)), allocator);
        predictObj.AddMember("player_name", rapidjson::Value(PQgetvalue(ret, i, 29), allocator), allocator);
        predictObj.AddMember("player_photo", rapidjson::Value(PQgetvalue(ret, i, 30), allocator), allocator);
        predictObj.AddMember("goals", atoi(PQgetvalue(ret, i, 31)), allocator);
        predictObj.AddMember("status", atoi(PQgetvalue(ret, i, 32)), allocator);
        matchObj.AddMember("fireballPredict", predictObj, allocator);

        document.PushBack(matchObj, allocator);
    }
    PQclear(ret);
    return true;
}

bool MatchesManager::GetMatchesByDateWithCareer(PGconn* pg,
    int userId,
    long long dayStart,
    long long dayEnd,
    const std::string& lang,
    rapidjson::Document& document
)
{
    std::string sql = "SELECT m.id, m.league, m.season, m.week, m.week_type, m.match_date, m.team1_score, m.team2_score, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.preview, m.teaser, m.play_off, m.team1_score_90, m.team2_score_90, m.team1_score_pen, m.team2_score_pen,"
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "

        "l.name AS league_name, "  // Include league name
        "l.country AS league_country, "  // Include league name
        "l.current_week, "

        "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches 
        "COALESCE(s.stadium, '') AS special_match_stadium, " // Fetch title from special_matches table
        "COALESCE(s.points, '') AS special_match_points "

        "FROM matches m "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "JOIN leagues l ON m.league = l.id "  // Join with leagues table
        "LEFT JOIN special_matches s ON s.match_id = m.id " // Join special_matches
        "WHERE m.match_date >= " + std::to_string(dayStart) + " AND m.match_date <= " + std::to_string(dayEnd) + " "
        "ORDER BY m.league ASC, m.match_date ASC, m.id ASC;";

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to get matches by day with predicts: %s", PQerrorMessage(pg));
        PQclear(ret);
        return false;
    }

    int nrows = PQntuples(ret);
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
        int isSpecial = atol(PQgetvalue(ret, i, 12));
        std::string preview = (PQgetvalue(ret, i, 13));
        std::string teaser = (PQgetvalue(ret, i, 14));
        int isPlayOff = atol(PQgetvalue(ret, i, 15));

        int team1Score90 = atoi(PQgetvalue(ret, i, 16));
        int team2Score90 = atoi(PQgetvalue(ret, i, 17));
        int team1ScorePen = atoi(PQgetvalue(ret, i, 18));
        int team2ScorePen = atoi(PQgetvalue(ret, i, 19));

        std::string leagueName = PQgetvalue(ret, i, 22); // Assuming league_name is the last column
        std::string leagueCountry = PQgetvalue(ret, i, 23); // Assuming league_name is the last column

        int currentWeek = atol(PQgetvalue(ret, i, 24));

        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 16)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 17), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 18), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 19)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 20), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 21), allocator), allocator);

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
        matchObj.AddMember("is_special", isSpecial, allocator);
        matchObj.AddMember("preview", rapidjson::Value(preview.c_str(), allocator), allocator);
        matchObj.AddMember("teaser", rapidjson::Value(teaser.c_str(), allocator), allocator);
        matchObj.AddMember("playOff", isPlayOff, allocator);

        matchObj.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 25), allocator), allocator);
        matchObj.AddMember("special_match_stadium", rapidjson::Value(PQgetvalue(ret, i, 26), allocator), allocator);
        matchObj.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 27), allocator), allocator);

        std::string title = PQgetvalue(ret, i, 25);
        std::string translatedTitle;
        if (isSpecial)
        {
            std::string filename = "data/special.json";
            std::string jsonString = ReadFile(filename);
            rapidjson::Document d;
            d.Parse(jsonString.c_str());
            std::string l = lang.size() ? lang : "en";
            translatedTitle = d[l.c_str()][title.c_str()].GetString();
        }
        rapidjson::Value v;
        v.SetString(translatedTitle.c_str(), allocator);
        matchObj.AddMember("special_match_tr_title", v, allocator);

        matchObj.AddMember("league_name", rapidjson::Value(leagueName.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("league_country", rapidjson::Value(leagueCountry.c_str(), allocator), allocator); // Add league country
        matchObj.AddMember("currentWeek", currentWeek, allocator);

        document.PushBack(matchObj, allocator);
    }
    PQclear(ret);
    return true;
}

bool MatchesManager::GetMatchesLiveWithPredicts(PGconn* pg,
    int userId,
    long long currentTimeMs,
    rapidjson::Document& document
)
{
    std::string sql = "SELECT m.id, m.league, m.season, m.week, m.match_date, m.team1_score, m.team2_score, m.week_type, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.play_off, "
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "
        "COALESCE(p.team1_score, -1) AS predicted_team1_score, " // Default -1 if NULL
        "COALESCE(p.team2_score, -1) AS predicted_team2_score, " // Default -1 if NULL
        "COALESCE(p.status, -1) AS status, " // Default -1 if NULL
        "l.name AS league_name, "  // Include league name
        "l.country AS league_country, "  // Include league name
        "l.current_week, "
        "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches 
        "COALESCE(s.points, '') AS special_match_points "
        "FROM matches m "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "LEFT JOIN predicts p ON p.match_id = m.id AND p.user_id = " + std::to_string(userId) + " "
        "JOIN leagues l ON m.league = l.id "  // Join with leagues table
        "LEFT JOIN special_matches s ON s.match_id = m.id " // Join special_matches
        "WHERE m.match_date < " + std::to_string(currentTimeMs) + " "
        "AND m.team1_score = -1 AND m.team2_score = -1 "
        "AND m.status <> 'PST' ORDER BY m.league ASC, m.match_date ASC;";

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK) 
    {
        fprintf(stderr, "Failed to fetch live matches with predicts: %s", PQerrorMessage(pg));
        PQclear(ret);
        return false;
    }

    int nrows = PQntuples(ret);
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
        int isSpecial = atoi(PQgetvalue(ret, i, 12));
        int playOff = atoi(PQgetvalue(ret, i, 13));

        std::string leagueName = PQgetvalue(ret, i, 23); // Assuming league_name is the last column
        std::string leagueCountry = PQgetvalue(ret, i, 24); // Assuming league_name is the last column
        int currentWeek = atol(PQgetvalue(ret, i, 25));
        std::string specialMatchTitle = PQgetvalue(ret, i, 26);
        std::string specialMatchPoints = PQgetvalue(ret, i, 27);

        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 14)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 15), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 16), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 17)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 18), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 19), allocator), allocator);

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
        matchObj.AddMember("is_special", isSpecial, allocator);
        matchObj.AddMember("playOff", playOff, allocator);

        matchObj.AddMember("league_name", rapidjson::Value(leagueName.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("league_country", rapidjson::Value(leagueCountry.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("currentWeek", currentWeek, allocator);
        matchObj.AddMember("special_match_title", rapidjson::Value(specialMatchTitle.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("special_match_points", rapidjson::Value(specialMatchPoints.c_str(), allocator), allocator); // Add league name

        rapidjson::Value predictObj(rapidjson::kObjectType);
        predictObj.AddMember("team1_score", atoi(PQgetvalue(ret, i, 20)), allocator);
        predictObj.AddMember("team2_score", atoi(PQgetvalue(ret, i, 21)), allocator);
        predictObj.AddMember("status", atoi(PQgetvalue(ret, i, 22)), allocator);
        matchObj.AddMember("predict", predictObj, allocator);

        document.PushBack(matchObj, allocator);
    }

    PQclear(ret);
    return true;
}

bool MatchesManager::GetMatchesLiveWithBets(PGconn* pg,
    int userId,
    long long currentTimeMs,
    rapidjson::Document& document
)
{
    std::string sql = "SELECT m.id, m.league, m.season, m.week, m.match_date, m.team1_score, m.team2_score, m.week_type, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.play_off, "
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "
        
        // user bet fields (default values if no bet)
        "COALESCE(b.id, -1) AS bet_id, "
        "COALESCE(b.bet, '') AS bet, "
        "COALESCE(b.amount, 0) AS bet_amount, "
        "COALESCE(b.odd, 0.0) AS bet_odd, "
        "COALESCE(b.status, -1) AS bet_status, "
       
        "l.name AS league_name, "  // Include league name
        "l.country AS league_country, "  // Include league name
        "l.current_week, "
        "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches 
        "COALESCE(s.points, '') AS special_match_points "
        "FROM matches m "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "LEFT JOIN bets b ON b.match_id = m.id AND b.user_id = " + std::to_string(userId) + " "
        "JOIN leagues l ON m.league = l.id "  // Join with leagues table
        "LEFT JOIN special_matches s ON s.match_id = m.id " // Join special_matches
        "WHERE m.match_date < " + std::to_string(currentTimeMs) + " "
        "AND m.team1_score = -1 AND m.team2_score = -1 "
        "AND m.status <> 'PST' ORDER BY m.league ASC, m.match_date ASC;";

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch live matches with predicts: %s", PQerrorMessage(pg));
        PQclear(ret);
        return false;
    }

    int nrows = PQntuples(ret);
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
        int isSpecial = atoi(PQgetvalue(ret, i, 12));
        int playOff = atoi(PQgetvalue(ret, i, 13));

        std::string leagueName = PQgetvalue(ret, i, 25); // Assuming league_name is the last column
        std::string leagueCountry = PQgetvalue(ret, i, 26); // Assuming league_name is the last column
        int currentWeek = atol(PQgetvalue(ret, i, 27));
        std::string specialMatchTitle = PQgetvalue(ret, i, 28);
        std::string specialMatchPoints = PQgetvalue(ret, i, 29);

        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 14)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 15), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 16), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 17)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 18), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 19), allocator), allocator);

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
        matchObj.AddMember("is_special", isSpecial, allocator);
        matchObj.AddMember("playOff", playOff, allocator);

        matchObj.AddMember("league_name", rapidjson::Value(leagueName.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("league_country", rapidjson::Value(leagueCountry.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("currentWeek", currentWeek, allocator);
        matchObj.AddMember("special_match_title", rapidjson::Value(specialMatchTitle.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("special_match_points", rapidjson::Value(specialMatchPoints.c_str(), allocator), allocator); // Add league name

        // Add bet object
        rapidjson::Value betObj(rapidjson::kObjectType);
        betObj.AddMember("id", atoi(PQgetvalue(ret, i, 20)), allocator);
        betObj.AddMember("bet", rapidjson::Value(PQgetvalue(ret, i, 21), allocator), allocator);
        betObj.AddMember("amount", atoi(PQgetvalue(ret, i, 22)), allocator);
        betObj.AddMember("odd", atof(PQgetvalue(ret, i, 23)), allocator);
        betObj.AddMember("status", atoi(PQgetvalue(ret, i, 24)), allocator);
        matchObj.AddMember("bet", betObj, allocator);

        document.PushBack(matchObj, allocator);
    }

    PQclear(ret);
    return true;
}

bool MatchesManager::GetMatchesLiveWithFireball(PGconn* pg,
    int userId,
    long long currentTimeMs,
    rapidjson::Document& document
)
{
    std::string sql = "SELECT m.id, m.league, m.season, m.week, m.match_date, m.team1_score, m.team2_score, m.week_type, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.play_off, "
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "

        // user bet fields (default values if no bet)
        "COALESCE(fp.id, -1) AS fp_id, "
        "COALESCE(fp.team_id, -1) AS fp_team_id, "
        "COALESCE(fp.player_api_id, -1) AS fp_player_api_id, "
        "COALESCE(fp.player_name, '') AS fp_player_name, "
        "COALESCE(fp.player_photo, '') AS fp_player_photo, "
        "COALESCE(fp.goals, 0) AS fp_goals, "
        "COALESCE(fp.status, -2) AS fp_status, "

        "l.name AS league_name, "  // Include league name
        "l.country AS league_country, "  // Include league name
        "l.current_week, "
        "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches 
        "COALESCE(s.points, '') AS special_match_points "
        "FROM matches m "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "LEFT JOIN fireball_predicts fp ON fp.match_id = m.id AND fp.user_id = " + std::to_string(userId) + " "
        "JOIN leagues l ON m.league = l.id "  // Join with leagues table
        "LEFT JOIN special_matches s ON s.match_id = m.id " // Join special_matches
        "WHERE m.match_date < " + std::to_string(currentTimeMs) + " "
        "AND m.team1_score = -1 AND m.team2_score = -1 "
        "AND m.status <> 'PST' ORDER BY m.league ASC, m.match_date ASC;";

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch live matches with predicts: %s", PQerrorMessage(pg));
        PQclear(ret);
        return false;
    }

    int nrows = PQntuples(ret);
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
        int isSpecial = atoi(PQgetvalue(ret, i, 12));
        int playOff = atoi(PQgetvalue(ret, i, 13));

        std::string leagueName = PQgetvalue(ret, i, 27); // Assuming league_name is the last column
        std::string leagueCountry = PQgetvalue(ret, i, 28); // Assuming league_name is the last column
        int currentWeek = atol(PQgetvalue(ret, i, 29));
        std::string specialMatchTitle = PQgetvalue(ret, i, 30);
        std::string specialMatchPoints = PQgetvalue(ret, i, 31);

        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 14)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 15), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 16), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 17)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 18), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 19), allocator), allocator);

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
        matchObj.AddMember("is_special", isSpecial, allocator);
        matchObj.AddMember("playOff", playOff, allocator);

        matchObj.AddMember("league_name", rapidjson::Value(leagueName.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("league_country", rapidjson::Value(leagueCountry.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("currentWeek", currentWeek, allocator);
        matchObj.AddMember("special_match_title", rapidjson::Value(specialMatchTitle.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("special_match_points", rapidjson::Value(specialMatchPoints.c_str(), allocator), allocator); // Add league name

        // Add bet object
        rapidjson::Value predictObj(rapidjson::kObjectType);
        predictObj.AddMember("id", atoi(PQgetvalue(ret, i, 20)), allocator);
        predictObj.AddMember("team_id", atoi(PQgetvalue(ret, i, 21)), allocator);
        predictObj.AddMember("player_api_id", atoi(PQgetvalue(ret, i, 22)), allocator);
        predictObj.AddMember("player_name", rapidjson::Value(PQgetvalue(ret, i, 23), allocator), allocator);
        predictObj.AddMember("player_photo", rapidjson::Value(PQgetvalue(ret, i, 24), allocator), allocator);
        predictObj.AddMember("goals", atoi(PQgetvalue(ret, i, 25)), allocator);
        predictObj.AddMember("status", atoi(PQgetvalue(ret, i, 26)), allocator);
        matchObj.AddMember("fireballPredict", predictObj, allocator);

        document.PushBack(matchObj, allocator);
    }

    PQclear(ret);
    return true;
}

bool MatchesManager::GetMatchesLiveWithCareer(PGconn* pg,
    int userId,
    long long currentTimeMs,
    rapidjson::Document& document
)
{
    std::string sql = "SELECT m.id, m.league, m.season, m.week, m.match_date, m.team1_score, m.team2_score, m.week_type, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.play_off, "
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "

        "l.name AS league_name, "  // Include league name
        "l.country AS league_country, "  // Include league name
        "l.current_week, "
        "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches 
        "COALESCE(s.points, '') AS special_match_points "
        "FROM matches m "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "JOIN leagues l ON m.league = l.id "  // Join with leagues table
        "LEFT JOIN special_matches s ON s.match_id = m.id " // Join special_matches
        "WHERE m.match_date < " + std::to_string(currentTimeMs) + " "
        "AND m.team1_score = -1 AND m.team2_score = -1 "
        "AND m.status <> 'PST' ORDER BY m.league ASC, m.match_date ASC;";

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch live matches with career: %s", PQerrorMessage(pg));
        PQclear(ret);
        return false;
    }

    int nrows = PQntuples(ret);
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
        int isSpecial = atoi(PQgetvalue(ret, i, 12));
        int playOff = atoi(PQgetvalue(ret, i, 13));

        std::string leagueName = PQgetvalue(ret, i, 20); // Assuming league_name is the last column
        std::string leagueCountry = PQgetvalue(ret, i, 21); // Assuming league_name is the last column
        int currentWeek = atol(PQgetvalue(ret, i, 22));
        std::string specialMatchTitle = PQgetvalue(ret, i, 23);
        std::string specialMatchPoints = PQgetvalue(ret, i, 24);

        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 14)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 15), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 16), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 17)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 18), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 19), allocator), allocator);

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
        matchObj.AddMember("is_special", isSpecial, allocator);
        matchObj.AddMember("playOff", playOff, allocator);

        matchObj.AddMember("league_name", rapidjson::Value(leagueName.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("league_country", rapidjson::Value(leagueCountry.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("currentWeek", currentWeek, allocator);
        matchObj.AddMember("special_match_title", rapidjson::Value(specialMatchTitle.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("special_match_points", rapidjson::Value(specialMatchPoints.c_str(), allocator), allocator); // Add league name

        document.PushBack(matchObj, allocator);
    }

    PQclear(ret);
    return true;
}

bool MatchesManager::GetMatchesUpcomingWithPredicts(PGconn* pg,
    int userId,
    long long currentTimeMs,
    rapidjson::Document& document
)
{
    std::string sql = "SELECT m.id, m.league, m.season, m.week, m.match_date, m.team1_score, m.team2_score, m.week_type, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.play_off, "
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "
        "COALESCE(p.team1_score, -1) AS predicted_team1_score, " // Default -1 if NULL
        "COALESCE(p.team2_score, -1) AS predicted_team2_score, " // Default -1 if NULL
        "COALESCE(p.status, -1) AS status, " // Default -1 if NULL
        "l.name AS league_name, "  // Include league name
        "l.country AS league_country, "  // Include league name
        "l.current_week, "
        "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches 
        "COALESCE(s.points, '') AS special_match_points "
        "FROM matches m "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "LEFT JOIN predicts p ON p.match_id = m.id AND p.user_id = " + std::to_string(userId) + " "
        "JOIN leagues l ON m.league = l.id "  // Join with leagues table
        "LEFT JOIN special_matches s ON s.match_id = m.id " // Join special_matches
        "WHERE m.match_date > " + std::to_string(currentTimeMs) + " "
        "ORDER BY m.match_date ASC "
        "LIMIT 10;";

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK) 
    {
        fprintf(stderr, "Failed to fetch upcoming matches with predicts: %s", PQerrorMessage(pg));
        PQclear(ret);
        return false;
    }

    int nrows = PQntuples(ret);
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
        int isSpecial = atoi(PQgetvalue(ret, i, 12));
        int playOff = atoi(PQgetvalue(ret, i, 13));

        std::string leagueName = PQgetvalue(ret, i, 23); // Assuming league_name is the last column
        std::string leagueCountry = PQgetvalue(ret, i, 24); // Assuming league_name is the last column
        int currentWeek = atol(PQgetvalue(ret, i, 25));
        std::string specialMatchTitle = PQgetvalue(ret, i, 26);
        std::string specialMatchPoints = PQgetvalue(ret, i, 27);

        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 14)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 15), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 16), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 17)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 18), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 19), allocator), allocator);

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
        matchObj.AddMember("is_special", isSpecial, allocator);
        matchObj.AddMember("playOff", playOff, allocator);

        matchObj.AddMember("league_name", rapidjson::Value(leagueName.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("league_country", rapidjson::Value(leagueCountry.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("currentWeek", currentWeek, allocator);
        matchObj.AddMember("special_match_title", rapidjson::Value(specialMatchTitle.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("special_match_points", rapidjson::Value(specialMatchPoints.c_str(), allocator), allocator); // Add league name

        rapidjson::Value predictObj(rapidjson::kObjectType);
        predictObj.AddMember("team1_score", atoi(PQgetvalue(ret, i, 20)), allocator);
        predictObj.AddMember("team2_score", atoi(PQgetvalue(ret, i, 21)), allocator);
        predictObj.AddMember("status", atoi(PQgetvalue(ret, i, 22)), allocator);
        matchObj.AddMember("predict", predictObj, allocator);

        document.PushBack(matchObj, allocator);
    }

    PQclear(ret);
    return true;
}

bool MatchesManager::GetMatchesUpcomingWithBets(PGconn* pg,
    int userId,
    long long currentTimeMs,
    rapidjson::Document& document
)
{
    std::string sql = "SELECT m.id, m.league, m.season, m.week, m.match_date, m.team1_score, m.team2_score, m.week_type, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.play_off, "
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "
        
        // user bet fields (default values if no bet)
        "COALESCE(b.id, -1) AS bet_id, "
        "COALESCE(b.bet, '') AS bet, "
        "COALESCE(b.amount, 0) AS bet_amount, "
        "COALESCE(b.odd, 0.0) AS bet_odd, "
        "COALESCE(b.status, -1) AS bet_status, "
        
        "l.name AS league_name, "  // Include league name
        "l.country AS league_country, "  // Include league name
        "l.current_week, "
        "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches 
        "COALESCE(s.points, '') AS special_match_points "
        "FROM matches m "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "LEFT JOIN bets b ON b.match_id = m.id AND b.user_id = " + std::to_string(userId) + " "
        "JOIN leagues l ON m.league = l.id "  // Join with leagues table
        "LEFT JOIN special_matches s ON s.match_id = m.id " // Join special_matches
        "WHERE m.match_date > " + std::to_string(currentTimeMs) + " "
        "ORDER BY m.match_date ASC "
        "LIMIT 10;";

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch upcoming matches with predicts: %s", PQerrorMessage(pg));
        PQclear(ret);
        return false;
    }

    int nrows = PQntuples(ret);
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
        int isSpecial = atoi(PQgetvalue(ret, i, 12));
        int playOff = atoi(PQgetvalue(ret, i, 13));

        std::string leagueName = PQgetvalue(ret, i, 25); // Assuming league_name is the last column
        std::string leagueCountry = PQgetvalue(ret, i, 26); // Assuming league_name is the last column
        int currentWeek = atol(PQgetvalue(ret, i, 27));
        std::string specialMatchTitle = PQgetvalue(ret, i, 28);
        std::string specialMatchPoints = PQgetvalue(ret, i, 29);

        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 14)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 15), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 16), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 17)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 18), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 19), allocator), allocator);

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
        matchObj.AddMember("is_special", isSpecial, allocator);
        matchObj.AddMember("playOff", playOff, allocator);

        matchObj.AddMember("league_name", rapidjson::Value(leagueName.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("league_country", rapidjson::Value(leagueCountry.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("currentWeek", currentWeek, allocator);
        matchObj.AddMember("special_match_title", rapidjson::Value(specialMatchTitle.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("special_match_points", rapidjson::Value(specialMatchPoints.c_str(), allocator), allocator); // Add league name

        // Add bet object
        rapidjson::Value betObj(rapidjson::kObjectType);
        betObj.AddMember("id", atoi(PQgetvalue(ret, i, 20)), allocator);
        betObj.AddMember("bet", rapidjson::Value(PQgetvalue(ret, i, 21), allocator), allocator);
        betObj.AddMember("amount", atoi(PQgetvalue(ret, i, 22)), allocator);
        betObj.AddMember("odd", atof(PQgetvalue(ret, i, 23)), allocator);
        betObj.AddMember("status", atoi(PQgetvalue(ret, i, 24)), allocator);
        matchObj.AddMember("bet", betObj, allocator);

        document.PushBack(matchObj, allocator);
    }

    PQclear(ret);
    return true;
}

bool MatchesManager::GetMatchesUpcomingWithFireball(PGconn* pg,
    int userId,
    long long currentTimeMs,
    rapidjson::Document& document
)
{
    std::string sql = "SELECT m.id, m.league, m.season, m.week, m.match_date, m.team1_score, m.team2_score, m.week_type, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.play_off, "
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "

        // user bet fields (default values if no bet)
        "COALESCE(fp.id, -1) AS fp_id, "
        "COALESCE(fp.team_id, -1) AS fp_team_id, "
        "COALESCE(fp.player_api_id, -1) AS fp_player_api_id, "
        "COALESCE(fp.player_name, '') AS fp_player_name, "
        "COALESCE(fp.player_photo, '') AS fp_player_photo, "
        "COALESCE(fp.goals, 0) AS fp_goals, "
        "COALESCE(fp.status, -2) AS fp_status, "

        "l.name AS league_name, "  // Include league name
        "l.country AS league_country, "  // Include league name
        "l.current_week, "
        "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches 
        "COALESCE(s.points, '') AS special_match_points "
        "FROM matches m "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "LEFT JOIN fireball_predicts fp ON fp.match_id = m.id AND fp.user_id = " + std::to_string(userId) + " "
        "JOIN leagues l ON m.league = l.id "  // Join with leagues table
        "LEFT JOIN special_matches s ON s.match_id = m.id " // Join special_matches
        "WHERE m.match_date > " + std::to_string(currentTimeMs) + " "
        "ORDER BY m.match_date ASC "
        "LIMIT 10;";

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch upcoming matches with predicts: %s", PQerrorMessage(pg));
        PQclear(ret);
        return false;
    }

    int nrows = PQntuples(ret);
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
        int isSpecial = atoi(PQgetvalue(ret, i, 12));
        int playOff = atoi(PQgetvalue(ret, i, 13));

        std::string leagueName = PQgetvalue(ret, i, 27); // Assuming league_name is the last column
        std::string leagueCountry = PQgetvalue(ret, i, 28); // Assuming league_name is the last column
        int currentWeek = atol(PQgetvalue(ret, i, 29));
        std::string specialMatchTitle = PQgetvalue(ret, i, 30);
        std::string specialMatchPoints = PQgetvalue(ret, i, 31);

        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 14)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 15), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 16), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 17)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 18), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 19), allocator), allocator);

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
        matchObj.AddMember("is_special", isSpecial, allocator);
        matchObj.AddMember("playOff", playOff, allocator);

        matchObj.AddMember("league_name", rapidjson::Value(leagueName.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("league_country", rapidjson::Value(leagueCountry.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("currentWeek", currentWeek, allocator);
        matchObj.AddMember("special_match_title", rapidjson::Value(specialMatchTitle.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("special_match_points", rapidjson::Value(specialMatchPoints.c_str(), allocator), allocator); // Add league name

        // Add bet object
        rapidjson::Value predictObj(rapidjson::kObjectType);
        predictObj.AddMember("id", atoi(PQgetvalue(ret, i, 20)), allocator);
        predictObj.AddMember("team_id", atoi(PQgetvalue(ret, i, 21)), allocator);
        predictObj.AddMember("player_api_id", atoi(PQgetvalue(ret, i, 22)), allocator);
        predictObj.AddMember("player_name", rapidjson::Value(PQgetvalue(ret, i, 23), allocator), allocator);
        predictObj.AddMember("player_photo", rapidjson::Value(PQgetvalue(ret, i, 24), allocator), allocator);
        predictObj.AddMember("goals", atoi(PQgetvalue(ret, i, 25)), allocator);
        predictObj.AddMember("status", atoi(PQgetvalue(ret, i, 26)), allocator);
        matchObj.AddMember("fireballPredict", predictObj, allocator);

        document.PushBack(matchObj, allocator);
    }

    PQclear(ret);
    return true;
}

bool MatchesManager::GetMatchesUpcomingWithCareer(PGconn* pg,
    int userId,
    long long currentTimeMs,
    rapidjson::Document& document
)
{
    std::string sql = "SELECT m.id, m.league, m.season, m.week, m.match_date, m.team1_score, m.team2_score, m.week_type, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.play_off, "
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "

        "l.name AS league_name, "  // Include league name
        "l.country AS league_country, "  // Include league name
        "l.current_week, "
        "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches 
        "COALESCE(s.points, '') AS special_match_points "
        "FROM matches m "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "JOIN leagues l ON m.league = l.id "  // Join with leagues table
        "LEFT JOIN special_matches s ON s.match_id = m.id " // Join special_matches
        "WHERE m.match_date > " + std::to_string(currentTimeMs) + " "
        "ORDER BY m.match_date ASC "
        "LIMIT 10;";

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch upcoming matches with predicts: %s", PQerrorMessage(pg));
        PQclear(ret);
        return false;
    }

    int nrows = PQntuples(ret);
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
        int isSpecial = atoi(PQgetvalue(ret, i, 12));
        int playOff = atoi(PQgetvalue(ret, i, 13));

        std::string leagueName = PQgetvalue(ret, i, 20); // Assuming league_name is the last column
        std::string leagueCountry = PQgetvalue(ret, i, 21); // Assuming league_name is the last column
        int currentWeek = atol(PQgetvalue(ret, i, 22));
        std::string specialMatchTitle = PQgetvalue(ret, i, 23);
        std::string specialMatchPoints = PQgetvalue(ret, i, 24);

        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 14)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 15), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 16), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 17)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 18), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 19), allocator), allocator);

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
        matchObj.AddMember("is_special", isSpecial, allocator);
        matchObj.AddMember("playOff", playOff, allocator);

        matchObj.AddMember("league_name", rapidjson::Value(leagueName.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("league_country", rapidjson::Value(leagueCountry.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("currentWeek", currentWeek, allocator);
        matchObj.AddMember("special_match_title", rapidjson::Value(specialMatchTitle.c_str(), allocator), allocator); // Add league name
        matchObj.AddMember("special_match_points", rapidjson::Value(specialMatchPoints.c_str(), allocator), allocator); // Add league name

        document.PushBack(matchObj, allocator);
    }

    PQclear(ret);
    return true;
}

bool MatchesManager::GetMatchesTeamWithPredicts(PGconn* pg,
    int userId,
    long tid,
    rapidjson::Document& document
)
{
    std::string sql = "SELECT m.id, m.league, l.name AS league_name, l.country AS league_country, m.season, m.week, m.week_type, m.match_date, m.team1_score, m.team2_score, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.preview, m.teaser, m.play_off, "
        "m.team1_score_90, m.team2_score_90, m.team1_score_pen, m.team2_score_pen, "
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "
        "COALESCE(p.team1_score, -1) AS predicted_team1_score, " // Default -1 if NULL
        "COALESCE(p.team2_score, -1) AS predicted_team2_score, " // Default -1 if NULL
        "COALESCE(p.status, -1) AS status, " // Default -1 if NULL    
        "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches table
        "COALESCE(s.points, '') AS special_match_points "
        "FROM matches m "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "JOIN leagues l ON m.league = l.id "
        "LEFT JOIN predicts p ON p.match_id = m.id AND p.user_id = " + std::to_string(userId) + " "
        "LEFT JOIN special_matches s ON s.match_id = m.id " // Join special_matches
        "WHERE (m.team1 = " + std::to_string(tid) + " OR m.team2 = " + std::to_string(tid) + ") AND m.team1_score > -1 AND m.team2_score > -1 ORDER BY m.match_date DESC LIMIT 20;";

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch team matches: %s", PQerrorMessage(pg));
        PQclear(ret);
        return false;
    }

    int nrows = PQntuples(ret);
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
        leagueObj.AddMember("country", rapidjson::Value(PQgetvalue(ret, i, 3), allocator), allocator);

        std::string season = PQgetvalue(ret, i, 4);
        int week = atoi(PQgetvalue(ret, i, 5));
        int weekType = atoi(PQgetvalue(ret, i, 6));

        long long date = atoll(PQgetvalue(ret, i, 7));

        int team1Score = atol(PQgetvalue(ret, i, 8));
        int team2Score = atol(PQgetvalue(ret, i, 9));
        int elapsed = atol(PQgetvalue(ret, i, 10));
        int team1ScoreLive = atol(PQgetvalue(ret, i, 11));
        int team2ScoreLive = atol(PQgetvalue(ret, i, 12));
        std::string status = PQgetvalue(ret, i, 13);
        int isSpecial = atol(PQgetvalue(ret, i, 14));
        std::string preview = PQgetvalue(ret, i, 15);
        std::string teaser = PQgetvalue(ret, i, 16);
        int playOff = atol(PQgetvalue(ret, i, 17));

        int team1Score90 = atoi(PQgetvalue(ret, i, 18));
        int team2Score90 = atoi(PQgetvalue(ret, i, 19));
        int team1ScorePen = atoi(PQgetvalue(ret, i, 20));
        int team2ScorePen = atoi(PQgetvalue(ret, i, 21));

        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 22)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 23), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 24), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 25)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 26), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 27), allocator), allocator);

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
        matchObj.AddMember("team1_score_90", team1Score90, allocator);
        matchObj.AddMember("team2_score_90", team2Score90, allocator);
        matchObj.AddMember("team1_score_pen", team1ScorePen, allocator);
        matchObj.AddMember("team2_score_pen", team2ScorePen, allocator);
        matchObj.AddMember("status", rapidjson::Value(status.c_str(), allocator), allocator);
        matchObj.AddMember("is_special", isSpecial, allocator);
        matchObj.AddMember("preview", rapidjson::Value(preview.c_str(), allocator), allocator);
        matchObj.AddMember("teaser", rapidjson::Value(teaser.c_str(), allocator), allocator);
        matchObj.AddMember("playOff", playOff, allocator);

        rapidjson::Value predictObj(rapidjson::kObjectType);
        predictObj.AddMember("team1_score", atoi(PQgetvalue(ret, i, 28)), allocator);
        predictObj.AddMember("team2_score", atoi(PQgetvalue(ret, i, 29)), allocator);
        predictObj.AddMember("status", atoi(PQgetvalue(ret, i, 30)), allocator);
        matchObj.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 31), allocator), allocator);
        matchObj.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 32), allocator), allocator);

        // Include prediction in match object
        matchObj.AddMember("predict", predictObj, allocator);

        // Add the updated match object to the document array
        document.PushBack(matchObj, allocator);
    }

    PQclear(ret);
    return true;
}

bool MatchesManager::GetMatchesTeamWithBets(PGconn* pg,
    int userId,
    long tid,
    rapidjson::Document& document
)
{
    std::string sql = "SELECT m.id, m.league, l.name AS league_name, l.country AS league_country, m.season, m.week, m.week_type, m.match_date, m.team1_score, m.team2_score, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.preview, m.teaser, m.play_off, "
        "m.team1_score_90, m.team2_score_90, m.team1_score_pen, m.team2_score_pen, "
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "

        // user bet fields (default values if no bet)
        "COALESCE(b.id, -1) AS bet_id, "
        "COALESCE(b.bet, '') AS bet, "
        "COALESCE(b.amount, 0) AS bet_amount, "
        "COALESCE(b.odd, 0.0) AS bet_odd, "
        "COALESCE(b.status, -1) AS bet_status, "

        "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches table
        "COALESCE(s.points, '') AS special_match_points "
        "FROM matches m "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "JOIN leagues l ON m.league = l.id "
        "LEFT JOIN bets b ON b.match_id = m.id AND b.user_id = " + std::to_string(userId) + " "
        "LEFT JOIN special_matches s ON s.match_id = m.id " // Join special_matches
        "WHERE (m.team1 = " + std::to_string(tid) + " OR m.team2 = " + std::to_string(tid) + ") AND m.team1_score > -1 AND m.team2_score > -1 ORDER BY m.match_date DESC LIMIT 20;";

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch team matches: %s", PQerrorMessage(pg));
        PQclear(ret);
        return false;
    }

    int nrows = PQntuples(ret);
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
        leagueObj.AddMember("country", rapidjson::Value(PQgetvalue(ret, i, 3), allocator), allocator);

        std::string season = PQgetvalue(ret, i, 4);
        int week = atoi(PQgetvalue(ret, i, 5));
        int weekType = atoi(PQgetvalue(ret, i, 6));

        long long date = atoll(PQgetvalue(ret, i, 7));

        int team1Score = atol(PQgetvalue(ret, i, 8));
        int team2Score = atol(PQgetvalue(ret, i, 9));
        int elapsed = atol(PQgetvalue(ret, i, 10));
        int team1ScoreLive = atol(PQgetvalue(ret, i, 11));
        int team2ScoreLive = atol(PQgetvalue(ret, i, 12));
        std::string status = PQgetvalue(ret, i, 13);
        int isSpecial = atol(PQgetvalue(ret, i, 14));
        std::string preview = PQgetvalue(ret, i, 15);
        std::string teaser = PQgetvalue(ret, i, 16);
        int playOff = atol(PQgetvalue(ret, i, 17));

        int team1Score90 = atoi(PQgetvalue(ret, i, 18));
        int team2Score90 = atoi(PQgetvalue(ret, i, 19));
        int team1ScorePen = atoi(PQgetvalue(ret, i, 20));
        int team2ScorePen = atoi(PQgetvalue(ret, i, 21));

        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 22)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 23), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 24), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 25)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 26), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 27), allocator), allocator);

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
        matchObj.AddMember("team1_score_90", team1Score90, allocator);
        matchObj.AddMember("team2_score_90", team2Score90, allocator);
        matchObj.AddMember("team1_score_pen", team1ScorePen, allocator);
        matchObj.AddMember("team2_score_pen", team2ScorePen, allocator);
        matchObj.AddMember("status", rapidjson::Value(status.c_str(), allocator), allocator);
        matchObj.AddMember("is_special", isSpecial, allocator);
        matchObj.AddMember("preview", rapidjson::Value(preview.c_str(), allocator), allocator);
        matchObj.AddMember("teaser", rapidjson::Value(teaser.c_str(), allocator), allocator);
        matchObj.AddMember("playOff", playOff, allocator);

        matchObj.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 33), allocator), allocator);
        matchObj.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 34), allocator), allocator);

        // Add bet object
        rapidjson::Value betObj(rapidjson::kObjectType);
        betObj.AddMember("id", atoi(PQgetvalue(ret, i, 28)), allocator);
        betObj.AddMember("bet", rapidjson::Value(PQgetvalue(ret, i, 29), allocator), allocator);
        betObj.AddMember("amount", atoi(PQgetvalue(ret, i, 30)), allocator);
        betObj.AddMember("odd", atof(PQgetvalue(ret, i, 31)), allocator);
        betObj.AddMember("status", atoi(PQgetvalue(ret, i, 32)), allocator);
        matchObj.AddMember("bet", betObj, allocator);

        // Add the updated match object to the document array
        document.PushBack(matchObj, allocator);
    }

    PQclear(ret);
    return true;
}

bool MatchesManager::GetMatchesTeamWithFireball(PGconn* pg,
    int userId,
    long tid,
    rapidjson::Document& document
)
{
    std::string sql = "SELECT m.id, m.league, l.name AS league_name, l.country AS league_country, m.season, m.week, m.week_type, m.match_date, m.team1_score, m.team2_score, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.preview, m.teaser, m.play_off, "
        "m.team1_score_90, m.team2_score_90, m.team1_score_pen, m.team2_score_pen, "
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "

        // user bet fields (default values if no bet)
        "COALESCE(fp.id, -1) AS fp_id, "
        "COALESCE(fp.team_id, -1) AS fp_team_id, "
        "COALESCE(fp.player_api_id, -1) AS fp_player_api_id, "
        "COALESCE(fp.player_name, '') AS fp_player_name, "
        "COALESCE(fp.player_photo, '') AS fp_player_photo, "
        "COALESCE(fp.goals, 0) AS fp_goals, "
        "COALESCE(fp.status, -2) AS fp_status, "

        "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches table
        "COALESCE(s.points, '') AS special_match_points "
        "FROM matches m "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "JOIN leagues l ON m.league = l.id "
        "LEFT JOIN fireball_predicts fp ON fp.match_id = m.id AND fp.user_id = " + std::to_string(userId) + " "
        "LEFT JOIN special_matches s ON s.match_id = m.id " // Join special_matches
        "WHERE (m.team1 = " + std::to_string(tid) + " OR m.team2 = " + std::to_string(tid) + ") AND m.team1_score > -1 AND m.team2_score > -1 ORDER BY m.match_date DESC LIMIT 20;";

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch team matches: %s", PQerrorMessage(pg));
        PQclear(ret);
        return false;
    }

    int nrows = PQntuples(ret);
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
        leagueObj.AddMember("country", rapidjson::Value(PQgetvalue(ret, i, 3), allocator), allocator);

        std::string season = PQgetvalue(ret, i, 4);
        int week = atoi(PQgetvalue(ret, i, 5));
        int weekType = atoi(PQgetvalue(ret, i, 6));

        long long date = atoll(PQgetvalue(ret, i, 7));

        int team1Score = atol(PQgetvalue(ret, i, 8));
        int team2Score = atol(PQgetvalue(ret, i, 9));
        int elapsed = atol(PQgetvalue(ret, i, 10));
        int team1ScoreLive = atol(PQgetvalue(ret, i, 11));
        int team2ScoreLive = atol(PQgetvalue(ret, i, 12));
        std::string status = PQgetvalue(ret, i, 13);
        int isSpecial = atol(PQgetvalue(ret, i, 14));
        std::string preview = PQgetvalue(ret, i, 15);
        std::string teaser = PQgetvalue(ret, i, 16);
        int playOff = atol(PQgetvalue(ret, i, 17));

        int team1Score90 = atoi(PQgetvalue(ret, i, 18));
        int team2Score90 = atoi(PQgetvalue(ret, i, 19));
        int team1ScorePen = atoi(PQgetvalue(ret, i, 20));
        int team2ScorePen = atoi(PQgetvalue(ret, i, 21));

        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 22)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 23), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 24), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 25)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 26), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 27), allocator), allocator);

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
        matchObj.AddMember("team1_score_90", team1Score90, allocator);
        matchObj.AddMember("team2_score_90", team2Score90, allocator);
        matchObj.AddMember("team1_score_pen", team1ScorePen, allocator);
        matchObj.AddMember("team2_score_pen", team2ScorePen, allocator);
        matchObj.AddMember("status", rapidjson::Value(status.c_str(), allocator), allocator);
        matchObj.AddMember("is_special", isSpecial, allocator);
        matchObj.AddMember("preview", rapidjson::Value(preview.c_str(), allocator), allocator);
        matchObj.AddMember("teaser", rapidjson::Value(teaser.c_str(), allocator), allocator);
        matchObj.AddMember("playOff", playOff, allocator);

        matchObj.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 35), allocator), allocator);
        matchObj.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 36), allocator), allocator);

        // Add bet object
        rapidjson::Value predictObj(rapidjson::kObjectType);
        predictObj.AddMember("id", atoi(PQgetvalue(ret, i, 28)), allocator);
        predictObj.AddMember("team_id", atoi(PQgetvalue(ret, i, 29)), allocator);
        predictObj.AddMember("player_api_id", atoi(PQgetvalue(ret, i, 30)), allocator);
        predictObj.AddMember("player_name", rapidjson::Value(PQgetvalue(ret, i, 31), allocator), allocator);
        predictObj.AddMember("player_photo", rapidjson::Value(PQgetvalue(ret, i, 32), allocator), allocator);
        predictObj.AddMember("goals", atoi(PQgetvalue(ret, i, 33)), allocator);
        predictObj.AddMember("status", atoi(PQgetvalue(ret, i, 34)), allocator);
        matchObj.AddMember("fireballPredict", predictObj, allocator);

        // Add the updated match object to the document array
        document.PushBack(matchObj, allocator);
    }

    PQclear(ret);
    return true;
}

bool MatchesManager::GetMatchesTeamWithCareer(PGconn* pg,
    int userId,
    long tid,
    rapidjson::Document& document
)
{
    std::string sql = "SELECT m.id, m.league, l.name AS league_name, l.country AS league_country, m.season, m.week, m.week_type, m.match_date, m.team1_score, m.team2_score, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.preview, m.teaser, m.play_off, "
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "

        "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches table
        "COALESCE(s.points, '') AS special_match_points "
        "FROM matches m "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "JOIN leagues l ON m.league = l.id "
        "LEFT JOIN fireball_predicts fp ON fp.match_id = m.id AND fp.user_id = " + std::to_string(userId) + " "
        "LEFT JOIN special_matches s ON s.match_id = m.id " // Join special_matches
        "WHERE (m.team1 = " + std::to_string(tid) + " OR m.team2 = " + std::to_string(tid) + ") AND m.team1_score > -1 AND m.team2_score > -1 ORDER BY m.match_date DESC LIMIT 20;";

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch team matches: %s", PQerrorMessage(pg));
        PQclear(ret);
        return false;
    }

    int nrows = PQntuples(ret);
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
        leagueObj.AddMember("country", rapidjson::Value(PQgetvalue(ret, i, 3), allocator), allocator);

        std::string season = PQgetvalue(ret, i, 4);
        int week = atoi(PQgetvalue(ret, i, 5));
        int weekType = atoi(PQgetvalue(ret, i, 6));

        long long date = atoll(PQgetvalue(ret, i, 7));

        int team1Score = atol(PQgetvalue(ret, i, 8));
        int team2Score = atol(PQgetvalue(ret, i, 9));
        int elapsed = atol(PQgetvalue(ret, i, 10));
        int team1ScoreLive = atol(PQgetvalue(ret, i, 11));
        int team2ScoreLive = atol(PQgetvalue(ret, i, 12));
        std::string status = PQgetvalue(ret, i, 13);
        int isSpecial = atol(PQgetvalue(ret, i, 14));
        std::string preview = PQgetvalue(ret, i, 15);
        std::string teaser = PQgetvalue(ret, i, 16);
        int playOff = atol(PQgetvalue(ret, i, 17));

        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 18)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 19), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 20), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 21)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 22), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 23), allocator), allocator);

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
        matchObj.AddMember("is_special", isSpecial, allocator);
        matchObj.AddMember("preview", rapidjson::Value(preview.c_str(), allocator), allocator);
        matchObj.AddMember("teaser", rapidjson::Value(teaser.c_str(), allocator), allocator);
        matchObj.AddMember("playOff", playOff, allocator);

        matchObj.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 24), allocator), allocator);
        matchObj.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 25), allocator), allocator);

        // Add the updated match object to the document array
        document.PushBack(matchObj, allocator);
    }

    PQclear(ret);
    return true;
}

bool MatchesManager::FillTeamMatchesWithPredicts(PGconn* pg, 
    int userId, 
    int tid, 
    rapidjson::Value& document, 
    rapidjson::Document::AllocatorType& allocator, 
    ETeamMatch eMatch
)
{
    std::string sql = "SELECT m.id, m.league, l.name AS league_name, l.country AS league_country, m.season, m.week, m.week_type, m.match_date, m.team1_score, m.team2_score, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.preview, m.teaser, m.play_off, "
        "m.team1_score_90, m.team2_score_90, m.team1_score_pen, m.team2_score_pen,"
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "
        "COALESCE(p.team1_score, -1) AS predicted_team1_score, " // Default -1 if NULL
        "COALESCE(p.team2_score, -1) AS predicted_team2_score, " // Default -1 if NULL
        "COALESCE(p.status, -1) AS status, " // Default -1 if NULL    
        "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches table
        "COALESCE(s.points, '') AS special_match_points "
        "FROM matches m "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "JOIN leagues l ON m.league = l.id "
        "LEFT JOIN predicts p ON p.match_id = m.id AND p.user_id = " + std::to_string(userId) + " "
        "LEFT JOIN special_matches s ON s.match_id = m.id ";

    if (eMatch == ETeamMatch::Finished)
    {
        sql += "WHERE (m.team1 = " + std::to_string(tid) + " OR m.team2 = " + std::to_string(tid) + ") AND m.team1_score > -1 AND m.team2_score > -1 ORDER BY m.match_date DESC LIMIT 20;";
    }
    else if (eMatch == ETeamMatch::Live)
    {
        auto now = std::chrono::system_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto epoch = now_ms.time_since_epoch();
        auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
        long long currentTimeMs = value.count();

        sql += "WHERE (m.team1 = " + std::to_string(tid) + " OR m.team2 = "
            + std::to_string(tid) + ") AND m.team1_score = -1 AND m.team2_score = -1 AND "
            + "m.match_date < " + std::to_string(currentTimeMs)
            + ";";
    }
    else if (eMatch == ETeamMatch::Upcoming)
    {
        auto now = std::chrono::system_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto epoch = now_ms.time_since_epoch();
        auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
        long long currentTimeMs = value.count();
        sql = "SELECT * FROM (" + sql;

        sql += "WHERE (m.team1 = " + std::to_string(tid) + " OR m.team2 = " + std::to_string(tid) + ") "
            "AND m.match_date > " + std::to_string(currentTimeMs) + " "
            "ORDER BY m.match_date ASC LIMIT 3"
            ") AS sub "
            "ORDER BY sub.match_date DESC;";
    }

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK) 
    {
        fprintf(stderr, "Failed to fetch team page matches with predicts: %s", PQerrorMessage(pg));
        PQclear(ret);
        return false;
    }

    int nrows = PQntuples(ret);

    for (int i = 0; i < nrows; ++i)
    {
        rapidjson::Value matchObj(rapidjson::kObjectType);
        int id = atoi(PQgetvalue(ret, i, 0));

        // League object
        rapidjson::Value leagueObj(rapidjson::kObjectType);
        leagueObj.AddMember("id", atoi(PQgetvalue(ret, i, 1)), allocator);
        leagueObj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 2), allocator), allocator);
        leagueObj.AddMember("country", rapidjson::Value(PQgetvalue(ret, i, 3), allocator), allocator);

        std::string season = PQgetvalue(ret, i, 4);
        int week = atoi(PQgetvalue(ret, i, 5));
        int weekType = atoi(PQgetvalue(ret, i, 6));

        long long date = atoll(PQgetvalue(ret, i, 7));

        int team1Score = atol(PQgetvalue(ret, i, 8));
        int team2Score = atol(PQgetvalue(ret, i, 9));
        int elapsed = atol(PQgetvalue(ret, i, 10));
        int team1ScoreLive = atol(PQgetvalue(ret, i, 11));
        int team2ScoreLive = atol(PQgetvalue(ret, i, 12));
        std::string status = PQgetvalue(ret, i, 13);
        int isSpecial = atol(PQgetvalue(ret, i, 14));
        std::string preview = PQgetvalue(ret, i, 15);
        std::string teaser = PQgetvalue(ret, i, 16);
        int playOff = atol(PQgetvalue(ret, i, 17));

        int team1Score90 = atoi(PQgetvalue(ret, i, 18));
        int team2Score90 = atoi(PQgetvalue(ret, i, 19));
        int team1ScorePen = atoi(PQgetvalue(ret, i, 20));
        int team2ScorePen = atoi(PQgetvalue(ret, i, 21));

        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 22)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 23), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 24), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 25)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 26), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 27), allocator), allocator);

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
        matchObj.AddMember("team1_score_90", team1Score90, allocator);
        matchObj.AddMember("team2_score_90", team2Score90, allocator);
        matchObj.AddMember("team1_score_pen", team1ScorePen, allocator);
        matchObj.AddMember("team2_score_pen", team2ScorePen, allocator);
        matchObj.AddMember("status", rapidjson::Value(status.c_str(), allocator), allocator);
        matchObj.AddMember("is_special", isSpecial, allocator);
        matchObj.AddMember("preview", rapidjson::Value(preview.c_str(), allocator), allocator);
        matchObj.AddMember("teaser", rapidjson::Value(teaser.c_str(), allocator), allocator);
        matchObj.AddMember("playOff", playOff, allocator);

        rapidjson::Value predictObj(rapidjson::kObjectType);
        predictObj.AddMember("team1_score", atoi(PQgetvalue(ret, i, 28)), allocator);
        predictObj.AddMember("team2_score", atoi(PQgetvalue(ret, i, 29)), allocator);
        predictObj.AddMember("status", atoi(PQgetvalue(ret, i, 30)), allocator);
        matchObj.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 31), allocator), allocator);
        matchObj.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 32), allocator), allocator);

        // Include prediction in match object
        matchObj.AddMember("predict", predictObj, allocator);

        // Add the updated match object to the document array
        document.PushBack(matchObj, allocator);
    }
    PQclear(ret);
    return true;
}

bool MatchesManager::FillTeamMatchesWithBets(PGconn* pg,
    int userId,
    int tid,
    rapidjson::Value& document,
    rapidjson::Document::AllocatorType& allocator,
    ETeamMatch eMatch
)
{
    std::string sql = "SELECT m.id, m.league, l.name AS league_name, l.country AS league_country, m.season, m.week, m.week_type, m.match_date, m.team1_score, m.team2_score, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.preview, m.teaser, m.play_off, "
        "m.team1_score_90, m.team2_score_90, m.team1_score_pen, m.team2_score_pen,"
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "
        
        // user bet fields (default values if no bet)
        "COALESCE(b.id, -1) AS bet_id, "
        "COALESCE(b.bet, '') AS bet, "
        "COALESCE(b.amount, 0) AS bet_amount, "
        "COALESCE(b.odd, 0.0) AS bet_odd, "
        "COALESCE(b.status, -1) AS bet_status, "
        
        "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches table
        "COALESCE(s.points, '') AS special_match_points "
        "FROM matches m "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "JOIN leagues l ON m.league = l.id "
        "LEFT JOIN bets b ON b.match_id = m.id AND b.user_id = " + std::to_string(userId) + " "
        "LEFT JOIN special_matches s ON s.match_id = m.id ";

    if (eMatch == ETeamMatch::Finished)
    {
        sql += "WHERE (m.team1 = " + std::to_string(tid) + " OR m.team2 = " + std::to_string(tid) + ") AND m.team1_score > -1 AND m.team2_score > -1 ORDER BY m.match_date DESC LIMIT 20;";
    }
    else if (eMatch == ETeamMatch::Live)
    {
        auto now = std::chrono::system_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto epoch = now_ms.time_since_epoch();
        auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
        long long currentTimeMs = value.count();

        sql += "WHERE (m.team1 = " + std::to_string(tid) + " OR m.team2 = "
            + std::to_string(tid) + ") AND m.team1_score = -1 AND m.team2_score = -1 AND "
            + "m.match_date < " + std::to_string(currentTimeMs)
            + ";";
    }
    else if (eMatch == ETeamMatch::Upcoming)
    {
        auto now = std::chrono::system_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto epoch = now_ms.time_since_epoch();
        auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
        long long currentTimeMs = value.count();
        sql = "SELECT * FROM (" + sql;

        sql += "WHERE (m.team1 = " + std::to_string(tid) + " OR m.team2 = " + std::to_string(tid) + ") "
            "AND m.match_date > " + std::to_string(currentTimeMs) + " "
            "ORDER BY m.match_date ASC LIMIT 3"
            ") AS sub "
            "ORDER BY sub.match_date DESC;";
    }

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK) 
    {
        fprintf(stderr, "Failed to fetch team page matches: %s", PQerrorMessage(pg));
        PQclear(ret);
        return false;
    }

    int nrows = PQntuples(ret);

    for (int i = 0; i < nrows; ++i)
    {
        rapidjson::Value matchObj(rapidjson::kObjectType);
        int id = atoi(PQgetvalue(ret, i, 0));

        // League object
        rapidjson::Value leagueObj(rapidjson::kObjectType);
        leagueObj.AddMember("id", atoi(PQgetvalue(ret, i, 1)), allocator);
        leagueObj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 2), allocator), allocator);
        leagueObj.AddMember("country", rapidjson::Value(PQgetvalue(ret, i, 3), allocator), allocator);

        std::string season = PQgetvalue(ret, i, 4);
        int week = atoi(PQgetvalue(ret, i, 5));
        int weekType = atoi(PQgetvalue(ret, i, 6));

        long long date = atoll(PQgetvalue(ret, i, 7));

        int team1Score = atol(PQgetvalue(ret, i, 8));
        int team2Score = atol(PQgetvalue(ret, i, 9));
        int elapsed = atol(PQgetvalue(ret, i, 10));
        int team1ScoreLive = atol(PQgetvalue(ret, i, 11));
        int team2ScoreLive = atol(PQgetvalue(ret, i, 12));
        std::string status = PQgetvalue(ret, i, 13);
        int isSpecial = atol(PQgetvalue(ret, i, 14));
        std::string preview = PQgetvalue(ret, i, 15);
        std::string teaser = PQgetvalue(ret, i, 16);
        int playOff = atol(PQgetvalue(ret, i, 17));

        int team1Score90 = atoi(PQgetvalue(ret, i, 18));
        int team2Score90 = atoi(PQgetvalue(ret, i, 19));
        int team1ScorePen = atoi(PQgetvalue(ret, i, 20));
        int team2ScorePen = atoi(PQgetvalue(ret, i, 21));

        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 22)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 23), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 24), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 25)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 26), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 27), allocator), allocator);

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
        matchObj.AddMember("team1_score_90", team1Score90, allocator);
        matchObj.AddMember("team2_score_90", team2Score90, allocator);
        matchObj.AddMember("team1_score_pen", team1ScorePen, allocator);
        matchObj.AddMember("team2_score_pen", team2ScorePen, allocator);
        matchObj.AddMember("status", rapidjson::Value(status.c_str(), allocator), allocator);
        matchObj.AddMember("is_special", isSpecial, allocator);
        matchObj.AddMember("preview", rapidjson::Value(preview.c_str(), allocator), allocator);
        matchObj.AddMember("teaser", rapidjson::Value(teaser.c_str(), allocator), allocator);
        matchObj.AddMember("playOff", playOff, allocator);

        // Add bet object
        rapidjson::Value betObj(rapidjson::kObjectType);
        betObj.AddMember("id", atoi(PQgetvalue(ret, i, 28)), allocator);
        betObj.AddMember("bet", rapidjson::Value(PQgetvalue(ret, i, 29), allocator), allocator);
        betObj.AddMember("amount", atoi(PQgetvalue(ret, i, 30)), allocator);
        betObj.AddMember("odd", atof(PQgetvalue(ret, i, 31)), allocator);
        betObj.AddMember("status", atoi(PQgetvalue(ret, i, 32)), allocator);
        matchObj.AddMember("bet", betObj, allocator);
        
        matchObj.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 33), allocator), allocator);
        matchObj.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 34), allocator), allocator);

        // Add the updated match object to the document array
        document.PushBack(matchObj, allocator);
    }
    PQclear(ret);
    return true;
}

bool MatchesManager::FillTeamMatchesWithFireball(PGconn* pg,
    int userId,
    int tid,
    rapidjson::Value& document,
    rapidjson::Document::AllocatorType& allocator,
    ETeamMatch eMatch
)
{
    std::string sql = "SELECT m.id, m.league, l.name AS league_name, l.country AS league_country, m.season, m.week, m.week_type, m.match_date, m.team1_score, m.team2_score, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.preview, m.teaser, m.play_off, "
        "m.team1_score_90, m.team2_score_90, m.team1_score_pen, m.team2_score_pen,"
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "

        // user bet fields (default values if no bet)
        "COALESCE(fp.id, -1) AS fp_id, "
        "COALESCE(fp.team_id, -1) AS fp_team_id, "
        "COALESCE(fp.player_api_id, -1) AS fp_player_api_id, "
        "COALESCE(fp.player_name, '') AS fp_player_name, "
        "COALESCE(fp.player_photo, '') AS fp_player_photo, "
        "COALESCE(fp.goals, 0) AS fp_goals, "
        "COALESCE(fp.status, -2) AS fp_status, "

        "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches table
        "COALESCE(s.points, '') AS special_match_points "
        "FROM matches m "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "JOIN leagues l ON m.league = l.id "
        "LEFT JOIN fireball_predicts fp ON fp.match_id = m.id AND fp.user_id = " + std::to_string(userId) + " "
        "LEFT JOIN special_matches s ON s.match_id = m.id ";

    if (eMatch == ETeamMatch::Finished)
    {
        sql += "WHERE (m.team1 = " + std::to_string(tid) + " OR m.team2 = " + std::to_string(tid) + ") AND m.team1_score > -1 AND m.team2_score > -1 ORDER BY m.match_date DESC LIMIT 20;";
    }
    else if (eMatch == ETeamMatch::Live)
    {
        auto now = std::chrono::system_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto epoch = now_ms.time_since_epoch();
        auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
        long long currentTimeMs = value.count();

        sql += "WHERE (m.team1 = " + std::to_string(tid) + " OR m.team2 = "
            + std::to_string(tid) + ") AND m.team1_score = -1 AND m.team2_score = -1 AND "
            + "m.match_date < " + std::to_string(currentTimeMs)
            + ";";
    }
    else if (eMatch == ETeamMatch::Upcoming)
    {
        auto now = std::chrono::system_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto epoch = now_ms.time_since_epoch();
        auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
        long long currentTimeMs = value.count();
        sql = "SELECT * FROM (" + sql;

        sql += "WHERE (m.team1 = " + std::to_string(tid) + " OR m.team2 = " + std::to_string(tid) + ") "
            "AND m.match_date > " + std::to_string(currentTimeMs) + " "
            "ORDER BY m.match_date ASC LIMIT 3"
            ") AS sub "
            "ORDER BY sub.match_date DESC;";
    }

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch team page matches: %s", PQerrorMessage(pg));
        PQclear(ret);
        return false;
    }

    int nrows = PQntuples(ret);

    for (int i = 0; i < nrows; ++i)
    {
        rapidjson::Value matchObj(rapidjson::kObjectType);
        int id = atoi(PQgetvalue(ret, i, 0));

        // League object
        rapidjson::Value leagueObj(rapidjson::kObjectType);
        leagueObj.AddMember("id", atoi(PQgetvalue(ret, i, 1)), allocator);
        leagueObj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 2), allocator), allocator);
        leagueObj.AddMember("country", rapidjson::Value(PQgetvalue(ret, i, 3), allocator), allocator);

        std::string season = PQgetvalue(ret, i, 4);
        int week = atoi(PQgetvalue(ret, i, 5));
        int weekType = atoi(PQgetvalue(ret, i, 6));

        long long date = atoll(PQgetvalue(ret, i, 7));

        int team1Score = atol(PQgetvalue(ret, i, 8));
        int team2Score = atol(PQgetvalue(ret, i, 9));
        int elapsed = atol(PQgetvalue(ret, i, 10));
        int team1ScoreLive = atol(PQgetvalue(ret, i, 11));
        int team2ScoreLive = atol(PQgetvalue(ret, i, 12));
        std::string status = PQgetvalue(ret, i, 13);
        int isSpecial = atol(PQgetvalue(ret, i, 14));
        std::string preview = PQgetvalue(ret, i, 15);
        std::string teaser = PQgetvalue(ret, i, 16);
        int playOff = atol(PQgetvalue(ret, i, 17));

        int team1Score90 = atoi(PQgetvalue(ret, i, 18));
        int team2Score90 = atoi(PQgetvalue(ret, i, 19));
        int team1ScorePen = atoi(PQgetvalue(ret, i, 20));
        int team2ScorePen = atoi(PQgetvalue(ret, i, 21));

        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 22)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 23), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 24), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 25)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 26), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 27), allocator), allocator);

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
        matchObj.AddMember("team1_score_90", team1Score90, allocator);
        matchObj.AddMember("team2_score_90", team2Score90, allocator);
        matchObj.AddMember("team1_score_pen", team1ScorePen, allocator);
        matchObj.AddMember("team2_score_pen", team2ScorePen, allocator);
        matchObj.AddMember("status", rapidjson::Value(status.c_str(), allocator), allocator);
        matchObj.AddMember("is_special", isSpecial, allocator);
        matchObj.AddMember("preview", rapidjson::Value(preview.c_str(), allocator), allocator);
        matchObj.AddMember("teaser", rapidjson::Value(teaser.c_str(), allocator), allocator);
        matchObj.AddMember("playOff", playOff, allocator);

        // Add bet object
        rapidjson::Value predictObj(rapidjson::kObjectType);
        predictObj.AddMember("id", atoi(PQgetvalue(ret, i, 28)), allocator);
        predictObj.AddMember("team_id", atoi(PQgetvalue(ret, i, 29)), allocator);
        predictObj.AddMember("player_api_id", atoi(PQgetvalue(ret, i, 30)), allocator);
        predictObj.AddMember("player_name", rapidjson::Value(PQgetvalue(ret, i, 31), allocator), allocator);
        predictObj.AddMember("player_photo", rapidjson::Value(PQgetvalue(ret, i, 32), allocator), allocator);
        predictObj.AddMember("goals", atoi(PQgetvalue(ret, i, 33)), allocator);
        predictObj.AddMember("status", atoi(PQgetvalue(ret, i, 34)), allocator);
        matchObj.AddMember("fireballPredict", predictObj, allocator);

        matchObj.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 35), allocator), allocator);
        matchObj.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 36), allocator), allocator);

        // Add the updated match object to the document array
        document.PushBack(matchObj, allocator);
    }
    PQclear(ret);
    return true;
}

bool MatchesManager::FillTeamMatchesWithCareer(PGconn* pg,
    int userId,
    int tid,
    rapidjson::Value& document,
    rapidjson::Document::AllocatorType& allocator,
    ETeamMatch eMatch
)
{
    std::string sql = "SELECT m.id, m.league, l.name AS league_name, l.country AS league_country, m.season, m.week, m.week_type, m.match_date, m.team1_score, m.team2_score, m.elapsed, m.team1_score_live, m.team2_score_live, m.status, m.is_special, m.preview, m.teaser, m.play_off, "
        "t1.id AS team1_id, t1.name AS team1_name, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.name AS team2_name, t2.short_name AS team2_short_name, "

        "COALESCE(s.title, '') AS special_match_title, " // Fetch title from special_matches table
        "COALESCE(s.points, '') AS special_match_points "
        "FROM matches m "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "JOIN leagues l ON m.league = l.id "
        "LEFT JOIN fireball_predicts fp ON fp.match_id = m.id AND fp.user_id = " + std::to_string(userId) + " "
        "LEFT JOIN special_matches s ON s.match_id = m.id ";

    if (eMatch == ETeamMatch::Finished)
    {
        sql += "WHERE (m.team1 = " + std::to_string(tid) + " OR m.team2 = " + std::to_string(tid) + ") AND m.team1_score > -1 AND m.team2_score > -1 ORDER BY m.match_date DESC LIMIT 20;";
    }
    else if (eMatch == ETeamMatch::Live)
    {
        auto now = std::chrono::system_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto epoch = now_ms.time_since_epoch();
        auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
        long long currentTimeMs = value.count();

        sql += "WHERE (m.team1 = " + std::to_string(tid) + " OR m.team2 = "
            + std::to_string(tid) + ") AND m.team1_score = -1 AND m.team2_score = -1 AND "
            + "m.match_date < " + std::to_string(currentTimeMs)
            + ";";
    }
    else if (eMatch == ETeamMatch::Upcoming)
    {
        auto now = std::chrono::system_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto epoch = now_ms.time_since_epoch();
        auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
        long long currentTimeMs = value.count();
        sql = "SELECT * FROM (" + sql;

        sql += "WHERE (m.team1 = " + std::to_string(tid) + " OR m.team2 = " + std::to_string(tid) + ") "
            "AND m.match_date > " + std::to_string(currentTimeMs) + " "
            "ORDER BY m.match_date ASC LIMIT 3"
            ") AS sub "
            "ORDER BY sub.match_date DESC;";
    }

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch team page matches: %s", PQerrorMessage(pg));
        PQclear(ret);
        return false;
    }

    int nrows = PQntuples(ret);

    for (int i = 0; i < nrows; ++i)
    {
        rapidjson::Value matchObj(rapidjson::kObjectType);
        int id = atoi(PQgetvalue(ret, i, 0));

        // League object
        rapidjson::Value leagueObj(rapidjson::kObjectType);
        leagueObj.AddMember("id", atoi(PQgetvalue(ret, i, 1)), allocator);
        leagueObj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 2), allocator), allocator);
        leagueObj.AddMember("country", rapidjson::Value(PQgetvalue(ret, i, 3), allocator), allocator);

        std::string season = PQgetvalue(ret, i, 4);
        int week = atoi(PQgetvalue(ret, i, 5));
        int weekType = atoi(PQgetvalue(ret, i, 6));

        long long date = atoll(PQgetvalue(ret, i, 7));

        int team1Score = atol(PQgetvalue(ret, i, 8));
        int team2Score = atol(PQgetvalue(ret, i, 9));
        int elapsed = atol(PQgetvalue(ret, i, 10));
        int team1ScoreLive = atol(PQgetvalue(ret, i, 11));
        int team2ScoreLive = atol(PQgetvalue(ret, i, 12));
        std::string status = PQgetvalue(ret, i, 13);
        int isSpecial = atol(PQgetvalue(ret, i, 14));
        std::string preview = PQgetvalue(ret, i, 15);
        std::string teaser = PQgetvalue(ret, i, 16);
        int playOff = atol(PQgetvalue(ret, i, 17));

        rapidjson::Value team1Obj(rapidjson::kObjectType);
        team1Obj.AddMember("id", atoi(PQgetvalue(ret, i, 18)), allocator);
        team1Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 19), allocator), allocator);
        team1Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 20), allocator), allocator);

        rapidjson::Value team2Obj(rapidjson::kObjectType);
        team2Obj.AddMember("id", atoi(PQgetvalue(ret, i, 21)), allocator);
        team2Obj.AddMember("name", rapidjson::Value(PQgetvalue(ret, i, 22), allocator), allocator);
        team2Obj.AddMember("shortName", rapidjson::Value(PQgetvalue(ret, i, 23), allocator), allocator);

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
        matchObj.AddMember("is_special", isSpecial, allocator);
        matchObj.AddMember("preview", rapidjson::Value(preview.c_str(), allocator), allocator);
        matchObj.AddMember("teaser", rapidjson::Value(teaser.c_str(), allocator), allocator);
        matchObj.AddMember("playOff", playOff, allocator);

        matchObj.AddMember("special_match_title", rapidjson::Value(PQgetvalue(ret, i, 24), allocator), allocator);
        matchObj.AddMember("special_match_points", rapidjson::Value(PQgetvalue(ret, i, 25), allocator), allocator);

        // Add the updated match object to the document array
        document.PushBack(matchObj, allocator);
    }
    PQclear(ret);
    return true;
}
