

#include "managers/PQManager.h"
#include <cpr/cpr.h>
#undef GetObject

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
	case ELeague::NationsLeague:
		return 5;
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

std::string getStatisticString(const rapidjson::Value& team1Stats, const rapidjson::Value& team2Stats, const std::string& statName)
{
	int team1Value = 0;
	int team2Value = 0;

	// Iterate through team1Stats to find the stat
	for (const auto& stat : team1Stats.GetArray())
	{
		if (stat["type"].GetString() == statName)
		{
			if (statName == "Ball Possession")
			{
				if (stat["value"].IsString())
					team1Value = atoi(stat["value"].GetString());
			}
			else
			{
				if (stat["value"].IsInt())
					team1Value = stat["value"].GetInt();
			}
			break;
		}
	}

	// Iterate through team2Stats to find the stat
	for (const auto& stat : team2Stats.GetArray())
	{
		if (stat["type"].GetString() == statName)
		{
			if (statName == "Ball Possession")
			{
				if (stat["value"].IsString())
					team2Value = atoi(stat["value"].GetString());
			}
			else
			{
				if (stat["value"].IsInt())
					team2Value = stat["value"].GetInt();
			}
			break;
		}
	}

	// Format the string like "1-4"
	std::ostringstream oss;
	oss << team1Value << "-" << team2Value;

	return oss.str();
}

void FillMatchEvents(PGconn* pg, rapidjson::Document& document, int matchId, CronTeam& team1, CronTeam& team2)
{
	std::string sql = "DELETE FROM events WHERE match_id = " + std::to_string(matchId) + ";";
	PGresult* ret = PQexec(pg, sql.c_str());
	PQclear(ret);

	if (document.HasMember("response") && document["response"].IsArray() &&
		!document["response"].Empty() &&
		document["response"][0].HasMember("events") && document["response"][0]["events"].IsArray() &&
		!document["response"][0]["events"].Empty())
	{

	}
	else
	{
		return;
	}

	rapidjson::Value events = document["response"][0]["events"].GetArray();
	for (rapidjson::SizeType i = 0; i < events.Size(); ++i)
	{
		const rapidjson::Value& ev = events[i];
		int elapsed = ev["time"]["elapsed"].GetInt();
		int extra = 0;
		if (ev["time"].HasMember("extra") && ev["time"]["extra"].IsInt()) 
		{
			extra = ev["time"]["extra"].GetInt();
		}
		std::string player = "";
		if (ev["player"].HasMember("name") && ev["player"]["name"].IsString())
		{
			player = ev["player"]["name"].GetString();
		}
		std::string assist = "";
		if (ev["assist"].HasMember("name") && ev["assist"]["name"].IsString()) 
		{
			assist = ev["assist"]["name"].GetString();
		}

		std::string type = ev["type"].GetString();
		std::string detail = ev["detail"].GetString();

		int team = ev["team"]["id"].GetInt();
		int teamNo = 1;
		if (team == team1.ApiId) teamNo = 1;
		else teamNo = 2;

		// create table events (id serial primary key not null, match_id integer not null, elapsed integer not null, elapsed_extra integer not null, team integer not null, player text not null, assist text not null, type text not null, detail text not null);
		// insert event sql command here
		sql = "INSERT INTO events (match_id, elapsed, elapsed_extra, team, player, assist, type, detail) "
			"VALUES (" + std::to_string(matchId) + ", " + std::to_string(elapsed) + ", " + std::to_string(extra) +
			", " + std::to_string(teamNo) + ", '" + player + "', '" + assist + "', '" + type + "', '" + detail + "');";

		ret = PQexec(pg, sql.c_str());

		if (PQresultStatus(ret) != PGRES_COMMAND_OK)
		{
			fprintf(stderr, "Insert failed: %s", PQerrorMessage(pg));
		}
		else
		{
			printf("Match events inserted successfully.\n");
		}
		PQclear(ret);
	}
}

