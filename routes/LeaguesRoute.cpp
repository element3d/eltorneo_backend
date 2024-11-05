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
       // MatchesInitializer::InitNationsLeague24_25(pg);
       // MatchesInitializer::InitNationsLeagueTeams24_25(pg);
        //MatchesInitializer::InitChampionsLeague24_25(pg);
        //MatchesInitializer::InitLigue1Teams24_25(pg);

        //MatchesInitializer::InitLigue124_25(pg);

        //MatchesInitializer::InitChampionsLeagueTeams24_25(pg);
        // MatchesInitializer::InitChampionsLeagueTable(pg);

        /*MatchesInitializer::InitPremierLeagueTable(pg);
        MatchesInitializer::FillPremierLeagueTable(pg);

        MatchesInitializer::InitLaLigaTable(pg);
        MatchesInitializer::FillLaLigaTable(pg);

        MatchesInitializer::InitSeriaATable(pg);
        MatchesInitializer::FillSeriaATable(pg);

        MatchesInitializer::InitBundesligaTable(pg);
        MatchesInitializer::FillBundesligaTable(pg);

        MatchesInitializer::InitLigue1Table(pg);
        MatchesInitializer::FillLigue1Table(pg);*/

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
    MatchesInitializer::InitBundesligaTeams24_25(pg);
    MatchesInitializer::InitLigue1Teams24_25(pg);

    MatchesInitializer::InitPremierLeague24_25(pg);
    MatchesInitializer::InitLaLiga24_25(pg);
    MatchesInitializer::InitSerieA24_25(pg);
    MatchesInitializer::InitBundesliga24_25(pg);
    MatchesInitializer::InitLigue124_25(pg);

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
            objValue.AddMember("prodAds", atoi(PQgetvalue(ret, i, 4)), allocator);
            objValue.AddMember("adDiffHours", atoi(PQgetvalue(ret, i, 5)), allocator);
            objValue.AddMember("enableNativeAds", atoi(PQgetvalue(ret, i, 6)), allocator);
            objValue.AddMember("bannerType", atoi(PQgetvalue(ret, i, 7)), allocator);

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
        const char* sql = "SELECT * FROM leagues where status = 1 order by order_pos asc;";
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

            int type = atoi(PQgetvalue(ret, i, 5));
            objValue.AddMember("type", type, allocator);

            int isSpecial = atoi(PQgetvalue(ret, i, 7));
            objValue.AddMember("is_special", isSpecial, allocator);

            int numLeagues = atoi(PQgetvalue(ret, i, 8));
            objValue.AddMember("num_leagues", numLeagues, allocator);

            rapidjson::Value weeks;
            weeks.SetArray();
            if (id == (int)ELeague::ChampionsLeague)
            {
                int i = 1;
                for (; i < 8; ++i)
                {
                    rapidjson::Value weekObject;
                    weekObject.SetObject();
                    weekObject.AddMember("week", i, allocator);
                    weekObject.AddMember("type", (int)EWeekType::Matchday, allocator);
                    weeks.PushBack(weekObject, allocator);
                }

                {
                    rapidjson::Value weekObject;
                    weekObject.SetObject();
                    weekObject.AddMember("week", i++, allocator);
                    weekObject.AddMember("type", (int)EWeekType::RoundOf16, allocator);
                    weeks.PushBack(weekObject, allocator);
                }
                {
                    rapidjson::Value weekObject;
                    weekObject.SetObject();
                    weekObject.AddMember("week", i++, allocator);
                    weekObject.AddMember("type", (int)EWeekType::QuarterFinal, allocator);
                    weeks.PushBack(weekObject, allocator);
                }
                {
                    rapidjson::Value weekObject;
                    weekObject.SetObject();
                    weekObject.AddMember("week", i++, allocator);
                    weekObject.AddMember("type", (int)EWeekType::SemiFinal, allocator);
                    weeks.PushBack(weekObject, allocator);
                }
                {
                    rapidjson::Value weekObject;
                    weekObject.SetObject();
                    weekObject.AddMember("week", i++, allocator);
                    weekObject.AddMember("type", (int)EWeekType::Final, allocator);
                    weeks.PushBack(weekObject, allocator);
                }
            }
            objValue.AddMember("weeks", weeks, allocator);

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

