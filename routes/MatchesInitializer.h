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
    bool PlayOff = false;
};  

class MatchesInitializer 
{
public:
    static void InitChampionsLeagueTeams24_25(PGconn* pg);
    static void InitChampionsLeagueTable(PGconn* pg);


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

    static void InitChampionsLeague24_25(PGconn* pg);
    static void InitLigue124_25(PGconn* pg);
    static void InitBundesliga24_25(PGconn* pg);
    static void InitSerieA24_25(PGconn* pg);
	static void InitPremierLeague24_25(PGconn* pg);
    static void InitLaLiga24_25(PGconn* pg);

    static void InitCoppaItaliaTeams24_25(PGconn* pg);
    static void InitCoppaItalia24_25(PGconn* pg);

    static void InitSuperCupItaliaTeams24_25(PGconn* pg);
    static void InitSuperCupItalia24_25(PGconn* pg);

    static void InitSuperCupFranceTeams24_25(PGconn* pg);
    static void InitSuperCupFrance24_25(PGconn* pg);

    static void InitNationsLeagueTeams24_25(PGconn* pg);
    static void InitNationsLeague24_25(PGconn* pg);


};