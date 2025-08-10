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
    Final,
    RoundOf8,
    ThirdPlace
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
    static void InitClubWorldCupTeams24_25(PGconn* pg);
    static void InitClubWorldCupTable24_25(PGconn* pg);
    static void InitClubWorldCup24_25(PGconn* pg);
    static void InitClubWorldCupPO24_25(PGconn* pg);

    static void InitChampionsLeagueTeams24_25(PGconn* pg);
    static void InitChampionsLeagueTable(PGconn* pg);

    static void InitPremierLeagueTeams25_26(PGconn* pg);
    static void InitPremierLeagueTable(PGconn* pg);
    static void FillPremierLeagueTable(PGconn* pg);

    static void InitLaLigaTeams25_26(PGconn* pg);
    static void InitLaLigaTable(PGconn* pg);
    static void FillLaLigaTable(PGconn* pg);

    static void InitSerieATeams25_26(PGconn* pg);
    static void InitSeriaATable(PGconn* pg);
    static void FillSeriaATable(PGconn* pg);

    static void InitBundesligaTeams25_26(PGconn* pg);
    static void InitBundesligaTable(PGconn* pg);
    static void FillBundesligaTable(PGconn* pg);

    static void InitLigue1Teams25_26(PGconn* pg);
    static void InitLigue1Table(PGconn* pg);
    static void FillLigue1Table(PGconn* pg);

    static void InitChampionsLeague24_25(PGconn* pg);
    static void InitChampionsLeaguePO24_25(PGconn* pg);

    static void InitLigue125_26(PGconn* pg);
    static void InitBundesliga25_26(PGconn* pg);
    static void InitSerieA25_26(PGconn* pg);
    static void InitPremierLeague25_26(PGconn* pg);
    static void InitLaLiga25_26(PGconn* pg);

    static void InitCopaDelReyTeams24_25(PGconn* pg);
    static void InitCopaDelRey24_25(PGconn* pg);

    static void InitCoppaItaliaTeams24_25(PGconn* pg);
    static void InitCoppaItalia24_25(PGconn* pg);

    static void InitSuperCupItaliaTeams24_25(PGconn* pg);
    static void InitSuperCupItalia24_25(PGconn* pg);

    static void InitSuperCupFranceTeams24_25(PGconn* pg);
    static void InitSuperCupFrance24_25(PGconn* pg);

    static void InitSuperCupSpainTeams24_25(PGconn* pg);
    static void InitSuperCupSpain24_25(PGconn* pg);

    static void InitEFLCupTeams24_25(PGconn* pg);
    static void InitEFLCup24_25(PGconn* pg);

    static void InitNationsLeagueTeams24_25(PGconn* pg);
    static void InitNationsLeague24_25(PGconn* pg);
    static void InitNationsLeaguePO24_25(PGconn* pg);

    static void InitUEFASuperCupTeams25_26(PGconn* pg);
    static void InitUEFASuperCup25_26(PGconn* pg);

    static void FillAwards(PGconn* pg);
};