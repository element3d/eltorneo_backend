

#include "managers/PQManager.h"
#include <cpr/cpr.h>
#include <rapidjson/document.h>
#include <iostream>
#include <string>
#include "routes/League.h"
#undef min
#undef max
#include "managers/PNManager.h"

int elTorneoLeagueIdToApiFootball(ELeague league) 
{
	switch (league)
	{
	case ELeague::ChampionsLeague:
		return 2;
		break;
	case ELeague::PremierLeague:
		return 39;
		break;
	case ELeague::LaLiga:
		return 140;
		break;
	case ELeague::SerieA:
		return 135;
		break;
	case ELeague::Bundesliga:
		return 78;
		break;
	case ELeague::Ligue1:
		return 61;
		break;
	default:
		break;
	}
	return 0;
}

struct CronTeam
{
	int Id;
	int ApiId;
	std::string ShortName;
};
#include "routes/Team.h"

int GetApiFootballMatches(PGconn* pg, ELeague league, int matchId, CronTeam& team1, CronTeam& team2, const std::string& season, int week)
{
	std::string apiKey = "74035ea910ab742b96bece628c3ca1e1";

	int leagueId = elTorneoLeagueIdToApiFootball(league);
	std::string url = "https://v3.football.api-sports.io/fixtures";
	cpr::Parameters params = {
		  {"league", std::to_string(leagueId)},
		  {"season", season},
		  {"round", "Regular Season - " + std::to_string(week)}
	};

	// Make the request
	cpr::Response r = cpr::Get(cpr::Url{ url },
		params,
		cpr::Header{ {"x-apisports-key", apiKey} });

	if (r.status_code == 200) 
	{
		// Parse the JSON response
		rapidjson::Document document;
		document.Parse(r.text.c_str());

		if (document.HasMember("response") && document["response"].IsArray()) 
		{
			const rapidjson::Value& matches = document["response"];
			for (rapidjson::SizeType i = 0; i < matches.Size(); i++) 
			{
				const rapidjson::Value& match = matches[i];
				if (match.HasMember("fixture")) 
				{
					std::string date = match["fixture"]["date"].GetString();
					int id = match["fixture"]["id"].GetInt();
					std::string team1Name = Team::ToString(ETeam(team1.Id));
					std::string team2Name = Team::ToString(ETeam(team2.Id));

					std::string homeTeam = match["teams"]["home"]["name"].GetString();
					std::string awayTeam = match["teams"]["away"]["name"].GetString();

					if (homeTeam == team1Name && awayTeam == team2Name)
					{
						int homeId = match["teams"]["home"]["id"].GetInt();
						int awayId = match["teams"]["away"]["id"].GetInt();

						std::string sql = "update teams set api_id = " + std::to_string(homeId) + " where id = " + std::to_string(team1.Id) + ";";
						PGresult* ret = PQexec(pg, sql.c_str());
						PQclear(ret);
						sql = "update teams set api_id = " + std::to_string(awayId) + " where id = " + std::to_string(team2.Id) + ";";
						ret = PQexec(pg, sql.c_str());
						PQclear(ret);

						team1.ApiId = homeId;
						team2.ApiId = awayId;

						sql = "update matches set api_id = " + std::to_string(id) + " where id = " + std::to_string(matchId) + ";";
						ret = PQexec(pg, sql.c_str());
						PQclear(ret);
						return id;
					}	
				}
			}
		}
		else {
			std::cerr << "No matches found in the response." << std::endl;
		}
	}
	else {
		std::cerr << "Failed to retrieve data. HTTP Status code: " << r.status_code << std::endl;
		std::cerr << "Response: " << r.text << std::endl;
	}
	return -1;
}

void SendPushNotification() 
{
	
}

