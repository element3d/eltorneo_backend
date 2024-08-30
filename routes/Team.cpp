#include "Team.h"

std::string Team::ToString(ETeam team)
{
    switch (team)
    {
    case ETeam::AFCBournemouth:
        return "Bournemouth";
    case ETeam::Arsenal:
        return "Arsenal";
    case ETeam::AstonVilla:
        return "Aston Villa";
    case ETeam::Brentford:
        return "Brentford";
    case ETeam::BrightonAndHoveAlbion:
        return "Brighton";
    case ETeam::Chelsea:
        return "Chelsea";
    case ETeam::CrystalPalace:
        return "Crystal Palace";
    case ETeam::Everton:
        return "Everton";
    case ETeam::Fulham:
        return "Fulham";
    case ETeam::IpswichTown:
        return "Ipswich";
    case ETeam::LeicesterCity:
        return "Leicester";
    case ETeam::Liverpool:
        return "Liverpool";
    case ETeam::ManchesterCity:
        return "Manchester City";
    case ETeam::ManchesterUnited:
        return "Manchester United";
    case ETeam::NewcastleUnited:
        return "Newcastle";
    case ETeam::NottinghamForest:
        return "Nottingham Forest";
    case ETeam::Southampton:
        return "Southampton";
    case ETeam::TottenhamHotspur:
        return "Tottenham";
    case ETeam::WestHamUnited:
        return "West Ham";
    case ETeam::Wolverhampton:
        return "Wolves";

        //LaLiga
    case ETeam::Alaves:
        return "Alaves";
    case ETeam::AthleticClub:
        return "Athletic Club";
    case ETeam::AtleticoMadrid:
        return "Atletico Madrid";
    case ETeam::Barcelona:
        return "Barcelona";
    case ETeam::CeltaVigo:
        return "Celta Vigo";
    case ETeam::Espanyol:
        return "Espanyol";
    case ETeam::Getafe:
        return "Getafe";
    case ETeam::Girona:
        return "Girona";
    case ETeam::LasPalmas:
        return "Las Palmas";
    case ETeam::Leganes:
        return "Leganes";
    case ETeam::Mallorca:
        return "Mallorca";
    case ETeam::Osasuna:
        return "Osasuna";
    case ETeam::RayoVallecano:
        return "Rayo Vallecano";
    case ETeam::RealBetis:
        return "Real Betis";
    case ETeam::RealMadrid:
        return "Real Madrid";
    case ETeam::RealSociedad:
        return "Real Sociedad";
    case ETeam::RealValladolid:
        return "Valladolid";
    case ETeam::Sevilla:
        return "Sevilla";
    case ETeam::Valencia:
        return "Valencia";
    case ETeam::Villarreal:
        return "Villarreal";

        // Serie A
    case ETeam::ACMilan:
        return "AC Milan";
    case ETeam::Atalanta:
        return "Atalanta";
    case ETeam::Bologna:
        return "Bologna";
    case ETeam::Cagliari:
        return "Cagliari";
    case ETeam::Como:
        return "Como";
    case ETeam::Empoli:
        return "Empoli";
    case ETeam::Fiorentina:
        return "Fiorentina";
    case ETeam::Genoa:
        return "Genoa";
    case ETeam::InterMilan:
        return "Inter";
    case ETeam::Juventus:
        return "Juventus";
    case ETeam::Lazio:
        return "Lazio";
    case ETeam::Lecce:
        return "Lecce";
    case ETeam::Monza:
        return "Monza";
    case ETeam::Napoli:
        return "Napoli";
    case ETeam::Parma:
        return "Parma";
    case ETeam::Roma:
        return "AS Roma";
    case ETeam::Torino:
        return "Torino";
    case ETeam::Udinese:
        return "Udinese";
    case ETeam::Venezia:
        return "Venezia";
    case ETeam::Verona:
        return "Verona";

        // Bundesliga
    case ETeam::Augsburg:
        return "FC Augsburg";
    case ETeam::BayerLeverkusen:
        return "Bayer Leverkusen";
    case ETeam::BayernMunich:
        return "Bayern München";
    case ETeam::Bochum:
        return "VfL Bochum";
    case ETeam::BorussiaDortmund:
        return "Borussia Dortmund";
    case ETeam::BorussiaMgladbach:
        return "Borussia Mönchengladbach";
    case ETeam::EintrachtFrankfurt:
        return "Eintracht Frankfurt";
    case ETeam::Freiburg:
        return "SC Freiburg";
    case ETeam::Heidenheim:
        return "1. FC Heidenheim";
    case ETeam::Hoffenheim:
        return "1899 Hoffenheim";
    case ETeam::HolsteinKiel:
        return "Holstein Kiel";
    case ETeam::Mainz:
        return "FSV Mainz 05";
    case ETeam::RBLeipzig:
        return "RB Leipzig";
    case ETeam::StPauli:
        return "FC St. Pauli";
    case ETeam::Stuttgart:
        return "VfB Stuttgart";
    case ETeam::UnionBerlin:
        return "Union Berlin";
    case ETeam::WerderBremen:
        return "Werder Bremen";
    case ETeam::Wolfsburg:
        return "VfL Wolfsburg";

    // Ligue1
    case ETeam::Angers:
        return "Angers";
    case ETeam::Auxerre:
        return "Auxerre";
    case ETeam::Brest:
        return "Stade Brestois 29";
    case ETeam::LeHavre:
        return "LE Havre";
    case ETeam::Lens:
        return "Lens";
    case ETeam::Lille:
        return "Lille";
    case ETeam::Lyon:
        return "Lyon";
    case ETeam::Marseille:
        return "Marseille";
    case ETeam::Monaco:
        return "Monaco";
    case ETeam::Montpellier:
        return "Montpellier";
    case ETeam::Nantes:
        return "Nantes";
    case ETeam::Nice:
        return "Nice";
    case ETeam::PSG:
        return "Paris Saint Germain";
    case ETeam::Reims:
        return "Reims";
    case ETeam::Rennes:
        return "Rennes";
    case ETeam::SaintEtienne:
        return "Saint Etienne";
    case ETeam::Strasbourg:
        return "Strasbourg";
    case ETeam::Toulouse:
        return "Toulouse";

        // 
    case ETeam::Benfica:
        return "Benfica";
    case ETeam::Celtic:
        return "Celtic";
    case ETeam::ClubBrugge:
        return "Club Brugge KV";
    case ETeam::DinamoZagreb:
        return "Dinamo Zagreb";
    case ETeam::FKCrvenaZvezda:
        return "FK Crvena Zvezda";
    case ETeam::Feyenoord:
        return "Feyenoord";
    case ETeam::PSV:
        return "PSV Eindhoven";
    case ETeam::Salzburg:
        return "Red Bull Salzburg";
    case ETeam::ShakhtarDonetsk:
        return "Shakhtar Donetsk";
    case ETeam::SlovanBratislava:
        return "Slovan Bratislava";
    case ETeam::SpartaPrague:
        return "Sparta Praha";
    case ETeam::SportingLisbon:
        return "Sporting CP";
    case ETeam::SturmGraz:
        return "Sturm Graz";
    case ETeam::YoungBoys:
        return "BSC Young Boys";

    default:
        return "Unknown Team";
    }
}

