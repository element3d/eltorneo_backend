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
    End = Ligue1
};

class League
{
public:
    static std::string ToString(ELeague league);
};