static std::string ReadFile(const std::string& filename)
{
	std::ifstream file(filename);
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

void GetLiveMatches(PGconn* pg)
{
	std::string apiKey = "74035ea910ab742b96bece628c3ca1e1";

	auto now = std::chrono::system_clock::now();

	// Convert the time point to a duration since the epoch
	auto duration = now.time_since_epoch();

	// Convert the duration to milliseconds
	long long milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();


	std::string sql = "SELECT m.id, m.league, m.week, "
		"t1.id AS team1_id, t1.api_id AS team1_api_id, t1.short_name AS team1_short_name, "
		"t2.id AS team2_id, t2.api_id AS team2_api_id, t2.short_name AS team2_short_name, "
		"m.api_id "
		"FROM matches m "
		"JOIN teams t1 ON m.team1 = t1.id "
		"JOIN teams t2 ON m.team2 = t2.id "
		"WHERE m.team1_score = -1 AND m.team2_score = -1 AND match_date < " + std::to_string(milliseconds) +
		" ORDER BY m.match_date;";

	PGresult* ret = PQexec(pg, sql.c_str());
	int nrows = PQntuples(ret);
	for (int i = 0; i < nrows; ++i)
	{
		int id = atoi(PQgetvalue(ret, i, 0));
		int league = atoi(PQgetvalue(ret, i, 1));
		int week = atoi(PQgetvalue(ret, i, 2));

		CronTeam team1;
		team1.Id = atoi(PQgetvalue(ret, i, 3));
		team1.ApiId = atoi(PQgetvalue(ret, i, 4));
		team1.ShortName = PQgetvalue(ret, i, 5); // Retrieve team1 short_name

		CronTeam team2;
		team2.Id = atoi(PQgetvalue(ret, i, 6));
		team2.ApiId = atoi(PQgetvalue(ret, i, 7));
		team2.ShortName = PQgetvalue(ret, i, 8); // Retrieve team2 short_name

		int apiId = atoi(PQgetvalue(ret, i, 9));


		if (apiId == -1 || team1.ApiId == -1 || team2.ApiId == -1)
		{
			apiId = GetApiFootballMatches(pg, ELeague(league), id, team1, team2, "2024", week);
		}

		std::string url = "https://v3.football.api-sports.io/fixtures?id=" + std::to_string(apiId);

		// Make the GET request
		cpr::Response r = cpr::Get(cpr::Url{ url },
			cpr::Header{ {"x-apisports-key", apiKey} });

		if (r.status_code == 200)
		{
			// Parse the JSON response
			rapidjson::Document document;
			document.Parse(r.text.c_str());

			int elapsed = document["response"][0]["fixture"]["status"]["elapsed"].GetInt();
			int team1Goals = document["response"][0]["goals"]["home"].GetInt();
			int team2Goals = document["response"][0]["goals"]["away"].GetInt();
			std::string status = document["response"][0]["fixture"]["status"]["short"].GetString();

			sql = "update matches set elapsed = " + std::to_string(elapsed) +
				", team1_score_live = " + std::to_string(team1Goals) +
				", team2_score_live = " + std::to_string(team2Goals) + 
				", status = '" + status + "'" + 
				" where id = " + std::to_string(id) + ";";
			PGresult* updated = PQexec(pg, sql.c_str());
			PQclear(updated);

			std::string filename = "data/notifications.json";
			std::string jsonString = ReadFile(filename);
			rapidjson::Document notificationsDocument;
			notificationsDocument.Parse(jsonString.c_str());

			if (status == "FT") 
			{
				sql = "update matches set team1_score = " + std::to_string(team1Goals) +
					", team2_score = " + std::to_string(team2Goals) +
					" where id = " + std::to_string(id) + ";";
				updated = PQexec(pg, sql.c_str());
				PQclear(updated);

				// Update the league table for both teams
				auto updateLeagueTable = [&](int team, int goalsFor, int goalsAgainst, int points) {
					sql = "UPDATE tables SET "
						"matches_played = matches_played + 1, "
						"goals_f = goals_f + " + std::to_string(goalsFor) + ", "
						"goals_a = goals_a + " + std::to_string(goalsAgainst) + ", "
						"points = points + " + std::to_string(points) + " "
						"WHERE team_id = " + std::to_string(team) + " AND league_id = " + std::to_string(league) + " AND season = '" + "24/25" + "'" + ";";
					PGresult* updateRet = PQexec(pg, sql.c_str());
					PQclear(updateRet);
				};

				// Determine points to assign
				int pointsForTeam1 = 0;
				int pointsForTeam2 = 0;

				if (team1Goals > team2Goals) 
				{
					pointsForTeam1 = 3; // Team 1 wins
				}
				else if (team1Goals < team2Goals) 
				{
					pointsForTeam2 = 3; // Team 2 wins
				}
				else 
				{
					pointsForTeam1 = 1; // Draw
					pointsForTeam2 = 1; // Draw
				}

				// Update league table for both teams
				updateLeagueTable(team1.Id, team1Goals, team2Goals, pointsForTeam1);
				updateLeagueTable(team2.Id, team2Goals, team1Goals, pointsForTeam2);


				sql = "SELECT * FROM predicts WHERE match_id = " + std::to_string(id) + ";";
				PGresult* pret = PQexec(pg, sql.c_str());

				int nrows = PQntuples(pret);

				bool sendPN = nrows > 0;
				std::string accessToken;
				std::string jwt = PNManager::CreateJwtToken();
				if (!jwt.size()) sendPN = false;
				else 
				{
					accessToken = PNManager::RequestAccessToken(jwt);
				}
				if (!accessToken.size()) sendPN = false;

				for (int i = 0; i < nrows; ++i)
				{
					int id = atoi(PQgetvalue(pret, i, 0));
					int userId = atoi(PQgetvalue(pret, i, 1));
					int t1score = atoi(PQgetvalue(pret, i, 3));
					int t2score = atoi(PQgetvalue(pret, i, 4));
					EPredictStatus predictStatus = (EPredictStatus)atoi(PQgetvalue(pret, i, 5));
					if (predictStatus != EPredictStatus::Pending) continue;

					std::string nTitle = "prediction_score_title";
					std::string nMsg = "prediction_score_msg";
					int points = 0;
					EPredictStatus status = EPredictStatus::Pending;
					if (team1Goals == t1score && team2Goals == t2score)
					{
						points = 3;
						status = EPredictStatus::ScorePredicted;
					}
					else
					{
						if ((team1Goals > team2Goals && t1score > t2score) ||
							(team1Goals < team2Goals && t1score < t2score) ||
							(team1Goals == team2Goals && t1score == t2score))
						{
							points = 1;
							status = EPredictStatus::WinnerPredicted;

							if (team1Goals == team2Goals && t1score == t2score)
							{
								nTitle = "prediction_draw_title";
								nMsg = "prediction_draw_msg";
							}
							else 
							{
								nTitle = "prediction_winner_title";
								nMsg = "prediction_winner_msg";
							}
						}
						else
						{
							points = -1;
							status = EPredictStatus::Failed;
							sendPN = false;
						}
					}

					sql = "UPDATE users SET points = GREATEST(0, points + " + std::to_string(points) + ") WHERE id = " + std::to_string(userId) + ";";
					PGresult* updateRet = PQexec(pg, sql.c_str());
					PQclear(updateRet);

					sql = "UPDATE predicts SET status = " + std::to_string(int(status)) + " WHERE id = " + std::to_string(id) + ";";
					updateRet = PQexec(pg, sql.c_str());
					PQclear(updateRet);

					// Send push notifications
					if (sendPN)
					{
						sql = "SELECT * FROM fcm_tokens WHERE user_id = " + std::to_string(userId);
						updateRet = PQexec(pg, sql.c_str());

						char* temp = (char*)calloc(4096, sizeof(char));
						std::vector<int> invalidTokens;
						int nTokens = PQntuples(updateRet);
						for (int i = 0; i < nTokens; ++i)
						{
							// Handle ID as integer
							int id = atoi(PQgetvalue(updateRet, i, 0));
							int userId = atoi(PQgetvalue(updateRet, i, 1));
							strcpy(temp, PQgetvalue(updateRet, i, 2));
							std::string token = temp;
							strcpy(temp, PQgetvalue(updateRet, i, 3));
							std::string os = temp;
							strcpy(temp, PQgetvalue(updateRet, i, 4));
							std::string lang = temp;

							std::string t = notificationsDocument[lang.c_str()][nTitle.c_str()].GetString()
								+ std::string(" ") + team1.ShortName + " " + std::to_string(team1Goals) + " - " + std::to_string(team2Goals) + " " + team2.ShortName;
							
							std::string m = notificationsDocument[lang.c_str()][nMsg.c_str()].GetString();

							bool sendRet = PNManager::SendPushNotification(accessToken, token, t, m);
							if (!sendRet) invalidTokens.push_back(id);
						}

						free(temp);
						PQclear(updateRet);

						if (invalidTokens.size())
						{
							for (auto id : invalidTokens)
							{
								sql = std::string("delete from fcm_tokens where id = ") + std::to_string(id) + ";";
								PGresult* res = PQexec(pg, sql.c_str());
								PQclear(res);
							}
						}
					}
				}
				PQclear(pret);
			}
		}
	}
	PQclear(ret);

}

int main() 
{
	PGconn* pg = ConnectionPool::Get()->getConnection();

	while (true) 
	{
		GetLiveMatches(pg);
		// sleep for 1 minute
		std::this_thread::sleep_for(std::chrono::minutes(5));

	}

	return 0;
}