#pragma once
#include "League.h"
#include "Team.h"
#include "../managers/PQManager.h"

enum class EWeekType 
{
    Matchday,
    RoundOf16,
    QuarterFinal,
    SemiFinal,
    Final
};

class Match
{
public:
    ELeague League;
    std::string Season;
    int Week;
    ETeam Team1;
    ETeam Team2;
    long long Date;
    EWeekType WeekType = EWeekType::Matchday;
};  

class MatchesInitializer 
{
public:
    static void InitPremierLeagueTeams24_25(PGconn* pg);
    static void InitPremierLeagueTable(PGconn* pg);
    static void FillPremierLeagueTable(PGconn* pg);

    static void InitLaLigaTeams24_25(PGconn* pg);
    static void InitLaLigaTable(PGconn* pg);
    static void FillLaLigaTable(PGconn* pg);

    static void InitSerieATeams24_25(PGconn* pg);
    static void InitSeriaATable(PGconn* pg);
    static void FillSeriaATable(PGconn* pg);

    static void InitBundesligaTeams24_25(PGconn* pg);
    static void InitBundesligaTable(PGconn* pg);
    static void FillBundesligaTable(PGconn* pg);

    static void InitLigue1Teams24_25(PGconn* pg);
    static void InitLigue1Table(PGconn* pg);
    static void FillLigue1Table(PGconn* pg);

    static void InitLigue124_25(PGconn* pg);
    static void InitBundesliga24_25(PGconn* pg);
    static void InitSerieA24_25(PGconn* pg);
	static void InitPremierLeague24_25(PGconn* pg);
    static void InitLaLiga24_25(PGconn* pg);

};