#pragma once

#include <string>

enum class ELeague
{
    ChampionsLeague = 1,
    PremierLeague,
    LaLiga,
    SerieA,
    Bundesliga,
    Ligue1,
    NationsLeague,
    CoppaItalia,
    SuperCupItalia,
    SuperCupFrance,
    SuperCupSpain,
    EFLCup,
    CopaDelRey,
    EuropaLeague,
    ConferenceLeague,
    ClubWorldCup,
    CommunityShield,
    UEFASuperCup,
    DFLSuperCup,
    UEFAWorldClubQualification,
    DFBPokal,
    End = UEFAWorldClubQualification
};

enum class ELeagueType 
{
    StandartLeague,
    KnockOutLeague
};

enum class ELeagueStatus 
{
    NotReady,
    Ready
};

class League
{
public:
    static std::string ToString(ELeague league);
};