void FillMatchLineups(PGconn* pg, rapidjson::Document& document, int matchId, long long matchDate)
{
	{
		std::string sql = "SELECT * FROM lineups WHERE match_id = " + std::to_string(matchId) + ";";
		PGresult* ret = PQexec(pg, sql.c_str());
		if (PQresultStatus(ret) != PGRES_TUPLES_OK)
		{
			return;
		}
		int nrows = PQntuples(ret);
		if (nrows > 0) 
		{
			return;
		}

	}

	rapidjson::Value lineup1 = document["response"][0]["lineups"][0].GetObject();
	rapidjson::Value lineup2 = document["response"][0]["lineups"][1].GetObject();

	// team1
	std::string team1Formation = lineup1["formation"].GetString();
	std::string team1PlayerColor = lineup1["team"]["colors"]["player"]["primary"].GetString();
	std::string team1PlayerNColor = lineup1["team"]["colors"]["player"]["number"].GetString();
	std::string team1PlayerBColor = lineup1["team"]["colors"]["player"]["border"].GetString();
	std::string team1GKColor = lineup1["team"]["colors"]["goalkeeper"]["primary"].GetString();
	std::string team1GKNColor = lineup1["team"]["colors"]["goalkeeper"]["number"].GetString();
	std::string team1GKBColor = lineup1["team"]["colors"]["goalkeeper"]["border"].GetString();

	// team2
	std::string team2Formation = lineup2["formation"].GetString();
	std::string team2PlayerColor = lineup2["team"]["colors"]["player"]["primary"].GetString();
	std::string team2PlayerNColor = lineup2["team"]["colors"]["player"]["number"].GetString();
	std::string team2PlayerBColor = lineup2["team"]["colors"]["player"]["border"].GetString();
	std::string team2GKColor = lineup2["team"]["colors"]["goalkeeper"]["primary"].GetString();
	std::string team2GKNColor = lineup2["team"]["colors"]["goalkeeper"]["number"].GetString();
	std::string team2GKBColor = lineup2["team"]["colors"]["goalkeeper"]["border"].GetString();

	// SQL insert command
	std::string sql = "INSERT INTO lineups (match_id, match_date, formation1, player_color1, player_ncolor1, player_bcolor1, "
		"gk_color1, gk_ncolor1, gk_bcolor1, formation2, player_color2, player_ncolor2, player_bcolor2, "
		"gk_color2, gk_ncolor2, gk_bcolor2) VALUES (" +
		std::to_string(matchId) + ", " +
		std::to_string(matchDate) + ", '" +
		team1Formation + "', '" +
		team1PlayerColor + "', '" +
		team1PlayerNColor + "', '" +
		team1PlayerBColor + "', '" +
		team1GKColor + "', '" +
		team1GKNColor + "', '" +
		team1GKBColor + "', '" +
		team2Formation + "', '" +
		team2PlayerColor + "', '" +
		team2PlayerNColor + "', '" +
		team2PlayerBColor + "', '" +
		team2GKColor + "', '" +
		team2GKNColor + "', '" +
		team2GKBColor + "');";

	PGresult* ret = PQexec(pg, sql.c_str());
	if (PQresultStatus(ret) != PGRES_COMMAND_OK)
	{
		// Handle error
		std::cerr << "Error executing SQL: " << PQerrorMessage(pg) << std::endl;
	}

	PQclear(ret);
}


void FillMatchStats(PGconn* pg, rapidjson::Document& document, int matchId)
{
	if (!document["response"][0]["statistics"].Size()) return;

	/*if (!document["response"][0].HasMember("statistics") ||
		!document["response"][0]["statistics"][0].HasMember("statistics") ||
		!document["response"][0]["statistics"][1].HasMember("statistics") ||
		!document["response"][0]["statistics"][0]["statistics"].IsArray() ||
		!document["response"][0]["statistics"][1]["statistics"].IsArray() ||
		document["response"][0]["statistics"][0]["statistics"].Size() == 0 ||
		document["response"][0]["statistics"][1]["statistics"].Size() == 0)
	{
		printf("Statistics not available for this match.\n");
		return;
	} */

	rapidjson::Value team1Stats = document["response"][0]["statistics"][0]["statistics"].GetArray();
	rapidjson::Value team2Stats = document["response"][0]["statistics"][1]["statistics"].GetArray();

	std::string shotsOnTarget = getStatisticString(team1Stats, team2Stats, "Shots on Goal");
	std::string shotsOffTarget = getStatisticString(team1Stats, team2Stats, "Shots off Goal");
	std::string blockedShots = getStatisticString(team1Stats, team2Stats, "Blocked Shots");
	std::string fouls = getStatisticString(team1Stats, team2Stats, "Fouls");
	std::string corners = getStatisticString(team1Stats, team2Stats, "Corner Kicks");
	std::string offsides = getStatisticString(team1Stats, team2Stats, "Offsides");
	std::string possession = getStatisticString(team1Stats, team2Stats, "Ball Possession");
	std::string saves = getStatisticString(team1Stats, team2Stats, "Goalkeeper Saves");

	std::string sql = "INSERT INTO match_stats (match_id, shots_on_target, shots_off_target, blocked_shots, fouls, corners, offsides, possession, saves) "
		"VALUES (" + std::to_string(matchId) + ", '" + shotsOnTarget + "', '" + shotsOffTarget + "', '" + blockedShots + "', '" + fouls + "', '" + corners + "', '" + offsides + "', '" + possession + "', '" + saves + "') "
		"ON CONFLICT (match_id) DO UPDATE SET "
		"shots_on_target = EXCLUDED.shots_on_target, "
		"shots_off_target = EXCLUDED.shots_off_target, "
		"blocked_shots = EXCLUDED.blocked_shots, "
		"fouls = EXCLUDED.fouls, "
		"corners = EXCLUDED.corners, "
		"offsides = EXCLUDED.offsides, "
		"possession = EXCLUDED.possession, "
		"saves = EXCLUDED.saves;";

	PGresult* ret = PQexec(pg, sql.c_str());

	if (PQresultStatus(ret) != PGRES_COMMAND_OK) {
		fprintf(stderr, "Insert/Update failed: %s", PQerrorMessage(pg));
	}
	else {
		printf("Match stats inserted/updated successfully.\n");
	}

	PQclear(ret);
}