std::function<void(const httplib::Request&, httplib::Response&)> LeaguesRoute::GetWeeks()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        int id = atoi(req.get_param_value("league_id").c_str());

        rapidjson::Document d;
        rapidjson::Document::AllocatorType& allocator = d.GetAllocator();

        d.SetArray();
        if (id == (int)ELeague::ChampionsLeague) 
        {
            int i = 0;
            for (; i < 8; ++i)
            {
                rapidjson::Value weekObject;
                weekObject.SetObject();
                weekObject.AddMember("week", i, allocator);
                weekObject.AddMember("type", (int)EWeekType::Matchday, allocator);
                d.PushBack(weekObject, allocator);
            }

            {
                rapidjson::Value weekObject;
                weekObject.SetObject();
                weekObject.AddMember("week", i++, allocator);
                weekObject.AddMember("type", (int)EWeekType::RoundOf16, allocator);
                d.PushBack(weekObject, allocator);
            }
            {
                rapidjson::Value weekObject;
                weekObject.SetObject();
                weekObject.AddMember("week", i++, allocator);
                weekObject.AddMember("type", (int)EWeekType::QuarterFinal, allocator);
                d.PushBack(weekObject, allocator);
            }
            {
                rapidjson::Value weekObject;
                weekObject.SetObject();
                weekObject.AddMember("week", i++, allocator);
                weekObject.AddMember("type", (int)EWeekType::SemiFinal, allocator);
                d.PushBack(weekObject, allocator);
            }
            {
                rapidjson::Value weekObject;
                weekObject.SetObject();
                weekObject.AddMember("week", i++, allocator);
                weekObject.AddMember("type", (int)EWeekType::Final, allocator);
                d.PushBack(weekObject, allocator);
            }
        }

        // Assuming you convert the Document to a string and send it in the response as before
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        d.Accept(writer);

        // You can then use `buffer.GetString()` to get the JSON string
        // And send it in the response as follows:
        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;  // OK
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> LeaguesRoute::SetCurrentWeek()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        int id = atoi(req.get_param_value("league_id").c_str());

        rapidjson::Document document;
        document.Parse(req.body.c_str());
        int week = document["week"].GetInt();

        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string sql = "UPDATE leagues SET current_week = " + std::to_string(week) + " where id = " + std::to_string(id) + ";";
        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to set current week: %s", PQerrorMessage(pg));
            PQclear(ret);
            res.status = 500;  // Internal Server Error
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }

        PQclear(ret);
        res.status = 200; 
        ConnectionPool::Get()->releaseConnection(pg);
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> LeaguesRoute::GetLeagueTable()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        int leagueId = atoi(req.get_param_value("league_id").c_str());
        int leagueIndex = req.has_param("league_index") ? atoi(req.get_param_value("league_index").c_str()) : 0;

        // Connect to the database
        PGconn* pg = ConnectionPool::Get()->getConnection();

        // SQL query to get the league table sorted by points and then by goal difference
        std::string sql = "SELECT team_id, matches_played, goals_f, goals_a, points, league_index, group_index "
            "FROM tables WHERE league_id = " + std::to_string(leagueId) + " AND league_index = " + std::to_string(leagueIndex) +
            " ORDER BY group_index, points DESC, (goals_f - goals_a) DESC;";

        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to get league table: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500; // Internal Server Error
            return;
        }

        int nrows = PQntuples(ret);

        // Create a JSON document to hold the league table
        rapidjson::Document document;
        document.SetArray();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        for (int i = 0; i < nrows; ++i)
        {
            rapidjson::Value teamObject(rapidjson::kObjectType);

            int teamId = atoi(PQgetvalue(ret, i, 0));
            int matchesPlayed = atoi(PQgetvalue(ret, i, 1));
            int goalsFor = atoi(PQgetvalue(ret, i, 2));
            int goalsAgainst = atoi(PQgetvalue(ret, i, 3));
            int points = atoi(PQgetvalue(ret, i, 4));
            int lIndex = atoi(PQgetvalue(ret, i, 5));
            int gIndex = atoi(PQgetvalue(ret, i, 6));

            // Fetch team details
            std::string teamSql = "SELECT id, name, short_name FROM teams WHERE id = " + std::to_string(teamId) + ";";
            PGresult* teamRet = PQexec(pg, teamSql.c_str());

            if (PQresultStatus(teamRet) == PGRES_TUPLES_OK && PQntuples(teamRet) > 0) {
                rapidjson::Value teamDetails(rapidjson::kObjectType);
                teamDetails.AddMember("id", atoi(PQgetvalue(teamRet, 0, 0)), allocator);
                teamDetails.AddMember("name", rapidjson::Value(PQgetvalue(teamRet, 0, 1), allocator), allocator);
                teamDetails.AddMember("short_name", rapidjson::Value(PQgetvalue(teamRet, 0, 2), allocator), allocator);

                teamObject.AddMember("team", teamDetails, allocator);
            }
       
            PQclear(teamRet);

            // Add other league table fields
            teamObject.AddMember("matches_played", matchesPlayed, allocator);
            teamObject.AddMember("goals_f", goalsFor, allocator);
            teamObject.AddMember("goals_a", goalsAgainst, allocator);
            teamObject.AddMember("goal_difference", goalsFor - goalsAgainst, allocator);
            teamObject.AddMember("points", points, allocator);
            teamObject.AddMember("league_index", lIndex, allocator);
            teamObject.AddMember("group_index", gIndex, allocator);

            document.PushBack(teamObject, allocator);
        }

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);

        // Convert JSON document to string and set it as the response body
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200; // OK
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

        std::string season = PQgetvalue(ret, 0, 2);
        rapidjson::Value saesonValue;
        saesonValue.SetString(season.c_str(), season.size(), allocator);
        document.AddMember("season", saesonValue, allocator);

        int currentWeek = atoi(PQgetvalue(ret, 0, 3));
        document.AddMember("week", currentWeek, allocator);

        int numWeeks = atoi(PQgetvalue(ret, 0, 4));
        document.AddMember("num_weeks", numWeeks, allocator);

        int type = atoi(PQgetvalue(ret, 0, 5));
        document.AddMember("type", type, allocator);

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

