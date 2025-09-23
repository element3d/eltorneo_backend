

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
#include <thread>

std::string apiKey = "74035ea910ab742b96bece628c3ca1e1";
void GetMatchPlayers
(
	PGconn* pg, 
	int matchId, 
	int matchApiId, 
	int team1Score,
	int team2Score,
	int team1Id,
	int team2Id, 
	bool updateFireball = false
);

struct FinishedMatch 
{
	long long Timestamp;
	int MatchId;
	int MatchApiId;
	int Team1Score;
	int Team2Score;
	int Team1Id;
	int Team2Id;
};
std::vector<FinishedMatch> finishedMatches;

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
	case ELeague::CoppaItalia:
		return 137;
	case ELeague::SuperCupItalia:
		return 547;
	case ELeague::SuperCupFrance:
		return 526;
	case ELeague::SuperCupSpain:
		return 556;
	case ELeague::EFLCup:
		return 48;
	case ELeague::CopaDelRey:
		return 143;
	case ELeague::EuropaLeague:
		return 3;
	case ELeague::ConferenceLeague:
		return 848;
	case ELeague::ClubWorldCup:
		return 15;
	case ELeague::CommunityShield:
		return 528;
	case ELeague::UEFASuperCup:
		return 531;
	case ELeague::DFLSuperCup:
		return 529;
	case ELeague::UEFAWorldClubQualification:
		return 32;
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