std::string getLeagueNameFromIndex(int index) 
{
	if (index == 0) return "A";
	if (index == 1) return "B";
	if (index == 2) return "C";
	if (index == 3) return "D";
	return "";
}

int GetApiFootballMatches(PGconn* pg, ELeague league, int matchId, CronTeam& team1, CronTeam& team2, const std::string& season, int week)
{
	std::string round = "Regular Season - " + std::to_string(week);
	if (league == ELeague::NationsLeague) 
	{
		std::string sql = "SELECT league_index FROM leagues_teams where league_id = " + std::to_string(int(league))
			+ " AND team_id = " + std::to_string(team1.Id) + ";";

		PGresult* ret = PQexec(pg, sql.c_str());
		int leagueIndex = atoi(PQgetvalue(ret, 0, 0));
		round = "League " + getLeagueNameFromIndex(leagueIndex) + " - " + std::to_string(week);
		PQclear(ret);
	}

	std::string apiKey = "74035ea910ab742b96bece628c3ca1e1";

	int leagueId = elTorneoLeagueIdToApiFootball(league);
	std::string url = "https://v3.football.api-sports.io/fixtures";
	cpr::Parameters params = {
		  {"league", std::to_string(leagueId)},
		  {"season", season},
		  {"round", round}
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


	std::string sql = "SELECT m.id, m.league, m.week, m.match_date, "
		"t1.id AS team1_id, t1.api_id AS team1_api_id, t1.short_name AS team1_short_name, "
		"t2.id AS team2_id, t2.api_id AS team2_api_id, t2.short_name AS team2_short_name, "
		"m.api_id "
		"FROM matches m "
		"JOIN teams t1 ON m.team1 = t1.id "
		"JOIN teams t2 ON m.team2 = t2.id "
		"WHERE m.team1_score = -1 AND m.team2_score = -1 AND match_date < " + std::to_string(milliseconds) +
		" AND status <> 'PST' ORDER BY m.match_date;";

	PGresult* ret = PQexec(pg, sql.c_str());
	int nrows = PQntuples(ret);
	for (int i = 0; i < nrows; ++i)
	{
		int id = atoi(PQgetvalue(ret, i, 0));
		int league = atoi(PQgetvalue(ret, i, 1));
		int week = atoi(PQgetvalue(ret, i, 2));
		long long matchDate = atoll(PQgetvalue(ret, i, 3));

		CronTeam team1;
		team1.Id = atoi(PQgetvalue(ret, i, 4));
		team1.ApiId = atoi(PQgetvalue(ret, i, 5));
		team1.ShortName = PQgetvalue(ret, i, 6); // Retrieve team1 short_name

		CronTeam team2;
		team2.Id = atoi(PQgetvalue(ret, i, 7));
		team2.ApiId = atoi(PQgetvalue(ret, i, 8));
		team2.ShortName = PQgetvalue(ret, i, 9); // Retrieve team2 short_name

		int apiId = atoi(PQgetvalue(ret, i, 10));


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

			rapidjson::Value statusValue = document["response"][0]["fixture"]["status"].GetObject();
			int elapsed = 1; 
			if (statusValue["elapsed"].IsInt()) elapsed = statusValue["elapsed"].GetInt();

			rapidjson::Value goalsValue = document["response"][0]["goals"].GetObject();
			int team1Goals = 0;
			if (goalsValue["home"].IsInt()) team1Goals = goalsValue["home"].GetInt();

			int team2Goals = 0;
			if (goalsValue["away"].IsInt()) team2Goals = goalsValue["away"].GetInt();

			std::string status = "";
			if (statusValue["short"].IsString()) status = statusValue["short"].GetString();

			sql = "update matches set elapsed = " + std::to_string(elapsed) +
				", team1_score_live = " + std::to_string(team1Goals) +
				", team2_score_live = " + std::to_string(team2Goals) + 
				", status = '" + status + "'" + 
				" where id = " + std::to_string(id) + ";";
			PGresult* updated = PQexec(pg, sql.c_str());
			PQclear(updated);

			if (status == "PST") continue;

			std::string filename = "data/notifications.json";
			std::string jsonString = ReadFile(filename);
			rapidjson::Document notificationsDocument;
			notificationsDocument.Parse(jsonString.c_str());

			FillMatchStats(pg, document, id);
			FillMatchEvents(pg, document, id, team1, team2);
			// FillMatchLineups(pg, document, id, matchDate);

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
						for (int j = 0; j < nTokens; ++j)
						{
							// Handle ID as integer
							int id = atoi(PQgetvalue(updateRet, j, 0));
							int userId = atoi(PQgetvalue(updateRet, j, 1));
							strcpy(temp, PQgetvalue(updateRet, j, 2));
							std::string token = temp;
							strcpy(temp, PQgetvalue(updateRet, j, 3));
							std::string os = temp;
							strcpy(temp, PQgetvalue(updateRet, j, 4));
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
		std::this_thread::sleep_for(std::chrono::minutes(1));
	}

	return 0;
}