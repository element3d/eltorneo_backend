#pragma once

#include <string>

enum class EPredictStatus
{
    Pending,
    WinnerPredicted,
    ScorePredicted,
    Failed
};

enum class ETeam
{
    PremierLeagueStart = 1,
    AFCBournemouth = 1,
    Arsenal,
    AstonVilla,
    Brentford,
    BrightonAndHoveAlbion,
    Chelsea,
    CrystalPalace,
    Everton,
    Fulham,
    IpswichTown,
    LeicesterCity,
    Liverpool,
    ManchesterCity,
    ManchesterUnited,
    NewcastleUnited,
    NottinghamForest,
    Southampton,
    TottenhamHotspur,
    WestHamUnited,
    Wolverhampton,
    PremierLeagueEnd = Wolverhampton,

    LaLigaStart = PremierLeagueEnd + 1,
    Alaves = LaLigaStart,
    AthleticClub,
    AtleticoMadrid,
    Barcelona,
    CeltaVigo,
    Espanyol,
    Getafe,
    Girona,
    LasPalmas,
    Leganes,
    Mallorca,
    Osasuna,
    RayoVallecano,
    RealBetis,
    RealMadrid,
    RealSociedad,
    RealValladolid,
    Sevilla,
    Valencia,
    Villarreal,
    LaLigaEnd = Villarreal,

    // SerieA
    SerieAStart = LaLigaEnd + 1,
    ACMilan = SerieAStart,
    Atalanta,
    Bologna,
    Cagliari,
    Como,
    Empoli,
    Fiorentina,
    Genoa,
    InterMilan,
    Juventus,
    Lazio,
    Lecce,
    Monza,
    Napoli,
    Parma,
    Roma,
    Torino,
    Udinese,
    Venezia,
    Verona,
    SerieAEnd = Verona,

    BundesligaStart = SerieAEnd + 1,
    Augsburg = BundesligaStart,
    BayerLeverkusen,
    BayernMunich,
    Bochum,
    BorussiaDortmund,
    BorussiaMgladbach,
    EintrachtFrankfurt,
    Freiburg,
    Heidenheim,
    Hoffenheim,
    HolsteinKiel,
    Mainz,
    RBLeipzig,
    StPauli,
    Stuttgart,
    UnionBerlin,
    WerderBremen,
    Wolfsburg,
    BundesligaEnd = Wolfsburg,

    Ligue1Start = BundesligaEnd + 1,
    Angers = Ligue1Start,
    Auxerre,
    Brest,
    LeHavre,
    Lens,
    Lille,
    Lyon,
    Marseille,
    Monaco,
    Montpellier,
    Nantes,
    Nice,
    PSG,
    Reims,
    Rennes,
    SaintEtienne,
    Strasbourg,
    Toulouse,
    Ligue1End = Toulouse

};

class Team
{
public:
    static std::string ToString(ETeam team);
    static std::string ToShortString(ETeam team);
};
