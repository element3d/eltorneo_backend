#pragma once

#include "PQManager.h"

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

enum class ETeamMatch
{
	Finished,
	Live,
	Upcoming
};

class MatchesManager 
{
public:
	static bool GetLeagueMatchesWithPredicts(PGconn* pg, 
		int userId, 
		int lid, 
		const std::string& season, 
		const std::string& week,
		const std::string& lang,
		rapidjson::Document& document);

	static bool GetLeagueMatchesWithBets(PGconn* pg,
		int userId,
		int lid,
		const std::string& season,
		const std::string& week,
		const std::string& lang,
		rapidjson::Document& document);

	// Matches by date (Calendar page)
	static bool GetMatchesByDateWithPredicts(PGconn* pg,
		int userId,
		long long dayStart,
		long long dayEnd,
		const std::string& lang,
		rapidjson::Document& document);

	static bool GetMatchesByDateWithBets(PGconn* pg,
		int userId,
		long long dayStart,
		long long dayEnd,
		const std::string& lang,
		rapidjson::Document& document);

	static bool GetMatchesByDateWithFireball(PGconn* pg,
		int userId,
		long long dayStart,
		long long dayEnd,
		const std::string& lang,
		rapidjson::Document& document);

	// Matches live (Live page)
	static bool GetMatchesLiveWithPredicts(PGconn* pg,
		int userId,
		long long currentTimeMs,
		rapidjson::Document& document);

	static bool GetMatchesLiveWithBets(PGconn* pg,
		int userId,
		long long currentTimeMs,
		rapidjson::Document& document);

	// Matches upcoming (Live page)
	static bool GetMatchesUpcomingWithPredicts(PGconn* pg,
		int userId,
		long long currentTimeMs,
		rapidjson::Document& document);

	static bool GetMatchesUpcomingWithBets(PGconn* pg,
		int userId,
		long long currentTimeMs,
		rapidjson::Document& document);

	// Matches team (H2H page)
	static bool GetMatchesTeamWithPredicts(PGconn* pg,
		int userId,
		long tid,
		rapidjson::Document& document);

	static bool GetMatchesTeamWithBets(PGconn* pg,
		int userId,
		long tid,
		rapidjson::Document& document);

	// Matches team (Team page)
	static bool FillTeamMatchesWithPredicts(PGconn* pg,
		int userId,
		int tid,
		rapidjson::Value& document,
		rapidjson::Document::AllocatorType& allocator,
		ETeamMatch eMatch);

	static bool FillTeamMatchesWithBets(PGconn* pg,
		int userId,
		int tid,
		rapidjson::Value& document,
		rapidjson::Document::AllocatorType& allocator,
		ETeamMatch eMatch);
};