// Function to escape single quotes in a string
std::string escapeSingleQuotes(const std::string& str) {
	std::string escapedStr;
	for (char c : str) {
		if (c == '\'') {
			escapedStr += "''"; // Escape single quote
		}
		else {
			escapedStr += c;
		}
	}
	return escapedStr;
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

		player = escapeSingleQuotes(player);
		assist = escapeSingleQuotes(assist);

		std::string type = ev["type"].GetString();
		std::string detail = ev["detail"].GetString();
		std::string comments;
		if (ev.HasMember("comments") && !ev["comments"].IsNull()) 
		{
			comments = ev["comments"].GetString();
		}

		int team = ev["team"]["id"].GetInt();
		int teamNo = 1;
		if (team == team1.ApiId) teamNo = 1;
		else teamNo = 2;

		// create table events (id serial primary key not null, match_id integer not null, elapsed integer not null, elapsed_extra integer not null, team integer not null, player text not null, assist text not null, type text not null, detail text not null);
		// insert event sql command here
		sql = "INSERT INTO events (match_id, elapsed, elapsed_extra, team, player, assist, type, detail, comments) "
			"VALUES (" + std::to_string(matchId) + ", " + std::to_string(elapsed) + ", " + std::to_string(extra) +
			", " + std::to_string(teamNo) + ", '" + player + "', '" 
			+ assist + "', '" 
			+ type + "', '" 
			+ detail + "', '"
			+ comments 
			+ "');";

		ret = PQexec(pg, sql.c_str());

		if (PQresultStatus(ret) != PGRES_COMMAND_OK)
		{
			fprintf(stderr, "Insert failed: %s", PQerrorMessage(pg));
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

	if (PQresultStatus(ret) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "Insert/Update failed: %s", PQerrorMessage(pg));
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

std::string GetApiFootballRound(PGconn* pg, ELeague league, int week, int team1Id)
{
	std::string round = "Regular Season - " + std::to_string(week);
	if (league == ELeague::NationsLeague)
	{
		if (week <= 6) 
		{
			std::string sql = "SELECT league_index FROM leagues_teams where league_id = " + std::to_string(int(league))
				+ " AND team_id = " + std::to_string(team1Id) + ";";

			PGresult* ret = PQexec(pg, sql.c_str());
			int leagueIndex = atoi(PQgetvalue(ret, 0, 0));
			round = "League " + getLeagueNameFromIndex(leagueIndex) + " - " + std::to_string(week);
			PQclear(ret);
		} 
		else if (week == 7) 
		{
			round = "Quarter-finals";
		}
		else if (week == 8)
		{
			round = "Semi-finals";
		}
		else if (week == 9)
		{
			if (team1Id == 10008)
				round = "3rd Place Final";
			else
				round = "Final";
		}
	}
	else if (league == ELeague::ChampionsLeague)
	{
		if (week <= 8)
		{
			round = "League Stage - " + std::to_string(week);
		}
		else if (week == 9)
		{
			round = "Knockout Round Play-offs";
		}
		else if (week == 10) 
		{
			round = "Round of 16";
		}
		else if (week == 11)
		{
			round = "Quarter-finals";
		}
		else if (week == 12)
		{
			round = "Semi-finals";
		}
		else if (week == 13)
		{
			round = "Final";
		}
	}
	else if (league == ELeague::SuperCupItalia || league == ELeague::SuperCupSpain || league == ELeague::EFLCup)
	{
		if (week == 1)
		{
			round = "Semi-finals";
		}
		else if (week == 2)
		{
			round = "Final";
		}
	}
	else if (league == ELeague::SuperCupFrance 
		|| league == ELeague::EuropaLeague 
		|| league == ELeague::ConferenceLeague
		|| league == ELeague::CommunityShield
		|| league == ELeague::UEFASuperCup
		|| league == ELeague::DFLSuperCup)
	{
		if (week == 1)
		{
			round = "Final";
		}
	}
	else if (league == ELeague::CopaDelRey || league == ELeague::CoppaItalia)
	{
		if (week == 1)
		{
			round = "Quarter-finals";
		}
		if (week == 2)
		{
			round = "Semi-finals";
		}
		else if (week == 3)
		{
			round = "Final";
		}
	}
	else if (league == ELeague::ClubWorldCup)
	{
		if (week == 1)
		{
			round = "Group Stage - 1";
		}
		if (week == 2)
		{
			round = "Group Stage - 2";
		}
		else if (week == 3)
		{
			round = "Group Stage - 3";
		}
		else if (week == 4)
		{
			round = "8th Finals";
		}
		else if (week == 5)
		{
			round = "Quarter-finals";
		}
		else if (week == 6)
		{
			round = "Semi-finals";
		}
		else if (week == 7)
		{
			round = "Final";
		}
	}
	else if (league == ELeague::UEFAWorldClubQualification)
	{
		if (week == 5)
		{
			round = "Group Stage - 5";
		}
		if (week == 6)
		{
			round = "Group Stage - 6";
		}
	}


	return round;
}

int GetApiFootballMatches(PGconn* pg, ELeague league, int matchId, CronTeam& team1, CronTeam& team2, const std::string& season, int week)
{
	std::string round = GetApiFootballRound(pg, league, week, team1.Id);


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

enum class EBeatBetType 
{
	Win,
	NotLoose,
	Draw,
	NotDraw
};

void UpdateBeatBetPredicts(PGconn* pg, int matchId, int team1Goals, int team2Goals)
{
	std::string beatBetSql =
		"SELECT id, ai_team, ai_type, ai_status, ls_team, ls_type, ls_percent, ls_status, "
		"score180_team, score180_type, score180_percent, score180_status "
		"FROM beat_bet WHERE match_id = " + std::to_string(matchId) + " LIMIT 1;";

	PGresult* beatBetRet = PQexec(pg, beatBetSql.c_str());

	int aiStatus = -1;
	int lsStatus = -1;
	int s180Status = -1;
	int id = -1;
	if (PQresultStatus(beatBetRet) == PGRES_TUPLES_OK && PQntuples(beatBetRet) > 0)
	{
		id = atoi(PQgetvalue(beatBetRet, 0, 0));
		int aiTeam = atoi(PQgetvalue(beatBetRet, 0, 1));
		int aiType = atoi(PQgetvalue(beatBetRet, 0, 2));
		int lsTeam = atoi(PQgetvalue(beatBetRet, 0, 4));
		int lsType = atoi(PQgetvalue(beatBetRet, 0, 5));
		int score180Team = atoi(PQgetvalue(beatBetRet, 0, 8));
		int score180Type = atoi(PQgetvalue(beatBetRet, 0, 9));

		// AI
		aiStatus = 0;
		{
			if (aiType == (int)EBeatBetType::Win) 
			{
				if (aiTeam == 1) 
				{
					aiStatus = team1Goals > team2Goals;
				}
				else if (aiTeam == 2)
				{
					aiStatus = team2Goals > team1Goals;
				}
			}
			else if (aiType == (int)EBeatBetType::NotLoose) 
			{
				if (aiTeam == 1)
				{
					aiStatus = team1Goals >= team2Goals;
				}
				else if (aiTeam == 2)
				{
					aiStatus = team2Goals >= team1Goals;
				}
			}
			else if (aiType == (int)EBeatBetType::Draw)
			{
				
				aiStatus = team1Goals == team2Goals;
			}
			else if (aiType == (int)EBeatBetType::NotDraw)
			{

				aiStatus = team1Goals != team2Goals;
			}
		}

		// LiveScore
		lsStatus = 0;
		{
			if (lsType == (int)EBeatBetType::Win)
			{
				if (lsTeam == 1)
				{
					lsStatus = team1Goals > team2Goals;
				}
				else if (lsTeam == 2)
				{
					lsStatus = team2Goals > team1Goals;
				}
			}
			else if (lsType == (int)EBeatBetType::NotLoose)
			{
				if (lsTeam == 1)
				{
					lsStatus = team1Goals >= team2Goals;
				}
				else if (lsTeam == 2)
				{
					lsStatus = team2Goals >= team1Goals;
				}
			}
			else if (lsType == (int)EBeatBetType::Draw)
			{

				lsStatus = team1Goals == team2Goals;
			}
			else if (lsType == (int)EBeatBetType::NotDraw)
			{

				lsStatus = team1Goals != team2Goals;
			}
		}

		// 180 Score
		s180Status = 0;
		{
			if (score180Type == (int)EBeatBetType::Win)
			{
				if (score180Team == 1)
				{
					s180Status = team1Goals > team2Goals;
				}
				else if (score180Team == 2)
				{
					s180Status = team2Goals > team1Goals;
				}
			}
			else if (score180Type == (int)EBeatBetType::NotLoose)
			{
				if (score180Team == 1)
				{
					s180Status = team1Goals >= team2Goals;
				}
				else if (score180Team == 2)
				{
					s180Status = team2Goals >= team1Goals;
				}
			}
			else if (score180Type == (int)EBeatBetType::Draw)
			{

				s180Status = team1Goals == team2Goals;
			}
			else if (score180Type == (int)EBeatBetType::NotDraw)
			{
				s180Status = team1Goals != team2Goals;
			}
		}
	}

	PQclear(beatBetRet);

	// Update
	if (id > 0)
	{
		beatBetSql = "UPDATE beat_bet SET ai_status = " + std::to_string(aiStatus)
			+ ", ls_status = " + std::to_string(lsStatus)
			+ ", score180_status = " + std::to_string(s180Status)
			+ " WHERE id = " + std::to_string(id)
			+ ";";
		beatBetRet = PQexec(pg, beatBetSql.c_str());
		PQclear(beatBetRet);
	}
}

void ProcessBetResults(PGconn* pg, int matchId, int team1Goals, int team2Goals, int isSpecial)
{
	std::string sql = "SELECT * FROM bets WHERE match_id = " + std::to_string(matchId) + ";";

	PGresult* ret = PQexec(pg, sql.c_str());
	int nrows = PQntuples(ret);

	for (int i = 0; i < nrows; ++i)
	{
		int id = atoi(PQgetvalue(ret, i, 0));
		int userId = atoi(PQgetvalue(ret, i, 1));
		// int matchId = atoi(PQgetvalue(ret, i, 2));
		std::string bet = PQgetvalue(ret, i, 3);
		int amount = atoi(PQgetvalue(ret, i, 4));
		float odd = atof(PQgetvalue(ret, i, 5));
		int status = atoi(PQgetvalue(ret, i, 6));
		int oldAmount = 0;
		if (isSpecial) 
		{
			oldAmount = amount;
			amount = 20;
		}

		if (team1Goals > team2Goals) 
		{
			if (bet == "w1" || bet == "x1" || bet == "x12") 
			{
				std::string betStatusSql = "UPDATE bets SET status = 1 WHERE id = " + std::to_string(id) + ";";
				PGresult* statusRet = PQexec(pg, betStatusSql.c_str());
				PQclear(statusRet);

				float win = amount * odd;
				std::string balanceSql = "UPDATE users SET balance = balance + " + std::to_string(win)
					+ " WHERE id = " + std::to_string(userId) + ";";
				PGresult* balanceRet = PQexec(pg, balanceSql.c_str());
				PQclear(balanceRet);
			}
			else 
			{
				std::string betStatusSql = "UPDATE bets SET status = 2 WHERE id = " + std::to_string(id) + ";";
				PGresult* statusRet = PQexec(pg, betStatusSql.c_str());
				PQclear(statusRet);

				if (isSpecial) 
				{
					std::string balanceSql = "UPDATE users SET balance = balance + " + std::to_string(oldAmount)
						+ " WHERE id = " + std::to_string(userId) + ";";
					PGresult* balanceRet = PQexec(pg, balanceSql.c_str());
					PQclear(balanceRet);
				}
			}
		}
		else if (team1Goals == team2Goals)
		{
			if (bet == "x" || bet == "x1" || bet == "x2")
			{
				std::string betStatusSql = "UPDATE bets SET status = 1 WHERE id = " + std::to_string(id) + ";";
				PGresult* statusRet = PQexec(pg, betStatusSql.c_str());
				PQclear(statusRet);

				float win = amount * odd;
				std::string balanceSql = "UPDATE users SET balance = balance + " + std::to_string(win)
					+ " WHERE id = " + std::to_string(userId) + ";";
				PGresult* balanceRet = PQexec(pg, balanceSql.c_str());
				PQclear(balanceRet);
			}
			else
			{
				std::string betStatusSql = "UPDATE bets SET status = 2 WHERE id = " + std::to_string(id) + ";";
				PGresult* statusRet = PQexec(pg, betStatusSql.c_str());
				PQclear(statusRet);

				if (isSpecial)
				{
					std::string balanceSql = "UPDATE users SET balance = balance + " + std::to_string(oldAmount)
						+ " WHERE id = " + std::to_string(userId) + ";";
					PGresult* balanceRet = PQexec(pg, balanceSql.c_str());
					PQclear(balanceRet);
				}
			}
		}
		else if (team1Goals < team2Goals)
		{
			if (bet == "w2" || bet == "x2" || bet == "x12")
			{
				std::string betStatusSql = "UPDATE bets SET status = 1 WHERE id = " + std::to_string(id) + ";";
				PGresult* statusRet = PQexec(pg, betStatusSql.c_str());
				PQclear(statusRet);

				float win = amount * odd;
				std::string balanceSql = "UPDATE users SET balance = balance + " + std::to_string(win)
					+ " WHERE id = " + std::to_string(userId) + ";";
				PGresult* balanceRet = PQexec(pg, balanceSql.c_str());
				PQclear(balanceRet);
			}
			else
			{
				std::string betStatusSql = "UPDATE bets SET status = 2 WHERE id = " + std::to_string(id) + ";";
				PGresult* statusRet = PQexec(pg, betStatusSql.c_str());
				PQclear(statusRet);

				if (isSpecial)
				{
					std::string balanceSql = "UPDATE users SET balance = balance + " + std::to_string(oldAmount)
						+ " WHERE id = " + std::to_string(userId) + ";";
					PGresult* balanceRet = PQexec(pg, balanceSql.c_str());
					PQclear(balanceRet);
				}
			}
		}
	}

	PQclear(ret);
}

void GetLiveMatches(PGconn* pg)
{
	auto now = std::chrono::system_clock::now();

	// Convert the time point to a duration since the epoch
	auto duration = now.time_since_epoch();

	// Convert the duration to milliseconds
	long long milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();


	std::string sql = "SELECT m.id, m.league, m.week, m.week_type, m.match_date, m.is_special, "
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
		int weekType = atoi(PQgetvalue(ret, i, 3));

		long long matchDate = atoll(PQgetvalue(ret, i, 4));
		int isSpecial = atoll(PQgetvalue(ret, i, 5));

		CronTeam team1;
		team1.Id = atoi(PQgetvalue(ret, i, 6));
		team1.ApiId = atoi(PQgetvalue(ret, i, 7));
		team1.ShortName = PQgetvalue(ret, i, 8); // Retrieve team1 short_name

		CronTeam team2;
		team2.Id = atoi(PQgetvalue(ret, i, 9));
		team2.ApiId = atoi(PQgetvalue(ret, i, 10));
		team2.ShortName = PQgetvalue(ret, i, 11); // Retrieve team2 short_name

		int apiId = atoi(PQgetvalue(ret, i, 12));


		if (apiId == -1 || team1.ApiId == -1 || team2.ApiId == -1)
		{
			apiId = GetApiFootballMatches(pg, ELeague(league), id, team1, team2, league == 20 ? "2024" : "2025", week);
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
			bool hasScore = false;
			rapidjson::Value scoreValue;
			if (document["response"][0].HasMember("score") && document["response"][0]["score"].IsObject())
			{
				scoreValue = document["response"][0]["score"].GetObject();
				hasScore = true;
			}
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
			GetMatchPlayers(pg, id, apiId, 0, 0, 0, 0, false);
			// FillMatchLineups(pg, document, id, matchDate);

			if (status == "FT" || status == "AET" || status == "PEN")
			{
				int team1GoalsAll = team1Goals;
				int team2GoalsAll = team2Goals;
				int team1Goals90 = -1;
				int team2Goals90 = -1;
				int team1GoalsPen = -1;
				int team2GoalsPen = -1;
				if (hasScore)
				{
					if (scoreValue["fulltime"]["home"].IsInt()) 
						team1Goals90 = scoreValue["fulltime"]["home"].GetInt();

					if (scoreValue["fulltime"]["away"].IsInt()) 
						team2Goals90 = scoreValue["fulltime"]["away"].GetInt();

					if (scoreValue.HasMember("penalty")) 
					{
						if (scoreValue["penalty"]["home"].IsInt())
							team1GoalsPen = scoreValue["penalty"]["home"].GetInt();

						if (scoreValue["penalty"]["away"].IsInt())
							team2GoalsPen = scoreValue["penalty"]["away"].GetInt();
					}

				}

				if (status == "FT")
				{
					sql = "update matches set team1_score = " + std::to_string(team1Goals) +
						", team2_score = " + std::to_string(team2Goals) +
						" where id = " + std::to_string(id) + ";";
					updated = PQexec(pg, sql.c_str());
					PQclear(updated);
				}
				else if (status == "AET")
				{
					sql = "update matches set team1_score = " + std::to_string(team1Goals) +
						", team2_score = " + std::to_string(team2Goals) +
						", team1_score_90 = " + std::to_string(team1Goals90) +
						", team2_score_90 = " + std::to_string(team2Goals90) +
						" where id = " + std::to_string(id) + ";";
					updated = PQexec(pg, sql.c_str());
					PQclear(updated);

					team1Goals = team1Goals90;
					team2Goals = team2Goals90;
				}
				else if (status == "PEN")
				{
					sql = "update matches set team1_score = " + std::to_string(team1Goals) +
						", team2_score = " + std::to_string(team2Goals) +
						", team1_score_90 = " + std::to_string(team1Goals90) +
						", team2_score_90 = " + std::to_string(team2Goals90) +
						", team1_score_pen = " + std::to_string(team1GoalsPen) +
						", team2_score_pen = " + std::to_string(team2GoalsPen) +
						" where id = " + std::to_string(id) + ";";
					updated = PQexec(pg, sql.c_str());
					PQclear(updated);

					team1Goals = team1Goals90;
					team2Goals = team2Goals90;
				}

				//if (status == "FT")
				{
					// Update league tables
					if (weekType == 0)
					{
						// Update the league table for both teams
						auto updateLeagueTable = [&](int team, int goalsFor, int goalsAgainst, int points) {
							sql = "UPDATE tables SET "
								"matches_played = matches_played + 1, "
								"goals_f = goals_f + " + std::to_string(goalsFor) + ", "
								"goals_a = goals_a + " + std::to_string(goalsAgainst) + ", "
								"points = points + " + std::to_string(points) + " "
								"WHERE team_id = " + std::to_string(team) + " AND league_id = " + std::to_string(league) + " AND season = '" + "25/26" + "'" + ";";
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
					}

					// Update BeatBet
					// UpdateBeatBetPredicts(pg, id, team1Goals, team2Goals);

					// Update user predics
					ProcessBetResults(pg, id, team1Goals, team2Goals, isSpecial);

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

					std::vector<int> specialPoints;
					bool isQuest = false;
					if (isSpecial)
					{
						std::string sql = "SELECT points, title FROM special_matches where match_id = " + std::to_string(id) + ";";
						PGresult* ret = PQexec(pg, sql.c_str());
						std::string pp = PQgetvalue(ret, 0, 0);
						std::string tt = PQgetvalue(ret, 0, 1);
						isQuest = tt == "quest";
						specialPoints = splitPoints(pp, ':');
						PQclear(ret);
					}

					for (int i = 0; i < nrows; ++i)
					{
						bool localSendPN = sendPN;
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
							points = isSpecial ? specialPoints[0] : 3;
							status = EPredictStatus::ScorePredicted;
						}
						else
						{
							int actualDiff = team1Goals - team2Goals;
							int predictedDiff = t1score - t2score;

							if ((team1Goals > team2Goals && t1score > t2score) ||
								(team1Goals < team2Goals && t1score < t2score) ||
								(team1Goals == team2Goals && t1score == t2score))
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

								//points = isSpecial ? specialPoints[1] : 1;
							//	status = EPredictStatus::WinnerPredicted;

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
								points = isSpecial ? specialPoints[2] : -1;
								status = EPredictStatus::Failed;
								localSendPN = false;
							}
						}

						sql = "UPDATE users SET points = GREATEST(0, points + " + std::to_string(points) + ") WHERE id = " + std::to_string(userId) + ";";
						PGresult* updateRet = PQexec(pg, sql.c_str());
						PQclear(updateRet);

						sql = "UPDATE predicts SET status = " + std::to_string(int(status)) + " WHERE id = " + std::to_string(id) + ";";
						updateRet = PQexec(pg, sql.c_str());
						PQclear(updateRet);

						// Send push notifications
						if (localSendPN)
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

								bool sendRet = PNManager::SendPushNotification(accessToken, token, t, m, "ic_notification");
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

					// Quest remove points
					/*if (isQuest)
					{
						sql =
							"UPDATE users "
							"SET points = GREATEST(0, points - 2) "
							"WHERE id NOT IN (SELECT user_id FROM predicts WHERE match_id = " + std::to_string(id) + ");";
						PGresult* pret = PQexec(pg, sql.c_str());
						PQclear(pret);

						// Insert empty predictions for users who didn't predict the match
						sql =
							"INSERT INTO predicts (user_id, match_id, team1_score, team2_score, status) "
							"SELECT id, " + std::to_string(id) + ", 0, 0, 4 "
							"FROM users "
							"WHERE id NOT IN (SELECT user_id FROM predicts WHERE match_id = " + std::to_string(id) + ");";
						pret = PQexec(pg, sql.c_str());
						PQclear(pret);
					} */

					// Update match players
					GetMatchPlayers(pg, id, apiId, 0, 0, 0, 0, false);
					auto now = std::chrono::system_clock::now();
					auto nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
					/*FinishedMatch fm;
					fm.Timestamp = nowMs;
					fm.MatchApiId = apiId;
					fm.MatchId = id;
					fm.Team1Score = team1GoalsAll;
					fm.Team2Score = team2GoalsAll;
					fm.Team1Id = team1.Id;
					fm.Team2Id = team2.Id;
					finishedMatches.push_back(fm);*/
					{
						std::string sql = "INSERT INTO finished_matches(match_id, match_api_id, team1_score, team2_score, team1, team2, ts) VALUES ("
							+ std::to_string(id) + ", "
							+ std::to_string(apiId) + ", "
							+ std::to_string(team1GoalsAll) + ", "
							+ std::to_string(team2GoalsAll) + ", "
							+ std::to_string(team1.Id) + ", "
							+ std::to_string(team2.Id) + ", "
							+ std::to_string(nowMs) + ");";
						PGresult* pret = PQexec(pg, sql.c_str());
						PQclear(pret);
					}
				}
			}
		}
	}
	PQclear(ret);

}

void DeleteExistingLineups(PGconn* pg, int matchId)
{
	// Delete from lineups_players first (foreign key relationship)
	std::string sqlDeletePlayers = "DELETE FROM lineups_players WHERE lineup IN (SELECT id FROM lineups WHERE match_id = " + std::to_string(matchId) + ");";
	PGresult* retPlayers = PQexec(pg, sqlDeletePlayers.c_str());
	if (PQresultStatus(retPlayers) != PGRES_COMMAND_OK)
	{
		std::cerr << "Error deleting players: " << PQerrorMessage(pg) << std::endl;
	}
	PQclear(retPlayers);

	// Then delete from lineups
	std::string sqlDeleteLineups = "DELETE FROM lineups WHERE match_id = " + std::to_string(matchId) + ";";
	PGresult* retLineups = PQexec(pg, sqlDeleteLineups.c_str());
	if (PQresultStatus(retLineups) != PGRES_COMMAND_OK)
	{
		std::cerr << "Error deleting lineups: " << PQerrorMessage(pg) << std::endl;
	}
	PQclear(retLineups);
}

void FillLineupPlayers(PGconn* pg, int lineupId, rapidjson::Value& lineup, int team)
{
	const rapidjson::Value& start11 = lineup["startXI"].GetArray();
	for (rapidjson::SizeType i = 0; i < start11.Size(); ++i)
	{
		const rapidjson::Value& player = start11[i]["player"];
		int apiId = player["id"].IsNull() ? 0 : player["id"].GetInt();
		int number = player["number"].GetInt();
		std::string name = escapeSingleQuotes(player["name"].GetString());
		std::string pos = escapeSingleQuotes(player["pos"].GetString());
		std::string grid = escapeSingleQuotes(player["grid"].GetString());

		int start11Flag = 1;

		std::string sql = "INSERT INTO lineups_players (lineup, name, number, grid, start11, team, pos, api_id) VALUES (" +
			std::to_string(lineupId) + ", '" +
			name + "', " +
			std::to_string(number) + ", '" +
			grid + "', " +
			std::to_string(start11Flag) + ", " +
			std::to_string(team) + ", '" +
			pos + "', " + 
			std::to_string(apiId) + 
			");";

		PGresult* ret = PQexec(pg, sql.c_str());
		if (PQresultStatus(ret) != PGRES_COMMAND_OK)
		{
			std::cerr << "Error inserting player: " << PQerrorMessage(pg) << std::endl;
		}
		PQclear(ret);
	}

	const rapidjson::Value& subs = lineup["substitutes"].GetArray();
	for (rapidjson::SizeType i = 0; i < subs.Size(); ++i)
	{
		const rapidjson::Value& player = subs[i]["player"];
		int apiId = player["id"].IsNull() ? 0 : player["id"].GetInt();
		int number = player["number"].GetInt();
		std::string grid = "";
		std::string name = escapeSingleQuotes(player["name"].GetString());
		std::string pos = escapeSingleQuotes(player["pos"].GetString());

		int start11Flag = 0;

		std::string sql = "INSERT INTO lineups_players (lineup, name, number, grid, start11, team, pos, api_id) VALUES (" +
			std::to_string(lineupId) + ", '" +
			name + "', " +
			std::to_string(number) + ", '" +
			grid + "', " +
			std::to_string(start11Flag) + ", " +
			std::to_string(team) + ", '" +
			pos + "', " +
			std::to_string(apiId) +
			");";

		PGresult* ret = PQexec(pg, sql.c_str());
		if (PQresultStatus(ret) != PGRES_COMMAND_OK)
		{
			std::cerr << "Error inserting substitute: " << PQerrorMessage(pg) << std::endl;
		}
		PQclear(ret);
	}
}


void GetMatchLineups(PGconn* pg, int apiId, int matchId, long long matchDate)
{
	std::string url = "https://v3.football.api-sports.io/fixtures/lineups?fixture=" + std::to_string(apiId);
	cpr::Response r = cpr::Get(cpr::Url{ url }, cpr::Header{ {"x-apisports-key", apiKey} });

	if (r.status_code == 200)
	{
		rapidjson::Document document;
		document.Parse(r.text.c_str());
		if (!document["response"].Size()) return;

		rapidjson::Value lineup1 = document["response"][0].GetObject();
		rapidjson::Value lineup2 = document["response"][1].GetObject();

		// Delete existing lineups and players for this match
		DeleteExistingLineups(pg, matchId);

		// Extract team1 details
		std::string team1Formation = lineup1["formation"].GetString();
		if (!lineup1["team"].HasMember("colors") || lineup1["team"]["colors"].IsNull()) return;

		std::string team1PlayerColor = lineup1["team"]["colors"]["player"]["primary"].GetString();
		std::string team1PlayerNColor = lineup1["team"]["colors"]["player"]["number"].GetString();
		std::string team1PlayerBColor = lineup1["team"]["colors"]["player"]["border"].GetString();
		std::string team1GKColor = lineup1["team"]["colors"]["goalkeeper"]["primary"].GetString();
		std::string team1GKNColor = lineup1["team"]["colors"]["goalkeeper"]["number"].GetString();
		std::string team1GKBColor = lineup1["team"]["colors"]["goalkeeper"]["border"].GetString();
		std::string coach1 = "";
		int coach1ApiId = -1;
		std::string coach1Photo = "";

		if (!lineup1.HasMember("coach") || lineup1["coach"].IsNull() || !lineup1["coach"].HasMember("name") || lineup1["coach"]["name"].IsNull()) {}
		else 
		{
			coach1ApiId = lineup1["coach"]["id"].GetInt();
			coach1 = lineup1["coach"]["name"].GetString();
			if (!lineup1["coach"]["photo"].IsNull())
			{
				coach1Photo = lineup1["coach"]["photo"].GetString();
			}
		}

		// Extract team2 details
		std::string team2Formation = lineup2["formation"].GetString();
		if (!lineup2["team"].HasMember("colors") || lineup2["team"]["colors"].IsNull()) return;

		std::string team2PlayerColor = lineup2["team"]["colors"]["player"]["primary"].GetString();
		std::string team2PlayerNColor = lineup2["team"]["colors"]["player"]["number"].GetString();
		std::string team2PlayerBColor = lineup2["team"]["colors"]["player"]["border"].GetString();
		std::string team2GKColor = lineup2["team"]["colors"]["goalkeeper"]["primary"].GetString();
		std::string team2GKNColor = lineup2["team"]["colors"]["goalkeeper"]["number"].GetString();
		std::string team2GKBColor = lineup2["team"]["colors"]["goalkeeper"]["border"].GetString();
		
		std::string coach2 = "";
		int coach2ApiId = -1;
		std::string coach2Photo = "";

		if (!lineup2.HasMember("coach") || lineup2["coach"].IsNull() || !lineup2["coach"].HasMember("name") || lineup2["coach"]["name"].IsNull()) {}
		else
		{
			coach2ApiId = lineup2["coach"]["id"].GetInt();
			coach2 = lineup2["coach"]["name"].GetString();
			if (!lineup2["coach"]["photo"].IsNull())
			{
				coach2Photo = lineup2["coach"]["photo"].GetString();
			}
		}
		
		// Insert into lineups table
		std::string sql = "INSERT INTO lineups (match_id, match_date, formation1, player_color1, player_ncolor1, player_bcolor1, "
			"gk_color1, gk_ncolor1, gk_bcolor1, formation2, player_color2, player_ncolor2, player_bcolor2, "
			"gk_color2, gk_ncolor2, gk_bcolor2, coach1, coach2, coach1_photo, coach2_photo, coach1_api_id, coach2_api_id) VALUES (" +
			std::to_string(matchId) + ", " +
			std::to_string(matchDate) + ", '" +
			escapeSingleQuotes(team1Formation) + "', '" +
			escapeSingleQuotes(team1PlayerColor) + "', '" +
			escapeSingleQuotes(team1PlayerNColor) + "', '" +
			escapeSingleQuotes(team1PlayerBColor) + "', '" +
			escapeSingleQuotes(team1GKColor) + "', '" +
			escapeSingleQuotes(team1GKNColor) + "', '" +
			escapeSingleQuotes(team1GKBColor) + "', '" +
			escapeSingleQuotes(team2Formation) + "', '" +
			escapeSingleQuotes(team2PlayerColor) + "', '" +
			escapeSingleQuotes(team2PlayerNColor) + "', '" +
			escapeSingleQuotes(team2PlayerBColor) + "', '" +
			escapeSingleQuotes(team2GKColor) + "', '" +
			escapeSingleQuotes(team2GKNColor) + "', '" +
			escapeSingleQuotes(team2GKBColor) + "', '" +
			escapeSingleQuotes(coach1) + "', '" +
			escapeSingleQuotes(coach2) + "', '" +
			escapeSingleQuotes(coach1Photo) + "', '" +
			escapeSingleQuotes(coach2Photo) + "', " +
			std::to_string(coach1ApiId) + ", " +
			std::to_string(coach2ApiId) +
			") RETURNING id;";

		PGresult* ret = PQexec(pg, sql.c_str());
		if (PQresultStatus(ret) != PGRES_TUPLES_OK)
		{
			std::cerr << "Error executing SQL: " << PQerrorMessage(pg) << std::endl;
			PQclear(ret);
			return;
		}

		// Get the inserted lineup ID
		int lineupId = atoi(PQgetvalue(ret, 0, 0));
		PQclear(ret);

		// Fill players for both lineups
		FillLineupPlayers(pg, lineupId, lineup1, 1);
		FillLineupPlayers(pg, lineupId, lineup2, 2);
	}
}

void GetTodayMatches(PGconn* pg) 
{
	auto now = std::chrono::system_clock::now();
	auto nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
	auto oneHourLaterMs = nowMs + (3600 + 1200) * 1000;  // 3600 seconds = 1 20min hour in milliseconds

	const std::string sql = "SELECT m.id, m.api_id, m.league, m.team1, m.team2, m.week, m.match_date "
		"FROM MATCHES m "
		"WHERE m.match_date >= " + std::to_string(nowMs) +
		" AND m.match_date < " + std::to_string(oneHourLaterMs) + ";";

	PGresult* res = PQexec(pg, sql.c_str());

	if (PQresultStatus(res) != PGRES_TUPLES_OK) 
	{
		std::cerr << "Error executing query: " << PQerrorMessage(pg) << std::endl;
		PQclear(res);
		return;
	}

	int rows = PQntuples(res);
	for (int i = 0; i < rows; i++) 
	{
		std::string id = PQgetvalue(res, i, 0);           // Match ID
		std::string api_id = PQgetvalue(res, i, 1);       // API ID
		std::string league_id = PQgetvalue(res, i, 2);    // League ID
		std::string team1_id = PQgetvalue(res, i, 3);     // Team 1 ID
		std::string team2_id = PQgetvalue(res, i, 4);     // Team 2 ID
		std::string week = PQgetvalue(res, i, 5);
		std::string matchDate = PQgetvalue(res, i, 6);

		CronTeam team1;
		team1.Id = atoi(team1_id.c_str());
		CronTeam team2;
		team2.Id = atoi(team2_id.c_str());

		int apiId = atoi(api_id.c_str());

		if (apiId == -1) 
		{
			apiId = GetApiFootballMatches(pg, ELeague(atoi(league_id.c_str())), atoi(id.c_str()), team1, team2, atoi(league_id.c_str()) == 20 ? "2024" : "2025", atoi(week.c_str()));
		}

		if (apiId > 0) 
		{
			GetMatchLineups(pg, apiId, atoi(id.c_str()), atoll(matchDate.c_str()));
		}
	}

	// Clean up
	PQclear(res);
}

void FillTodayLineups(PGconn* pg)
{
	GetTodayMatches(pg);
	
	//int matchId = 38;
	//long long matchDate = 1726340400000;
	//int apiId = 1208051;
}

void FillLeagueTopScorers(PGconn* pg, ELeague league)
{
	int leagueId = elTorneoLeagueIdToApiFootball(league);
	std::string season = "2025";

	std::string url = "https://v3.football.api-sports.io/players/topscorers";
	cpr::Parameters params = {
		  {"league", std::to_string(leagueId)},
		  {"season", season}
	};

	// Make the request
	cpr::Response r = cpr::Get(cpr::Url{ url },
		params,
		cpr::Header{ {"x-apisports-key", apiKey} });

	if (r.status_code == 200)
	{
		std::string& res = r.text;
		rapidjson::Document d;
		d.Parse(res.c_str());

		rapidjson::Value player = d["response"][0]["player"].GetObject();
		int id = player["id"].GetInt();
		std::string name = player["name"].GetString();

		rapidjson::Value stats = d["response"][0]["statistics"][0].GetObject();
		int teamId = stats["team"]["id"].GetInt();
		int games = stats["games"]["appearences"].GetInt();
		int goals = stats["goals"]["total"].GetInt();
		
		std::string teamName;
		std::string teamShortName;
		int tid;
		{
			std::string sql = "SELECT id, name, short_name from teams where api_id = " + std::to_string(teamId) + ";";
			PGresult* res = PQexec(pg, sql.c_str());
			int rows = PQntuples(res);
			std::string teamid = PQgetvalue(res, 0, 0);     
			tid = atoi(teamid.c_str());
			teamName = PQgetvalue(res, 0, 1);
			teamShortName = PQgetvalue(res, 0, 2);
			PQclear(res);
		}
		int playerId;
		int playerReady = 0;
		{
			std::string sql = "select id from players where api_id = "
				+ std::to_string(id) + " AND team_id = " + std::to_string(tid) + ";";
			PGresult* res = PQexec(pg, sql.c_str());
			int rows = PQntuples(res);

			if (rows <= 0) 
			{
				sql = "insert into players (name, team_id, team_name, team_short_name, api_id) values ('"
					+ name + "', "
					+ std::to_string(tid) + ", '"
					+ teamName + "', '"
					+ teamShortName + "', "
					+ std::to_string(id) 
					+ ") RETURNING id;";

				PQclear(res);
				res = PQexec(pg, sql.c_str());
				playerId = atoi(PQgetvalue(res, 0, 0));
				PQclear(res);
			}
			else 
			{
				playerId = atoi(PQgetvalue(res, 0, 0));
				PQclear(res);
			}
		}

		{
			std::string sql = "delete from top_scorers where league_id = " + std::to_string((int)league) + ";";
			PGresult* res = PQexec(pg, sql.c_str());
			PQclear(res);
		}

		std::string sql = "insert into top_scorers (player_id, league_id, team_id, games, goals) values ("
			+ std::to_string(playerId) + ", "
			+ std::to_string((int)league) + ", "
			+ std::to_string(tid) + ", "
			+ std::to_string(games) + ", "
			+ std::to_string(goals)
			+ ");";

		PGresult* ret = PQexec(pg, sql.c_str());
		PQclear(ret);
	}
}

void FillTopScorers(PGconn* pg)
{
	for (int i = (int)ELeague::PremierLeague; i <= (int)ELeague::Ligue1; ++i) 
	{
		FillLeagueTopScorers(pg, ELeague(i));
	}
}

void GetMatchBets(PGconn* pg, int matchId, int apiId)
{
	std::string url = "https://v3.football.api-sports.io/odds";
	cpr::Response r;
	cpr::Parameters params;
	params = {
		{"fixture", std::to_string(apiId)},
		{"bookmaker", "8"},
		{"bet", "1"}
	};

	float w1, w2, x, x1, x12, x2;

	{
		r = cpr::Get(cpr::Url{ url },
			params,
			cpr::Header{ {"x-apisports-key", apiKey} });

		if (r.status_code == 200)
		{
			// Parse the JSON response
			rapidjson::Document document;
			document.Parse(r.text.c_str());

			if (document.HasMember("response"))
			{
				if (!document["response"].Size() || !document["response"][0].HasMember("bookmakers") /* || !document["response"]["bookmakers"].IsArray()*/) return;
				rapidjson::Value& bets = document["response"][0]["bookmakers"][0]["bets"];
				rapidjson::Value& bet = bets[0];
				if (!bet.HasMember("values") || !bet["values"].IsArray()) return;

				w1 = atof(bet["values"][0]["odd"].GetString());
				x = atof(bet["values"][1]["odd"].GetString());
				w2 = atof(bet["values"][2]["odd"].GetString());
			}
			else return;
		}
		else return;
	}

	params = {
		{"fixture", std::to_string(apiId)},
		{"bookmaker", "8"},
		{"bet", "12"}
	};

	{
		r = cpr::Get(cpr::Url{ url },
			params,
			cpr::Header{ {"x-apisports-key", apiKey} });

		if (r.status_code == 200)
		{
			// Parse the JSON response
			rapidjson::Document document;
			document.Parse(r.text.c_str());

			if (document.HasMember("response"))
			{
				if (!document["response"].Size() || !document["response"][0].HasMember("bookmakers") /* || !document["response"]["bookmakers"].IsArray()*/) return;
				rapidjson::Value& bets = document["response"][0]["bookmakers"][0]["bets"];
				rapidjson::Value& bet = bets[0];
				if (!bet.HasMember("values") || !bet["values"].IsArray()) return;

				x1 = atof(bet["values"][0]["odd"].GetString());
				x12 = atof(bet["values"][1]["odd"].GetString());
				x2 = atof(bet["values"][2]["odd"].GetString());
			}
			else return;
		}
		else return;
	}

	std::string sql = "INSERT INTO odds (match_id, w1, x, w2, x1, x12, x2) VALUES ("
		+ std::to_string(matchId) + ", "
		+ std::to_string(w1) + ", "
		+ std::to_string(x) + ", "
		+ std::to_string(w2) + ", "
		+ std::to_string(x1) + ", "
		+ std::to_string(x12) + ", "
		+ std::to_string(x2) + ") "
		"ON CONFLICT (match_id) DO UPDATE SET "
		"w1 = EXCLUDED.w1, "
		"x = EXCLUDED.x, "
		"w2 = EXCLUDED.w2, "
		"x1 = EXCLUDED.x1, "
		"x12 = EXCLUDED.x12, "
		"x2 = EXCLUDED.x2;";

	PGresult* ret = PQexec(pg, sql.c_str());
	PQclear(ret);

	return;
}

void ProcessMatchesForOdds(PGconn* pg, int lId, int w, PGresult* res)
{
	int rows = PQntuples(res);
	std::string season = lId == 20 ? "2024": "2025";
	for (int i = 0; i < rows; ++i) 
	{
		int id = atoi(PQgetvalue(res, i, 0));
		int team1 = atoi(PQgetvalue(res, i, 1));
		int team2 = atoi(PQgetvalue(res, i, 2));
		long long ts = atoll(PQgetvalue(res, i, 3));
		int apiId = atoi(PQgetvalue(res, i, 4));
		int week = atoi(PQgetvalue(res, i, 5));

		int leagueId = elTorneoLeagueIdToApiFootball(ELeague(lId));
		std::string round = GetApiFootballRound(pg, ELeague(lId), week, team1);
		std::string url = "https://v3.football.api-sports.io/fixtures";

		cpr::Response r;
		cpr::Parameters params;
		if (apiId == -1)
		{
			params = {
				  {"league", std::to_string(leagueId)},
				  {"season", season},
				  {"round", round}
			};
		}
		else
		{
			params = {
				  {"id", std::to_string(apiId)}
			};
		}

		// Make the request
		r = cpr::Get(cpr::Url{ url },
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
						long long date = match["fixture"]["timestamp"].GetInt64() * 1000;
						int newApiId = match["fixture"]["id"].GetInt();
						std::string team1Name = Team::ToString(ETeam(team1));
						std::string team2Name = Team::ToString(ETeam(team2));

						std::string homeTeam = match["teams"]["home"]["name"].GetString();
						std::string awayTeam = match["teams"]["away"]["name"].GetString();

						if (homeTeam == team1Name && awayTeam == team2Name)
						{
							int homeId = match["teams"]["home"]["id"].GetInt();
							int awayId = match["teams"]["away"]["id"].GetInt();

							std::string sql = "update matches set api_id = " + std::to_string(newApiId)
								+ ", match_date = " + std::to_string(date) +
								+" where id = " + std::to_string(id) + ";";
							PGresult* ret = PQexec(pg, sql.c_str());
							PQclear(ret);

							sql = "update teams set api_id = " + std::to_string(homeId) + " where id = " + std::to_string(team1) + ";";
							ret = PQexec(pg, sql.c_str());
							PQclear(ret);

							sql = "update teams set api_id = " + std::to_string(awayId) + " where id = " + std::to_string(team2) + ";";
							ret = PQexec(pg, sql.c_str());
							PQclear(ret);

							GetMatchBets(pg, id, newApiId);
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

		//return;
	}
	PQclear(res);
}

void ProcessLeagueMatches(PGconn* pg, int lId, int week)
{
	std::string sql = "SELECT id, team1, team2, match_date, api_id, week from matches where status = '' and league = " +
		std::to_string(lId) + " AND week = " + std::to_string(week) + " AND season = '25/26';";
	PGresult* res = PQexec(pg, sql.c_str());
	ProcessMatchesForOdds(pg, lId, week, res);
}

void ProcessLeaguePSTMatches(PGconn* pg, int lId, int week) 
{
	std::string sql = "SELECT id, team1, team2, match_date, api_id, week from matches where status = '' and league = " +
		std::to_string(lId) + " AND week < " + std::to_string(week) + " and team1_score = -1 and team2_score = -1;";
	PGresult* res = PQexec(pg, sql.c_str());
	ProcessMatchesForOdds(pg, lId, week, res);
}


void CorrectMatchDates(PGconn* pg)
{
	std::string sql = "SELECT id, current_week, num_weeks from leagues order by id;";
	PGresult* res = PQexec(pg, sql.c_str());
	
	int rows = PQntuples(res);
	for (int i = 0; i < rows; ++i) 
	{
		
		int id = atoi(PQgetvalue(res, i, 0));
		 //if (id != 3) continue;
		int week = atoi(PQgetvalue(res, i, 1));
		int numWeeks = atoi(PQgetvalue(res, i, 2));
		for (int w = week; w <= std::min(week + 3, numWeeks); ++w) 
		{
			ProcessLeagueMatches(pg, id, w);
		}

		ProcessLeaguePSTMatches(pg, id, week);

		//return;
	}
	PQclear(res);
	return;
}

std::string escape_sql_string(const std::string& input) {
	std::string output;
	for (char c : input) {
		if (c == '\'') output += "''";
		else output += c;
	}
	return output;
}

ELeague ApiLeagueToLeagueId(int leagueApiId)
{
	if (leagueApiId == 2) return ELeague::ChampionsLeague; // Champions league
	if (leagueApiId == 3) return ELeague::EuropaLeague; // Europa league
	if (leagueApiId == 848) return ELeague::ConferenceLeague; // Conference league

	if (leagueApiId == 39) return ELeague::PremierLeague; // Premier league
	if (leagueApiId == 135) return ELeague::SerieA; // Serie A
	if (leagueApiId == 140) return ELeague::LaLiga; // LaLiga
	if (leagueApiId == 78) return ELeague::Bundesliga; // Bundesliga
	if (leagueApiId == 61) return ELeague::Ligue1; // Ligue1

	if (leagueApiId == 5) return ELeague::NationsLeague; // Nations League
	if (leagueApiId == 137) return ELeague::CoppaItalia; // Coppa Italia
	if (leagueApiId == 143) return ELeague::CopaDelRey; // CopaDelRey
	if (leagueApiId == 15) return ELeague::ClubWorldCup; // ClubWorldCup
	if (leagueApiId == 32) return ELeague::UEFAWorldClubQualification; // ClubWorldCup

	return ELeague::End;
}

bool IsApiLeagueSupported(int leagueApiId) 
{
	if (leagueApiId == 2) return true; // Champions league
	if (leagueApiId == 3) return true; // Europa league
	if (leagueApiId == 848) return true; // Conference league

	if (leagueApiId == 39) return true; // Premier league
	if (leagueApiId == 135) return true; // Serie A
	if (leagueApiId == 140) return true; // LaLiga
	if (leagueApiId == 78) return true; // Bundesliga
	if (leagueApiId == 61) return true; // Ligue1

	if (leagueApiId == 5) return true; // Nations League
	if (leagueApiId == 137) return true; // Coppa Italia
	if (leagueApiId == 143) return true; // CopaDelRey
	if (leagueApiId == 15) return true; // FIFA Club World Cup
	if (leagueApiId == 32) return true; // FIFA Club World Cup


	return false;
}

void FillPlayerStats(PGconn* pg, int playerApiId, int teamId, int teamApiId, int leagueId)
{
	std::string url = "https://v3.football.api-sports.io/players";
	std::string season = "2025";
	if (leagueId == (int)ELeague::UEFAWorldClubQualification) season = "2024";
	cpr::Response r;
	cpr::Parameters params;
	if (teamApiId == -1)
	{
		return;
	}
	else
	{
		params = {
			{"id", std::to_string(playerApiId)},
			{"season", season},
			{"team", std::to_string(teamApiId)}
		};
	}

	int filterLeagueApiId = elTorneoLeagueIdToApiFootball((ELeague)leagueId);

	r = cpr::Get(cpr::Url{ url },
		params,
		cpr::Header{ {"x-apisports-key", apiKey} });

	if (r.status_code == 200)
	{
		rapidjson::Document document;
		document.Parse(r.text.c_str());

		if (document.HasMember("response") && document["response"].IsArray() && document["response"].Size() > 0)
		{
			const rapidjson::Value& statistics = document["response"][0]["statistics"];
			std::vector<int> processedLeagues;
			for (rapidjson::SizeType i = 0; i < statistics.Size(); i++)
			{
				const auto& stat = statistics[i];
				const auto& league = stat["league"];
				if (league["id"].IsNull()) continue;
				int leagueApiId = league["id"].GetInt();
				if (!IsApiLeagueSupported(leagueApiId)) continue;
				if (filterLeagueApiId != leagueApiId) continue;
				bool br = false;
				for (int pl = 0; pl < processedLeagues.size(); ++pl) 
				{
					if (processedLeagues[pl] == leagueApiId)
					{
						br = true;
						break;
					}
				}
				if (br) break;
				processedLeagues.push_back(leagueApiId);
				const auto& games = stat["games"];
				int appearences = games["appearences"].IsNull() ? 0 : games["appearences"].GetInt();
				std::string rating = games["rating"].IsNull() ? "" : games["rating"].GetString();

				const auto& goals = stat["goals"];
				int numGoals = goals["total"].IsNull() ? 0 : goals["total"].GetInt();
				int numAssists = goals["assists"].IsNull() ? 0 : goals["assists"].GetInt();

				std::string sql = "INSERT INTO player_stats (player_api_id, league_id, league_api_id, team_id, team_api_id, games, rating, goals, assists) VALUES ("
					+ std::to_string(playerApiId) + ", "
					+ std::to_string(int(ApiLeagueToLeagueId(leagueApiId))) + ", "
					+ std::to_string(leagueApiId) + ", "
					+ std::to_string(teamId) + ", "
					+ std::to_string(teamApiId) + ", "
					+ std::to_string(appearences) + ", '"
					+ rating + "', "
					+ std::to_string(numGoals) + ", "
					+ std::to_string(numAssists) + ");";

				PGresult* insertRes = PQexec(pg, sql.c_str());
				if (PQresultStatus(insertRes) != PGRES_COMMAND_OK)
				{
					std::cerr << "Error executing query: " << PQerrorMessage(pg) << std::endl;
					PQclear(insertRes);
					return;
				}
				PQclear(insertRes);
			}
		}
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void FillOneTeamPlayers(PGconn* pg, int teamId, int teamApiId, int leagueId)
{
	std::string sql;
	std::string url = "https://v3.football.api-sports.io/players/squads";

	cpr::Response r;
	cpr::Parameters params;
	if (teamApiId == -1)
	{
		return;
	}
	else
	{
		params = {
			  {"team", std::to_string(teamApiId)}
		};
	}

	r = cpr::Get(cpr::Url{ url },
		params,
		cpr::Header{ {"x-apisports-key", apiKey} });

	if (r.status_code == 200)
	{
		// Parse the JSON response
		rapidjson::Document document;
		document.Parse(r.text.c_str());

		if (document.HasMember("response") && document["response"].IsArray())
		{
			const rapidjson::Value& players = document["response"][0]["players"];
			for (rapidjson::SizeType i = 0; i < players.Size(); i++)
			{
				const auto& player = players[i];
				int playerId = player["id"].GetInt();
				if (playerId == 0 || player["name"].IsNull()) continue;
				std::string name = player["name"].GetString();
				int age = player["age"].IsNull() ? 0 : player["age"].GetInt();
				int number = player["number"].IsNull() ? 0 : player["number"].GetInt();
				std::string pos = player["position"].IsNull() ? "" : player["position"].GetString();
				std::string photo = player["photo"].IsNull() ? "" : player["photo"].GetString();

				std::string sql = "INSERT INTO team_players(api_id, team_id, name, age, number, position, photo) VALUES ("
					+ std::to_string(playerId) + ", "
					+ std::to_string(teamId) + ", '"
					+ escape_sql_string(name) + "', "
					+ std::to_string(age) + ", "
					+ std::to_string(number) + ", '"
					+ escape_sql_string(pos) + "', '"
					+ escape_sql_string(photo) + "');";

				PGresult* insertRes = PQexec(pg, sql.c_str());
				if (PQresultStatus(insertRes) != PGRES_COMMAND_OK)
				{
					std::cerr << "Error executing query: " << PQerrorMessage(pg) << std::endl;
					PQclear(insertRes);
					return;
				}
				PQclear(insertRes);

				FillPlayerStats(pg, playerId, teamId, teamApiId, leagueId);
			}
		}
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}


void FillTeamData(PGconn* pg, int teamId, int teamApiId)
{
	std::string sql;
	std::string url = "https://v3.football.api-sports.io/teams";

	cpr::Response r;
	cpr::Parameters params;
	if (teamApiId == -1)
	{
		return;
	}
	else
	{
		params = {
			  {"id", std::to_string(teamApiId)}
		};
	}

	r = cpr::Get(cpr::Url{ url },
		params,
		cpr::Header{ {"x-apisports-key", apiKey} });

	if (r.status_code == 200)
	{
		// Parse the JSON response
		rapidjson::Document document;
		document.Parse(r.text.c_str());

		if (document.HasMember("response") && document["response"].IsArray())
		{
			const rapidjson::Value& team = document["response"][0]["team"];
			std::string country = team["country"].IsNull() ? "" : team["country"].GetString();
			int national = team["national"].GetBool();

			const rapidjson::Value& venue = document["response"][0]["venue"];
			std::string venueName = venue["name"].GetString();

			sql = "UPDATE teams set country = '" + country + "', national = " + std::to_string(national) + ", venue = '" + escapeSingleQuotes(venueName)
				+ "' where id = " + std::to_string(teamId) + ";";

			PGresult* insertRes = PQexec(pg, sql.c_str());
			PQclear(insertRes);
		}
	}
}

void FillTeamSquad(PGconn* pg)
{
	std::string sql = "SELECT id from leagues;";
	PGresult* res = PQexec(pg, sql.c_str());

	int rows = PQntuples(res);
	if (rows > 0) 
	{
		/* {
			sql = "DROP TABLE team_players;";
			PGresult* res = PQexec(pg, sql.c_str());
			PQclear(res);
		}
		{
			sql = "DROP TABLE player_stats;";
			PGresult* res = PQexec(pg, sql.c_str());
			PQclear(res);
		}
		{
			sql = "CREATE TABLE team_players(id serial primary key not null, team_id integer, name text, age integer, number integer, position text, photo text, api_id integer);";
			PGresult* res = PQexec(pg, sql.c_str());
			PQclear(res);
		}
		{
			sql = "CREATE TABLE player_stats(id serial primary key not null, player_api_id integer, league_id integer, league_api_id integer, team_id integer, team_api_id integer, games integer, rating text, goals integer, assists integer);";
			PGresult* res = PQexec(pg, sql.c_str());
			PQclear(res);
		}*/
	}
	for (int i = 0; i < rows; ++i)
	{
		int leagueId = atoi(PQgetvalue(res, i, 0));
		if (leagueId == (int)ELeague::PremierLeague
			|| leagueId == (int)ELeague::LaLiga
			|| leagueId == (int)ELeague::SerieA
			|| leagueId == (int)ELeague::Bundesliga
			|| leagueId == (int)ELeague::Ligue1)
		{

		}
		else
		{
			continue;
		}

		std::string teamSql =
			"SELECT lt.team_id, t.api_id "
			"FROM leagues_teams lt "
			"JOIN teams t ON t.id = lt.team_id "
			"WHERE lt.league_id = " + std::to_string(leagueId) + ";";
		PGresult* teamRes = PQexec(pg, teamSql.c_str());
		int nTeams = PQntuples(teamRes);
		if (!nTeams) continue;

		for (int t = 0; t < nTeams; ++t)
		{
			int teamId = atoi(PQgetvalue(teamRes, t, 0));
			int teamApiId = atoi(PQgetvalue(teamRes, t, 1));

			{
				std::string deleteSql = "DELETE FROM team_players WHERE team_id = " + std::to_string(teamId) + ";";
				PGresult* deleteRes = PQexec(pg, deleteSql.c_str());
				PQclear(deleteRes);
			}
			{
				std::string deleteSql = "DELETE FROM player_stats WHERE team_id = " + std::to_string(teamId) 
					+ " AND league_id = " + std::to_string(leagueId) + ";";
				PGresult* deleteRes = PQexec(pg, deleteSql.c_str());
				PQclear(deleteRes);
			}

			FillOneTeamPlayers(pg, teamId, teamApiId, leagueId);
			FillTeamData(pg, teamId, teamApiId);
		}
	}

	PQclear(res);
}

void UpdateFireballPredictsForNonPlayedPlayer(PGconn* pg, int matchId)
{
	std::string sql = "SELECT id, user_id FROM fireball_predicts WHERE match_id = " + std::to_string(matchId)
		+ " AND status = 0;";
	PGresult* res = PQexec(pg, sql.c_str());
	int rows = PQntuples(res);
	if (rows == 0)
	{
		PQclear(res);
		return;
	}

	for (int i = 0; i < rows; ++i)
	{
		int predictId = atoi(PQgetvalue(res, i, 0));
		int userId = atoi(PQgetvalue(res, i, 1));

		std::string updatePointsSql =
			"UPDATE fireball_users "
			"SET points = GREATEST(points - 1, 0) "
			"WHERE user_id = " + std::to_string(userId) + ";";
		PGresult* resUpdatePoints = PQexec(pg, updatePointsSql.c_str());
		PQclear(resUpdatePoints);

		std::string updatePredictStatusSql = "UPDATE fireball_predicts SET status = -1 WHERE id = " + std::to_string(predictId) + ";";
		PGresult* updatePredictStatusRes = PQexec(pg, updatePredictStatusSql.c_str());
		PQclear(updatePredictStatusRes);
	}
	PQclear(res);
}

void UpdateCareerForPlayer
(
	PGconn* pg, 
	int matchId,
	int playerApiId, 
	int minutes, 
	int goals, 
	int assists, 
	int yellowCards,
	int redCards,
	int penMissed,
	int penSaved,
	int team1Score,
	int team2Score,
	int team1Id,
	int team2Id
)
{
	std::string sql = "SELECT id, user_id, pos, team, name FROM career_players WHERE api_id = "
		+ std::to_string(playerApiId)
		+ " AND start11 = 1;";
	PGresult* res = PQexec(pg, sql.c_str());
	int rows = PQntuples(res);
	if (rows == 0)
	{
		PQclear(res);
		return;
	}

	for (int i = 0; i < rows; ++i)
	{
		int id = atoi(PQgetvalue(res, i, 0));
		int userId = atoi(PQgetvalue(res, i, 1));
		std::string pos = PQgetvalue(res, i, 2);
		int teamId = atoi(PQgetvalue(res, i, 3));
		std::string playerName = (PQgetvalue(res, i, 4));

		int points = 0;
		int goalsA = 0;
		if (minutes <= 0) 
		{
			// points -= 1;
		}
		else
		{
			if (minutes >= 45) 
			{
				if (pos == "Goalkeeper") points += 2;
				if (pos == "Defender") points += 1;
			}

			if (goals > 0)
			{
				if (pos == "Attacker") points += 3 * goals;
				if (pos == "Midfielder") points += 4 * goals;
				if (pos == "Defender") points += 6 * goals;
				if (pos == "Goalkeeper") points += 10 * goals;
			}
			else
			{
				//if (minutes > 0 && pos == "Attacker") points -= 1;
			}

			if (assists > 0) points += assists;

			if (redCards > 0) points -= 3;
			else if (yellowCards > 0) points -= 1;

			if (pos == "Defender")
			{
				if (teamId == team1Id) 
				{
					goalsA = team2Score;
					points -= team2Score;
				}
				else
				{
					goalsA = team1Score;
					points -= team1Score;
				}
			}

			if (pos == "Goalkeeper")
			{
				if (teamId == team1Id) 
				{
					goalsA = team2Score;
					points -= 2 * team2Score;
				}
				else
				{
					goalsA = team1Score;
					points -= 2 * team1Score;
				}

				if (penSaved > 0) points += penSaved * 3;
			}

			if (pos == "Defender" || pos == "Goalkeeper")
			{
				if (teamId == team1Id && team2Score == 0) points += 3;
				else if (teamId == team2Id && team1Score == 0) points += 3;
			}

			if (penMissed > 0) points -= 3 * penMissed;
		}

		{
			std::string updateSql =
				"UPDATE career_users "
				"SET points = GREATEST(points + " + std::to_string(points) + ", 0) "
				"WHERE user_id = " + std::to_string(userId) + ";";
			PGresult* updateRes = PQexec(pg, updateSql.c_str());
			if (PQresultStatus(updateRes) != PGRES_COMMAND_OK)
			{
				fprintf(stderr, "Update career user failed: %s\n", PQerrorMessage(pg));
			}
			PQclear(updateRes);
		}
		{
			long long nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::system_clock::now().time_since_epoch()
			).count();
			std::string insertSql = "INSERT INTO career_predicts (user_id, match_id, player_api_id, minutes, goals, assists, yellow_cards, red_cards, goals_a, pen_saved, pen_missed, points, player_name, player_pos, ts, team_id) VALUES ("
				+ std::to_string(userId) + ", "
				+ std::to_string(matchId) + ", "
				+ std::to_string(playerApiId) + ", "
				+ std::to_string(minutes) + ", "
				+ std::to_string(goals) + ", "
				+ std::to_string(assists) + ", "
				+ std::to_string(yellowCards) + ", "
				+ std::to_string(redCards) + ", "
				+ std::to_string(goalsA) + ", "
				+ std::to_string(penSaved) + ", "
				+ std::to_string(penMissed) + ", "
				+ std::to_string(points) + ", '"
				+ playerName + "', '"
				+ pos + "', "
				+ std::to_string(nowMs) + ", "
				+ std::to_string(teamId) + ");";

			PGresult* updateRes = PQexec(pg, insertSql.c_str());
			if (PQresultStatus(updateRes) != PGRES_COMMAND_OK)
			{
				fprintf(stderr, "Insert career predict failed: %s\n", PQerrorMessage(pg));
			}
			PQclear(updateRes);
		}
	}
}

void UpdateFireballPredictsForPlayer(PGconn* pg, int matchId, int playerApiId, int minutes, int goals)
{
	std::string sql = "SELECT is_special FROM matches WHERE id = " + std::to_string(matchId) + ";";
	PGresult* res = PQexec(pg, sql.c_str());
	int isSpecial = atoi(PQgetvalue(res, 0, 0));
	PQclear(res);

	sql = "SELECT id, user_id FROM fireball_predicts WHERE match_id = " + std::to_string(matchId)
		+ " AND player_api_id = " + std::to_string(playerApiId) + ";";
	res = PQexec(pg, sql.c_str());
	int rows = PQntuples(res);
	if (rows == 0) 
	{
		PQclear(res);
		return;
	}

	for (int i = 0; i < rows; ++i)
	{
		int predictId = atoi(PQgetvalue(res, i, 0));
		int userId = atoi(PQgetvalue(res, i, 1));

		int points = 0;
		int status = 0;

		if (minutes <= 0) 
		{
			status = -1;  // did not play
			points = isSpecial ? 0 : -1;
		}
		else if (goals == 1) 
		{
			status = 1;
			points = isSpecial ? 4 : 2;
		}
		else if (goals == 2) 
		{
			status = 2;
			points = isSpecial ? 5 : 3;
		}
		else if (goals >= 3) 
		{
			status = 3;
			points = isSpecial ? 8 : 5;
		}
		else 
		{ // goals == 0
			status = 4;
			points = isSpecial ? 0 : -1;
		}

		std::string updatePointsSql =
			"UPDATE fireball_users "
			"SET points = GREATEST(points + " + std::to_string(points) + ", 0) "
			"WHERE user_id = " + std::to_string(userId) + ";";
		PGresult* resUpdatePoints = PQexec(pg, updatePointsSql.c_str());

		PQclear(resUpdatePoints);

		std::string updatePredictStatusSql = "UPDATE fireball_predicts SET status = " + std::to_string(status) +
			", goals = " + std::to_string(goals) + " WHERE id = " + std::to_string(predictId) + ";";
		PGresult* updatePredictStatusRes = PQexec(pg, updatePredictStatusSql.c_str());
		PQclear(updatePredictStatusRes);
	}
	PQclear(res);
}

void GetMatchPlayers(
	PGconn* pg, 
	int matchId, 
	int matchApiId, 
	int team1Score,
	int team2Score,
	int team1Id,
	int team2Id,
	bool updateFireball)
{
	std::string url = "https://v3.football.api-sports.io/fixtures/players";
	cpr::Response r;
	cpr::Parameters params = {
		{"fixture", std::to_string(matchApiId)}
	};

	r = cpr::Get(cpr::Url{ url },
		params,
		cpr::Header{ {"x-apisports-key", apiKey} });

	if (r.status_code == 200)
	{
		// Parse the JSON response
		rapidjson::Document document;
		document.Parse(r.text.c_str());

		if (document.HasMember("response") && document["response"].IsArray() && document["response"].Size())
		{
			for (rapidjson::SizeType teamIndex = 0; teamIndex < document["response"].Size(); teamIndex++)
			{
				const rapidjson::Value& team1 = document["response"][teamIndex];
				const rapidjson::Value& players = team1["players"];
				for (rapidjson::SizeType i = 0; i < players.Size(); i++)
				{
					const rapidjson::Value& player = players[i]["player"];
					int id = player["id"].GetInt();
					std::string name = player["name"].GetString();
					std::string photo = player["photo"].IsNull() ? "" : player["photo"].GetString();

					const rapidjson::Value& statistics = players[i]["statistics"];
					const rapidjson::Value& games = statistics[0]["games"];
					if (games["minutes"].IsNull())
					{
						if (updateFireball) 
						{
							UpdateFireballPredictsForPlayer(pg, matchId, id, 0, 0);
							UpdateCareerForPlayer(pg, matchId, id, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
						}
						continue;
					}
					int minutes = games["minutes"].GetInt();
					int number = games["number"].GetInt();
					std::string position = games["position"].GetString();
					float rating = games["rating"].IsNull() ? 0 : atof(games["rating"].GetString());

					const rapidjson::Value& goals = statistics[0]["goals"];
					int total = goals["total"].IsNull() ? 0 : goals["total"].GetInt();
					int assists = goals["assists"].IsNull() ? 0 : goals["assists"].GetInt();

					const rapidjson::Value& cards = statistics[0]["cards"];
					int yellow = cards["yellow"].GetInt();
					int red = cards["red"].GetInt();

					const rapidjson::Value& penalty = statistics[0]["penalty"];
					int penMissed = penalty["missed"].IsNull() ? 0 : penalty["missed"].GetInt();
					int penSaved = penalty["saved"].IsNull() ? 0 : penalty["saved"].GetInt();

					std::string sql = "insert into match_players "
						"(api_id, match_id, match_api_id, name, photo, number, position, rating, goals, assists, yellow, red, minutes) values (";

					sql += std::to_string(id) + ",";
					sql += std::to_string(matchId) + ",";
					sql += std::to_string(matchApiId) + ",";

					// Escape strings for SQL
					char* escName = PQescapeLiteral(pg, name.c_str(), name.size());
					char* escPhoto = PQescapeLiteral(pg, photo.c_str(), photo.size());
					char* escPosition = PQescapeLiteral(pg, position.c_str(), position.size());

					sql += std::string(escName) + ",";
					sql += std::string(escPhoto) + ",";
					sql += std::to_string(number) + ",";
					sql += std::string(escPosition) + ",";
					sql += std::to_string(rating) + ",";
					sql += std::to_string(total) + ",";
					sql += std::to_string(assists) + ",";
					sql += std::to_string(yellow) + ",";
					sql += std::to_string(red) + ",";
					sql += std::to_string(minutes) + ") ";

					sql += "ON CONFLICT (api_id, match_id) DO UPDATE SET "
						"match_api_id = EXCLUDED.match_api_id, "
						"name = EXCLUDED.name, "
						"photo = EXCLUDED.photo, "
						"number = EXCLUDED.number, "
						"position = EXCLUDED.position, "
						"rating = EXCLUDED.rating, "
						"goals = EXCLUDED.goals, "
						"assists = EXCLUDED.assists, "
						"yellow = EXCLUDED.yellow, "
						"red = EXCLUDED.red, "
						"minutes = EXCLUDED.minutes";

					PQfreemem(escName);
					PQfreemem(escPhoto);
					PQfreemem(escPosition);

					PGresult* insertRes = PQexec(pg, sql.c_str());
					if (PQresultStatus(insertRes) != PGRES_COMMAND_OK) 
					{
						fprintf(stderr, "Insert failed: %s\n", PQerrorMessage(pg));
					}
					PQclear(insertRes);
					if (updateFireball)
					{
						UpdateFireballPredictsForPlayer(pg, matchId, id, minutes, total);
						UpdateCareerForPlayer(pg, matchId, id, minutes, total, assists, yellow, red, penMissed, penSaved, team1Score, team2Score, team1Id, team2Id);
					}
				}
			}

			if (updateFireball)
			{
				UpdateFireballPredictsForNonPlayedPlayer(pg, matchId);
			}
		}
	}
}

void ProcessFinishedMatches(PGconn* pg)
{
	long long nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();
	long long cutoff = nowMs - 5 * 60 * 1000;

	std::string sql =
		"SELECT * FROM finished_matches "
		"WHERE status = 0 "
		"AND ts <= " + std::to_string(cutoff) + ";";
	PGresult* res = PQexec(pg, sql.c_str());
	int rows = PQntuples(res);
	for (int i = 0; i < rows; ++i) 
	{
		int id = atoi(PQgetvalue(res, i, 0));
		int matchId = atoi(PQgetvalue(res, i, 1));
		int matchApiId = atoi(PQgetvalue(res, i, 2));
		int team1Score = atoi(PQgetvalue(res, i, 3));
		int team2Score = atoi(PQgetvalue(res, i, 4));
		int team1 = atoi(PQgetvalue(res, i, 5));
		int team2 = atoi(PQgetvalue(res, i, 6));

		GetMatchPlayers
		(
			pg,
			matchId,
			matchApiId,
			team1Score,
			team2Score,
			team1,
			team2,
			true
		);

		{
			std::string sql = "DELETE FROM finished_matches WHERE id = " + std::to_string(id) + ";";
			PGresult* res = PQexec(pg, sql.c_str());
			PQclear(res);
		}
	}
	PQclear(res);
}

int main()
{

	PGconn* pg = ConnectionPool::Get()->getConnection();
	//FillTodayLineups(pg);
    //GetMatchPlayers(pg, 3966, 1451024, 2, 1, 35, 86, true);
	//FillTeamSquad(pg);
	//printf("\nDONE...\n");
	//return 0;
	// Get current time
	auto lastFillTime = std::chrono::system_clock::now();
	auto lastTopScorersFillTime = lastFillTime;

	// Run FillTopScorers at the start
	//FillTopScorers(pg);

	auto getCurrentDate = []() {
		std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::tm tm = *std::localtime(&t);
		char buffer[11]; // "YYYY-MM-DD\0" -> 11 characters
		std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tm);
		return std::string(buffer);
	};

	std::string lastCorrectMatchDatesDate;
	CorrectMatchDates(pg);
	lastCorrectMatchDatesDate = getCurrentDate();

	while (true)
	{
		GetLiveMatches(pg);

		// Get the current time
		auto now = std::chrono::system_clock::now();
		auto nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
		ProcessFinishedMatches(pg);

		// Check if 5 minutes have passed to fill today's lineups
		if (std::chrono::duration_cast<std::chrono::minutes>(now - lastFillTime).count() >= 5)
		{
			FillTodayLineups(pg);
			lastFillTime = now;  // Update the last fill time
		}

		// Check if 6 hours have passed to fill top scorers again
		/*if (std::chrono::duration_cast<std::chrono::hours>(now - lastTopScorersFillTime).count() >= 6)
		{
			FillTopScorers(pg);
			lastTopScorersFillTime = now;  // Update the last fill time for top scorers
		}*/

		// Check if it's a new day to run CorrectMatchDates
		std::string currentDate = getCurrentDate();
		if (currentDate != lastCorrectMatchDatesDate)
		{
			CorrectMatchDates(pg);
			lastCorrectMatchDatesDate = currentDate; // Update the last execution date
		}

		// Sleep for 1 minute
		std::this_thread::sleep_for(std::chrono::seconds(30));
	}

	return 0;
}