std::string Team::ToShortString(ETeam team)
{
    switch (team)
    {
    case ETeam::AFCBournemouth:
        return "Bournemouth";
    case ETeam::Arsenal:
        return "Arsenal";
    case ETeam::AstonVilla:
        return "Aston Villa";
    case ETeam::Brentford:
        return "Brentford";
    case ETeam::BrightonAndHoveAlbion:
        return "Brighton";
    case ETeam::Chelsea:
        return "Chelsea";
    case ETeam::CrystalPalace:
        return "Crystal P.";
    case ETeam::Everton:
        return "Everton";
    case ETeam::Fulham:
        return "Fulham";
    case ETeam::IpswichTown:
        return "Ipswich";
    case ETeam::LeicesterCity:
        return "Leicester";
    case ETeam::Liverpool:
        return "Liverpool";
    case ETeam::ManchesterCity:
        return "Man City";
    case ETeam::ManchesterUnited:
        return "Man United";
    case ETeam::NewcastleUnited:
        return "Newcastle";
    case ETeam::NottinghamForest:
        return "N. Forest";
    case ETeam::Southampton:
        return "Southampton";
    case ETeam::TottenhamHotspur:
        return "Tottenham";
    case ETeam::WestHamUnited:
        return "West Ham";
    case ETeam::Wolverhampton:
        return "Wolves";

        //LaLiga
    case ETeam::Alaves:
        return "Alaves";
    case ETeam::AthleticClub:
        return "Ath. Bilbao";
    case ETeam::AtleticoMadrid:
        return "Atletico M.";
    case ETeam::Barcelona:
        return "Barcelona";
    case ETeam::CeltaVigo:
        return "Celta";
    case ETeam::Espanyol:
        return "Espanyol";
    case ETeam::Getafe:
        return "Getafe";
    case ETeam::Girona:
        return "Girona";
    case ETeam::LasPalmas:
        return "Las Palmas";
    case ETeam::Leganes:
        return "Leganes";
    case ETeam::Mallorca:
        return "Mallorca";
    case ETeam::Osasuna:
        return "Osasuna";
    case ETeam::RayoVallecano:
        return "Rayo V.";
    case ETeam::RealBetis:
        return "Betis";
    case ETeam::RealMadrid:
        return "Real Madrid";
    case ETeam::RealSociedad:
        return "Real Soc.";
    case ETeam::RealValladolid:
        return "Valladolid";
    case ETeam::Sevilla:
        return "Sevilla";
    case ETeam::Valencia:
        return "Valencia";
    case ETeam::Villarreal:
        return "Villarreal";

        // Serie A
    case ETeam::ACMilan:
        return "Milan";
    case ETeam::Atalanta:
        return "Atalanta";
    case ETeam::Bologna:
        return "Bologna";
    case ETeam::Cagliari:
        return "Cagliari";
    case ETeam::Como:
        return "Como";
    case ETeam::Empoli:
        return "Empoli";
    case ETeam::Fiorentina:
        return "Fiorentina";
    case ETeam::Genoa:
        return "Genoa";
    case ETeam::InterMilan:
        return "Inter";
    case ETeam::Juventus:
        return "Juventus";
    case ETeam::Lazio:
        return "Lazio";
    case ETeam::Lecce:
        return "Lecce";
    case ETeam::Monza:
        return "Monza";
    case ETeam::Napoli:
        return "Napoli";
    case ETeam::Parma:
        return "Parma";
    case ETeam::Roma:
        return "Roma";
    case ETeam::Torino:
        return "Torino";
    case ETeam::Udinese:
        return "Udinese";
    case ETeam::Venezia:
        return "Venezia";
    case ETeam::Verona:
        return "Verona";

    // Bundesliga
    case ETeam::Augsburg:
        return "Augsburg";
    case ETeam::BayerLeverkusen:
        return "Bayer Lev.";
    case ETeam::BayernMunich:
        return "Bayern Mun.";
    case ETeam::Bochum:
        return "Bochum";
    case ETeam::BorussiaDortmund:
        return "Borussia D.";
    case ETeam::BorussiaMgladbach:
        return "Borussia M.";
    case ETeam::EintrachtFrankfurt:
        return "Eintracht F.";
    case ETeam::Freiburg:
        return "Freiburg";
    case ETeam::Heidenheim:
        return "Heidenheim";
    case ETeam::Hoffenheim:
        return "Hoffenheim";
    case ETeam::HolsteinKiel:
        return "Holstein Kiel";
    case ETeam::Mainz:
        return "Mainz";
    case ETeam::RBLeipzig:
        return "RB Leipzig";
    case ETeam::StPauli:
        return "St. Pauli";
    case ETeam::Stuttgart:
        return "Stuttgart";
    case ETeam::UnionBerlin:
        return "Union Berlin";
    case ETeam::WerderBremen:
        return "Werder";
    case ETeam::Wolfsburg:
        return "Wolfsburg";

    // Ligue1
    case ETeam::Angers:
        return "Angers";
    case ETeam::Auxerre:
        return "Auxerre";
    case ETeam::Brest:
        return "Brest";
    case ETeam::LeHavre:
        return "Le Havre";
    case ETeam::Lens:
        return "Lens";
    case ETeam::Lille:
        return "Lille";
    case ETeam::Lyon:
        return "Lyon";
    case ETeam::Marseille:
        return "Marseille";
    case ETeam::Monaco:
        return "Monaco";
    case ETeam::Montpellier:
        return "Montpellier";
    case ETeam::Nantes:
        return "Nantes";
    case ETeam::Nice:
        return "Nice";
    case ETeam::PSG:
        return "PSG";
    case ETeam::Reims:
        return "Reims";
    case ETeam::Rennes:
        return "Rennes";
    case ETeam::SaintEtienne:
        return "Saint-Etienne";
    case ETeam::Strasbourg:
        return "Strasbourg";
    case ETeam::Toulouse:
        return "Toulouse";

    // 
    case ETeam::Benfica:
        return "Benfica";
    case ETeam::Celtic:
        return "Celtic";
    case ETeam::ClubBrugge:
        return "Club Brugge";
    case ETeam::DinamoZagreb:
        return "Dinamo Zagreb";
    case ETeam::FKCrvenaZvezda:
        return "Crvena Zvezda";
    case ETeam::Feyenoord:
        return "Feyenoord";
    case ETeam::PSV:
        return "PSV";
    case ETeam::Salzburg:
        return "Salzburg";
    case ETeam::ShakhtarDonetsk:
        return "Shakhtar D.";
    case ETeam::SlovanBratislava:
        return "Slovan B.";
    case ETeam::SpartaPrague:
        return "Sparta Praha";
    case ETeam::SportingLisbon:
        return "Sporting CP";
    case ETeam::SturmGraz:
        return "Sturm Graz";
    case ETeam::YoungBoys:
        return "Young Boys";

    default:
        return "Unknown Team";
    }
}