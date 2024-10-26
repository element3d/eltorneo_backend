//
//  upload.cc
//
//  Copyright (c) 2019 Yuji Hirose. All rights reserved.
//  MIT License
//

#include <fstream>
#include "httplib.h"
#include <iostream>
//#include <pqxx/pqxx>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include "routes/LeaguesRoute.h"
#include "routes/AnalyticsRoute.h"
#include "routes/TeamsRoute.h"
#include "routes/MatchesRoute.h"
#include "routes/AuthRoute.h"
#include "routes/PredictsRoute.h"
#include <cpr/cpr.h>

using namespace httplib;
using namespace std;
// using namespace pqxx;


const char *html = R"(
<form id="formElem">
  <input type="file" name="image_file" accept="image/*">
  <input type="file" name="text_file" accept="text/*">
  <input type="submit">
</form>
<script>
  formElem.onsubmit = async (e) => {
    e.preventDefault();
    let res = await fetch('/post', {
      method: 'POST',
      body: new FormData(formElem)
    });
    console.log(await res.text());
  };
</script>
)";






#include "routes/AuthRoute.h"
#include <libpq-fe.h>

int main(void) 
{
    Server svr;

    PGconn* pg = PQconnectdb("host=127.0.0.1 port=5432 dbname=cars user=postgres password=postgres");



/*	connection cc("dbname = cars user = postgres password = postgres \
        hostaddr = 127.0.0.1 port = 5432");
    connection* psql;
    try
    {
        psql = new connection("dbname = cars user = postgres password = postgres \
        hostaddr = 127.0.0.1 port = 5432");
        if (psql->is_open())
        {
            cout << "Opened database successfully: " << psql->dbname() << endl;
        }
        else
        {
            cout << "Can't open database" << endl;
            return 1;
        }
        psql->disconnect ();
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << std::endl;
        return 1;
    }*/

    //AutoPartManager::Get()->SetPG(pg);
	if (PQstatus(pg) != CONNECTION_OK)
	{
		fprintf(stderr, "Connection to database failed: %s",
			PQerrorMessage(pg));
	//	exit_nicely(conn);
	}



    svr.Options("/(.*)",
			[&](const Request & /*req*/, Response &res) {
			res.set_header("Access-Control-Allow-Methods", "POST, GET, DELETE, PUT, OPTIONS");
			res.set_header("Content-Type", "text/html; charset=utf-8");
			res.set_header("Access-Control-Allow-Headers", "X-Requested-With, Content-Type, Accept, Authentication");
			res.set_header("Access-Control-Allow-Origin", "*");
			res.set_header("Connection", "close");
		});

        

   
    svr.set_mount_point("/", "./www");
    svr.Get("/", [](const Request & req, Response &res) {
        std::string lang = req.get_param_value("lang");
        std::string line;
        std::string html;
        std::ifstream myfile ("./www/index.html");
        if (myfile.is_open())
        {
            while ( getline (myfile,line) )
            {
                html += line;
            }
            myfile.close();
        }

        //if (lang.size())
        {
            std::regex reg("<CPP_CODE>");
            html = regex_replace(html, reg, lang);
        }
        res.set_content(html, "text/html");
    });

    svr.Post("/api/v1/signin", AuthRoute::Get()->SignIn());
    svr.Post("/api/v1/signup", AuthRoute::Get()->SignUpV2());
    svr.Get("/api/v1/me", AuthRoute::Get()->Me());
    svr.Get("/api/v1/user", AuthRoute::Get()->GetUser());
    svr.Put("/api/v1/me/avatar", AuthRoute::Get()->MeUploadAvatar());
    svr.Put("/api/v1/me/name", AuthRoute::Get()->MeSetName());
    svr.Delete("/api/v1/me", AuthRoute::Get()->MeDelete());
    svr.Post("/api/v1/me/fcm_token", AuthRoute::Get()->MeAddFcmToken());

    svr.Post("/api/v1/user/notification", AuthRoute::Get()->UserSendNotification());
    svr.Post("/api/v1/user/notification/cl", AuthRoute::Get()->UserSendNotificationCL());
    svr.Post("/api/v1/user/notification/nl", AuthRoute::Get()->UserSendNotificationNL());
    svr.Post("/api/v1/user/notification/update", AuthRoute::Get()->UserSendNotificationUpdate());
    svr.Post("/api/v1/user/notification/quest", AuthRoute::Get()->UserSendNotificationQuest());
    svr.Post("/api/v1/user/notification/elclasico", AuthRoute::Get()->UserSendNotificationElClasico());

    svr.Post("/api/v1/user/notification/special", AuthRoute::Get()->UserSendSpecialMatchNotification());

    svr.Post("/api/v1/user/notification/prediction", AuthRoute::Get()->UserPredictionSendNotification());

    svr.Delete("/api/v1/me/avatar", AuthRoute::Get()->MeDeleteAvatar());
    svr.Get("/api/v1/user/stats", AuthRoute::Get()->GetStats());
    svr.Post("/api/v1/signin/googlemail", AuthRoute::Get()->SignInGoogleWithEmail());


    svr.Get("/api/v1/settings", LeaguesRoute::Get()->GetSettings());

    svr.Get("/api/v1/leagues", LeaguesRoute::Get()->GetLeagues());
    svr.Get("/api/v1/league", LeaguesRoute::Get()->GetLeague());
    svr.Post("/api/v1/leagues", LeaguesRoute::Get()->PostLeague());
    svr.Get("/api/v1/weeks", LeaguesRoute::Get()->GetWeeks());
    svr.Post("/api/v1/league/week", LeaguesRoute::Get()->SetCurrentWeek());
    svr.Get("/api/v1/league/table", LeaguesRoute::Get()->GetLeagueTable());

    svr.Get("/api/v1/teams", TeamsRoute::Get()->GetTeams());
    svr.Post("/api/v1/teams", TeamsRoute::Get()->PostTeam());

    svr.Get("/api/v1/matches", MatchesRoute::Get()->GetMatches());
    svr.Get("/api/v1/matches/day", MatchesRoute::Get()->GetMatchesByDay());
    svr.Get("/api/v1/matches/live", MatchesRoute::Get()->GetMatchesLive());
    svr.Get("/api/v1/matches/upcoming", MatchesRoute::Get()->GetUpcomingMatches());
    svr.Get("/api/v1/match", MatchesRoute::Get()->GetMatch());
    svr.Post("/api/v1/matches", MatchesRoute::Get()->PostMatch());
    svr.Put("/api/v1/match", MatchesRoute::Get()->EditMatch());
    svr.Get("/api/v1/match/statistics", MatchesRoute::Get()->GetMatchStatistics());
    svr.Get("/api/v1/match/events", MatchesRoute::Get()->GetMatchEvents());
    svr.Get("/api/v1/match/header", MatchesRoute::Get()->GetMatchHeader());
    svr.Get("/api/v1/match/live", MatchesRoute::Get()->GetMatchLive());
    svr.Get("/api/v1/match/lineups", MatchesRoute::Get()->GetMatchLineups());
    svr.Get("/api/v1/matches/special", MatchesRoute::Get()->GetSpecialMatch());

    svr.Get("/api/v1/team/matches", MatchesRoute::Get()->GetTeamMatches());

    svr.Post("/api/v1/predicts", PredictsRoute::Get()->PostPredict());
    svr.Put("/api/v1/predicts", PredictsRoute::Get()->EditPredict());
    svr.Get("/api/v1/user/predict", PredictsRoute::Get()->GetUserPredict());
    svr.Get("/api/v1/user/predicts", PredictsRoute::Get()->GetUserPredicts());
    svr.Get("/api/v1/user/score_predicts", PredictsRoute::Get()->GetUserScorePredicts());
    svr.Get("/api/v1/user/winner_predicts", PredictsRoute::Get()->GetUserWinnerPredicts());

    svr.Get("/api/v1/match/predicts", PredictsRoute::Get()->GetMatchPredicts());
    svr.Get("/api/v1/match/predicts/top3", PredictsRoute::Get()->GetMatchPredictsTop3());
    svr.Get("/api/v1/table/points", PredictsRoute::Get()->GetTableByPoints());
    svr.Get("/api/v1/table/score", PredictsRoute::Get()->GetTableByScore());
    svr.Get("/api/v1/table/winner", PredictsRoute::Get()->GetTableByWinner());
    svr.Get("/api/v1/top_scorers", LeaguesRoute::Get()->GetTopScorers());


    svr.Post("/api/v1/analytics/page", AnalyticsRoute::Get()->PostPage());

    svr.Post("/post", [](const Request &req, Response &res) {
		req.params;
        auto image_file = req.get_file_value("image_file");
        auto text_file = req.get_file_value("text_file");

        cout << "image file length: " << image_file.content.length() << endl
             << "image file name: " << image_file.filename << endl
             << "text file length: " << text_file.content.length() << endl
             << "text file name: " << text_file.filename << endl;

        {
          ofstream ofs(image_file.filename, ios::binary);
          ofs << image_file.content;
        }
        {
          ofstream ofs(text_file.filename);
          ofs << text_file.content;
        }

        res.set_content("done", "text/plain");
    });

    auto ret = svr.set_mount_point("/assets", "./assets");
	ret = svr.set_mount_point("/data", "./data");

    svr.listen("192.168.18.234", 1234);
}