std::function<void(const httplib::Request&, httplib::Response&)> LeaguesRoute::GetTopScorers()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        // SQL query to retrieve all data from players and top_scorers, excluding players whose ready != 1
        std::string sql = R"(
            SELECT ts.id, ts.player_id, ts.league_id, ts.team_id, ts.games, ts.goals,
                   p.id, p.name, p.team_id, p.team_name, p.team_short_name, p.number, p.firstname, p.lastname, p.api_id, p.ready
            FROM top_scorers ts
            JOIN players p ON ts.player_id = p.id
            WHERE p.ready = 1;
        )";

        PGconn* pg = ConnectionPool::Get()->getConnection();
        PGresult* ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to get top scorers: %s", PQerrorMessage(pg));
            PQclear(ret);
            res.status = 500;
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }

        rapidjson::Document d;
        d.SetObject();

        int nrows = PQntuples(ret);
        for (int i = 0; i < nrows; ++i)
        {
            rapidjson::Value player(rapidjson::kObjectType);

            // Data from top_scorers table
            int id = atoi(PQgetvalue(ret, i, 0));
            int playerId = atoi(PQgetvalue(ret, i, 1));
            int leagueId = atoi(PQgetvalue(ret, i, 2));
            int teamId = atoi(PQgetvalue(ret, i, 3));
            int games = atoi(PQgetvalue(ret, i, 4));
            int goals = atoi(PQgetvalue(ret, i, 5));

            // Data from players table
            int playerIdFromPlayers = atoi(PQgetvalue(ret, i, 6));  // This should match ts.player_id
            std::string playerName = PQgetvalue(ret, i, 7);
            int playerTeamId = atoi(PQgetvalue(ret, i, 8));
            std::string teamName = PQgetvalue(ret, i, 9);
            std::string teamShortName = PQgetvalue(ret, i, 10);
            int number = atoi(PQgetvalue(ret, i, 11));
            std::string firstName = PQgetvalue(ret, i, 12);
            std::string lastName = PQgetvalue(ret, i, 13);
            int apiId = atoi(PQgetvalue(ret, i, 14));
            int ready = atoi(PQgetvalue(ret, i, 15));  // ready should always be 1 due to the filter

            // Build player JSON object
            rapidjson::Value v;
            v.SetInt(id);
            player.AddMember("id", v, d.GetAllocator());
            v.SetInt(playerId);
            player.AddMember("player_id", v, d.GetAllocator());
            v.SetInt(leagueId);
            player.AddMember("league_id", v, d.GetAllocator());
            v.SetInt(teamId);
            player.AddMember("team_id", v, d.GetAllocator());
            v.SetInt(games);
            player.AddMember("games", v, d.GetAllocator());
            v.SetInt(goals);
            player.AddMember("goals", v, d.GetAllocator());

            // Add player table data to the JSON
            v.SetInt(playerIdFromPlayers);
            player.AddMember("player_id_from_players", v, d.GetAllocator());
            v.SetString(playerName.c_str(), d.GetAllocator());
            player.AddMember("player_name", v, d.GetAllocator());
            v.SetInt(playerTeamId);
            player.AddMember("player_team_id", v, d.GetAllocator());
            v.SetString(teamName.c_str(), d.GetAllocator());
            player.AddMember("team_name", v, d.GetAllocator());
            v.SetString(teamShortName.c_str(), d.GetAllocator());
            player.AddMember("team_short_name", v, d.GetAllocator());
            v.SetInt(number);
            player.AddMember("number", v, d.GetAllocator());
            v.SetString(firstName.c_str(), d.GetAllocator());
            player.AddMember("firstname", v, d.GetAllocator());
            v.SetString(lastName.c_str(), d.GetAllocator());
            player.AddMember("lastname", v, d.GetAllocator());
            v.SetInt(apiId);
            player.AddMember("api_id", v, d.GetAllocator());
            v.SetInt(ready);
            player.AddMember("ready", v, d.GetAllocator());

            // Add the player object to the league ID key in the document
            rapidjson::Value k;
            k.SetString(std::to_string(leagueId).c_str(), d.GetAllocator());
            d.AddMember(k, player, d.GetAllocator());
        }

        // Serialize the JSON response
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        d.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;  // OK

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}
