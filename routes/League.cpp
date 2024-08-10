#include "League.h"

std::string League::ToString(ELeague league)
{
    switch (league)
    {
    case ELeague::ChampionsLeague:
        return "Champions League";
    case ELeague::PremierLeague:
        break;
    case ELeague::LaLiga:
        break;
    case ELeague::SerieA:
        break;
    case ELeague::Bundesliga:
        break;
    case ELeague::Ligue1:
        break;
    default:
        break;
    }
}