#include "MatchesInitializer.h"
#include <vector>
#include <unordered_map>

void MatchesInitializer::InitClubWorldCupTeams24_25(PGconn* pg)
{
    std::vector<ETeam> newTeams =
    {
        ETeam::AlAhly,
        ETeam::AlAin,
        ETeam::AlHilal,
        ETeam::AucklandCity,
        ETeam::BocaJuniors,
        ETeam::Botafogo,
        ETeam::Esperance,
        ETeam::Flamengo,
        ETeam::Fluminense,
        ETeam::InterMiami,
        ETeam::MamelodiSundowns,
        ETeam::Monterrey,
        ETeam::Pachuca,
        ETeam::Palmerias,
        ETeam::Porto,
        ETeam::RiverPlate,
        ETeam::SeatleSounders,
        ETeam::Ulsan,
        ETeam::UrawaReds,
        ETeam::Wydad,
        ETeam::LosAngelesFC
    };

    for (int i = (int)newTeams[0]; i <= (int)newTeams[newTeams.size() - 1]; ++i)
    {
        std::string sql = "insert into teams(id, name, short_name) values ("
            + std::to_string(i) + ", '"
            + Team::ToString((ETeam)i) + "', '"
            + Team::ToShortString((ETeam)i)
            + "');";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }

    int groupIndex = 0;

    // Group A
    std::vector group1Teams =
    {
        ETeam::AlAhly,
        ETeam::InterMiami,
        ETeam::Palmerias,
        ETeam::Porto
    };

    for (auto team : group1Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::ClubWorldCup)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex)
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group B
    std::vector group2Teams =
    {
        ETeam::AtleticoMadrid,
        ETeam::Botafogo,
        ETeam::PSG,
        ETeam::SeatleSounders
    };

    for (auto team : group2Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::ClubWorldCup)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex)
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group C
    std::vector group3Teams =
    {
        ETeam::AucklandCity,
        ETeam::BayernMunich,
        ETeam::Benfica,
        ETeam::BocaJuniors
    };

    for (auto team : group3Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::ClubWorldCup)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex)
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group D
    std::vector group4Teams =
    {
        ETeam::Chelsea,
        ETeam::Esperance,
        ETeam::Flamengo,
        ETeam::LosAngelesFC
    };

    for (auto team : group4Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::ClubWorldCup)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex)
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group E
    std::vector group5Teams =
    {
        ETeam::InterMilan,
        ETeam::RiverPlate,
        ETeam::Monterrey,
        ETeam::UrawaReds
    };

    for (auto team : group5Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::ClubWorldCup)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex)
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group F
    std::vector group6Teams =
    {
        ETeam::BorussiaDortmund,
        ETeam::Fluminense,
        ETeam::MamelodiSundowns,
        ETeam::Ulsan
    };

    for (auto team : group6Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::ClubWorldCup)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex)
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group G
    std::vector group7Teams =
    {
        ETeam::AlAin,
        ETeam::Juventus,
        ETeam::ManchesterCity,
        ETeam::Wydad
    };

    for (auto team : group7Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::ClubWorldCup)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex)
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group H
    std::vector group8Teams =
    {
        ETeam::AlHilal,
        ETeam::Pachuca,
        ETeam::RealMadrid,
        ETeam::Salzburg
    };

    for (auto team : group8Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::ClubWorldCup)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex)
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;
}

void MatchesInitializer::InitClubWorldCupTable24_25(PGconn* pg)
{
    int groupIndex = 0;

    // Group A
    std::vector group1Teams =
    {
        ETeam::AlAhly,
        ETeam::InterMiami,
        ETeam::Palmerias,
        ETeam::Porto
    };

    for (auto team : group1Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::ClubWorldCup)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex) + ", '24/25'"
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group B
    std::vector group2Teams =
    {
        ETeam::AtleticoMadrid,
        ETeam::Botafogo,
        ETeam::PSG,
        ETeam::SeatleSounders
    };

    for (auto team : group2Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::ClubWorldCup)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex) + ", '24/25'"
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group C
    std::vector group3Teams =
    {
        ETeam::AucklandCity,
        ETeam::BayernMunich,
        ETeam::Benfica,
        ETeam::BocaJuniors
    };

    for (auto team : group3Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::ClubWorldCup)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex) + ", '24/25'"
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group D
    std::vector group4Teams =
    {
        ETeam::Chelsea,
        ETeam::Esperance,
        ETeam::Flamengo,
        ETeam::LosAngelesFC
    };

    for (auto team : group4Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::ClubWorldCup)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex) + ", '24/25'"
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group E
    std::vector group5Teams =
    {
        ETeam::InterMilan,
        ETeam::RiverPlate,
        ETeam::Monterrey,
        ETeam::UrawaReds
    };

    for (auto team : group5Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::ClubWorldCup)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex) + ", '24/25'"
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group F
    std::vector group6Teams =
    {
        ETeam::BorussiaDortmund,
        ETeam::Fluminense,
        ETeam::MamelodiSundowns,
        ETeam::Ulsan
    };

    for (auto team : group6Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::ClubWorldCup)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex) + ", '24/25'"
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group G
    std::vector group7Teams =
    {
        ETeam::AlAin,
        ETeam::Juventus,
        ETeam::ManchesterCity,
        ETeam::Wydad
    };

    for (auto team : group7Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::ClubWorldCup)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex) + ", '24/25'"
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group H
    std::vector group8Teams =
    {
        ETeam::AlHilal,
        ETeam::Pachuca,
        ETeam::RealMadrid,
        ETeam::Salzburg
    };

    for (auto team : group8Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::ClubWorldCup)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex) + ", '24/25'"
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;
}

void MatchesInitializer::InitChampionsLeagueTeams25_26(PGconn* pg)
{
    std::vector<ETeam> newTeams =
    {
        ETeam::UnionSG,
        ETeam::Qarabag,
        ETeam::Olympiakos,
        ETeam::Pafos,
        ETeam::Slavia,
        ETeam::BodoGlimt,
        ETeam::Ajax,
        ETeam::Copenhagen,
        ETeam::Kairat
    };

    for (int i = (int)newTeams[0]; i <= (int)newTeams[newTeams.size() - 1]; ++i)
    {
        std::string sql = "insert into teams(id, name, short_name) values ("
            + std::to_string(i) + ", '"
            + Team::ToString((ETeam)i) + "', '"
            + Team::ToShortString((ETeam)i)
            + "');";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }

    std::vector clTeams =
    {
        ETeam::Ajax,
        ETeam::Arsenal,
        ETeam::Atalanta,
        ETeam::AthleticClub,
        ETeam::AtleticoMadrid,
        ETeam::BorussiaDortmund,
        ETeam::Barcelona,
        ETeam::BayernMunich,
        ETeam::Benfica,
        ETeam::BodoGlimt,
        ETeam::Chelsea,
        ETeam::ClubBrugge,
        ETeam::Copenhagen,
        ETeam::EintrachtFrankfurt,
        ETeam::Galatasaray,
        ETeam::InterMilan,
        ETeam::Juventus,
        ETeam::Kairat,
        ETeam::BayerLeverkusen,
        ETeam::Liverpool,
        ETeam::ManchesterCity,
        ETeam::Marseille,
        ETeam::Monaco,
        ETeam::Napoli,
        ETeam::NewcastleUnited,
        ETeam::Olympiakos,
        ETeam::Pafos,
        ETeam::PSG,
        ETeam::PSV,
        ETeam::Qarabag,
        ETeam::RealMadrid,
        ETeam::Slavia,
        ETeam::SportingLisbon,
        ETeam::TottenhamHotspur,
        ETeam::UnionSG,
        ETeam::Villarreal
    };

    for (auto team : clTeams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id) values ("
            + std::to_string(int(ELeague::ChampionsLeague)) + ", "
            + std::to_string(int(team)) + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}


void MatchesInitializer::InitChampionsLeagueTable(PGconn* pg)
{
    std::vector clTeams =
    {
        ETeam::Ajax,
        ETeam::Arsenal,
        ETeam::Atalanta,
        ETeam::AthleticClub,
        ETeam::AtleticoMadrid,
        ETeam::BorussiaDortmund,
        ETeam::Barcelona,
        ETeam::BayernMunich,
        ETeam::Benfica,
        ETeam::BodoGlimt,
        ETeam::Chelsea,
        ETeam::ClubBrugge,
        ETeam::Copenhagen,
        ETeam::EintrachtFrankfurt,
        ETeam::Galatasaray,
        ETeam::InterMilan,
        ETeam::Juventus,
        ETeam::Kairat,
        ETeam::BayerLeverkusen,
        ETeam::Liverpool,
        ETeam::ManchesterCity,
        ETeam::Marseille,
        ETeam::Monaco,
        ETeam::Napoli,
        ETeam::NewcastleUnited,
        ETeam::Olympiakos,
        ETeam::Pafos,
        ETeam::PSG,
        ETeam::PSV,
        ETeam::Qarabag,
        ETeam::RealMadrid,
        ETeam::Slavia,
        ETeam::SportingLisbon,
        ETeam::TottenhamHotspur,
        ETeam::UnionSG,
        ETeam::Villarreal
    };

    for (auto team : clTeams)
    {
        std::string sql = "insert into tables(team_id, league_id, season) values ("
            + std::to_string(int(team)) + ", "
            + std::to_string(int(ELeague::ChampionsLeague)) + " ,'"
            + "25/26"
            + "');";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitPremierLeagueTeams25_26(PGconn* pg)
{
    for (int i = (int)ETeam::PremierLeague2025Start; i <= (int)ETeam::PremierLeague2025End; ++i)
    {
        std::string sql = "insert into teams(id, name, short_name) values ("
            + std::to_string(i) + ", '"
            + Team::ToString((ETeam)i) + "', '"
            + Team::ToShortString((ETeam)i)
            + "');";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);

        sql = "insert into leagues_teams(league_id, team_id) values ("
            + std::to_string(int(ELeague::PremierLeague)) + ", "
            + std::to_string(i) + ");";
        ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitPremierLeagueTable(PGconn* pg)
{
    std::string sql = "create table tables(id serial primary key not null, team_id integer not null, league_id integer not null, season text not null, matches_played integer not null default 0, goals_f integer not null default 0, goals_a integer not null default 0, points integer not null default 0);";
    PGresult* ret = PQexec(pg, sql.c_str());
    PQclear(ret);

    std::vector<ETeam> teams =
    {
        ETeam::AFCBournemouth,
        ETeam::Arsenal,
        ETeam::AstonVilla,
        ETeam::Brentford,
        ETeam::BrightonAndHoveAlbion,
        ETeam::Burnley,
        ETeam::Chelsea,
        ETeam::CrystalPalace,
        ETeam::Everton,
        ETeam::Fulham,
        ETeam::Leeds,
        ETeam::Liverpool,
        ETeam::ManchesterCity,
        ETeam::ManchesterUnited,
        ETeam::NewcastleUnited,
        ETeam::NottinghamForest,
        ETeam::Sunderland,
        ETeam::TottenhamHotspur,
        ETeam::WestHamUnited,
        ETeam::Wolverhampton
    };
    for (ETeam i : teams)
    {
        sql = "insert into tables(team_id, league_id, season) values ("
            + std::to_string(int(i)) + ", "
            + std::to_string(int(ELeague::PremierLeague)) + " ,'"
            + "25/26" 
            + "');";
        ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void FillLeagueTable(PGconn* pg, int league)
{
    std::string sql = "select team1, team2, team1_score, team2_score from matches where league = " + std::to_string(league) + ";";
    PGresult* ret = PQexec(pg, sql.c_str());

    int nrows = PQntuples(ret);

    // Create a map to store the table data temporarily
    std::unordered_map<int, std::tuple<int, int, int, int, int>> tableData;

    for (int i = 0; i < nrows; ++i)
    {
        int team1 = atoi(PQgetvalue(ret, i, 0));
        int team2 = atoi(PQgetvalue(ret, i, 1));
        int team1Score = atoi(PQgetvalue(ret, i, 2));
        int team2Score = atoi(PQgetvalue(ret, i, 3));

        if (team1Score < 0 || team2Score < 0) continue;

        // Initialize or update team1's data
        if (tableData.find(team1) == tableData.end())
            tableData[team1] = std::make_tuple(0, 0, 0, 0, 0);

        auto& team1Data = tableData[team1];
        std::get<0>(team1Data)++; // matches_played
        std::get<1>(team1Data) += team1Score; // goals_f
        std::get<2>(team1Data) += team2Score; // goals_a

        // Initialize or update team2's data
        if (tableData.find(team2) == tableData.end())
            tableData[team2] = std::make_tuple(0, 0, 0, 0, 0);

        auto& team2Data = tableData[team2];
        std::get<0>(team2Data)++; // matches_played
        std::get<1>(team2Data) += team2Score; // goals_f
        std::get<2>(team2Data) += team1Score; // goals_a

        // Determine points for both teams
        if (team1Score > team2Score)
        {
            std::get<4>(team1Data) += 3; // 3 points for a win
        }
        else if (team1Score < team2Score)
        {
            std::get<4>(team2Data) += 3; // 3 points for a win
        }
        else
        {
            std::get<4>(team1Data) += 1; // 1 point for a draw
            std::get<4>(team2Data) += 1; // 1 point for a draw
        }
    }

    // Update the database
    for (const auto& entry : tableData)
    {
        int teamId = entry.first;
        int matchesPlayed = std::get<0>(entry.second);
        int goalsF = std::get<1>(entry.second);
        int goalsA = std::get<2>(entry.second);
        int points = std::get<4>(entry.second);

        sql = "update tables set matches_played = matches_played + " + std::to_string(matchesPlayed) +
            ", goals_f = goals_f + " + std::to_string(goalsF) +
            ", goals_a = goals_a + " + std::to_string(goalsA) +
            ", points = points + " + std::to_string(points) +
            " where team_id = " + std::to_string(teamId) +
            " and league_id = " + std::to_string(league) + ";";
        PQexec(pg, sql.c_str());
    }

    PQclear(ret);
}

void MatchesInitializer::FillPremierLeagueTable(PGconn* pg)
{
    FillLeagueTable(pg, int(ELeague::PremierLeague));
}


void MatchesInitializer::InitLaLigaTeams25_26(PGconn* pg)
{
    for (int i = (int)ETeam::LaLiga2025Start; i <= (int)ETeam::LaLiga2025End; ++i)
    {
        std::string sql = "insert into teams(id, name, short_name) values ("
            + std::to_string(i) + ", '"
            + Team::ToString((ETeam)i) + "', '"
            + Team::ToShortString((ETeam)i)
            + "');";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);

        sql = "insert into leagues_teams(league_id, team_id) values ("
            + std::to_string(int(ELeague::LaLiga)) + ", "
            + std::to_string(i) + ");";
        ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitLaLigaTable(PGconn* pg)
{
    std::vector<ETeam> teams =
    {
        ETeam::Alaves,
        ETeam::AthleticClub,
        ETeam::AtleticoMadrid,
        ETeam::Barcelona,
        ETeam::CeltaVigo,
        ETeam::Elche,
        ETeam::Espanyol,
        ETeam::Getafe,
        ETeam::Girona,
        ETeam::Levante,
        ETeam::Mallorca,
        ETeam::Osasuna,
        ETeam::RayoVallecano,
        ETeam::RealBetis,
        ETeam::RealMadrid,
        ETeam::Oviedo,
        ETeam::RealSociedad,
        ETeam::Sevilla,
        ETeam::Valencia,
        ETeam::Villarreal
    };
    for (ETeam i : teams)
    {
        std::string sql = "insert into tables(team_id, league_id, season) values ("
            + std::to_string((int)i) + ", "
            + std::to_string(int(ELeague::LaLiga)) + " ,'"
            + "25/26"
            + "');";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::FillLaLigaTable(PGconn* pg)
{
    FillLeagueTable(pg, int(ELeague::LaLiga));
}

void MatchesInitializer::InitSerieATeams25_26(PGconn* pg)
{

    for (int i = (int)ETeam::SerieA2025Start; i <= (int)ETeam::SerieA2025End; ++i)
    {
        std::string sql = "insert into teams(id, name, short_name) values ("
            + std::to_string(i) + ", '"
            + Team::ToString((ETeam)i) + "', '"
            + Team::ToShortString((ETeam)i)
            + "');";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);

        sql = "insert into leagues_teams(league_id, team_id) values ("
            + std::to_string(int(ELeague::SerieA)) + ", "
            + std::to_string(i) + ");";
        ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitSeriaATable(PGconn* pg) 
{
    std::vector<ETeam> teams =
    {
        ETeam::ACMilan,
        ETeam::Atalanta,
        ETeam::Bologna,
        ETeam::Cagliari,
        ETeam::Como,
        ETeam::Cremonese,
        ETeam::Fiorentina,
        ETeam::Genoa,
        ETeam::InterMilan,
        ETeam::Juventus,
        ETeam::Lazio,
        ETeam::Lecce,
        ETeam::Napoli,
        ETeam::Parma,
        ETeam::Pisa,
        ETeam::Roma,
        ETeam::Sassuolo,
        ETeam::Torino,
        ETeam::Udinese,
        ETeam::Verona
    };
    for (ETeam i : teams)
    {
        std::string sql = "insert into tables(team_id, league_id, season) values ("
            + std::to_string((int)i) + ", "
            + std::to_string(int(ELeague::SerieA)) + " ,'"
            + "25/26"
            + "');";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::FillSeriaATable(PGconn* pg) 
{
    FillLeagueTable(pg, int(ELeague::SerieA));
}

void MatchesInitializer::InitBundesligaTeams25_26(PGconn* pg)
{
    for (int i = (int)ETeam::Bundesliga2025Start; i <= (int)ETeam::Bundesliga2025End; ++i)
    {
        std::string sql = "insert into teams(id, name, short_name) values ("
            + std::to_string(i) + ", '"
            + Team::ToString((ETeam)i) + "', '"
            + Team::ToShortString((ETeam)i)
            + "');";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);

        sql = "insert into leagues_teams(league_id, team_id) values ("
            + std::to_string(int(ELeague::Bundesliga)) + ", "
            + std::to_string(i) + ");";
        ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitBundesligaTable(PGconn* pg)
{
    std::vector<ETeam> teams =
    {
        ETeam::Augsburg,
        ETeam::BayerLeverkusen,
        ETeam::BayernMunich,
        ETeam::BorussiaDortmund,
        ETeam::BorussiaMgladbach,
        ETeam::EintrachtFrankfurt,
        ETeam::Koln,
        ETeam::Freiburg,
        ETeam::Hamburg,
        ETeam::Heidenheim,
        ETeam::Hoffenheim,
        ETeam::Mainz,
        ETeam::RBLeipzig,
        ETeam::StPauli,
        ETeam::Stuttgart,
        ETeam::UnionBerlin,
        ETeam::WerderBremen,
        ETeam::Wolfsburg
    };
    for (ETeam i : teams)
    {
        std::string sql = "insert into tables(team_id, league_id, season) values ("
            + std::to_string(int(i)) + ", "
            + std::to_string(int(ELeague::Bundesliga)) + " ,'"
            + "25/26"
            + "');";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::FillBundesligaTable(PGconn* pg) 
{
    FillLeagueTable(pg, int(ELeague::Bundesliga));
}


void MatchesInitializer::InitLigue1Teams25_26(PGconn* pg)
{
    for (int i = (int)ETeam::Ligue12025Start; i <= (int)ETeam::Ligue12025End; ++i)
    {
        std::string sql = "insert into teams(id, name, short_name) values ("
            + std::to_string(i) + ", '"
            + Team::ToString((ETeam)i) + "', '"
            + Team::ToShortString((ETeam)i)
            + "');";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);

        sql = "insert into leagues_teams(league_id, team_id) values ("
            + std::to_string(int(ELeague::Ligue1)) + ", "
            + std::to_string(i) + ");";
        ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}
#include <functional>
void MatchesInitializer::InitNationsLeagueTeams24_25(PGconn* pg)
{
    std::function<void(ETeam, int, int)> insertInto = [pg](ETeam team, int leagueIndex, int groupIndex) {
        std::string sql = "insert into teams(id, name, short_name) values ("
            + std::to_string(int(team)) + ", '"
            + Team::ToString(team) + "', '"
            + Team::ToShortString(team) + "'"
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);

        sql = "insert into leagues_teams(league_id, team_id, league_index, group_index) values ("
            + std::to_string(int(ELeague::NationsLeague)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(leagueIndex) + ", "
            + std::to_string(groupIndex)
            + ");";
        ret = PQexec(pg, sql.c_str());
        PQclear(ret);

        sql = "insert into tables(team_id, league_id, season, league_index, group_index) values ("
            + std::to_string(int(team)) + ", "
            + std::to_string(int(ELeague::NationsLeague)) + " ,'"
            + "24/25" + "' ,"
            + std::to_string(leagueIndex) + ", "
            + std::to_string(groupIndex)
            + ");";
        ret = PQexec(pg, sql.c_str());
        PQclear(ret);

        ++groupIndex;
    };

    // Group A1
    std::vector<ETeam> groupA1Teams =
    {
        ETeam::Portugal,
        ETeam::Croatia,
        ETeam::Poland,
        ETeam::Scotland
    };

    int leagueIndex = 0;
    int groupIndex = 0;

    for (auto team : groupA1Teams) 
    {
        insertInto(team, leagueIndex, groupIndex);
    }

    // Group A2
    std::vector<ETeam> groupA2Teams =
    {
        ETeam::Italy,
        ETeam::France,
        ETeam::Belgium,
        ETeam::Israel
    };

    ++groupIndex;

    for (auto team : groupA2Teams)
    {
        insertInto(team, leagueIndex, groupIndex);
    }

    // Group A3
    std::vector<ETeam> groupA3Teams =
    {
        ETeam::Germany,
        ETeam::Netherlands,
        ETeam::BosniaAndHerzegovina,
        ETeam::Hungary,
    };

    ++groupIndex;

    for (auto team : groupA3Teams)
    {
        insertInto(team, leagueIndex, groupIndex);
    }

    // Group A4
    std::vector<ETeam> groupA4Teams =
    {
        ETeam::Denmark,
        ETeam::Spain,
        ETeam::Serbia,
        ETeam::Switzerland,
    };

    ++groupIndex;

    for (auto team : groupA4Teams)
    {
        insertInto(team, leagueIndex, groupIndex);
    }

    // Group B1
    std::vector<ETeam> groupB1Teams =
    {
        ETeam::Georgia,
        ETeam::Albania,
        ETeam::Czechia,
        ETeam::Ukraine
    };

    ++leagueIndex;
    groupIndex = 0;

    for (auto team : groupB1Teams)
    {
        insertInto(team, leagueIndex, groupIndex);
    }

    // Group B2
    std::vector<ETeam> groupB2Teams =
    {
        ETeam::Greece,
        ETeam::England,
        ETeam::RepublicOfIreland,
        ETeam::Finland
    };

    ++groupIndex;

    for (auto team : groupB2Teams)
    {
        insertInto(team, leagueIndex, groupIndex);
    }

    // Group B3
    std::vector<ETeam> groupB3Teams =
    {
        ETeam::Slovenia,
        ETeam::Norway,
        ETeam::Austria,
        ETeam::Kazakhstan
    };

    ++groupIndex;

    for (auto team : groupB3Teams)
    {
        insertInto(team, leagueIndex, groupIndex);
    }

    // Group B4
    std::vector<ETeam> groupB4Teams =
    {
        ETeam::Turkiye,
        ETeam::Wales,
        ETeam::Iceland,
        ETeam::Montenegro
    };

    ++groupIndex;

    for (auto team : groupB4Teams)
    {
        insertInto(team, leagueIndex, groupIndex);
    }

    // Group C1
    std::vector<ETeam> groupC1Teams =
    {
        ETeam::Sweden,
        ETeam::Slovakia,
        ETeam::Azerbaijan,
        ETeam::Estonia
    };

    ++leagueIndex;
    groupIndex = 0;

    for (auto team : groupC1Teams)
    {
        insertInto(team, leagueIndex, groupIndex);
    }

    // Group C2
    std::vector<ETeam> groupC2Teams =
    {
        ETeam::Romania,
        ETeam::Kosovo,
        ETeam::Cyprus,
        ETeam::Lithuania
    };

    ++groupIndex;

    for (auto team : groupC2Teams)
    {
        insertInto(team, leagueIndex, groupIndex);
    }

    // Group C3
    std::vector<ETeam> groupC3Teams =
    {
        ETeam::Belarus,
        ETeam::Bulgaria,
        ETeam::NorthernIreland,
        ETeam::Luxemburg
    };

    ++groupIndex;

    for (auto team : groupC3Teams)
    {
        insertInto(team, leagueIndex, groupIndex);
    }

    // Group C4
    std::vector<ETeam> groupC4Teams =
    {
        ETeam::NorthMacedonia,
        ETeam::Armenia,
        ETeam::Latvia,
        ETeam::FaroeIslands
    };

    ++groupIndex;

    for (auto team : groupC4Teams)
    {
        insertInto(team, leagueIndex, groupIndex);
    }

    // Group D1
    std::vector<ETeam> groupD1Teams =
    {
        ETeam::SanMarino,
        ETeam::Gibraltar,
        ETeam::Liechtenstein
    };

    ++leagueIndex;
    groupIndex = 0;

    for (auto team : groupD1Teams)
    {
        insertInto(team, leagueIndex, groupIndex);
    }

    // Group D2
    std::vector<ETeam> groupD2Teams =
    {
        ETeam::Moldova,
        ETeam::Malta,
        ETeam::Andorra
    };

    ++groupIndex;

    for (auto team : groupD2Teams)
    {
        insertInto(team, leagueIndex, groupIndex);
    } 
}

void MatchesInitializer::InitClubWorldCupPO24_25(PGconn* pg)
{
    // ClubWorldCup
    std::vector<Match> matches;
    // Week 1
//    matches.push_back({ ELeague::ClubWorldCup, "24/25", 4, ETeam::Palmerias, ETeam::Botafogo, 1751126400000, EWeekType::RoundOf16, true });
//    matches.push_back({ ELeague::ClubWorldCup, "24/25", 4, ETeam::Benfica, ETeam::Chelsea, 1751140800000, EWeekType::RoundOf16, true });
//    matches.push_back({ ELeague::ClubWorldCup, "24/25", 4, ETeam::PSG, ETeam::InterMiami, 1751212800000, EWeekType::RoundOf16, true });
//    matches.push_back({ ELeague::ClubWorldCup, "24/25", 4, ETeam::Flamengo, ETeam::BayernMunich, 1751227200000, EWeekType::RoundOf16, true });
//    matches.push_back({ ELeague::ClubWorldCup, "24/25", 4, ETeam::InterMilan, ETeam::Fluminense, 1751310000000, EWeekType::RoundOf16, true });

    //matches.push_back({ ELeague::ClubWorldCup, "24/25", 4, ETeam::ManchesterCity, ETeam::AlHilal, 1751331600000, EWeekType::RoundOf16, true });
  //  matches.push_back({ ELeague::ClubWorldCup, "24/25", 4, ETeam::RealMadrid, ETeam::Juventus, 1751396400000, EWeekType::RoundOf16, true });
//    matches.push_back({ ELeague::ClubWorldCup, "24/25", 4, ETeam::BorussiaDortmund, ETeam::Monterrey, 1751418000000, EWeekType::RoundOf16, true });

   // matches.push_back({ ELeague::ClubWorldCup, "24/25", 5, ETeam::Palmerias, ETeam::Chelsea, 1751677200000, EWeekType::RoundOf8, true });
   // matches.push_back({ ELeague::ClubWorldCup, "24/25", 5, ETeam::PSG, ETeam::BayernMunich, 1751731200000, EWeekType::RoundOf8, true });

    //matches.push_back({ ELeague::ClubWorldCup, "24/25", 6, ETeam::PSG, ETeam::RealMadrid, 1752087600000, EWeekType::SemiFinal, true });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 7, ETeam::Chelsea, ETeam::PSG, 1752433200000, EWeekType::Final, true });

    
    for (auto& m : matches)
    {
        std::string sql = "insert into matches(league, season, week, week_type, team1, team2,match_date,play_off) values ("
            + std::to_string(int(m.League)) + ", '"
            + m.Season + "', "
            + std::to_string(m.Week) + ", "
            + std::to_string((int)m.WeekType) + ", "
            + std::to_string((int)m.Team1) + ", "
            + std::to_string((int)m.Team2) + ", "
            + std::to_string(m.Date) + ", "
            + std::to_string((int)m.PlayOff) + ""
            + ");";


        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitClubWorldCup24_25(PGconn* pg)
{
    // ClubWorldCup
    std::vector<Match> matches;
    // Week 1
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 1, ETeam::AlAhly, ETeam::InterMiami, 1749945600000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 1, ETeam::Palmerias, ETeam::Porto, 1750024800000 });

    matches.push_back({ ELeague::ClubWorldCup, "24/25", 1, ETeam::PSG, ETeam::AtleticoMadrid, 1750014000000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 1, ETeam::Botafogo, ETeam::SeatleSounders, 1750039200000 });

    matches.push_back({ ELeague::ClubWorldCup, "24/25", 1, ETeam::BayernMunich, ETeam::AucklandCity, 1750003200000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 1, ETeam::BocaJuniors, ETeam::Benfica, 1750111200000 });

    matches.push_back({ ELeague::ClubWorldCup, "24/25", 1, ETeam::Chelsea, ETeam::LosAngelesFC, 1750100400000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 1, ETeam::Flamengo, ETeam::Esperance, 1750122000000 });

    matches.push_back({ ELeague::ClubWorldCup, "24/25", 1, ETeam::RiverPlate, ETeam::UrawaReds, 1750186800000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 1, ETeam::Monterrey, ETeam::InterMilan, 1750208400000 });

    matches.push_back({ ELeague::ClubWorldCup, "24/25", 1, ETeam::Fluminense, ETeam::BorussiaDortmund, 1750176000000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 1, ETeam::Ulsan, ETeam::MamelodiSundowns, 1750197600000 });

    matches.push_back({ ELeague::ClubWorldCup, "24/25", 1, ETeam::ManchesterCity, ETeam::Wydad, 1750262400000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 1, ETeam::AlAin, ETeam::Juventus, 1750294800000 });

    matches.push_back({ ELeague::ClubWorldCup, "24/25", 1, ETeam::RealMadrid, ETeam::AlHilal, 1750273200000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 1, ETeam::Pachuca, ETeam::Salzburg, 1750284000000 });

    // Week 2
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 2, ETeam::Palmerias, ETeam::AlAhly, 1750348800000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 2, ETeam::InterMiami, ETeam::Porto, 1750359600000 });

    matches.push_back({ ELeague::ClubWorldCup, "24/25", 2, ETeam::SeatleSounders, ETeam::AtleticoMadrid, 1750370400000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 2, ETeam::PSG, ETeam::Botafogo, 1750381200000 });

    matches.push_back({ ELeague::ClubWorldCup, "24/25", 2, ETeam::Benfica, ETeam::AucklandCity, 1750435200000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 2, ETeam::BayernMunich, ETeam::BocaJuniors, 1750467600000 });

    matches.push_back({ ELeague::ClubWorldCup, "24/25", 2, ETeam::Flamengo, ETeam::Chelsea, 1750442400000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 2, ETeam::LosAngelesFC, ETeam::Esperance, 1750456800000 });

    matches.push_back({ ELeague::ClubWorldCup, "24/25", 2, ETeam::InterMilan, ETeam::UrawaReds, 1750532400000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 2, ETeam::RiverPlate, ETeam::Monterrey, 1750554000000 });

    matches.push_back({ ELeague::ClubWorldCup, "24/25", 2, ETeam::MamelodiSundowns, ETeam::BorussiaDortmund, 1750521600000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 2, ETeam::Fluminense, ETeam::Ulsan, 1750543200000 });

    matches.push_back({ ELeague::ClubWorldCup, "24/25", 2, ETeam::Juventus, ETeam::Wydad, 1750608000000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 2, ETeam::ManchesterCity, ETeam::AlAin, 1750640400000 });

    matches.push_back({ ELeague::ClubWorldCup, "24/25", 2, ETeam::RealMadrid, ETeam::Pachuca, 1750618800000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 2, ETeam::Salzburg, ETeam::AlHilal, 1750629600000 });

    // Week 3
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 3, ETeam::InterMiami, ETeam::Palmerias, 1750726800000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 3, ETeam::Porto, ETeam::AlAhly, 1750726800000 });

    matches.push_back({ ELeague::ClubWorldCup, "24/25", 3, ETeam::AtleticoMadrid, ETeam::Botafogo, 1750705200000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 3, ETeam::SeatleSounders, ETeam::PSG, 1750705200000 });

    matches.push_back({ ELeague::ClubWorldCup, "24/25", 3, ETeam::Benfica, ETeam::BayernMunich, 1750791600000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 3, ETeam::AucklandCity, ETeam::BocaJuniors, 1750791600000 });

    matches.push_back({ ELeague::ClubWorldCup, "24/25", 3, ETeam::LosAngelesFC, ETeam::Flamengo, 1750813200000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 3, ETeam::Esperance, ETeam::Chelsea, 1750813200000 });

    matches.push_back({ ELeague::ClubWorldCup, "24/25", 3, ETeam::UrawaReds, ETeam::Monterrey, 1750899600000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 3, ETeam::InterMilan, ETeam::RiverPlate, 1750899600000 });

    matches.push_back({ ELeague::ClubWorldCup, "24/25", 3, ETeam::BorussiaDortmund, ETeam::Ulsan, 1750878000000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 3, ETeam::MamelodiSundowns, ETeam::Fluminense, 1750878000000 });

    matches.push_back({ ELeague::ClubWorldCup, "24/25", 3, ETeam::Juventus, ETeam::ManchesterCity, 1750964400000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 3, ETeam::Wydad, ETeam::AlAin, 1750964400000 });

    matches.push_back({ ELeague::ClubWorldCup, "24/25", 3, ETeam::AlHilal, ETeam::Pachuca, 1750986000000 });
    matches.push_back({ ELeague::ClubWorldCup, "24/25", 3, ETeam::Salzburg, ETeam::RealMadrid, 1750986000000 });

    for (auto& m : matches)
    {
        std::string sql = "insert into matches(league, season, week, team1, team2, match_date) values ("
            + std::to_string(int(m.League)) + ", '"
            + m.Season + "', "
            + std::to_string(m.Week) + ", "
            + std::to_string((int)m.Team1) + ", "
            + std::to_string((int)m.Team2) + ", "
            + std::to_string(m.Date) + ");";

        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitNationsLeague24_25(PGconn* pg)
{
    // Nations League
    std::vector<Match> matches;
    // Week 1
   // matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::Portugal, ETeam::Croatia, 1722985200000 });
   // matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::Scotland, ETeam::Poland, 1722985200000 });
   // matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::Denmark, ETeam::Switzerland, 1722985200000 });
   // matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::Serbia, ETeam::Spain, 1722985200000 });
   // matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::Belgium, ETeam::Israel, 1722985200000 });
   // matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::France, ETeam::Italy, 1722985200000 });
   // matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::Germany, ETeam::Hungary, 1722985200000 });
   // matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::Netherlands, ETeam::BosniaAndHerzegovina, 1722985200000 });

   // matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::Kazakhstan, ETeam::Norway, 1722985200000 });
   // matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::Slovenia, ETeam::Austria, 1722985200000 });
   // matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::Iceland, ETeam::Montenegro, 1722985200000 });
   // matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::Wales, ETeam::Turkiye, 1722985200000 });
   // matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::Georgia, ETeam::Czechia, 1722985200000 });
   // matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::RepublicOfIreland, ETeam::England, 1722985200000 });
   // matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::Ukraine, ETeam::Albania, 1722985200000 });
   // matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::Greece, ETeam::Finland, 1722985200000 });
   
  //  matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::Azerbaijan, ETeam::Sweden, 1722985200000 });
  //  matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::Estonia, ETeam::Slovakia, 1722985200000 });
  //  matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::Belarus, ETeam::Bulgaria, 1722985200000 });
  //  matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::NorthernIreland, ETeam::Luxemburg, 1722985200000 });
  //  matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::Lithuania, ETeam::Cyprus, 1722985200000 });
  //  matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::Kosovo, ETeam::Romania, 1722985200000 });
  //  matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::FaroeIslands, ETeam::NorthMacedonia, 1722985200000 });
  //  matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::Armenia, ETeam::Latvia, 1722985200000 });

   // matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::SanMarino, ETeam::Liechtenstein, 1722985200000 });
   // matches.push_back({ ELeague::NationsLeague, "24/25", 1, ETeam::Moldova, ETeam::Malta, 1722985200000 });

    // week 2
    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::Denmark, ETeam::Serbia, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::Croatia, ETeam::Poland, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::Portugal, ETeam::Scotland, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::Switzerland, ETeam::Spain, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::France, ETeam::Belgium, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::Israel, ETeam::Italy, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::Hungary, ETeam::BosniaAndHerzegovina, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::Netherlands, ETeam::Germany, 1722985200000 });

    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::Norway, ETeam::Austria, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::Slovenia, ETeam::Kazakhstan, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::Montenegro, ETeam::Wales, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::Turkiye, ETeam::Iceland, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::Albania, ETeam::Georgia, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::Czechia, ETeam::Ukraine, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::England, ETeam::Finland, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::RepublicOfIreland, ETeam::Greece, 1722985200000 });

    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::Luxemburg, ETeam::Belarus, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::Slovakia, ETeam::Azerbaijan, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::Bulgaria, ETeam::NorthernIreland, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::Sweden, ETeam::Estonia, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::Cyprus, ETeam::Kosovo, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::Romania, ETeam::Lithuania, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::Latvia, ETeam::FaroeIslands, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::NorthMacedonia, ETeam::Armenia, 1722985200000 });

    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::Gibraltar, ETeam::Liechtenstein, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 2, ETeam::Andorra, ETeam::Malta, 1722985200000 });

    // week 3
    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::Israel, ETeam::France, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::Italy, ETeam::Belgium, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::BosniaAndHerzegovina, ETeam::Germany, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::Hungary, ETeam::Netherlands, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::Croatia, ETeam::Scotland, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::Poland, ETeam::Portugal, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::Serbia, ETeam::Switzerland, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::Spain, ETeam::Denmark, 1722985200000 });

    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::England, ETeam::Greece, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::Finland, ETeam::RepublicOfIreland, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::Austria, ETeam::Kazakhstan, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::Norway, ETeam::Slovenia, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::Czechia, ETeam::Albania, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::Ukraine, ETeam::Georgia, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::Iceland, ETeam::Wales, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::Turkiye, ETeam::Montenegro, 1722985200000 });

    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::Latvia, ETeam::NorthMacedonia, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::FaroeIslands, ETeam::Armenia, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::Estonia, ETeam::Azerbaijan, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::Slovakia, ETeam::Sweden, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::Lithuania, ETeam::Kosovo, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::Bulgaria, ETeam::Luxemburg, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::Cyprus, ETeam::Romania, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::Belarus, ETeam::NorthernIreland, 1722985200000 });

    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::Moldova, ETeam::Andorra, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 3, ETeam::Gibraltar, ETeam::SanMarino, 1722985200000 });

    // week 4
    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::Belgium, ETeam::France, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::Italy, ETeam::Israel, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::BosniaAndHerzegovina, ETeam::Hungary, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::Germany, ETeam::Netherlands, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::Poland, ETeam::Croatia, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::Scotland, ETeam::Portugal, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::Spain, ETeam::Serbia, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::Switzerland, ETeam::Denmark, 1722985200000 });

    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::Kazakhstan, ETeam::Slovenia, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::Finland, ETeam::England, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::Greece, ETeam::RepublicOfIreland, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::Austria, ETeam::Norway, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::Georgia, ETeam::Albania, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::Ukraine, ETeam::Czechia, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::Iceland, ETeam::Turkiye, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::Wales, ETeam::Montenegro, 1722985200000 });

    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::Armenia, ETeam::NorthMacedonia, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::FaroeIslands, ETeam::Latvia, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::Azerbaijan, ETeam::Slovakia, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::Estonia, ETeam::Sweden, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::Kosovo, ETeam::Cyprus, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::Belarus, ETeam::Luxemburg, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::NorthernIreland, ETeam::Bulgaria, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::Lithuania, ETeam::Romania, 1722985200000 });

    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::Malta, ETeam::Moldova, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 4, ETeam::Liechtenstein, ETeam::Gibraltar, 1722985200000 });

    // week 5
    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::Belgium, ETeam::Italy, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::France, ETeam::Israel, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::Portugal, ETeam::Poland, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::Scotland, ETeam::Croatia, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::Denmark, ETeam::Spain, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::Switzerland, ETeam::Serbia, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::Germany, ETeam::BosniaAndHerzegovina, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::Netherlands, ETeam::Hungary, 1722985200000 });

    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::Kazakhstan, ETeam::Austria, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::Greece, ETeam::England, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::RepublicOfIreland, ETeam::Finland, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::Slovenia, ETeam::Norway, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::Georgia, ETeam::Ukraine, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::Montenegro, ETeam::Iceland, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::Turkiye, ETeam::Wales, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::Albania, ETeam::Czechia, 1722985200000 });

    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::Armenia, ETeam::FaroeIslands, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::NorthMacedonia, ETeam::Latvia, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::Cyprus, ETeam::Lithuania, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::Romania, ETeam::Kosovo, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::Luxemburg, ETeam::Bulgaria, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::NorthernIreland, ETeam::Belarus, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::Azerbaijan, ETeam::Estonia, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::Sweden, ETeam::Slovakia, 1722985200000 });

    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::SanMarino, ETeam::Gibraltar, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 5, ETeam::Andorra, ETeam::Moldova, 1722985200000 });

    // week 6
    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::Israel, ETeam::Belgium, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::Italy, ETeam::France, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::Croatia, ETeam::Portugal, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::Poland, ETeam::Scotland, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::Serbia, ETeam::Denmark, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::Spain, ETeam::Switzerland, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::BosniaAndHerzegovina, ETeam::Netherlands, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::Hungary, ETeam::Germany, 1722985200000 });

    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::England, ETeam::RepublicOfIreland, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::Finland, ETeam::Greece, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::Austria, ETeam::Slovenia, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::Norway, ETeam::Kazakhstan, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::Albania, ETeam::Ukraine, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::Czechia, ETeam::Georgia, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::Montenegro, ETeam::Turkiye, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::Wales, ETeam::Iceland, 1722985200000 });

    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::Latvia, ETeam::Armenia, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::NorthMacedonia, ETeam::FaroeIslands, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::Romania, ETeam::Cyprus, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::Bulgaria, ETeam::Belarus, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::Luxemburg, ETeam::NorthernIreland, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::Kosovo, ETeam::Lithuania, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::Slovakia, ETeam::Estonia, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::Sweden, ETeam::Azerbaijan, 1722985200000 });

    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::Liechtenstein, ETeam::SanMarino, 1722985200000 });
    matches.push_back({ ELeague::NationsLeague, "24/25", 6, ETeam::Malta, ETeam::Andorra, 1722985200000 });

    for (auto& m : matches)
    {
        std::string sql = "insert into matches(league, season, week, team1, team2, match_date) values ("
            + std::to_string(int(m.League)) + ", '"
            + m.Season + "', "
            + std::to_string(m.Week) + ", "
            + std::to_string((int)m.Team1) + ", "
            + std::to_string((int)m.Team2) + ", "
            + std::to_string(m.Date) + ");";

        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitNationsLeaguePO24_25(PGconn* pg)
{
    // Nations League
    std::vector<Match> matches;

   //matches.push_back({ ELeague::NationsLeague, "24/25", 7, ETeam::Italy, ETeam::Germany, 1742499900000, EWeekType::QuarterFinal });
   //matches.push_back({ ELeague::NationsLeague, "24/25", 7, ETeam::Denmark, ETeam::Portugal, 1742499900000, EWeekType::QuarterFinal });
   //matches.push_back({ ELeague::NationsLeague, "24/25", 7, ETeam::Croatia, ETeam::France, 1742499900000, EWeekType::QuarterFinal });
   //matches.push_back({ ELeague::NationsLeague, "24/25", 7, ETeam::Netherlands, ETeam::Spain, 1742499900000, EWeekType::QuarterFinal });

   // matches.push_back({ ELeague::NationsLeague, "24/25", 7, ETeam::Germany, ETeam::Italy, 1742759100000, EWeekType::QuarterFinal, true });
    //matches.push_back({ ELeague::NationsLeague, "24/25", 7, ETeam::Portugal, ETeam::Denmark, 1742759100000, EWeekType::QuarterFinal, true });
  //  matches.push_back({ ELeague::NationsLeague, "24/25", 7, ETeam::France, ETeam::Croatia, 1742759100000, EWeekType::QuarterFinal, true });
//    matches.push_back({ ELeague::NationsLeague, "24/25", 7, ETeam::Spain, ETeam::Netherlands, 1742759100000, EWeekType::QuarterFinal, true });

   // matches.push_back({ ELeague::NationsLeague, "24/25", 8, ETeam::Germany, ETeam::Portugal, 1749063600000, EWeekType::SemiFinal, false });
   // matches.push_back({ ELeague::NationsLeague, "24/25", 8, ETeam::Spain, ETeam::France, 1749150000000, EWeekType::SemiFinal, false });

    matches.push_back({ ELeague::NationsLeague, "24/25", 9, ETeam::Germany, ETeam::France, 1749387600000, EWeekType::SemiFinal, true });
    matches.push_back({ ELeague::NationsLeague, "24/25", 10, ETeam::Portugal, ETeam::Spain, 1749409200000, EWeekType::Final, true });


    for (auto& m : matches)
    {
        std::string sql = "insert into matches(league, season, week, week_type, team1, team2,match_date,play_off) values ("
            + std::to_string(int(m.League)) + ", '"
            + m.Season + "', "
            + std::to_string(m.Week) + ", "
            + std::to_string((int)m.WeekType) + ", "
            + std::to_string((int)m.Team1) + ", "
            + std::to_string((int)m.Team2) + ", "
            + std::to_string(m.Date) + ", "
            + std::to_string((int)m.PlayOff) + ""
            + ");";


        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitLigue1Table(PGconn* pg)
{
    std::vector<ETeam> teams =
    {
        ETeam::Angers,
        ETeam::Auxerre,
        ETeam::Brest,
        ETeam::LeHavre,
        ETeam::Lens,
        ETeam::Lille,
        ETeam::Lorient,
        ETeam::Lyon,
        ETeam::Marseille,
        ETeam::Metz,
        ETeam::Monaco,
        ETeam::Nantes,
        ETeam::Nice,
        ETeam::PSG,
        ETeam::ParisFC,
        ETeam::Rennes,
        ETeam::Strasbourg,
        ETeam::Toulouse
    };
    for (ETeam i : teams)
    {
        std::string sql = "insert into tables(team_id, league_id, season) values ("
            + std::to_string(int(i)) + ", "
            + std::to_string(int(ELeague::Ligue1)) + " ,'"
            + "25/26"
            + "');";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::FillLigue1Table(PGconn* pg)
{
    FillLeagueTable(pg, int(ELeague::Ligue1));
}

void MatchesInitializer::InitChampionsLeaguePO25_26(PGconn* pg)
{
    std::vector<Match> matches;
    // 1-16 Finals
    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::Galatasaray, ETeam::Juventus, 1771350300000, EWeekType::RoundOf16, false });
    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::Monaco, ETeam::PSG, 1771358400000, EWeekType::RoundOf16, false });
    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::BorussiaDortmund, ETeam::Atalanta, 1771358400000, EWeekType::RoundOf16, false });
    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::Benfica, ETeam::RealMadrid, 1771358400000, EWeekType::RoundOf16, false });
    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::Qarabag, ETeam::NewcastleUnited, 1771436700000, EWeekType::RoundOf16, false });
    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::ClubBrugge, ETeam::AtleticoMadrid, 1771444800000, EWeekType::RoundOf16, false });
    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::BodoGlimt, ETeam::InterMilan, 1771444800000, EWeekType::RoundOf16, false });
    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::Olympiakos, ETeam::BayerLeverkusen, 1771444800000, EWeekType::RoundOf16, false });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::AtleticoMadrid, ETeam::ClubBrugge, 1771955100000, EWeekType::RoundOf16, true });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::BayerLeverkusen, ETeam::Olympiakos, 1771963200000, EWeekType::RoundOf16, true });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::InterMilan, ETeam::BodoGlimt, 1771963200000, EWeekType::RoundOf16, true });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::NewcastleUnited, ETeam::Qarabag, 1771963200000, EWeekType::RoundOf16, true });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::Atalanta, ETeam::BorussiaDortmund, 1772048700000, EWeekType::RoundOf16, true });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::Juventus, ETeam::Galatasaray, 1772049600000, EWeekType::RoundOf16, true });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::PSG, ETeam::Monaco, 1772049600000, EWeekType::RoundOf16, true });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::RealMadrid, ETeam::Benfica, 1772049600000, EWeekType::RoundOf16, true });


    //matches.push_back({ ELeague::ChampionsLeague, "24/25", 10, ETeam::ClubBrugge, ETeam::AstonVilla, 1741110300000, EWeekType::RoundOf8, false });
    //matches.push_back({ ELeague::ChampionsLeague, "24/25", 10, ETeam::BorussiaDortmund, ETeam::Lille, 1741118400000, EWeekType::RoundOf8, false });
    //matches.push_back({ ELeague::ChampionsLeague, "24/25", 10, ETeam::PSV, ETeam::Arsenal, 1741118400000, EWeekType::RoundOf8, false });
    //matches.push_back({ ELeague::ChampionsLeague, "24/25", 10, ETeam::RealMadrid, ETeam::AtleticoMadrid, 1741118400000, EWeekType::RoundOf8, false });
    //matches.push_back({ ELeague::ChampionsLeague, "24/25", 10, ETeam::Feyenoord, ETeam::InterMilan, 1741196700000, EWeekType::RoundOf8, false });
    //matches.push_back({ ELeague::ChampionsLeague, "24/25", 10, ETeam::BayernMunich, ETeam::BayerLeverkusen, 1741204800000, EWeekType::RoundOf8, false });
    //matches.push_back({ ELeague::ChampionsLeague, "24/25", 10, ETeam::Benfica, ETeam::Barcelona, 1741204800000, EWeekType::RoundOf8, false });
    //matches.push_back({ ELeague::ChampionsLeague, "24/25", 10, ETeam::PSG, ETeam::Liverpool, 1741204800000, EWeekType::RoundOf8, false });

   //matches.push_back({ ELeague::ChampionsLeague, "24/25", 10, ETeam::Barcelona, ETeam::Benfica, 1741715100000, EWeekType::RoundOf8, true });
   //matches.push_back({ ELeague::ChampionsLeague, "24/25", 10, ETeam::BayerLeverkusen, ETeam::BayernMunich, 1741723200000, EWeekType::RoundOf8, true });
   //matches.push_back({ ELeague::ChampionsLeague, "24/25", 10, ETeam::InterMilan, ETeam::Feyenoord, 1741723200000, EWeekType::RoundOf8, true });
   //matches.push_back({ ELeague::ChampionsLeague, "24/25", 10, ETeam::Liverpool, ETeam::PSG, 1741723200000, EWeekType::RoundOf8, true });
   //matches.push_back({ ELeague::ChampionsLeague, "24/25", 10, ETeam::Lille, ETeam::BorussiaDortmund, 1741801500000, EWeekType::RoundOf8, true });
   //matches.push_back({ ELeague::ChampionsLeague, "24/25", 10, ETeam::Arsenal, ETeam::PSV, 1741809600000, EWeekType::RoundOf8, true });
   //matches.push_back({ ELeague::ChampionsLeague, "24/25", 10, ETeam::AstonVilla, ETeam::ClubBrugge, 1741809600000, EWeekType::RoundOf8, true });
   //matches.push_back({ ELeague::ChampionsLeague, "24/25", 10, ETeam::AtleticoMadrid, ETeam::RealMadrid, 1741809600000, EWeekType::RoundOf8, true });

   // matches.push_back({ ELeague::ChampionsLeague, "24/25", 11, ETeam::Arsenal, ETeam::RealMadrid, 1744138800000, EWeekType::QuarterFinal, false });
   // matches.push_back({ ELeague::ChampionsLeague, "24/25", 11, ETeam::BayernMunich, ETeam::InterMilan, 1744138800000, EWeekType::QuarterFinal, false });
   // matches.push_back({ ELeague::ChampionsLeague, "24/25", 11, ETeam::Barcelona, ETeam::BorussiaDortmund, 1744225200000, EWeekType::QuarterFinal, false });
   // matches.push_back({ ELeague::ChampionsLeague, "24/25", 11, ETeam::PSG, ETeam::AstonVilla, 1744225200000, EWeekType::QuarterFinal, false });

   // matches.push_back({ ELeague::ChampionsLeague, "24/25", 11, ETeam::AstonVilla, ETeam::PSG, 1744743600000, EWeekType::QuarterFinal, true });
   // matches.push_back({ ELeague::ChampionsLeague, "24/25", 11, ETeam::BorussiaDortmund, ETeam::Barcelona, 1744743600000, EWeekType::QuarterFinal, true });
   // matches.push_back({ ELeague::ChampionsLeague, "24/25", 11, ETeam::InterMilan, ETeam::BayernMunich, 1744830000000, EWeekType::QuarterFinal, true });
   // matches.push_back({ ELeague::ChampionsLeague, "24/25", 11, ETeam::RealMadrid, ETeam::Arsenal, 1744830000000, EWeekType::QuarterFinal, true });

  //  matches.push_back({ ELeague::ChampionsLeague, "24/25", 12, ETeam::Arsenal, ETeam::PSG, 1745953200000, EWeekType::SemiFinal, false });
   // matches.push_back({ ELeague::ChampionsLeague, "24/25", 12, ETeam::Barcelona, ETeam::InterMilan, 1746039600000, EWeekType::SemiFinal, false });

   // matches.push_back({ ELeague::ChampionsLeague, "24/25", 12, ETeam::InterMilan, ETeam::Barcelona, 1746558000000, EWeekType::SemiFinal, true });
   // matches.push_back({ ELeague::ChampionsLeague, "24/25", 12, ETeam::PSG, ETeam::Arsenal, 1746644400000, EWeekType::SemiFinal, true });

  //  matches.push_back({ ELeague::ChampionsLeague, "24/25", 13, ETeam::PSG, ETeam::InterMilan, 1748718000000, EWeekType::Final, true });
  //  matches.push_back({ ELeague::EuropaLeague, "24/25", 1, ETeam::TottenhamHotspur, ETeam::ManchesterUnited, 1747854000000, EWeekType::Final, true });
  //  matches.push_back({ ELeague::ConferenceLeague, "24/25", 1, ETeam::RealBetis, ETeam::Chelsea, 1748458800000, EWeekType::Final, true });


    for (auto& m : matches)
    {
        std::string sql = "insert into matches(league, season, week, week_type, team1, team2, match_date, play_off) values ("
            + std::to_string(int(m.League)) + ", '"
            + m.Season + "', "
            + std::to_string(m.Week) + ", "
            + std::to_string((int)m.WeekType) + ", "
            + std::to_string((int)m.Team1) + ", "
            + std::to_string((int)m.Team2) + ", "
            + std::to_string(m.Date) + ", "
            + std::to_string((int)m.PlayOff) + ""
            + ");";

        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitChampionsLeague25_26(PGconn* pg)
{
    std::vector<Match> matches;
    // Week 1
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 1, ETeam::PSV, ETeam::UnionSG, 1758041100000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 1, ETeam::AthleticClub, ETeam::Arsenal, 1758041100000 });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 1, ETeam::Juventus, ETeam::BorussiaDortmund, 1758049200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 1, ETeam::TottenhamHotspur, ETeam::Villarreal, 1758049200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 1, ETeam::RealMadrid, ETeam::Marseille, 1758049200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 1, ETeam::Benfica, ETeam::Qarabag, 1758049200000 });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 1, ETeam::Olympiakos, ETeam::Pafos, 1758127500000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 1, ETeam::Slavia, ETeam::BodoGlimt, 1758127500000 });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 1, ETeam::Ajax, ETeam::InterMilan, 1758135600000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 1, ETeam::PSG, ETeam::Atalanta, 1758135600000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 1, ETeam::Liverpool, ETeam::AtleticoMadrid, 1758135600000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 1, ETeam::BayernMunich, ETeam::Chelsea, 1758135600000 });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 1, ETeam::ClubBrugge, ETeam::Monaco, 1758213900000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 1, ETeam::Copenhagen, ETeam::BayerLeverkusen, 1758213900000 });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 1, ETeam::EintrachtFrankfurt, ETeam::Galatasaray, 1758222000000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 1, ETeam::SportingLisbon, ETeam::Kairat, 1758222000000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 1, ETeam::NewcastleUnited, ETeam::Barcelona, 1758222000000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 1, ETeam::ManchesterCity, ETeam::Napoli, 1758222000000 });

    // Week 2
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 2, ETeam::Kairat, ETeam::RealMadrid, 1759250700000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 2, ETeam::Atalanta, ETeam::ClubBrugge, 1759250700000 });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 2, ETeam::AtleticoMadrid, ETeam::EintrachtFrankfurt, 1759258800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 2, ETeam::Marseille, ETeam::Ajax, 1759258800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 2, ETeam::Chelsea, ETeam::Benfica, 1759258800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 2, ETeam::InterMilan, ETeam::Slavia, 1759258800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 2, ETeam::BodoGlimt, ETeam::TottenhamHotspur, 1759258800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 2, ETeam::Pafos, ETeam::BayernMunich, 1759258800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 2, ETeam::Galatasaray, ETeam::Liverpool, 1759258800000 });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 2, ETeam::Qarabag, ETeam::Copenhagen, 1759337100000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 2, ETeam::UnionSG, ETeam::NewcastleUnited, 1759337100000 });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 2, ETeam::BorussiaDortmund, ETeam::AthleticClub, 1759345200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 2, ETeam::Barcelona, ETeam::PSG, 1759345200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 2, ETeam::Monaco, ETeam::ManchesterCity, 1759345200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 2, ETeam::Arsenal, ETeam::Olympiakos, 1759345200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 2, ETeam::Napoli, ETeam::SportingLisbon, 1759345200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 2, ETeam::BayerLeverkusen, ETeam::PSV, 1759345200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 2, ETeam::Villarreal, ETeam::Juventus, 1759345200000 });

    // Week 3
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 3, ETeam::Kairat, ETeam::Pafos, 1761065100000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 3, ETeam::Barcelona, ETeam::Olympiakos, 1761065100000 });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 3, ETeam::UnionSG, ETeam::InterMilan, 1761073200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 3, ETeam::PSV, ETeam::Napoli, 1761073200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 3, ETeam::BayerLeverkusen, ETeam::PSG, 1761073200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 3, ETeam::Arsenal, ETeam::AtleticoMadrid, 1761073200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 3, ETeam::Copenhagen, ETeam::BorussiaDortmund, 1761073200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 3, ETeam::Villarreal, ETeam::ManchesterCity, 1761073200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 3, ETeam::NewcastleUnited, ETeam::Benfica, 1761073200000 });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 3, ETeam::Galatasaray, ETeam::BodoGlimt, 1761151500000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 3, ETeam::AthleticClub, ETeam::Qarabag, 1761151500000 });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 3, ETeam::Monaco, ETeam::TottenhamHotspur, 1761159600000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 3, ETeam::RealMadrid, ETeam::Juventus, 1761159600000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 3, ETeam::EintrachtFrankfurt, ETeam::Liverpool, 1761159600000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 3, ETeam::Chelsea, ETeam::Ajax, 1761159600000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 3, ETeam::Atalanta, ETeam::Slavia, 1761159600000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 3, ETeam::SportingLisbon, ETeam::Marseille, 1761159600000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 3, ETeam::BayernMunich, ETeam::ClubBrugge, 1761159600000 });

    // Week 4
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 4, ETeam::Napoli, ETeam::EintrachtFrankfurt, 1762278300000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 4, ETeam::Slavia, ETeam::Arsenal, 1762278300000 });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 4, ETeam::TottenhamHotspur, ETeam::Copenhagen, 1762286400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 4, ETeam::Liverpool, ETeam::RealMadrid, 1762286400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 4, ETeam::Olympiakos, ETeam::PSV, 1762286400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 4, ETeam::AtleticoMadrid, ETeam::UnionSG, 1762286400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 4, ETeam::BodoGlimt, ETeam::Monaco, 1762286400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 4, ETeam::PSG, ETeam::BayernMunich, 1762286400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 4, ETeam::Juventus, ETeam::SportingLisbon, 1762286400000 });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 4, ETeam::Qarabag, ETeam::Chelsea, 1762364700000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 4, ETeam::Pafos, ETeam::Villarreal, 1762364700000 });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 4, ETeam::ManchesterCity, ETeam::BorussiaDortmund, 1762372800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 4, ETeam::ClubBrugge, ETeam::Barcelona, 1762372800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 4, ETeam::Ajax, ETeam::Galatasaray, 1762372800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 4, ETeam::NewcastleUnited, ETeam::AthleticClub, 1762372800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 4, ETeam::Benfica, ETeam::BayerLeverkusen, 1762372800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 4, ETeam::InterMilan, ETeam::Kairat, 1762372800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 4, ETeam::Marseille, ETeam::Atalanta, 1762372800000 });

    // Week 5
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 5, ETeam::Ajax, ETeam::Benfica, 1764092700000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 5, ETeam::Galatasaray, ETeam::UnionSG, 1764092700000 });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 5, ETeam::ManchesterCity, ETeam::BayerLeverkusen, 1764100800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 5, ETeam::Marseille, ETeam::NewcastleUnited, 1764100800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 5, ETeam::Chelsea, ETeam::Barcelona, 1764100800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 5, ETeam::Napoli, ETeam::Qarabag, 1764100800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 5, ETeam::BorussiaDortmund, ETeam::Villarreal, 1764100800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 5, ETeam::Slavia, ETeam::AthleticClub, 1764100800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 5, ETeam::BodoGlimt, ETeam::Juventus, 1764100800000 });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 5, ETeam::Copenhagen, ETeam::Kairat, 1764179100000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 5, ETeam::Pafos, ETeam::Monaco, 1764179100000 });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 5, ETeam::Olympiakos, ETeam::RealMadrid, 1764187200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 5, ETeam::AtleticoMadrid, ETeam::InterMilan, 1764187200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 5, ETeam::PSG, ETeam::TottenhamHotspur, 1764187200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 5, ETeam::SportingLisbon, ETeam::ClubBrugge, 1764187200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 5, ETeam::Arsenal, ETeam::BayernMunich, 1764187200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 5, ETeam::EintrachtFrankfurt, ETeam::Atalanta, 1764187200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 5, ETeam::Liverpool, ETeam::PSV, 1764187200000 });

    // Week 6
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 6, ETeam::Kairat, ETeam::Olympiakos, 1765302300000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 6, ETeam::BayernMunich, ETeam::SportingLisbon, 1765302300000 });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 6, ETeam::Barcelona, ETeam::EintrachtFrankfurt, 1765310400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 6, ETeam::InterMilan, ETeam::Liverpool, 1765310400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 6, ETeam::Atalanta, ETeam::Chelsea, 1765310400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 6, ETeam::UnionSG, ETeam::Marseille, 1765310400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 6, ETeam::Monaco, ETeam::Galatasaray, 1765310400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 6, ETeam::TottenhamHotspur, ETeam::Slavia, 1765310400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 6, ETeam::PSV, ETeam::AtleticoMadrid, 1765310400000 });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 6, ETeam::Villarreal, ETeam::Copenhagen, 1765388700000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 6, ETeam::Qarabag, ETeam::Ajax, 1765388700000 });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 6, ETeam::RealMadrid, ETeam::ManchesterCity, 1765396800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 6, ETeam::AthleticClub, ETeam::PSG, 1765396800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 6, ETeam::ClubBrugge, ETeam::Arsenal, 1765396800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 6, ETeam::BayerLeverkusen, ETeam::NewcastleUnited, 1765396800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 6, ETeam::Juventus, ETeam::Pafos, 1765396800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 6, ETeam::BorussiaDortmund, ETeam::BodoGlimt, 1765396800000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 6, ETeam::Benfica, ETeam::Napoli, 1765396800000 });

    // Week 7
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 7, ETeam::Kairat, ETeam::ClubBrugge, 1768931100000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 7, ETeam::BodoGlimt, ETeam::ManchesterCity, 1768931100000 });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 7, ETeam::RealMadrid, ETeam::Monaco, 1768939200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 7, ETeam::SportingLisbon, ETeam::PSG, 1768939200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 7, ETeam::Copenhagen, ETeam::Napoli, 1768939200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 7, ETeam::Villarreal, ETeam::Ajax, 1768939200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 7, ETeam::Olympiakos, ETeam::BayerLeverkusen, 1768939200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 7, ETeam::TottenhamHotspur, ETeam::BorussiaDortmund, 1768939200000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 7, ETeam::InterMilan, ETeam::Arsenal, 1768939200000 });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 7, ETeam::Galatasaray, ETeam::AtleticoMadrid, 1769017500000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 7, ETeam::Qarabag, ETeam::EintrachtFrankfurt, 1769017500000 });

    matches.push_back({ ELeague::ChampionsLeague, "25/26", 7, ETeam::Slavia, ETeam::Barcelona, 1769025600000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 7, ETeam::Atalanta, ETeam::AthleticClub, 1769025600000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 7, ETeam::Juventus, ETeam::Benfica, 1769025600000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 7, ETeam::Chelsea, ETeam::Pafos, 1769025600000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 7, ETeam::NewcastleUnited, ETeam::PSV, 1769025600000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 7, ETeam::BayernMunich, ETeam::UnionSG, 1769025600000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 7, ETeam::Marseille, ETeam::Liverpool, 1769025600000 });

    // Week 8
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 8, ETeam::Napoli, ETeam::Chelsea, 1769630400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 8, ETeam::BorussiaDortmund, ETeam::InterMilan, 1769630400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 8, ETeam::Monaco, ETeam::Juventus, 1769630400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 8, ETeam::PSG, ETeam::NewcastleUnited, 1769630400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 8, ETeam::EintrachtFrankfurt, ETeam::TottenhamHotspur, 1769630400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 8, ETeam::Pafos, ETeam::Slavia, 1769630400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 8, ETeam::AtleticoMadrid, ETeam::BodoGlimt, 1769630400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 8, ETeam::ManchesterCity, ETeam::Galatasaray, 1769630400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 8, ETeam::PSV, ETeam::BayernMunich, 1769630400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 8, ETeam::BayerLeverkusen, ETeam::Villarreal, 1769630400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 8, ETeam::AthleticClub, ETeam::SportingLisbon, 1769630400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 8, ETeam::Ajax, ETeam::Olympiakos, 1769630400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 8, ETeam::UnionSG, ETeam::Atalanta, 1769630400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 8, ETeam::Arsenal, ETeam::Kairat, 1769630400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 8, ETeam::Liverpool, ETeam::Qarabag, 1769630400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 8, ETeam::Barcelona, ETeam::Copenhagen, 1769630400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 8, ETeam::Benfica, ETeam::RealMadrid, 1769630400000 });
    matches.push_back({ ELeague::ChampionsLeague, "25/26", 8, ETeam::ClubBrugge, ETeam::Marseille, 1769630400000 });

    for (auto& m : matches)
    {
        std::string sql = "insert into matches(league, season, week, team1, team2, match_date) values ("
            + std::to_string(int(m.League)) + ", '"
            + m.Season + "', "
            + std::to_string(m.Week) + ", "
            + std::to_string((int)m.Team1) + ", "
            + std::to_string((int)m.Team2) + ", "
            + std::to_string(m.Date) + ");";

        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}


void MatchesInitializer::InitLigue125_26(PGconn* pg)
{
    std::vector<Match> matches;
    // Week 1
    matches.push_back({ ELeague::Ligue1, "25/26", 1, ETeam::Nantes, ETeam::PSG, 1755442800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 1, ETeam::Brest, ETeam::Lille, 1755442800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 1, ETeam::Monaco, ETeam::LeHavre, 1755442800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 1, ETeam::Auxerre, ETeam::Lorient, 1755442800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 1, ETeam::Metz, ETeam::Strasbourg, 1755442800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 1, ETeam::Rennes, ETeam::Marseille, 1755442800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 1, ETeam::Angers, ETeam::ParisFC, 1755442800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 1, ETeam::Lens, ETeam::Lyon, 1755442800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 1, ETeam::Nice, ETeam::Toulouse, 1755442800000 });

    // Week 2
    matches.push_back({ ELeague::Ligue1, "25/26", 2, ETeam::Toulouse, ETeam::Brest, 1756047600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 2, ETeam::Lorient, ETeam::Rennes, 1756047600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 2, ETeam::Lille, ETeam::Monaco, 1756047600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 2, ETeam::Nice, ETeam::Auxerre, 1756047600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 2, ETeam::PSG, ETeam::Angers, 1756047600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 2, ETeam::Strasbourg, ETeam::Nantes, 1756047600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 2, ETeam::LeHavre, ETeam::Lens, 1756047600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 2, ETeam::Lyon, ETeam::Metz, 1756047600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 2, ETeam::Marseille, ETeam::ParisFC, 1756047600000 });

    // Week 3
    matches.push_back({ ELeague::Ligue1, "25/26", 3, ETeam::Toulouse, ETeam::PSG, 1756652400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 3, ETeam::LeHavre, ETeam::Nice, 1756652400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 3, ETeam::Lyon, ETeam::Marseille, 1756652400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 3, ETeam::Nantes, ETeam::Auxerre, 1756652400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 3, ETeam::Lens, ETeam::Brest, 1756652400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 3, ETeam::Lorient, ETeam::Lille, 1756652400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 3, ETeam::Angers, ETeam::Rennes, 1756652400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 3, ETeam::Monaco, ETeam::Strasbourg, 1756652400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 3, ETeam::ParisFC, ETeam::Metz, 1756652400000 });

    // Week 4
    matches.push_back({ ELeague::Ligue1, "25/26", 4, ETeam::Brest, ETeam::ParisFC, 1757862000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 4, ETeam::Marseille, ETeam::Lorient, 1757862000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 4, ETeam::Metz, ETeam::Angers, 1757862000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 4, ETeam::Strasbourg, ETeam::LeHavre, 1757862000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 4, ETeam::Lille, ETeam::Toulouse, 1757862000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 4, ETeam::PSG, ETeam::Lens, 1757862000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 4, ETeam::Rennes, ETeam::Lyon, 1757862000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 4, ETeam::Auxerre, ETeam::Monaco, 1757862000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 4, ETeam::Nice, ETeam::Nantes, 1757862000000 });

    // Week 5
    matches.push_back({ ELeague::Ligue1, "25/26", 5, ETeam::Auxerre, ETeam::Toulouse, 1758466800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 5, ETeam::Monaco, ETeam::Metz, 1758466800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 5, ETeam::Lyon, ETeam::Angers, 1758466800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 5, ETeam::LeHavre, ETeam::Lorient, 1758466800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 5, ETeam::Brest, ETeam::Nice, 1758466800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 5, ETeam::Lens, ETeam::Lille, 1758466800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 5, ETeam::Marseille, ETeam::PSG, 1758466800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 5, ETeam::Nantes, ETeam::Rennes, 1758466800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 5, ETeam::ParisFC, ETeam::Strasbourg, 1758466800000 });

    // Week 6
    matches.push_back({ ELeague::Ligue1, "25/26", 6, ETeam::Rennes, ETeam::Lens, 1759071600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 6, ETeam::Nice, ETeam::ParisFC, 1759071600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 6, ETeam::Strasbourg, ETeam::Marseille, 1759071600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 6, ETeam::Angers, ETeam::Brest, 1759071600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 6, ETeam::Lille, ETeam::Lyon, 1759071600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 6, ETeam::Metz, ETeam::LeHavre, 1759071600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 6, ETeam::Toulouse, ETeam::Nantes, 1759071600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 6, ETeam::Lorient, ETeam::Monaco, 1759071600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 6, ETeam::PSG, ETeam::Auxerre, 1759071600000 });

    // Week 7
    matches.push_back({ ELeague::Ligue1, "25/26", 7, ETeam::Lyon, ETeam::Toulouse, 1759676400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 7, ETeam::Lille, ETeam::PSG, 1759676400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 7, ETeam::Auxerre, ETeam::Lens, 1759676400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 7, ETeam::Strasbourg, ETeam::Angers, 1759676400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 7, ETeam::LeHavre, ETeam::Rennes, 1759676400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 7, ETeam::Metz, ETeam::Marseille, 1759676400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 7, ETeam::Brest, ETeam::Nantes, 1759676400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 7, ETeam::Monaco, ETeam::Nice, 1759676400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 7, ETeam::ParisFC, ETeam::Lorient, 1759676400000 });

    // Week 8
    matches.push_back({ ELeague::Ligue1, "25/26", 8, ETeam::PSG, ETeam::Strasbourg, 1760886000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 8, ETeam::Nantes, ETeam::Lille, 1760886000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 8, ETeam::Marseille, ETeam::LeHavre, 1760886000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 8, ETeam::Lorient, ETeam::Brest, 1760886000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 8, ETeam::Rennes, ETeam::Auxerre, 1760886000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 8, ETeam::Angers, ETeam::Monaco, 1760886000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 8, ETeam::Toulouse, ETeam::Metz, 1760886000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 8, ETeam::Lens, ETeam::ParisFC, 1760886000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 8, ETeam::Nice, ETeam::Lyon, 1760886000000 });

    // Week 9
    matches.push_back({ ELeague::Ligue1, "25/26", 9, ETeam::Lyon, ETeam::Strasbourg, 1761490800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 9, ETeam::Lens, ETeam::Marseille, 1761490800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 9, ETeam::Auxerre, ETeam::LeHavre, 1761490800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 9, ETeam::Monaco, ETeam::Toulouse, 1761490800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 9, ETeam::Lille, ETeam::Metz, 1761490800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 9, ETeam::Brest, ETeam::PSG, 1761490800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 9, ETeam::Rennes, ETeam::Nice, 1761490800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 9, ETeam::Angers, ETeam::Lorient, 1761490800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 9, ETeam::ParisFC, ETeam::Nantes, 1761490800000 });

    // Week 10
    matches.push_back({ ELeague::Ligue1, "25/26", 10, ETeam::LeHavre, ETeam::Brest, 1761750000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 10, ETeam::ParisFC, ETeam::Lyon, 1761750000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 10, ETeam::Toulouse, ETeam::Rennes, 1761750000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 10, ETeam::Marseille, ETeam::Angers, 1761750000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 10, ETeam::Lorient, ETeam::PSG, 1761750000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 10, ETeam::Nice, ETeam::Lille, 1761750000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 10, ETeam::Nantes, ETeam::Monaco, 1761750000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 10, ETeam::Strasbourg, ETeam::Auxerre, 1761750000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 10, ETeam::Metz, ETeam::Lens, 1761750000000 });

    // Week 11
    matches.push_back({ ELeague::Ligue1, "25/26", 11, ETeam::Nantes, ETeam::Metz, 1762095600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 11, ETeam::Toulouse, ETeam::LeHavre, 1762095600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 11, ETeam::Lille, ETeam::Angers, 1762095600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 11, ETeam::PSG, ETeam::Nice, 1762095600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 11, ETeam::Monaco, ETeam::ParisFC, 1762095600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 11, ETeam::Brest, ETeam::Lyon, 1762095600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 11, ETeam::Lens, ETeam::Lorient, 1762095600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 11, ETeam::Auxerre, ETeam::Marseille, 1762095600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 11, ETeam::Rennes, ETeam::Strasbourg, 1762095600000 });

    // Week 12
    matches.push_back({ ELeague::Ligue1, "25/26", 12, ETeam::Marseille, ETeam::Brest, 1762700400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 12, ETeam::Angers, ETeam::Auxerre, 1762700400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 12, ETeam::Lorient, ETeam::Toulouse, 1762700400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 12, ETeam::Lyon, ETeam::PSG, 1762700400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 12, ETeam::Metz, ETeam::Nice, 1762700400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 12, ETeam::Monaco, ETeam::Lens, 1762700400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 12, ETeam::ParisFC, ETeam::Rennes, 1762700400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 12, ETeam::LeHavre, ETeam::Nantes, 1762700400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 12, ETeam::Strasbourg, ETeam::Lille, 1762700400000 });

    // Week 13
    matches.push_back({ ELeague::Ligue1, "25/26", 13, ETeam::Lille, ETeam::ParisFC, 1763910000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 13, ETeam::Toulouse, ETeam::Angers, 1763910000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 13, ETeam::Nantes, ETeam::Lorient, 1763910000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 13, ETeam::PSG, ETeam::LeHavre, 1763910000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 13, ETeam::Rennes, ETeam::Monaco, 1763910000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 13, ETeam::Lens, ETeam::Strasbourg, 1763910000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 13, ETeam::Brest, ETeam::Metz, 1763910000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 13, ETeam::Auxerre, ETeam::Lyon, 1763910000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 13, ETeam::Nice, ETeam::Marseille, 1763910000000 });

    // Week 14
    matches.push_back({ ELeague::Ligue1, "25/26", 14, ETeam::Angers, ETeam::Lens, 1764514800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 14, ETeam::Lorient, ETeam::Nice, 1764514800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 14, ETeam::Lyon, ETeam::Nantes, 1764514800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 14, ETeam::Marseille, ETeam::Toulouse, 1764514800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 14, ETeam::Monaco, ETeam::PSG, 1764514800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 14, ETeam::Metz, ETeam::Rennes, 1764514800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 14, ETeam::LeHavre, ETeam::Lille, 1764514800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 14, ETeam::Strasbourg, ETeam::Brest, 1764514800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 14, ETeam::ParisFC, ETeam::Auxerre, 1764514800000 });

    // Week 15
    matches.push_back({ ELeague::Ligue1, "25/26", 15, ETeam::Nice, ETeam::Angers, 1765119600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 15, ETeam::Toulouse, ETeam::Strasbourg, 1765119600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 15, ETeam::Lorient, ETeam::Lyon, 1765119600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 15, ETeam::Auxerre, ETeam::Metz, 1765119600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 15, ETeam::PSG, ETeam::Rennes, 1765119600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 15, ETeam::Lille, ETeam::Marseille, 1765119600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 15, ETeam::LeHavre, ETeam::ParisFC, 1765119600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 15, ETeam::Brest, ETeam::Monaco, 1765119600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 15, ETeam::Nantes, ETeam::Lens, 1765119600000 });

    // Week 16
    matches.push_back({ ELeague::Ligue1, "25/26", 16, ETeam::Angers, ETeam::Nantes, 1765724400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 16, ETeam::Strasbourg, ETeam::Lorient, 1765724400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 16, ETeam::Lyon, ETeam::LeHavre, 1765724400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 16, ETeam::Rennes, ETeam::Brest, 1765724400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 16, ETeam::Marseille, ETeam::Monaco, 1765724400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 16, ETeam::Lens, ETeam::Nice, 1765724400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 16, ETeam::Metz, ETeam::PSG, 1765724400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 16, ETeam::Auxerre, ETeam::Lille, 1765724400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 16, ETeam::ParisFC, ETeam::Toulouse, 1765724400000 });

    // Week 17
    matches.push_back({ ELeague::Ligue1, "25/26", 17, ETeam::Lorient, ETeam::Metz, 1767538800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 17, ETeam::Marseille, ETeam::Nantes, 1767538800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 17, ETeam::PSG, ETeam::ParisFC, 1767538800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 17, ETeam::Brest, ETeam::Auxerre, 1767538800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 17, ETeam::Monaco, ETeam::Lyon, 1767538800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 17, ETeam::Lille, ETeam::Rennes, 1767538800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 17, ETeam::LeHavre, ETeam::Angers, 1767538800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 17, ETeam::Nice, ETeam::Strasbourg, 1767538800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 17, ETeam::Toulouse, ETeam::Lens, 1767538800000 });

    // Week 18
    matches.push_back({ ELeague::Ligue1, "25/26", 18, ETeam::Lens, ETeam::Auxerre, 1768748400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 18, ETeam::PSG, ETeam::Lille, 1768748400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 18, ETeam::Lyon, ETeam::Brest, 1768748400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 18, ETeam::Nantes, ETeam::ParisFC, 1768748400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 18, ETeam::Strasbourg, ETeam::Metz, 1768748400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 18, ETeam::Toulouse, ETeam::Nice, 1768748400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 18, ETeam::Rennes, ETeam::LeHavre, 1768748400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 18, ETeam::Angers, ETeam::Marseille, 1768748400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 18, ETeam::Monaco, ETeam::Lorient, 1768748400000 });

    // Week 19
    matches.push_back({ ELeague::Ligue1, "25/26", 19, ETeam::LeHavre, ETeam::Monaco, 1769353200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 19, ETeam::Rennes, ETeam::Lorient, 1769353200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 19, ETeam::Marseille, ETeam::Lens, 1769353200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 19, ETeam::ParisFC, ETeam::Angers, 1769353200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 19, ETeam::Nantes, ETeam::Nice, 1769353200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 19, ETeam::Brest, ETeam::Toulouse, 1769353200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 19, ETeam::Lille, ETeam::Strasbourg, 1769353200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 19, ETeam::Metz, ETeam::Lyon, 1769353200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 19, ETeam::Auxerre, ETeam::PSG, 1769353200000 });

    // Week 20
    matches.push_back({ ELeague::Ligue1, "25/26", 20, ETeam::Angers, ETeam::Metz, 1769958000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 20, ETeam::Toulouse, ETeam::Auxerre, 1769958000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 20, ETeam::Lyon, ETeam::Lille, 1769958000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 20, ETeam::Strasbourg, ETeam::PSG, 1769958000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 20, ETeam::Lens, ETeam::LeHavre, 1769958000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 20, ETeam::Nice, ETeam::Brest, 1769958000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 20, ETeam::ParisFC, ETeam::Marseille, 1769958000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 20, ETeam::Lorient, ETeam::Nantes, 1769958000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 20, ETeam::Monaco, ETeam::Rennes, 1769958000000 });

    // Week 21
    matches.push_back({ ELeague::Ligue1, "25/26", 21, ETeam::Metz, ETeam::Lille, 1770562800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 21, ETeam::Angers, ETeam::Toulouse, 1770562800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 21, ETeam::Lens, ETeam::Rennes, 1770562800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 21, ETeam::LeHavre, ETeam::Strasbourg, 1770562800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 21, ETeam::Auxerre, ETeam::ParisFC, 1770562800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 21, ETeam::Brest, ETeam::Lorient, 1770562800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 21, ETeam::PSG, ETeam::Marseille, 1770562800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 21, ETeam::Nantes, ETeam::Lyon, 1770562800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 21, ETeam::Nice, ETeam::Monaco, 1770562800000 });

    // Week 22
    matches.push_back({ ELeague::Ligue1, "25/26", 22, ETeam::Lorient, ETeam::Angers, 1771167600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 22, ETeam::Lyon, ETeam::Nice, 1771167600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 22, ETeam::Monaco, ETeam::Nantes, 1771167600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 22, ETeam::Lille, ETeam::Brest, 1771167600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 22, ETeam::Marseille, ETeam::Strasbourg, 1771167600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 22, ETeam::Metz, ETeam::Auxerre, 1771167600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 22, ETeam::ParisFC, ETeam::Lens, 1771167600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 22, ETeam::Rennes, ETeam::PSG, 1771167600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 22, ETeam::LeHavre, ETeam::Toulouse, 1771167600000 });

    // Week 23
    matches.push_back({ ELeague::Ligue1, "25/26", 23, ETeam::Lens, ETeam::Monaco, 1771772400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 23, ETeam::Brest, ETeam::Marseille, 1771772400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 23, ETeam::Angers, ETeam::Lille, 1771772400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 23, ETeam::PSG, ETeam::Metz, 1771772400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 23, ETeam::Strasbourg, ETeam::Lyon, 1771772400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 23, ETeam::Nantes, ETeam::LeHavre, 1771772400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 23, ETeam::Auxerre, ETeam::Rennes, 1771772400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 23, ETeam::Toulouse, ETeam::ParisFC, 1771772400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 23, ETeam::Nice, ETeam::Lorient, 1771772400000 });

    // Week 24
    matches.push_back({ ELeague::Ligue1, "25/26", 24, ETeam::Monaco, ETeam::Angers, 1772377200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 24, ETeam::Rennes, ETeam::Toulouse, 1772377200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 24, ETeam::ParisFC, ETeam::Nice, 1772377200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 24, ETeam::Strasbourg, ETeam::Lens, 1772377200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 24, ETeam::Marseille, ETeam::Lyon, 1772377200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 24, ETeam::LeHavre, ETeam::PSG, 1772377200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 24, ETeam::Lille, ETeam::Nantes, 1772377200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 24, ETeam::Lorient, ETeam::Auxerre, 1772377200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 24, ETeam::Metz, ETeam::Brest, 1772377200000 });

    // Week 25
    matches.push_back({ ELeague::Ligue1, "25/26", 25, ETeam::Nantes, ETeam::Angers, 1772982000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 25, ETeam::PSG, ETeam::Monaco, 1772982000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 25, ETeam::Auxerre, ETeam::Strasbourg, 1772982000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 25, ETeam::Lyon, ETeam::ParisFC, 1772982000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 25, ETeam::Toulouse, ETeam::Marseille, 1772982000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 25, ETeam::Lille, ETeam::Lorient, 1772982000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 25, ETeam::Lens, ETeam::Metz, 1772982000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 25, ETeam::Nice, ETeam::Rennes, 1772982000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 25, ETeam::Brest, ETeam::LeHavre, 1772982000000 });

    // Week 26
    matches.push_back({ ELeague::Ligue1, "25/26", 26, ETeam::Marseille, ETeam::Auxerre, 1773586800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 26, ETeam::LeHavre, ETeam::Lyon, 1773586800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 26, ETeam::Monaco, ETeam::Brest, 1773586800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 26, ETeam::Rennes, ETeam::Lille, 1773586800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 26, ETeam::Lorient, ETeam::Lens, 1773586800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 26, ETeam::Metz, ETeam::Toulouse, 1773586800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 26, ETeam::Angers, ETeam::Nice, 1773586800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 26, ETeam::PSG, ETeam::Nantes, 1773586800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 26, ETeam::Strasbourg, ETeam::ParisFC, 1773586800000 });

    // Week 27
    matches.push_back({ ELeague::Ligue1, "25/26", 27, ETeam::Toulouse, ETeam::Lorient, 1774191600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 27, ETeam::Lyon, ETeam::Monaco, 1774191600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 27, ETeam::Nantes, ETeam::Strasbourg, 1774191600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 27, ETeam::ParisFC, ETeam::LeHavre, 1774191600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 27, ETeam::Marseille, ETeam::Lille, 1774191600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 27, ETeam::Auxerre, ETeam::Brest, 1774191600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 27, ETeam::Nice, ETeam::PSG, 1774191600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 27, ETeam::Rennes, ETeam::Metz, 1774191600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 27, ETeam::Lens, ETeam::Angers, 1774191600000 });

    // Week 28
    matches.push_back({ ELeague::Ligue1, "25/26", 28, ETeam::Monaco, ETeam::Marseille, 1775401200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 28, ETeam::Metz, ETeam::Nantes, 1775401200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 28, ETeam::Brest, ETeam::Rennes, 1775401200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 28, ETeam::LeHavre, ETeam::Auxerre, 1775401200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 28, ETeam::Lorient, ETeam::ParisFC, 1775401200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 28, ETeam::Lille, ETeam::Lens, 1775401200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 28, ETeam::Strasbourg, ETeam::Nice, 1775401200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 28, ETeam::PSG, ETeam::Toulouse, 1775401200000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 28, ETeam::Angers, ETeam::Lyon, 1775401200000 });

    // Week 29
    matches.push_back({ ELeague::Ligue1, "25/26", 29, ETeam::Nice, ETeam::LeHavre, 1776006000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 29, ETeam::Toulouse, ETeam::Lille, 1776006000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 29, ETeam::Brest, ETeam::Strasbourg, 1776006000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 29, ETeam::Lyon, ETeam::Lorient, 1776006000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 29, ETeam::ParisFC, ETeam::Monaco, 1776006000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 29, ETeam::Auxerre, ETeam::Nantes, 1776006000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 29, ETeam::Lens, ETeam::PSG, 1776006000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 29, ETeam::Rennes, ETeam::Angers, 1776006000000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 29, ETeam::Marseille, ETeam::Metz, 1776006000000 });

    // Week 30
    matches.push_back({ ELeague::Ligue1, "25/26", 30, ETeam::Lille, ETeam::Nice, 1776610800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 30, ETeam::Metz, ETeam::ParisFC, 1776610800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 30, ETeam::Strasbourg, ETeam::Rennes, 1776610800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 30, ETeam::Lorient, ETeam::Marseille, 1776610800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 30, ETeam::PSG, ETeam::Lyon, 1776610800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 30, ETeam::Lens, ETeam::Toulouse, 1776610800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 30, ETeam::Angers, ETeam::LeHavre, 1776610800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 30, ETeam::Nantes, ETeam::Brest, 1776610800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 30, ETeam::Monaco, ETeam::Auxerre, 1776610800000 });

    // Week 31
    matches.push_back({ ELeague::Ligue1, "25/26", 31, ETeam::Rennes, ETeam::Nantes, 1777215600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 31, ETeam::Toulouse, ETeam::Monaco, 1777215600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 31, ETeam::Angers, ETeam::PSG, 1777215600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 31, ETeam::LeHavre, ETeam::Metz, 1777215600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 31, ETeam::Brest, ETeam::Lens, 1777215600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 31, ETeam::Lyon, ETeam::Auxerre, 1777215600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 31, ETeam::Marseille, ETeam::Nice, 1777215600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 31, ETeam::Lorient, ETeam::Strasbourg, 1777215600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 31, ETeam::ParisFC, ETeam::Lille, 1777215600000 });

    // Week 32
    matches.push_back({ ELeague::Ligue1, "25/26", 32, ETeam::PSG, ETeam::Lorient, 1777820400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 32, ETeam::Lille, ETeam::LeHavre, 1777820400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 32, ETeam::Auxerre, ETeam::Angers, 1777820400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 32, ETeam::Metz, ETeam::Monaco, 1777820400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 32, ETeam::Strasbourg, ETeam::Toulouse, 1777820400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 32, ETeam::Nice, ETeam::Lens, 1777820400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 32, ETeam::Nantes, ETeam::Marseille, 1777820400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 32, ETeam::ParisFC, ETeam::Brest, 1777820400000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 32, ETeam::Lyon, ETeam::Rennes, 1777820400000 });

    // Week 33
    matches.push_back({ ELeague::Ligue1, "25/26", 33, ETeam::Metz, ETeam::Lorient, 1778338800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 33, ETeam::Rennes, ETeam::ParisFC, 1778338800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 33, ETeam::Auxerre, ETeam::Nice, 1778338800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 33, ETeam::LeHavre, ETeam::Marseille, 1778338800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 33, ETeam::Angers, ETeam::Strasbourg, 1778338800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 33, ETeam::PSG, ETeam::Brest, 1778338800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 33, ETeam::Monaco, ETeam::Lille, 1778338800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 33, ETeam::Toulouse, ETeam::Lyon, 1778338800000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 33, ETeam::Lens, ETeam::Nantes, 1778338800000 });

    // Week 34
    matches.push_back({ ELeague::Ligue1, "25/26", 34, ETeam::Brest, ETeam::Angers, 1778943600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 34, ETeam::Lyon, ETeam::Lens, 1778943600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 34, ETeam::Nice, ETeam::Metz, 1778943600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 34, ETeam::Lorient, ETeam::LeHavre, 1778943600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 34, ETeam::Lille, ETeam::Auxerre, 1778943600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 34, ETeam::Strasbourg, ETeam::Monaco, 1778943600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 34, ETeam::Nantes, ETeam::Toulouse, 1778943600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 34, ETeam::ParisFC, ETeam::PSG, 1778943600000 });
    matches.push_back({ ELeague::Ligue1, "25/26", 34, ETeam::Marseille, ETeam::Rennes, 1778943600000 });

    for (auto& m : matches)
    {
        std::string sql = "insert into matches(league, season, week, team1, team2, match_date) values ("
            + std::to_string(int(m.League)) + ", '"
            + m.Season + "', "
            + std::to_string(m.Week) + ", "
            + std::to_string((int)m.Team1) + ", "
            + std::to_string((int)m.Team2) + ", "
            + std::to_string(m.Date) + ");";

        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitBundesliga25_26(PGconn* pg)
{
    std::vector<Match> matches;
    // Week 1
    matches.push_back({ ELeague::Bundesliga, "25/26", 1, ETeam::BayernMunich, ETeam::RBLeipzig, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 1, ETeam::BorussiaMgladbach, ETeam::Hamburg, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 1, ETeam::BayerLeverkusen, ETeam::Hoffenheim, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 1, ETeam::Mainz, ETeam::Koln, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 1, ETeam::Freiburg, ETeam::Augsburg, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 1, ETeam::Heidenheim, ETeam::Wolfsburg, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 1, ETeam::StPauli, ETeam::BorussiaDortmund, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 1, ETeam::EintrachtFrankfurt, ETeam::WerderBremen, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 1, ETeam::UnionBerlin, ETeam::Stuttgart, 1755874800000 });

    // Week 2
    matches.push_back({ ELeague::Bundesliga, "25/26", 2, ETeam::RBLeipzig, ETeam::Heidenheim, 1756566000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 2, ETeam::WerderBremen, ETeam::BayerLeverkusen, 1756566000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 2, ETeam::Hoffenheim, ETeam::EintrachtFrankfurt, 1756566000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 2, ETeam::Augsburg, ETeam::BayernMunich, 1756566000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 2, ETeam::Koln, ETeam::Freiburg, 1756566000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 2, ETeam::BorussiaDortmund, ETeam::UnionBerlin, 1756566000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 2, ETeam::Wolfsburg, ETeam::Mainz, 1756566000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 2, ETeam::Hamburg, ETeam::StPauli, 1756566000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 2, ETeam::Stuttgart, ETeam::BorussiaMgladbach, 1756566000000 });

    // Week 3
    matches.push_back({ ELeague::Bundesliga, "25/26", 3, ETeam::BorussiaMgladbach, ETeam::WerderBremen, 1757775600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 3, ETeam::Freiburg, ETeam::Stuttgart, 1757775600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 3, ETeam::UnionBerlin, ETeam::Hoffenheim, 1757775600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 3, ETeam::Mainz, ETeam::RBLeipzig, 1757775600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 3, ETeam::BayernMunich, ETeam::Hamburg, 1757775600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 3, ETeam::Wolfsburg, ETeam::Koln, 1757775600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 3, ETeam::StPauli, ETeam::Augsburg, 1757775600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 3, ETeam::BayerLeverkusen, ETeam::EintrachtFrankfurt, 1757775600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 3, ETeam::Heidenheim, ETeam::BorussiaDortmund, 1757775600000 });

    // Week 4
    matches.push_back({ ELeague::Bundesliga, "25/26", 4, ETeam::Augsburg, ETeam::Mainz, 1758380400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 4, ETeam::Stuttgart, ETeam::StPauli, 1758380400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 4, ETeam::Hamburg, ETeam::Heidenheim, 1758380400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 4, ETeam::BayerLeverkusen, ETeam::BorussiaMgladbach, 1758380400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 4, ETeam::EintrachtFrankfurt, ETeam::UnionBerlin, 1758380400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 4, ETeam::BorussiaDortmund, ETeam::Wolfsburg, 1758380400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 4, ETeam::WerderBremen, ETeam::Freiburg, 1758380400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 4, ETeam::RBLeipzig, ETeam::Koln, 1758380400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 4, ETeam::Hoffenheim, ETeam::BayernMunich, 1758380400000 });

    // Week 5
    matches.push_back({ ELeague::Bundesliga, "25/26", 5, ETeam::Mainz, ETeam::BorussiaDortmund, 1758985200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 5, ETeam::Wolfsburg, ETeam::RBLeipzig, 1758985200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 5, ETeam::BorussiaMgladbach, ETeam::EintrachtFrankfurt, 1758985200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 5, ETeam::Freiburg, ETeam::Hoffenheim, 1758985200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 5, ETeam::UnionBerlin, ETeam::Hamburg, 1758985200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 5, ETeam::BayernMunich, ETeam::WerderBremen, 1758985200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 5, ETeam::Heidenheim, ETeam::Augsburg, 1758985200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 5, ETeam::Koln, ETeam::Stuttgart, 1758985200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 5, ETeam::StPauli, ETeam::BayerLeverkusen, 1758985200000 });

    // Week 6
    matches.push_back({ ELeague::Bundesliga, "25/26", 6, ETeam::BorussiaDortmund, ETeam::RBLeipzig, 1759590000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 6, ETeam::Augsburg, ETeam::Wolfsburg, 1759590000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 6, ETeam::WerderBremen, ETeam::StPauli, 1759590000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 6, ETeam::Stuttgart, ETeam::Heidenheim, 1759590000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 6, ETeam::Hoffenheim, ETeam::Koln, 1759590000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 6, ETeam::EintrachtFrankfurt, ETeam::BayernMunich, 1759590000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 6, ETeam::BayerLeverkusen, ETeam::UnionBerlin, 1759590000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 6, ETeam::BorussiaMgladbach, ETeam::Freiburg, 1759590000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 6, ETeam::Hamburg, ETeam::Mainz, 1759590000000 });

    // Week 7
    matches.push_back({ ELeague::Bundesliga, "25/26", 7, ETeam::RBLeipzig, ETeam::Hamburg, 1760799600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 7, ETeam::UnionBerlin, ETeam::BorussiaMgladbach, 1760799600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 7, ETeam::Freiburg, ETeam::EintrachtFrankfurt, 1760799600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 7, ETeam::Heidenheim, ETeam::WerderBremen, 1760799600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 7, ETeam::Mainz, ETeam::BayerLeverkusen, 1760799600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 7, ETeam::Wolfsburg, ETeam::Stuttgart, 1760799600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 7, ETeam::Koln, ETeam::Augsburg, 1760799600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 7, ETeam::StPauli, ETeam::Hoffenheim, 1760799600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 7, ETeam::BayernMunich, ETeam::BorussiaDortmund, 1760799600000 });

    // Week 8
    matches.push_back({ ELeague::Bundesliga, "25/26", 8, ETeam::Hamburg, ETeam::Wolfsburg, 1761404400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 8, ETeam::Hoffenheim, ETeam::Heidenheim, 1761404400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 8, ETeam::WerderBremen, ETeam::UnionBerlin, 1761404400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 8, ETeam::BorussiaMgladbach, ETeam::BayernMunich, 1761404400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 8, ETeam::Augsburg, ETeam::RBLeipzig, 1761404400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 8, ETeam::BayerLeverkusen, ETeam::Freiburg, 1761404400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 8, ETeam::BorussiaDortmund, ETeam::Koln, 1761404400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 8, ETeam::EintrachtFrankfurt, ETeam::StPauli, 1761404400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 8, ETeam::Stuttgart, ETeam::Mainz, 1761404400000 });

    // Week 9
    matches.push_back({ ELeague::Bundesliga, "25/26", 9, ETeam::Koln, ETeam::Hamburg, 1762009200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 9, ETeam::Augsburg, ETeam::BorussiaDortmund, 1762009200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 9, ETeam::Mainz, ETeam::WerderBremen, 1762009200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 9, ETeam::UnionBerlin, ETeam::Freiburg, 1762009200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 9, ETeam::Wolfsburg, ETeam::Hoffenheim, 1762009200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 9, ETeam::RBLeipzig, ETeam::Stuttgart, 1762009200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 9, ETeam::Heidenheim, ETeam::EintrachtFrankfurt, 1762009200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 9, ETeam::StPauli, ETeam::BorussiaMgladbach, 1762009200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 9, ETeam::BayernMunich, ETeam::BayerLeverkusen, 1762009200000 });

    // Week 10
    matches.push_back({ ELeague::Bundesliga, "25/26", 10, ETeam::BorussiaMgladbach, ETeam::Koln, 1762614000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 10, ETeam::Freiburg, ETeam::StPauli, 1762614000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 10, ETeam::UnionBerlin, ETeam::BayernMunich, 1762614000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 10, ETeam::Stuttgart, ETeam::Augsburg, 1762614000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 10, ETeam::Hoffenheim, ETeam::RBLeipzig, 1762614000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 10, ETeam::BayerLeverkusen, ETeam::Heidenheim, 1762614000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 10, ETeam::EintrachtFrankfurt, ETeam::Mainz, 1762614000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 10, ETeam::Hamburg, ETeam::BorussiaDortmund, 1762614000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 10, ETeam::WerderBremen, ETeam::Wolfsburg, 1762614000000 });

    // Week 11
    matches.push_back({ ELeague::Bundesliga, "25/26", 11, ETeam::Wolfsburg, ETeam::BayerLeverkusen, 1763823600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 11, ETeam::BayernMunich, ETeam::Freiburg, 1763823600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 11, ETeam::Koln, ETeam::EintrachtFrankfurt, 1763823600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 11, ETeam::BorussiaDortmund, ETeam::Stuttgart, 1763823600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 11, ETeam::Heidenheim, ETeam::BorussiaMgladbach, 1763823600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 11, ETeam::Mainz, ETeam::Hoffenheim, 1763823600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 11, ETeam::StPauli, ETeam::UnionBerlin, 1763823600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 11, ETeam::Augsburg, ETeam::Hamburg, 1763823600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 11, ETeam::RBLeipzig, ETeam::WerderBremen, 1763823600000 });

    // Week 12
    matches.push_back({ ELeague::Bundesliga, "25/26", 12, ETeam::BorussiaMgladbach, ETeam::RBLeipzig, 1764428400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 12, ETeam::Hamburg, ETeam::Stuttgart, 1764428400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 12, ETeam::Hoffenheim, ETeam::Augsburg, 1764428400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 12, ETeam::UnionBerlin, ETeam::Heidenheim, 1764428400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 12, ETeam::BayerLeverkusen, ETeam::BorussiaDortmund, 1764428400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 12, ETeam::Freiburg, ETeam::Mainz, 1764428400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 12, ETeam::WerderBremen, ETeam::Koln, 1764428400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 12, ETeam::EintrachtFrankfurt, ETeam::Wolfsburg, 1764428400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 12, ETeam::BayernMunich, ETeam::StPauli, 1764428400000 });

    // Week 13
    matches.push_back({ ELeague::Bundesliga, "25/26", 13, ETeam::Wolfsburg, ETeam::UnionBerlin, 1765033200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 13, ETeam::Stuttgart, ETeam::BayernMunich, 1765033200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 13, ETeam::Heidenheim, ETeam::Freiburg, 1765033200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 13, ETeam::Augsburg, ETeam::BayerLeverkusen, 1765033200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 13, ETeam::RBLeipzig, ETeam::EintrachtFrankfurt, 1765033200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 13, ETeam::Koln, ETeam::StPauli, 1765033200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 13, ETeam::BorussiaDortmund, ETeam::Hoffenheim, 1765033200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 13, ETeam::Mainz, ETeam::BorussiaMgladbach, 1765033200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 13, ETeam::Hamburg, ETeam::WerderBremen, 1765033200000 });

    // Week 14
    matches.push_back({ ELeague::Bundesliga, "25/26", 14, ETeam::WerderBremen, ETeam::Stuttgart, 1765638000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 14, ETeam::BayerLeverkusen, ETeam::Koln, 1765638000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 14, ETeam::Hoffenheim, ETeam::Hamburg, 1765638000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 14, ETeam::BayernMunich, ETeam::Mainz, 1765638000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 14, ETeam::Freiburg, ETeam::BorussiaDortmund, 1765638000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 14, ETeam::EintrachtFrankfurt, ETeam::Augsburg, 1765638000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 14, ETeam::BorussiaMgladbach, ETeam::Wolfsburg, 1765638000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 14, ETeam::StPauli, ETeam::Heidenheim, 1765638000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 14, ETeam::UnionBerlin, ETeam::RBLeipzig, 1765638000000 });

    // Week 15
    matches.push_back({ ELeague::Bundesliga, "25/26", 15, ETeam::Hamburg, ETeam::EintrachtFrankfurt, 1766242800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 15, ETeam::BorussiaDortmund, ETeam::BorussiaMgladbach, 1766242800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 15, ETeam::Stuttgart, ETeam::Hoffenheim, 1766242800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 15, ETeam::Mainz, ETeam::StPauli, 1766242800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 15, ETeam::Augsburg, ETeam::WerderBremen, 1766242800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 15, ETeam::Wolfsburg, ETeam::Freiburg, 1766242800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 15, ETeam::Heidenheim, ETeam::BayernMunich, 1766242800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 15, ETeam::Koln, ETeam::UnionBerlin, 1766242800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 15, ETeam::RBLeipzig, ETeam::BayerLeverkusen, 1766242800000 });

    // Week 16
    matches.push_back({ ELeague::Bundesliga, "25/26", 16, ETeam::BorussiaMgladbach, ETeam::Augsburg, 1768057200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 16, ETeam::Freiburg, ETeam::Hamburg, 1768057200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 16, ETeam::EintrachtFrankfurt, ETeam::BorussiaDortmund, 1768057200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 16, ETeam::BayernMunich, ETeam::Wolfsburg, 1768057200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 16, ETeam::BayerLeverkusen, ETeam::Stuttgart, 1768057200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 16, ETeam::Heidenheim, ETeam::Koln, 1768057200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 16, ETeam::UnionBerlin, ETeam::Mainz, 1768057200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 16, ETeam::WerderBremen, ETeam::Hoffenheim, 1768057200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 16, ETeam::StPauli, ETeam::RBLeipzig, 1768057200000 });

    // Week 17
    matches.push_back({ ELeague::Bundesliga, "25/26", 17, ETeam::Koln, ETeam::BayernMunich, 1768402800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 17, ETeam::Augsburg, ETeam::UnionBerlin, 1768402800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 17, ETeam::Wolfsburg, ETeam::StPauli, 1768402800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 17, ETeam::RBLeipzig, ETeam::Freiburg, 1768402800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 17, ETeam::Mainz, ETeam::Heidenheim, 1768402800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 17, ETeam::Hoffenheim, ETeam::BorussiaMgladbach, 1768402800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 17, ETeam::Hamburg, ETeam::BayerLeverkusen, 1768402800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 17, ETeam::Stuttgart, ETeam::EintrachtFrankfurt, 1768402800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 17, ETeam::BorussiaDortmund, ETeam::WerderBremen, 1768402800000 });

    // Week 18
    matches.push_back({ ELeague::Bundesliga, "25/26", 18, ETeam::Wolfsburg, ETeam::Heidenheim, 1768662000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 18, ETeam::BorussiaDortmund, ETeam::StPauli, 1768662000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 18, ETeam::Hamburg, ETeam::BorussiaMgladbach, 1768662000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 18, ETeam::Augsburg, ETeam::Freiburg, 1768662000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 18, ETeam::Hoffenheim, ETeam::BayerLeverkusen, 1768662000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 18, ETeam::WerderBremen, ETeam::EintrachtFrankfurt, 1768662000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 18, ETeam::RBLeipzig, ETeam::BayernMunich, 1768662000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 18, ETeam::Stuttgart, ETeam::UnionBerlin, 1768662000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 18, ETeam::Koln, ETeam::Mainz, 1768662000000 });

    // Week 19
    matches.push_back({ ELeague::Bundesliga, "25/26", 19, ETeam::EintrachtFrankfurt, ETeam::Hoffenheim, 1769266800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 19, ETeam::BorussiaMgladbach, ETeam::Stuttgart, 1769266800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 19, ETeam::UnionBerlin, ETeam::BorussiaDortmund, 1769266800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 19, ETeam::BayernMunich, ETeam::Augsburg, 1769266800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 19, ETeam::Mainz, ETeam::Wolfsburg, 1769266800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 19, ETeam::Heidenheim, ETeam::RBLeipzig, 1769266800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 19, ETeam::Freiburg, ETeam::Koln, 1769266800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 19, ETeam::BayerLeverkusen, ETeam::WerderBremen, 1769266800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 19, ETeam::StPauli, ETeam::Hamburg, 1769266800000 });

    // Week 20
    matches.push_back({ ELeague::Bundesliga, "25/26", 20, ETeam::Koln, ETeam::Wolfsburg, 1769871600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 20, ETeam::WerderBremen, ETeam::BorussiaMgladbach, 1769871600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 20, ETeam::BorussiaDortmund, ETeam::Heidenheim, 1769871600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 20, ETeam::Hoffenheim, ETeam::UnionBerlin, 1769871600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 20, ETeam::Augsburg, ETeam::StPauli, 1769871600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 20, ETeam::Stuttgart, ETeam::Freiburg, 1769871600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 20, ETeam::Hamburg, ETeam::BayernMunich, 1769871600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 20, ETeam::RBLeipzig, ETeam::Mainz, 1769871600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 20, ETeam::EintrachtFrankfurt, ETeam::BayerLeverkusen, 1769871600000 });

    // Week 21
    matches.push_back({ ELeague::Bundesliga, "25/26", 21, ETeam::BayernMunich, ETeam::Hoffenheim, 1770476400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 21, ETeam::StPauli, ETeam::Stuttgart, 1770476400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 21, ETeam::UnionBerlin, ETeam::EintrachtFrankfurt, 1770476400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 21, ETeam::BorussiaMgladbach, ETeam::BayerLeverkusen, 1770476400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 21, ETeam::Koln, ETeam::RBLeipzig, 1770476400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 21, ETeam::Heidenheim, ETeam::Hamburg, 1770476400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 21, ETeam::Wolfsburg, ETeam::BorussiaDortmund, 1770476400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 21, ETeam::Freiburg, ETeam::WerderBremen, 1770476400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 21, ETeam::Mainz, ETeam::Augsburg, 1770476400000 });

    // Week 22
    matches.push_back({ ELeague::Bundesliga, "25/26", 22, ETeam::Augsburg, ETeam::Heidenheim, 1771081200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 22, ETeam::Stuttgart, ETeam::Koln, 1771081200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 22, ETeam::Hoffenheim, ETeam::Freiburg, 1771081200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 22, ETeam::BayerLeverkusen, ETeam::StPauli, 1771081200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 22, ETeam::Hamburg, ETeam::UnionBerlin, 1771081200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 22, ETeam::WerderBremen, ETeam::BayernMunich, 1771081200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 22, ETeam::BorussiaDortmund, ETeam::Mainz, 1771081200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 22, ETeam::RBLeipzig, ETeam::Wolfsburg, 1771081200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 22, ETeam::EintrachtFrankfurt, ETeam::BorussiaMgladbach, 1771081200000 });

    // Week 23
    matches.push_back({ ELeague::Bundesliga, "25/26", 23, ETeam::Freiburg, ETeam::BorussiaMgladbach, 1771686000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 23, ETeam::Wolfsburg, ETeam::Augsburg, 1771686000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 23, ETeam::StPauli, ETeam::WerderBremen, 1771686000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 23, ETeam::Mainz, ETeam::Hamburg, 1771686000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 23, ETeam::UnionBerlin, ETeam::BayerLeverkusen, 1771686000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 23, ETeam::BayernMunich, ETeam::EintrachtFrankfurt, 1771686000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 23, ETeam::Heidenheim, ETeam::Stuttgart, 1771686000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 23, ETeam::RBLeipzig, ETeam::BorussiaDortmund, 1771686000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 23, ETeam::Koln, ETeam::Hoffenheim, 1771686000000 });

    // Week 24
    matches.push_back({ ELeague::Bundesliga, "25/26", 24, ETeam::BorussiaDortmund, ETeam::BayernMunich, 1772290800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 24, ETeam::EintrachtFrankfurt, ETeam::Freiburg, 1772290800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 24, ETeam::WerderBremen, ETeam::Heidenheim, 1772290800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 24, ETeam::Augsburg, ETeam::Koln, 1772290800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 24, ETeam::Hoffenheim, ETeam::StPauli, 1772290800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 24, ETeam::BayerLeverkusen, ETeam::Mainz, 1772290800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 24, ETeam::Stuttgart, ETeam::Wolfsburg, 1772290800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 24, ETeam::Hamburg, ETeam::RBLeipzig, 1772290800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 24, ETeam::BorussiaMgladbach, ETeam::UnionBerlin, 1772290800000 });

    // Week 25
    matches.push_back({ ELeague::Bundesliga, "25/26", 25, ETeam::StPauli, ETeam::EintrachtFrankfurt, 1772895600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 25, ETeam::Heidenheim, ETeam::Hoffenheim, 1772895600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 25, ETeam::Freiburg, ETeam::BayerLeverkusen, 1772895600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 25, ETeam::RBLeipzig, ETeam::Augsburg, 1772895600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 25, ETeam::Koln, ETeam::BorussiaDortmund, 1772895600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 25, ETeam::UnionBerlin, ETeam::WerderBremen, 1772895600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 25, ETeam::Wolfsburg, ETeam::Hamburg, 1772895600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 25, ETeam::BayernMunich, ETeam::BorussiaMgladbach, 1772895600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 25, ETeam::Mainz, ETeam::Stuttgart, 1772895600000 });

    // Week 26
    matches.push_back({ ELeague::Bundesliga, "25/26", 26, ETeam::BorussiaMgladbach, ETeam::StPauli, 1773500400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 26, ETeam::BorussiaDortmund, ETeam::Augsburg, 1773500400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 26, ETeam::Freiburg, ETeam::UnionBerlin, 1773500400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 26, ETeam::WerderBremen, ETeam::Mainz, 1773500400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 26, ETeam::Hoffenheim, ETeam::Wolfsburg, 1773500400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 26, ETeam::EintrachtFrankfurt, ETeam::Heidenheim, 1773500400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 26, ETeam::Stuttgart, ETeam::RBLeipzig, 1773500400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 26, ETeam::Hamburg, ETeam::Koln, 1773500400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 26, ETeam::BayerLeverkusen, ETeam::BayernMunich, 1773500400000 });

    // Week 27
    matches.push_back({ ELeague::Bundesliga, "25/26", 27, ETeam::Mainz, ETeam::EintrachtFrankfurt, 1774105200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 27, ETeam::Heidenheim, ETeam::BayerLeverkusen, 1774105200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 27, ETeam::StPauli, ETeam::Freiburg, 1774105200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 27, ETeam::RBLeipzig, ETeam::Hoffenheim, 1774105200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 27, ETeam::BorussiaDortmund, ETeam::Hamburg, 1774105200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 27, ETeam::Augsburg, ETeam::Stuttgart, 1774105200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 27, ETeam::BayernMunich, ETeam::UnionBerlin, 1774105200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 27, ETeam::Koln, ETeam::BorussiaMgladbach, 1774105200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 27, ETeam::Wolfsburg, ETeam::WerderBremen, 1774105200000 });

    // Week 28
    matches.push_back({ ELeague::Bundesliga, "25/26", 28, ETeam::Hoffenheim, ETeam::Mainz, 1775314800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 28, ETeam::Stuttgart, ETeam::BorussiaDortmund, 1775314800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 28, ETeam::Freiburg, ETeam::BayernMunich, 1775314800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 28, ETeam::EintrachtFrankfurt, ETeam::Koln, 1775314800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 28, ETeam::BorussiaMgladbach, ETeam::Heidenheim, 1775314800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 28, ETeam::BayerLeverkusen, ETeam::Wolfsburg, 1775314800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 28, ETeam::UnionBerlin, ETeam::StPauli, 1775314800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 28, ETeam::Hamburg, ETeam::Augsburg, 1775314800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 28, ETeam::WerderBremen, ETeam::RBLeipzig, 1775314800000 });

    // Week 29
    matches.push_back({ ELeague::Bundesliga, "25/26", 29, ETeam::Stuttgart, ETeam::Hamburg, 1775919600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 29, ETeam::Heidenheim, ETeam::UnionBerlin, 1775919600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 29, ETeam::Wolfsburg, ETeam::EintrachtFrankfurt, 1775919600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 29, ETeam::Koln, ETeam::WerderBremen, 1775919600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 29, ETeam::StPauli, ETeam::BayernMunich, 1775919600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 29, ETeam::Augsburg, ETeam::Hoffenheim, 1775919600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 29, ETeam::BorussiaDortmund, ETeam::BayerLeverkusen, 1775919600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 29, ETeam::RBLeipzig, ETeam::BorussiaMgladbach, 1775919600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 29, ETeam::Mainz, ETeam::Freiburg, 1775919600000 });

    // Week 30
    matches.push_back({ ELeague::Bundesliga, "25/26", 30, ETeam::EintrachtFrankfurt, ETeam::RBLeipzig, 1776524400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 30, ETeam::BayerLeverkusen, ETeam::Augsburg, 1776524400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 30, ETeam::WerderBremen, ETeam::Hamburg, 1776524400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 30, ETeam::StPauli, ETeam::Koln, 1776524400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 30, ETeam::Hoffenheim, ETeam::BorussiaDortmund, 1776524400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 30, ETeam::BayernMunich, ETeam::Stuttgart, 1776524400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 30, ETeam::Freiburg, ETeam::Heidenheim, 1776524400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 30, ETeam::BorussiaMgladbach, ETeam::Mainz, 1776524400000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 30, ETeam::UnionBerlin, ETeam::Wolfsburg, 1776524400000 });

    // Week 31
    matches.push_back({ ELeague::Bundesliga, "25/26", 31, ETeam::Wolfsburg, ETeam::BorussiaMgladbach, 1777129200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 31, ETeam::Heidenheim, ETeam::StPauli, 1777129200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 31, ETeam::Augsburg, ETeam::EintrachtFrankfurt, 1777129200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 31, ETeam::Hamburg, ETeam::Hoffenheim, 1777129200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 31, ETeam::Stuttgart, ETeam::WerderBremen, 1777129200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 31, ETeam::RBLeipzig, ETeam::UnionBerlin, 1777129200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 31, ETeam::Koln, ETeam::BayerLeverkusen, 1777129200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 31, ETeam::Mainz, ETeam::BayernMunich, 1777129200000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 31, ETeam::BorussiaDortmund, ETeam::Freiburg, 1777129200000 });

    // Week 32
    matches.push_back({ ELeague::Bundesliga, "25/26", 32, ETeam::BorussiaMgladbach, ETeam::BorussiaDortmund, 1777734000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 32, ETeam::WerderBremen, ETeam::Augsburg, 1777734000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 32, ETeam::UnionBerlin, ETeam::Koln, 1777734000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 32, ETeam::BayerLeverkusen, ETeam::RBLeipzig, 1777734000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 32, ETeam::Freiburg, ETeam::Wolfsburg, 1777734000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 32, ETeam::Hoffenheim, ETeam::Stuttgart, 1777734000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 32, ETeam::EintrachtFrankfurt, ETeam::Hamburg, 1777734000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 32, ETeam::StPauli, ETeam::Mainz, 1777734000000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 32, ETeam::BayernMunich, ETeam::Heidenheim, 1777734000000 });

    // Week 33
    matches.push_back({ ELeague::Bundesliga, "25/26", 33, ETeam::BorussiaDortmund, ETeam::EintrachtFrankfurt, 1778338800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 33, ETeam::Mainz, ETeam::UnionBerlin, 1778338800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 33, ETeam::Wolfsburg, ETeam::BayernMunich, 1778338800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 33, ETeam::RBLeipzig, ETeam::StPauli, 1778338800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 33, ETeam::Hamburg, ETeam::Freiburg, 1778338800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 33, ETeam::Augsburg, ETeam::BorussiaMgladbach, 1778338800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 33, ETeam::Stuttgart, ETeam::BayerLeverkusen, 1778338800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 33, ETeam::Koln, ETeam::Heidenheim, 1778338800000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 33, ETeam::Hoffenheim, ETeam::WerderBremen, 1778338800000 });

    // Week 34
    matches.push_back({ ELeague::Bundesliga, "25/26", 34, ETeam::Heidenheim, ETeam::Mainz, 1778943600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 34, ETeam::UnionBerlin, ETeam::Augsburg, 1778943600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 34, ETeam::BorussiaMgladbach, ETeam::Hoffenheim, 1778943600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 34, ETeam::Freiburg, ETeam::RBLeipzig, 1778943600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 34, ETeam::WerderBremen, ETeam::BorussiaDortmund, 1778943600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 34, ETeam::BayernMunich, ETeam::Koln, 1778943600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 34, ETeam::EintrachtFrankfurt, ETeam::Stuttgart, 1778943600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 34, ETeam::BayerLeverkusen, ETeam::Hamburg, 1778943600000 });
    matches.push_back({ ELeague::Bundesliga, "25/26", 34, ETeam::StPauli, ETeam::Wolfsburg, 1778943600000 });

    for (auto& m : matches)
    {
        std::string sql = "insert into matches(league, season, week, team1, team2, match_date) values ("
            + std::to_string(int(m.League)) + ", '"
            + m.Season + "', "
            + std::to_string(m.Week) + ", "
            + std::to_string((int)m.Team1) + ", "
            + std::to_string((int)m.Team2) + ", "
            + std::to_string(m.Date) + ");";

        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitSerieA25_26(PGconn* pg)
{
    std::vector<Match> matches;
    // Week 1
    matches.push_back({ ELeague::SerieA, "25/26", 1, ETeam::Sassuolo, ETeam::Napoli, 1755966600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 1, ETeam::Genoa, ETeam::Lecce, 1755966600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 1, ETeam::ACMilan, ETeam::Cremonese, 1755966600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 1, ETeam::Roma, ETeam::Bologna, 1755966600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 1, ETeam::Cagliari, ETeam::Fiorentina, 1755966600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 1, ETeam::Como, ETeam::Lazio, 1755966600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 1, ETeam::Juventus, ETeam::Parma, 1755966600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 1, ETeam::Atalanta, ETeam::Pisa, 1755966600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 1, ETeam::Udinese, ETeam::Verona, 1755966600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 1, ETeam::InterMilan, ETeam::Torino, 1755966600000 });

    // Week 2
    matches.push_back({ ELeague::SerieA, "25/26", 2, ETeam::Cremonese, ETeam::Sassuolo, 1756485000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 2, ETeam::Lecce, ETeam::ACMilan, 1756485000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 2, ETeam::Bologna, ETeam::Como, 1756485000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 2, ETeam::Parma, ETeam::Atalanta, 1756485000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 2, ETeam::Napoli, ETeam::Cagliari, 1756485000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 2, ETeam::Pisa, ETeam::Roma, 1756485000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 2, ETeam::Torino, ETeam::Fiorentina, 1756485000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 2, ETeam::Genoa, ETeam::Juventus, 1756485000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 2, ETeam::InterMilan, ETeam::Udinese, 1756485000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 2, ETeam::Lazio, ETeam::Verona, 1756485000000 });

    // Week 3
    matches.push_back({ ELeague::SerieA, "25/26", 3, ETeam::Cagliari, ETeam::Parma, 1757781000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 3, ETeam::Juventus, ETeam::InterMilan, 1757781000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 3, ETeam::Fiorentina, ETeam::Napoli, 1757781000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 3, ETeam::Roma, ETeam::Torino, 1757781000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 3, ETeam::Pisa, ETeam::Udinese, 1757781000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 3, ETeam::Atalanta, ETeam::Lecce, 1757781000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 3, ETeam::Sassuolo, ETeam::Lazio, 1757781000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 3, ETeam::ACMilan, ETeam::Bologna, 1757781000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 3, ETeam::Verona, ETeam::Cremonese, 1757781000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 3, ETeam::Como, ETeam::Genoa, 1757781000000 });

    // Week 4
    matches.push_back({ ELeague::SerieA, "25/26", 4, ETeam::Lecce, ETeam::Cagliari, 1758472200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 4, ETeam::Torino, ETeam::Atalanta, 1758472200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 4, ETeam::Fiorentina, ETeam::Como, 1758472200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 4, ETeam::Udinese, ETeam::ACMilan, 1758472200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 4, ETeam::Cremonese, ETeam::Parma, 1758472200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 4, ETeam::Verona, ETeam::Juventus, 1758472200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 4, ETeam::Lazio, ETeam::Roma, 1758472200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 4, ETeam::Bologna, ETeam::Genoa, 1758472200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 4, ETeam::Napoli, ETeam::Pisa, 1758472200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 4, ETeam::InterMilan, ETeam::Sassuolo, 1758472200000 });

    // Week 5
    matches.push_back({ ELeague::SerieA, "25/26", 5, ETeam::Roma, ETeam::Verona, 1759077000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 5, ETeam::Cagliari, ETeam::InterMilan, 1759077000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 5, ETeam::Como, ETeam::Cremonese, 1759077000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 5, ETeam::Parma, ETeam::Torino, 1759077000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 5, ETeam::Lecce, ETeam::Bologna, 1759077000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 5, ETeam::Genoa, ETeam::Lazio, 1759077000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 5, ETeam::ACMilan, ETeam::Napoli, 1759077000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 5, ETeam::Juventus, ETeam::Atalanta, 1759077000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 5, ETeam::Pisa, ETeam::Fiorentina, 1759077000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 5, ETeam::Sassuolo, ETeam::Udinese, 1759077000000 });

    // Week 6
    matches.push_back({ ELeague::SerieA, "25/26", 6, ETeam::Napoli, ETeam::Genoa, 1759681800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 6, ETeam::Lazio, ETeam::Torino, 1759681800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 6, ETeam::Bologna, ETeam::Pisa, 1759681800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 6, ETeam::Udinese, ETeam::Cagliari, 1759681800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 6, ETeam::Verona, ETeam::Sassuolo, 1759681800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 6, ETeam::InterMilan, ETeam::Cremonese, 1759681800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 6, ETeam::Juventus, ETeam::ACMilan, 1759681800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 6, ETeam::Fiorentina, ETeam::Roma, 1759681800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 6, ETeam::Atalanta, ETeam::Como, 1759681800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 6, ETeam::Parma, ETeam::Lecce, 1759681800000 });

    // Week 7
    matches.push_back({ ELeague::SerieA, "25/26", 7, ETeam::Torino, ETeam::Napoli, 1760886000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 7, ETeam::Genoa, ETeam::Parma, 1760886000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 7, ETeam::Cagliari, ETeam::Bologna, 1760886000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 7, ETeam::ACMilan, ETeam::Fiorentina, 1760886000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 7, ETeam::Atalanta, ETeam::Lazio, 1760886000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 7, ETeam::Cremonese, ETeam::Udinese, 1760886000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 7, ETeam::Como, ETeam::Juventus, 1760886000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 7, ETeam::Roma, ETeam::InterMilan, 1760886000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 7, ETeam::Pisa, ETeam::Verona, 1760886000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 7, ETeam::Lecce, ETeam::Sassuolo, 1760886000000 });

    // Week 8
    matches.push_back({ ELeague::SerieA, "25/26", 8, ETeam::Parma, ETeam::Como, 1761490800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 8, ETeam::Fiorentina, ETeam::Bologna, 1761490800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 8, ETeam::Sassuolo, ETeam::Roma, 1761490800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 8, ETeam::Verona, ETeam::Cagliari, 1761490800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 8, ETeam::Cremonese, ETeam::Atalanta, 1761490800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 8, ETeam::Napoli, ETeam::InterMilan, 1761490800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 8, ETeam::Torino, ETeam::Genoa, 1761490800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 8, ETeam::Udinese, ETeam::Lecce, 1761490800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 8, ETeam::Lazio, ETeam::Juventus, 1761490800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 8, ETeam::ACMilan, ETeam::Pisa, 1761490800000 });

    // Week 9
    matches.push_back({ ELeague::SerieA, "25/26", 9, ETeam::Roma, ETeam::Parma, 1761750000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 9, ETeam::Genoa, ETeam::Cremonese, 1761750000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 9, ETeam::Cagliari, ETeam::Sassuolo, 1761750000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 9, ETeam::Bologna, ETeam::Torino, 1761750000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 9, ETeam::Juventus, ETeam::Udinese, 1761750000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 9, ETeam::InterMilan, ETeam::Fiorentina, 1761750000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 9, ETeam::Pisa, ETeam::Lazio, 1761750000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 9, ETeam::Lecce, ETeam::Napoli, 1761750000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 9, ETeam::Como, ETeam::Verona, 1761750000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 9, ETeam::Atalanta, ETeam::ACMilan, 1761750000000 });

    // Week 10
    matches.push_back({ ELeague::SerieA, "25/26", 10, ETeam::Lazio, ETeam::Cagliari, 1762095600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 10, ETeam::Udinese, ETeam::Atalanta, 1762095600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 10, ETeam::Fiorentina, ETeam::Lecce, 1762095600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 10, ETeam::Torino, ETeam::Pisa, 1762095600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 10, ETeam::Verona, ETeam::InterMilan, 1762095600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 10, ETeam::Parma, ETeam::Bologna, 1762095600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 10, ETeam::ACMilan, ETeam::Roma, 1762095600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 10, ETeam::Napoli, ETeam::Como, 1762095600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 10, ETeam::Sassuolo, ETeam::Genoa, 1762095600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 10, ETeam::Cremonese, ETeam::Juventus, 1762095600000 });

    // Week 11
    matches.push_back({ ELeague::SerieA, "25/26", 11, ETeam::Como, ETeam::Cagliari, 1762700400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 11, ETeam::Atalanta, ETeam::Sassuolo, 1762700400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 11, ETeam::Genoa, ETeam::Fiorentina, 1762700400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 11, ETeam::InterMilan, ETeam::Lazio, 1762700400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 11, ETeam::Parma, ETeam::ACMilan, 1762700400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 11, ETeam::Bologna, ETeam::Napoli, 1762700400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 11, ETeam::Roma, ETeam::Udinese, 1762700400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 11, ETeam::Pisa, ETeam::Cremonese, 1762700400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 11, ETeam::Lecce, ETeam::Verona, 1762700400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 11, ETeam::Juventus, ETeam::Torino, 1762700400000 });

    // Week 12
    matches.push_back({ ELeague::SerieA, "25/26", 12, ETeam::Napoli, ETeam::Atalanta, 1763910000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 12, ETeam::Cremonese, ETeam::Roma, 1763910000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 12, ETeam::Sassuolo, ETeam::Pisa, 1763910000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 12, ETeam::Udinese, ETeam::Bologna, 1763910000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 12, ETeam::Cagliari, ETeam::Genoa, 1763910000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 12, ETeam::InterMilan, ETeam::ACMilan, 1763910000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 12, ETeam::Fiorentina, ETeam::Juventus, 1763910000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 12, ETeam::Verona, ETeam::Parma, 1763910000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 12, ETeam::Lazio, ETeam::Lecce, 1763910000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 12, ETeam::Torino, ETeam::Como, 1763910000000 });

    // Week 13
    matches.push_back({ ELeague::SerieA, "25/26", 13, ETeam::Juventus, ETeam::Cagliari, 1764514800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 13, ETeam::Roma, ETeam::Napoli, 1764514800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 13, ETeam::ACMilan, ETeam::Lazio, 1764514800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 13, ETeam::Como, ETeam::Sassuolo, 1764514800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 13, ETeam::Genoa, ETeam::Verona, 1764514800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 13, ETeam::Bologna, ETeam::Cremonese, 1764514800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 13, ETeam::Pisa, ETeam::InterMilan, 1764514800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 13, ETeam::Atalanta, ETeam::Fiorentina, 1764514800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 13, ETeam::Parma, ETeam::Udinese, 1764514800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 13, ETeam::Lecce, ETeam::Torino, 1764514800000 });

    // Week 14
    matches.push_back({ ELeague::SerieA, "25/26", 14, ETeam::Verona, ETeam::Atalanta, 1765119600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 14, ETeam::Udinese, ETeam::Genoa, 1765119600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 14, ETeam::Pisa, ETeam::Parma, 1765119600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 14, ETeam::Cremonese, ETeam::Lecce, 1765119600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 14, ETeam::Napoli, ETeam::Juventus, 1765119600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 14, ETeam::Sassuolo, ETeam::Fiorentina, 1765119600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 14, ETeam::Cagliari, ETeam::Roma, 1765119600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 14, ETeam::Torino, ETeam::ACMilan, 1765119600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 14, ETeam::Lazio, ETeam::Bologna, 1765119600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 14, ETeam::InterMilan, ETeam::Como, 1765119600000 });

    // Week 15
    matches.push_back({ ELeague::SerieA, "25/26", 15, ETeam::Udinese, ETeam::Napoli, 1765724400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 15, ETeam::Lecce, ETeam::Pisa, 1765724400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 15, ETeam::Torino, ETeam::Cremonese, 1765724400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 15, ETeam::Fiorentina, ETeam::Verona, 1765724400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 15, ETeam::Atalanta, ETeam::Cagliari, 1765724400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 15, ETeam::Parma, ETeam::Lazio, 1765724400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 15, ETeam::Roma, ETeam::Como, 1765724400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 15, ETeam::Genoa, ETeam::InterMilan, 1765724400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 15, ETeam::ACMilan, ETeam::Sassuolo, 1765724400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 15, ETeam::Bologna, ETeam::Juventus, 1765724400000 });

    // Week 16
    matches.push_back({ ELeague::SerieA, "25/26", 16, ETeam::Fiorentina, ETeam::Udinese, 1766329200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 16, ETeam::Verona, ETeam::Bologna, 1766329200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 16, ETeam::Genoa, ETeam::Atalanta, 1766329200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 16, ETeam::InterMilan, ETeam::Lecce, 1766329200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 16, ETeam::Napoli, ETeam::Parma, 1766329200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 16, ETeam::Cagliari, ETeam::Pisa, 1766329200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 16, ETeam::Como, ETeam::ACMilan, 1766329200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 16, ETeam::Sassuolo, ETeam::Torino, 1766329200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 16, ETeam::Lazio, ETeam::Cremonese, 1766329200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 16, ETeam::Juventus, ETeam::Roma, 1766329200000 });

    // Week 17
    matches.push_back({ ELeague::SerieA, "25/26", 17, ETeam::Cremonese, ETeam::Napoli, 1766934000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 17, ETeam::Torino, ETeam::Cagliari, 1766934000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 17, ETeam::Bologna, ETeam::Sassuolo, 1766934000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 17, ETeam::Atalanta, ETeam::InterMilan, 1766934000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 17, ETeam::Pisa, ETeam::Juventus, 1766934000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 17, ETeam::Lecce, ETeam::Como, 1766934000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 17, ETeam::Udinese, ETeam::Lazio, 1766934000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 17, ETeam::Parma, ETeam::Fiorentina, 1766934000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 17, ETeam::ACMilan, ETeam::Verona, 1766934000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 17, ETeam::Roma, ETeam::Genoa, 1766934000000 });

    // Week 18
    matches.push_back({ ELeague::SerieA, "25/26", 18, ETeam::Juventus, ETeam::Lecce, 1767452400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 18, ETeam::Sassuolo, ETeam::Parma, 1767452400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 18, ETeam::Atalanta, ETeam::Roma, 1767452400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 18, ETeam::InterMilan, ETeam::Bologna, 1767452400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 18, ETeam::Genoa, ETeam::Pisa, 1767452400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 18, ETeam::Como, ETeam::Udinese, 1767452400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 18, ETeam::Verona, ETeam::Torino, 1767452400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 18, ETeam::Fiorentina, ETeam::Cremonese, 1767452400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 18, ETeam::Lazio, ETeam::Napoli, 1767452400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 18, ETeam::Cagliari, ETeam::ACMilan, 1767452400000 });

    // Week 19
    matches.push_back({ ELeague::SerieA, "25/26", 19, ETeam::Sassuolo, ETeam::Juventus, 1767711600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 19, ETeam::Cremonese, ETeam::Cagliari, 1767711600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 19, ETeam::Lazio, ETeam::Fiorentina, 1767711600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 19, ETeam::Lecce, ETeam::Roma, 1767711600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 19, ETeam::Parma, ETeam::InterMilan, 1767711600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 19, ETeam::ACMilan, ETeam::Genoa, 1767711600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 19, ETeam::Pisa, ETeam::Como, 1767711600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 19, ETeam::Torino, ETeam::Udinese, 1767711600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 19, ETeam::Bologna, ETeam::Atalanta, 1767711600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 19, ETeam::Napoli, ETeam::Verona, 1767711600000 });

    // Week 20
    matches.push_back({ ELeague::SerieA, "25/26", 20, ETeam::Genoa, ETeam::Cagliari, 1768143600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 20, ETeam::Fiorentina, ETeam::ACMilan, 1768143600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 20, ETeam::Juventus, ETeam::Cremonese, 1768143600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 20, ETeam::Roma, ETeam::Sassuolo, 1768143600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 20, ETeam::Verona, ETeam::Lazio, 1768143600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 20, ETeam::Udinese, ETeam::Pisa, 1768143600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 20, ETeam::Como, ETeam::Bologna, 1768143600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 20, ETeam::InterMilan, ETeam::Napoli, 1768143600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 20, ETeam::Lecce, ETeam::Parma, 1768143600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 20, ETeam::Atalanta, ETeam::Torino, 1768143600000 });

    // Week 21
    matches.push_back({ ELeague::SerieA, "25/26", 21, ETeam::Cremonese, ETeam::Verona, 1768748400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 21, ETeam::Parma, ETeam::Genoa, 1768748400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 21, ETeam::Pisa, ETeam::Atalanta, 1768748400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 21, ETeam::Torino, ETeam::Roma, 1768748400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 21, ETeam::Udinese, ETeam::InterMilan, 1768748400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 21, ETeam::Bologna, ETeam::Fiorentina, 1768748400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 21, ETeam::Lazio, ETeam::Como, 1768748400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 21, ETeam::Napoli, ETeam::Sassuolo, 1768748400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 21, ETeam::ACMilan, ETeam::Lecce, 1768748400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 21, ETeam::Cagliari, ETeam::Juventus, 1768748400000 });

    // Week 22
    matches.push_back({ ELeague::SerieA, "25/26", 22, ETeam::Genoa, ETeam::Bologna, 1769353200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 22, ETeam::Juventus, ETeam::Napoli, 1769353200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 22, ETeam::Roma, ETeam::ACMilan, 1769353200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 22, ETeam::Lecce, ETeam::Lazio, 1769353200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 22, ETeam::Atalanta, ETeam::Parma, 1769353200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 22, ETeam::Fiorentina, ETeam::Cagliari, 1769353200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 22, ETeam::InterMilan, ETeam::Pisa, 1769353200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 22, ETeam::Sassuolo, ETeam::Cremonese, 1769353200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 22, ETeam::Verona, ETeam::Udinese, 1769353200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 22, ETeam::Como, ETeam::Torino, 1769353200000 });

    // Week 23
    matches.push_back({ ELeague::SerieA, "25/26", 23, ETeam::Udinese, ETeam::Roma, 1769958000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 23, ETeam::Como, ETeam::Atalanta, 1769958000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 23, ETeam::Torino, ETeam::Lecce, 1769958000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 23, ETeam::Cagliari, ETeam::Verona, 1769958000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 23, ETeam::Cremonese, ETeam::InterMilan, 1769958000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 23, ETeam::Parma, ETeam::Juventus, 1769958000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 23, ETeam::Pisa, ETeam::Sassuolo, 1769958000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 23, ETeam::Lazio, ETeam::Genoa, 1769958000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 23, ETeam::Bologna, ETeam::ACMilan, 1769958000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 23, ETeam::Napoli, ETeam::Fiorentina, 1769958000000 });

    // Week 24
    matches.push_back({ ELeague::SerieA, "25/26", 24, ETeam::Juventus, ETeam::Lazio, 1770562800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 24, ETeam::Roma, ETeam::Cagliari, 1770562800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 24, ETeam::Fiorentina, ETeam::Torino, 1770562800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 24, ETeam::Lecce, ETeam::Udinese, 1770562800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 24, ETeam::Bologna, ETeam::Parma, 1770562800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 24, ETeam::ACMilan, ETeam::Como, 1770562800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 24, ETeam::Verona, ETeam::Pisa, 1770562800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 24, ETeam::Sassuolo, ETeam::InterMilan, 1770562800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 24, ETeam::Atalanta, ETeam::Cremonese, 1770562800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 24, ETeam::Genoa, ETeam::Napoli, 1770562800000 });

    // Week 25
    matches.push_back({ ELeague::SerieA, "25/26", 25, ETeam::Torino, ETeam::Bologna, 1771167600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 25, ETeam::Cremonese, ETeam::Genoa, 1771167600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 25, ETeam::Napoli, ETeam::Roma, 1771167600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 25, ETeam::InterMilan, ETeam::Juventus, 1771167600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 25, ETeam::Lazio, ETeam::Atalanta, 1771167600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 25, ETeam::Como, ETeam::Fiorentina, 1771167600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 25, ETeam::Pisa, ETeam::ACMilan, 1771167600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 25, ETeam::Parma, ETeam::Verona, 1771167600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 25, ETeam::Udinese, ETeam::Sassuolo, 1771167600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 25, ETeam::Cagliari, ETeam::Lecce, 1771167600000 });

    // Week 26
    matches.push_back({ ELeague::SerieA, "25/26", 26, ETeam::Genoa, ETeam::Torino, 1771772400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 26, ETeam::Juventus, ETeam::Como, 1771772400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 26, ETeam::Roma, ETeam::Cremonese, 1771772400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 26, ETeam::ACMilan, ETeam::Parma, 1771772400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 26, ETeam::Cagliari, ETeam::Lazio, 1771772400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 26, ETeam::Sassuolo, ETeam::Verona, 1771772400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 26, ETeam::Lecce, ETeam::InterMilan, 1771772400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 26, ETeam::Bologna, ETeam::Udinese, 1771772400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 26, ETeam::Fiorentina, ETeam::Pisa, 1771772400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 26, ETeam::Atalanta, ETeam::Napoli, 1771772400000 });

    // Week 27
    matches.push_back({ ELeague::SerieA, "25/26", 27, ETeam::Torino, ETeam::Lazio, 1772377200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 27, ETeam::Verona, ETeam::Napoli, 1772377200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 27, ETeam::Como, ETeam::Lecce, 1772377200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 27, ETeam::Pisa, ETeam::Bologna, 1772377200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 27, ETeam::Parma, ETeam::Cagliari, 1772377200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 27, ETeam::Roma, ETeam::Juventus, 1772377200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 27, ETeam::Sassuolo, ETeam::Atalanta, 1772377200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 27, ETeam::Cremonese, ETeam::ACMilan, 1772377200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 27, ETeam::Udinese, ETeam::Fiorentina, 1772377200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 27, ETeam::InterMilan, ETeam::Genoa, 1772377200000 });

    // Week 28
    matches.push_back({ ELeague::SerieA, "25/26", 28, ETeam::Cagliari, ETeam::Como, 1772982000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 28, ETeam::Genoa, ETeam::Roma, 1772982000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 28, ETeam::Napoli, ETeam::Torino, 1772982000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 28, ETeam::Lazio, ETeam::Sassuolo, 1772982000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 28, ETeam::Juventus, ETeam::Pisa, 1772982000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 28, ETeam::Lecce, ETeam::Cremonese, 1772982000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 28, ETeam::Atalanta, ETeam::Udinese, 1772982000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 28, ETeam::Bologna, ETeam::Verona, 1772982000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 28, ETeam::ACMilan, ETeam::InterMilan, 1772982000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 28, ETeam::Fiorentina, ETeam::Parma, 1772982000000 });

    // Week 29
    matches.push_back({ ELeague::SerieA, "25/26", 29, ETeam::Verona, ETeam::Genoa, 1773586800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 29, ETeam::Cremonese, ETeam::Fiorentina, 1773586800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 29, ETeam::Napoli, ETeam::Lecce, 1773586800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 29, ETeam::InterMilan, ETeam::Atalanta, 1773586800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 29, ETeam::Pisa, ETeam::Cagliari, 1773586800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 29, ETeam::Lazio, ETeam::ACMilan, 1773586800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 29, ETeam::Sassuolo, ETeam::Bologna, 1773586800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 29, ETeam::Udinese, ETeam::Juventus, 1773586800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 29, ETeam::Torino, ETeam::Parma, 1773586800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 29, ETeam::Como, ETeam::Roma, 1773586800000 });

    // Week 30
    matches.push_back({ ELeague::SerieA, "25/26", 30, ETeam::ACMilan, ETeam::Torino, 1774191600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 30, ETeam::Atalanta, ETeam::Verona, 1774191600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 30, ETeam::Bologna, ETeam::Lazio, 1774191600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 30, ETeam::Cagliari, ETeam::Napoli, 1774191600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 30, ETeam::Genoa, ETeam::Udinese, 1774191600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 30, ETeam::Parma, ETeam::Cremonese, 1774191600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 30, ETeam::Juventus, ETeam::Sassuolo, 1774191600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 30, ETeam::Como, ETeam::Pisa, 1774191600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 30, ETeam::Roma, ETeam::Lecce, 1774191600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 30, ETeam::Fiorentina, ETeam::InterMilan, 1774191600000 });

    // Week 31
    matches.push_back({ ELeague::SerieA, "25/26", 31, ETeam::Cremonese, ETeam::Bologna, 1775314800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 31, ETeam::Sassuolo, ETeam::Cagliari, 1775314800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 31, ETeam::Udinese, ETeam::Como, 1775314800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 31, ETeam::InterMilan, ETeam::Roma, 1775314800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 31, ETeam::Lecce, ETeam::Atalanta, 1775314800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 31, ETeam::Lazio, ETeam::Parma, 1775314800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 31, ETeam::Verona, ETeam::Fiorentina, 1775314800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 31, ETeam::Napoli, ETeam::ACMilan, 1775314800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 31, ETeam::Pisa, ETeam::Torino, 1775314800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 31, ETeam::Juventus, ETeam::Genoa, 1775314800000 });

    // Week 32
    matches.push_back({ ELeague::SerieA, "25/26", 32, ETeam::Cagliari, ETeam::Cremonese, 1776006000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 32, ETeam::Roma, ETeam::Pisa, 1776006000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 32, ETeam::Genoa, ETeam::Sassuolo, 1776006000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 32, ETeam::Fiorentina, ETeam::Lazio, 1776006000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 32, ETeam::Parma, ETeam::Napoli, 1776006000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 32, ETeam::Como, ETeam::InterMilan, 1776006000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 32, ETeam::Torino, ETeam::Verona, 1776006000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 32, ETeam::ACMilan, ETeam::Udinese, 1776006000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 32, ETeam::Atalanta, ETeam::Juventus, 1776006000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 32, ETeam::Bologna, ETeam::Lecce, 1776006000000 });

    // Week 33
    matches.push_back({ ELeague::SerieA, "25/26", 33, ETeam::Sassuolo, ETeam::Como, 1776610800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 33, ETeam::Pisa, ETeam::Genoa, 1776610800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 33, ETeam::Verona, ETeam::ACMilan, 1776610800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 33, ETeam::Juventus, ETeam::Bologna, 1776610800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 33, ETeam::Lecce, ETeam::Fiorentina, 1776610800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 33, ETeam::Udinese, ETeam::Parma, 1776610800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 33, ETeam::Cremonese, ETeam::Torino, 1776610800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 33, ETeam::InterMilan, ETeam::Cagliari, 1776610800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 33, ETeam::Roma, ETeam::Atalanta, 1776610800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 33, ETeam::Napoli, ETeam::Lazio, 1776610800000 });

    // Week 34
    matches.push_back({ ELeague::SerieA, "25/26", 34, ETeam::Torino, ETeam::InterMilan, 1777215600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 34, ETeam::Parma, ETeam::Pisa, 1777215600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 34, ETeam::Genoa, ETeam::Como, 1777215600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 34, ETeam::Bologna, ETeam::Roma, 1777215600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 34, ETeam::ACMilan, ETeam::Juventus, 1777215600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 34, ETeam::Fiorentina, ETeam::Sassuolo, 1777215600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 34, ETeam::Verona, ETeam::Lecce, 1777215600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 34, ETeam::Napoli, ETeam::Cremonese, 1777215600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 34, ETeam::Lazio, ETeam::Udinese, 1777215600000 });
    matches.push_back({ ELeague::SerieA, "25/26", 34, ETeam::Cagliari, ETeam::Atalanta, 1777215600000 });

    // Week 35
    matches.push_back({ ELeague::SerieA, "25/26", 35, ETeam::Atalanta, ETeam::Genoa, 1777820400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 35, ETeam::Pisa, ETeam::Lecce, 1777820400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 35, ETeam::Como, ETeam::Napoli, 1777820400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 35, ETeam::InterMilan, ETeam::Parma, 1777820400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 35, ETeam::Sassuolo, ETeam::ACMilan, 1777820400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 35, ETeam::Bologna, ETeam::Cagliari, 1777820400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 35, ETeam::Udinese, ETeam::Torino, 1777820400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 35, ETeam::Roma, ETeam::Fiorentina, 1777820400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 35, ETeam::Juventus, ETeam::Verona, 1777820400000 });
    matches.push_back({ ELeague::SerieA, "25/26", 35, ETeam::Cremonese, ETeam::Lazio, 1777820400000 });

    // Week 36
    matches.push_back({ ELeague::SerieA, "25/26", 36, ETeam::Napoli, ETeam::Bologna, 1778425200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 36, ETeam::Verona, ETeam::Como, 1778425200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 36, ETeam::ACMilan, ETeam::Atalanta, 1778425200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 36, ETeam::Lecce, ETeam::Juventus, 1778425200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 36, ETeam::Cagliari, ETeam::Udinese, 1778425200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 36, ETeam::Cremonese, ETeam::Pisa, 1778425200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 36, ETeam::Fiorentina, ETeam::Genoa, 1778425200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 36, ETeam::Torino, ETeam::Sassuolo, 1778425200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 36, ETeam::Lazio, ETeam::InterMilan, 1778425200000 });
    matches.push_back({ ELeague::SerieA, "25/26", 36, ETeam::Parma, ETeam::Roma, 1778425200000 });

    // Week 37
    matches.push_back({ ELeague::SerieA, "25/26", 37, ETeam::Sassuolo, ETeam::Lecce, 1779030000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 37, ETeam::Juventus, ETeam::Fiorentina, 1779030000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 37, ETeam::Pisa, ETeam::Napoli, 1779030000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 37, ETeam::Atalanta, ETeam::Bologna, 1779030000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 37, ETeam::Udinese, ETeam::Cremonese, 1779030000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 37, ETeam::Roma, ETeam::Lazio, 1779030000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 37, ETeam::InterMilan, ETeam::Verona, 1779030000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 37, ETeam::Como, ETeam::Parma, 1779030000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 37, ETeam::Cagliari, ETeam::Torino, 1779030000000 });
    matches.push_back({ ELeague::SerieA, "25/26", 37, ETeam::Genoa, ETeam::ACMilan, 1779030000000 });

    // Week 38
    matches.push_back({ ELeague::SerieA, "25/26", 38, ETeam::Cremonese, ETeam::Como, 1779634800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 38, ETeam::Napoli, ETeam::Udinese, 1779634800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 38, ETeam::Bologna, ETeam::InterMilan, 1779634800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 38, ETeam::Lazio, ETeam::Pisa, 1779634800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 38, ETeam::Parma, ETeam::Sassuolo, 1779634800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 38, ETeam::Verona, ETeam::Roma, 1779634800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 38, ETeam::Fiorentina, ETeam::Atalanta, 1779634800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 38, ETeam::Lecce, ETeam::Genoa, 1779634800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 38, ETeam::ACMilan, ETeam::Cagliari, 1779634800000 });
    matches.push_back({ ELeague::SerieA, "25/26", 38, ETeam::Torino, ETeam::Juventus, 1779634800000 });

    for (auto& m : matches)
    {
        std::string sql = "insert into matches(league, season, week, team1, team2, match_date) values ("
            + std::to_string(int(m.League)) + ", '"
            + m.Season + "', "
            + std::to_string(m.Week) + ", "
            + std::to_string((int)m.Team1) + ", "
            + std::to_string((int)m.Team2) + ", "
            + std::to_string(m.Date) + ");";

        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitLaLiga25_26(PGconn* pg)
{
    std::vector<Match> matches;
    // Week 1
    matches.push_back({ ELeague::LaLiga, "25/26", 1, ETeam::CeltaVigo, ETeam::Getafe, 1755442800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 1, ETeam::Mallorca, ETeam::Barcelona, 1755442800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 1, ETeam::Valencia, ETeam::RealSociedad, 1755442800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 1, ETeam::Girona, ETeam::RayoVallecano, 1755442800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 1, ETeam::Elche, ETeam::RealBetis, 1755442800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 1, ETeam::Villarreal, ETeam::Oviedo, 1755442800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 1, ETeam::Alaves, ETeam::Levante, 1755442800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 1, ETeam::RealMadrid, ETeam::Osasuna, 1755442800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 1, ETeam::AthleticClub, ETeam::Sevilla, 1755442800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 1, ETeam::Espanyol, ETeam::AtleticoMadrid, 1755442800000 });

    // Week 2
    matches.push_back({ ELeague::LaLiga, "25/26", 2, ETeam::Oviedo, ETeam::RealMadrid, 1756047600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 2, ETeam::RealSociedad, ETeam::Espanyol, 1756047600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 2, ETeam::AthleticClub, ETeam::RayoVallecano, 1756047600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 2, ETeam::Osasuna, ETeam::Valencia, 1756047600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 2, ETeam::Levante, ETeam::Barcelona, 1756047600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 2, ETeam::AtleticoMadrid, ETeam::Elche, 1756047600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 2, ETeam::Sevilla, ETeam::Getafe, 1756047600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 2, ETeam::RealBetis, ETeam::Alaves, 1756047600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 2, ETeam::Villarreal, ETeam::Girona, 1756047600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 2, ETeam::Mallorca, ETeam::CeltaVigo, 1756047600000 });

    // Week 3
    matches.push_back({ ELeague::LaLiga, "25/26", 3, ETeam::Girona, ETeam::Sevilla, 1756652400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 3, ETeam::CeltaVigo, ETeam::Villarreal, 1756652400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 3, ETeam::RealMadrid, ETeam::Mallorca, 1756652400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 3, ETeam::RealBetis, ETeam::AthleticClub, 1756652400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 3, ETeam::RayoVallecano, ETeam::Barcelona, 1756652400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 3, ETeam::Valencia, ETeam::Getafe, 1756652400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 3, ETeam::Oviedo, ETeam::RealSociedad, 1756652400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 3, ETeam::Espanyol, ETeam::Osasuna, 1756652400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 3, ETeam::Alaves, ETeam::AtleticoMadrid, 1756652400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 3, ETeam::Elche, ETeam::Levante, 1756652400000 });

    // Week 4
    matches.push_back({ ELeague::LaLiga, "25/26", 4, ETeam::Barcelona, ETeam::Valencia, 1757862000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 4, ETeam::AthleticClub, ETeam::Alaves, 1757862000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 4, ETeam::Getafe, ETeam::Oviedo, 1757862000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 4, ETeam::RealSociedad, ETeam::RealMadrid, 1757862000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 4, ETeam::Levante, ETeam::RealBetis, 1757862000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 4, ETeam::Osasuna, ETeam::RayoVallecano, 1757862000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 4, ETeam::Sevilla, ETeam::Elche, 1757862000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 4, ETeam::AtleticoMadrid, ETeam::Villarreal, 1757862000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 4, ETeam::CeltaVigo, ETeam::Girona, 1757862000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 4, ETeam::Espanyol, ETeam::Mallorca, 1757862000000 });

    // Week 5
    matches.push_back({ ELeague::LaLiga, "25/26", 5, ETeam::RealMadrid, ETeam::Espanyol, 1758466800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 5, ETeam::Mallorca, ETeam::AtleticoMadrid, 1758466800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 5, ETeam::Villarreal, ETeam::Osasuna, 1758466800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 5, ETeam::Barcelona, ETeam::Getafe, 1758466800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 5, ETeam::RayoVallecano, ETeam::CeltaVigo, 1758466800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 5, ETeam::Alaves, ETeam::Sevilla, 1758466800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 5, ETeam::Elche, ETeam::Oviedo, 1758466800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 5, ETeam::Valencia, ETeam::AthleticClub, 1758466800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 5, ETeam::RealBetis, ETeam::RealSociedad, 1758466800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 5, ETeam::Girona, ETeam::Levante, 1758466800000 });

    // Week 6
    matches.push_back({ ELeague::LaLiga, "25/26", 6, ETeam::Espanyol, ETeam::Valencia, 1758726000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 6, ETeam::Getafe, ETeam::Alaves, 1758726000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 6, ETeam::RealSociedad, ETeam::Mallorca, 1758726000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 6, ETeam::Sevilla, ETeam::Villarreal, 1758726000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 6, ETeam::AthleticClub, ETeam::Girona, 1758726000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 6, ETeam::Oviedo, ETeam::Barcelona, 1758726000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 6, ETeam::Osasuna, ETeam::Elche, 1758726000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 6, ETeam::CeltaVigo, ETeam::RealBetis, 1758726000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 6, ETeam::Levante, ETeam::RealMadrid, 1758726000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 6, ETeam::AtleticoMadrid, ETeam::RayoVallecano, 1758726000000 });

    // Week 7
    matches.push_back({ ELeague::LaLiga, "25/26", 7, ETeam::Mallorca, ETeam::Alaves, 1759071600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 7, ETeam::AtleticoMadrid, ETeam::RealMadrid, 1759071600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 7, ETeam::Getafe, ETeam::Levante, 1759071600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 7, ETeam::Elche, ETeam::CeltaVigo, 1759071600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 7, ETeam::RealBetis, ETeam::Osasuna, 1759071600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 7, ETeam::Barcelona, ETeam::RealSociedad, 1759071600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 7, ETeam::Girona, ETeam::Espanyol, 1759071600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 7, ETeam::Villarreal, ETeam::AthleticClub, 1759071600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 7, ETeam::Valencia, ETeam::Oviedo, 1759071600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 7, ETeam::RayoVallecano, ETeam::Sevilla, 1759071600000 });

    // Week 8
    matches.push_back({ ELeague::LaLiga, "25/26", 8, ETeam::Alaves, ETeam::Elche, 1759676400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 8, ETeam::RealSociedad, ETeam::RayoVallecano, 1759676400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 8, ETeam::CeltaVigo, ETeam::AtleticoMadrid, 1759676400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 8, ETeam::Osasuna, ETeam::Getafe, 1759676400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 8, ETeam::Sevilla, ETeam::Barcelona, 1759676400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 8, ETeam::RealMadrid, ETeam::Villarreal, 1759676400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 8, ETeam::Girona, ETeam::Valencia, 1759676400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 8, ETeam::Espanyol, ETeam::RealBetis, 1759676400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 8, ETeam::Oviedo, ETeam::Levante, 1759676400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 8, ETeam::AthleticClub, ETeam::Mallorca, 1759676400000 });

    // Week 9
    matches.push_back({ ELeague::LaLiga, "25/26", 9, ETeam::Villarreal, ETeam::RealBetis, 1760886000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 9, ETeam::Alaves, ETeam::Valencia, 1760886000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 9, ETeam::CeltaVigo, ETeam::RealSociedad, 1760886000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 9, ETeam::Sevilla, ETeam::Mallorca, 1760886000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 9, ETeam::Levante, ETeam::RayoVallecano, 1760886000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 9, ETeam::Elche, ETeam::AthleticClub, 1760886000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 9, ETeam::Barcelona, ETeam::Girona, 1760886000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 9, ETeam::Getafe, ETeam::RealMadrid, 1760886000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 9, ETeam::AtleticoMadrid, ETeam::Osasuna, 1760886000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 9, ETeam::Oviedo, ETeam::Espanyol, 1760886000000 });

    // Week 10
    matches.push_back({ ELeague::LaLiga, "25/26", 10, ETeam::Osasuna, ETeam::CeltaVigo, 1761490800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 10, ETeam::Valencia, ETeam::Villarreal, 1761490800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 10, ETeam::RayoVallecano, ETeam::Alaves, 1761490800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 10, ETeam::AthleticClub, ETeam::Getafe, 1761490800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 10, ETeam::Mallorca, ETeam::Levante, 1761490800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 10, ETeam::Girona, ETeam::Oviedo, 1761490800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 10, ETeam::RealBetis, ETeam::AtleticoMadrid, 1761490800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 10, ETeam::Espanyol, ETeam::Elche, 1761490800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 10, ETeam::RealMadrid, ETeam::Barcelona, 1761490800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 10, ETeam::RealSociedad, ETeam::Sevilla, 1761490800000 });

    // Week 11
    matches.push_back({ ELeague::LaLiga, "25/26", 11, ETeam::Levante, ETeam::CeltaVigo, 1762095600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 11, ETeam::RealMadrid, ETeam::Valencia, 1762095600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 11, ETeam::RealSociedad, ETeam::AthleticClub, 1762095600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 11, ETeam::Alaves, ETeam::Espanyol, 1762095600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 11, ETeam::Getafe, ETeam::Girona, 1762095600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 11, ETeam::Oviedo, ETeam::Osasuna, 1762095600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 11, ETeam::AtleticoMadrid, ETeam::Sevilla, 1762095600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 11, ETeam::Barcelona, ETeam::Elche, 1762095600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 11, ETeam::RealBetis, ETeam::Mallorca, 1762095600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 11, ETeam::Villarreal, ETeam::RayoVallecano, 1762095600000 });

    // Week 12
    matches.push_back({ ELeague::LaLiga, "25/26", 12, ETeam::Sevilla, ETeam::Osasuna, 1762700400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 12, ETeam::AtleticoMadrid, ETeam::Levante, 1762700400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 12, ETeam::Valencia, ETeam::RealBetis, 1762700400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 12, ETeam::CeltaVigo, ETeam::Barcelona, 1762700400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 12, ETeam::Girona, ETeam::Alaves, 1762700400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 12, ETeam::AthleticClub, ETeam::Oviedo, 1762700400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 12, ETeam::RayoVallecano, ETeam::RealMadrid, 1762700400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 12, ETeam::Elche, ETeam::RealSociedad, 1762700400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 12, ETeam::Mallorca, ETeam::Getafe, 1762700400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 12, ETeam::Espanyol, ETeam::Villarreal, 1762700400000 });

    // Week 13
    matches.push_back({ ELeague::LaLiga, "25/26", 13, ETeam::Elche, ETeam::RealMadrid, 1763910000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 13, ETeam::Getafe, ETeam::AtleticoMadrid, 1763910000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 13, ETeam::Villarreal, ETeam::Mallorca, 1763910000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 13, ETeam::Barcelona, ETeam::AthleticClub, 1763910000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 13, ETeam::Osasuna, ETeam::RealSociedad, 1763910000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 13, ETeam::RealBetis, ETeam::Girona, 1763910000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 13, ETeam::Alaves, ETeam::CeltaVigo, 1763910000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 13, ETeam::Espanyol, ETeam::Sevilla, 1763910000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 13, ETeam::Valencia, ETeam::Levante, 1763910000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 13, ETeam::Oviedo, ETeam::RayoVallecano, 1763910000000 });

    // Week 14
    matches.push_back({ ELeague::LaLiga, "25/26", 14, ETeam::Levante, ETeam::AthleticClub, 1764514800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 14, ETeam::RealSociedad, ETeam::Villarreal, 1764514800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 14, ETeam::Mallorca, ETeam::Osasuna, 1764514800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 14, ETeam::AtleticoMadrid, ETeam::Oviedo, 1764514800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 14, ETeam::Barcelona, ETeam::Alaves, 1764514800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 14, ETeam::Getafe, ETeam::Elche, 1764514800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 14, ETeam::RayoVallecano, ETeam::Valencia, 1764514800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 14, ETeam::Girona, ETeam::RealMadrid, 1764514800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 14, ETeam::CeltaVigo, ETeam::Espanyol, 1764514800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 14, ETeam::Sevilla, ETeam::RealBetis, 1764514800000 });

    // Week 15
    matches.push_back({ ELeague::LaLiga, "25/26", 15, ETeam::Espanyol, ETeam::RayoVallecano, 1765119600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 15, ETeam::AthleticClub, ETeam::AtleticoMadrid, 1765119600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 15, ETeam::Villarreal, ETeam::Getafe, 1765119600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 15, ETeam::Osasuna, ETeam::Levante, 1765119600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 15, ETeam::Valencia, ETeam::Sevilla, 1765119600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 15, ETeam::Oviedo, ETeam::Mallorca, 1765119600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 15, ETeam::RealMadrid, ETeam::CeltaVigo, 1765119600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 15, ETeam::Alaves, ETeam::RealSociedad, 1765119600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 15, ETeam::Elche, ETeam::Girona, 1765119600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 15, ETeam::RealBetis, ETeam::Barcelona, 1765119600000 });

    // Week 16
    matches.push_back({ ELeague::LaLiga, "25/26", 16, ETeam::Sevilla, ETeam::Oviedo, 1765724400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 16, ETeam::RayoVallecano, ETeam::RealBetis, 1765724400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 16, ETeam::AtleticoMadrid, ETeam::Valencia, 1765724400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 16, ETeam::Barcelona, ETeam::Osasuna, 1765724400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 16, ETeam::Levante, ETeam::Villarreal, 1765724400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 16, ETeam::RealSociedad, ETeam::Girona, 1765724400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 16, ETeam::Mallorca, ETeam::Elche, 1765724400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 16, ETeam::CeltaVigo, ETeam::AthleticClub, 1765724400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 16, ETeam::Alaves, ETeam::RealMadrid, 1765724400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 16, ETeam::Getafe, ETeam::Espanyol, 1765724400000 });

    // Week 17
    matches.push_back({ ELeague::LaLiga, "25/26", 17, ETeam::RealBetis, ETeam::Getafe, 1766329200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 17, ETeam::AthleticClub, ETeam::Espanyol, 1766329200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 17, ETeam::Osasuna, ETeam::Alaves, 1766329200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 17, ETeam::Oviedo, ETeam::CeltaVigo, 1766329200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 17, ETeam::RealMadrid, ETeam::Sevilla, 1766329200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 17, ETeam::Villarreal, ETeam::Barcelona, 1766329200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 17, ETeam::Girona, ETeam::AtleticoMadrid, 1766329200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 17, ETeam::Valencia, ETeam::Mallorca, 1766329200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 17, ETeam::Elche, ETeam::RayoVallecano, 1766329200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 17, ETeam::Levante, ETeam::RealSociedad, 1766329200000 });

    // Week 18
    matches.push_back({ ELeague::LaLiga, "25/26", 18, ETeam::RealMadrid, ETeam::RealBetis, 1767538800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 18, ETeam::RealSociedad, ETeam::AtleticoMadrid, 1767538800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 18, ETeam::Osasuna, ETeam::AthleticClub, 1767538800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 18, ETeam::Elche, ETeam::Villarreal, 1767538800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 18, ETeam::RayoVallecano, ETeam::Getafe, 1767538800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 18, ETeam::CeltaVigo, ETeam::Valencia, 1767538800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 18, ETeam::Alaves, ETeam::Oviedo, 1767538800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 18, ETeam::Mallorca, ETeam::Girona, 1767538800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 18, ETeam::Sevilla, ETeam::Levante, 1767538800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 18, ETeam::Espanyol, ETeam::Barcelona, 1767538800000 });

    // Week 19
    matches.push_back({ ELeague::LaLiga, "25/26", 19, ETeam::Villarreal, ETeam::Alaves, 1768143600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 19, ETeam::Levante, ETeam::Espanyol, 1768143600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 19, ETeam::Getafe, ETeam::RealSociedad, 1768143600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 19, ETeam::RayoVallecano, ETeam::Mallorca, 1768143600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 19, ETeam::AthleticClub, ETeam::RealMadrid, 1768143600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 19, ETeam::Sevilla, ETeam::CeltaVigo, 1768143600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 19, ETeam::Valencia, ETeam::Elche, 1768143600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 19, ETeam::Girona, ETeam::Osasuna, 1768143600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 19, ETeam::Barcelona, ETeam::AtleticoMadrid, 1768143600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 19, ETeam::Oviedo, ETeam::RealBetis, 1768143600000 });

    // Week 20
    matches.push_back({ ELeague::LaLiga, "25/26", 20, ETeam::Mallorca, ETeam::AthleticClub, 1768748400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 20, ETeam::Osasuna, ETeam::Oviedo, 1768748400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 20, ETeam::RealSociedad, ETeam::Barcelona, 1768748400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 20, ETeam::Getafe, ETeam::Valencia, 1768748400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 20, ETeam::Elche, ETeam::Sevilla, 1768748400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 20, ETeam::RealBetis, ETeam::Villarreal, 1768748400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 20, ETeam::AtleticoMadrid, ETeam::Alaves, 1768748400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 20, ETeam::Espanyol, ETeam::Girona, 1768748400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 20, ETeam::RealMadrid, ETeam::Levante, 1768748400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 20, ETeam::CeltaVigo, ETeam::RayoVallecano, 1768748400000 });

    // Week 21
    matches.push_back({ ELeague::LaLiga, "25/26", 21, ETeam::RayoVallecano, ETeam::Osasuna, 1769353200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 21, ETeam::Barcelona, ETeam::Oviedo, 1769353200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 21, ETeam::Alaves, ETeam::RealBetis, 1769353200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 21, ETeam::AtleticoMadrid, ETeam::Mallorca, 1769353200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 21, ETeam::Levante, ETeam::Elche, 1769353200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 21, ETeam::Sevilla, ETeam::AthleticClub, 1769353200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 21, ETeam::Girona, ETeam::Getafe, 1769353200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 21, ETeam::Villarreal, ETeam::RealMadrid, 1769353200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 21, ETeam::Valencia, ETeam::Espanyol, 1769353200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 21, ETeam::RealSociedad, ETeam::CeltaVigo, 1769353200000 });

    // Week 22
    matches.push_back({ ELeague::LaLiga, "25/26", 22, ETeam::RealMadrid, ETeam::RayoVallecano, 1769958000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 22, ETeam::AthleticClub, ETeam::RealSociedad, 1769958000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 22, ETeam::Osasuna, ETeam::Villarreal, 1769958000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 22, ETeam::RealBetis, ETeam::Valencia, 1769958000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 22, ETeam::Elche, ETeam::Barcelona, 1769958000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 22, ETeam::Levante, ETeam::AtleticoMadrid, 1769958000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 22, ETeam::Getafe, ETeam::CeltaVigo, 1769958000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 22, ETeam::Mallorca, ETeam::Sevilla, 1769958000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 22, ETeam::Espanyol, ETeam::Alaves, 1769958000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 22, ETeam::Oviedo, ETeam::Girona, 1769958000000 });

    // Week 23
    matches.push_back({ ELeague::LaLiga, "25/26", 23, ETeam::RayoVallecano, ETeam::Oviedo, 1770562800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 23, ETeam::AtleticoMadrid, ETeam::RealBetis, 1770562800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 23, ETeam::AthleticClub, ETeam::Levante, 1770562800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 23, ETeam::Alaves, ETeam::Getafe, 1770562800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 23, ETeam::Barcelona, ETeam::Mallorca, 1770562800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 23, ETeam::RealSociedad, ETeam::Elche, 1770562800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 23, ETeam::Valencia, ETeam::RealMadrid, 1770562800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 23, ETeam::Sevilla, ETeam::Girona, 1770562800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 23, ETeam::Villarreal, ETeam::Espanyol, 1770562800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 23, ETeam::CeltaVigo, ETeam::Osasuna, 1770562800000 });

    // Week 24
    matches.push_back({ ELeague::LaLiga, "25/26", 24, ETeam::Elche, ETeam::Osasuna, 1771167600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 24, ETeam::Girona, ETeam::Barcelona, 1771167600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 24, ETeam::Levante, ETeam::Valencia, 1771167600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 24, ETeam::Mallorca, ETeam::RealBetis, 1771167600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 24, ETeam::Getafe, ETeam::Villarreal, 1771167600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 24, ETeam::Oviedo, ETeam::AthleticClub, 1771167600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 24, ETeam::Sevilla, ETeam::Alaves, 1771167600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 24, ETeam::RayoVallecano, ETeam::AtleticoMadrid, 1771167600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 24, ETeam::RealMadrid, ETeam::RealSociedad, 1771167600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 24, ETeam::Espanyol, ETeam::CeltaVigo, 1771167600000 });

    // Week 25
    matches.push_back({ ELeague::LaLiga, "25/26", 25, ETeam::RealSociedad, ETeam::Oviedo, 1771772400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 25, ETeam::Getafe, ETeam::Sevilla, 1771772400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 25, ETeam::CeltaVigo, ETeam::Mallorca, 1771772400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 25, ETeam::RealBetis, ETeam::RayoVallecano, 1771772400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 25, ETeam::AthleticClub, ETeam::Elche, 1771772400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 25, ETeam::Villarreal, ETeam::Valencia, 1771772400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 25, ETeam::Alaves, ETeam::Girona, 1771772400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 25, ETeam::Osasuna, ETeam::RealMadrid, 1771772400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 25, ETeam::AtleticoMadrid, ETeam::Espanyol, 1771772400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 25, ETeam::Barcelona, ETeam::Levante, 1771772400000 });

    // Week 26
    matches.push_back({ ELeague::LaLiga, "25/26", 26, ETeam::Mallorca, ETeam::RealSociedad, 1772377200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 26, ETeam::RayoVallecano, ETeam::AthleticClub, 1772377200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 26, ETeam::Levante, ETeam::Alaves, 1772377200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 26, ETeam::Barcelona, ETeam::Villarreal, 1772377200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 26, ETeam::Oviedo, ETeam::AtleticoMadrid, 1772377200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 26, ETeam::Girona, ETeam::CeltaVigo, 1772377200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 26, ETeam::RealBetis, ETeam::Sevilla, 1772377200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 26, ETeam::Valencia, ETeam::Osasuna, 1772377200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 26, ETeam::RealMadrid, ETeam::Getafe, 1772377200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 26, ETeam::Elche, ETeam::Espanyol, 1772377200000 });

    // Week 27
    matches.push_back({ ELeague::LaLiga, "25/26", 27, ETeam::Villarreal, ETeam::Elche, 1772982000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 27, ETeam::CeltaVigo, ETeam::RealMadrid, 1772982000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 27, ETeam::AthleticClub, ETeam::Barcelona, 1772982000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 27, ETeam::Espanyol, ETeam::Oviedo, 1772982000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 27, ETeam::Osasuna, ETeam::Mallorca, 1772982000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 27, ETeam::Valencia, ETeam::Alaves, 1772982000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 27, ETeam::AtleticoMadrid, ETeam::RealSociedad, 1772982000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 27, ETeam::Sevilla, ETeam::RayoVallecano, 1772982000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 27, ETeam::Getafe, ETeam::RealBetis, 1772982000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 27, ETeam::Levante, ETeam::Girona, 1772982000000 });

    // Week 28
    matches.push_back({ ELeague::LaLiga, "25/26", 28, ETeam::RayoVallecano, ETeam::Levante, 1773586800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 28, ETeam::Alaves, ETeam::Villarreal, 1773586800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 28, ETeam::RealMadrid, ETeam::Elche, 1773586800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 28, ETeam::RealBetis, ETeam::CeltaVigo, 1773586800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 28, ETeam::RealSociedad, ETeam::Osasuna, 1773586800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 28, ETeam::AtleticoMadrid, ETeam::Getafe, 1773586800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 28, ETeam::Oviedo, ETeam::Valencia, 1773586800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 28, ETeam::Barcelona, ETeam::Sevilla, 1773586800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 28, ETeam::Girona, ETeam::AthleticClub, 1773586800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 28, ETeam::Mallorca, ETeam::Espanyol, 1773586800000 });

    // Week 29
    matches.push_back({ ELeague::LaLiga, "25/26", 29, ETeam::Barcelona, ETeam::RayoVallecano, 1774191600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 29, ETeam::Sevilla, ETeam::Valencia, 1774191600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 29, ETeam::AthleticClub, ETeam::RealBetis, 1774191600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 29, ETeam::Espanyol, ETeam::Getafe, 1774191600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 29, ETeam::Levante, ETeam::Oviedo, 1774191600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 29, ETeam::Osasuna, ETeam::Girona, 1774191600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 29, ETeam::CeltaVigo, ETeam::Alaves, 1774191600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 29, ETeam::Elche, ETeam::Mallorca, 1774191600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 29, ETeam::RealMadrid, ETeam::AtleticoMadrid, 1774191600000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 29, ETeam::Villarreal, ETeam::RealSociedad, 1774191600000 });

    // Week 30
    matches.push_back({ ELeague::LaLiga, "25/26", 30, ETeam::RealBetis, ETeam::Espanyol, 1775401200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 30, ETeam::Valencia, ETeam::CeltaVigo, 1775401200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 30, ETeam::Oviedo, ETeam::Sevilla, 1775401200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 30, ETeam::RayoVallecano, ETeam::Elche, 1775401200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 30, ETeam::Girona, ETeam::Villarreal, 1775401200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 30, ETeam::AtleticoMadrid, ETeam::Barcelona, 1775401200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 30, ETeam::Mallorca, ETeam::RealMadrid, 1775401200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 30, ETeam::RealSociedad, ETeam::Levante, 1775401200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 30, ETeam::Alaves, ETeam::Osasuna, 1775401200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 30, ETeam::Getafe, ETeam::AtleticoMadrid, 1775401200000 });

    // Week 31
    matches.push_back({ ELeague::LaLiga, "25/26", 31, ETeam::Mallorca, ETeam::RayoVallecano, 1776006000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 31, ETeam::Elche, ETeam::Valencia, 1776006000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 31, ETeam::RealSociedad, ETeam::Alaves, 1776006000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 31, ETeam::Barcelona, ETeam::Espanyol, 1776006000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 31, ETeam::Osasuna, ETeam::RealBetis, 1776006000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 31, ETeam::CeltaVigo, ETeam::Oviedo, 1776006000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 31, ETeam::Levante, ETeam::Getafe, 1776006000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 31, ETeam::RealMadrid, ETeam::Girona, 1776006000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 31, ETeam::AthleticClub, ETeam::Villarreal, 1776006000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 31, ETeam::Sevilla, ETeam::AtleticoMadrid, 1776006000000 });

    // Week 32
    matches.push_back({ ELeague::LaLiga, "25/26", 32, ETeam::AtleticoMadrid, ETeam::AthleticClub, 1776610800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 32, ETeam::Espanyol, ETeam::Levante, 1776610800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 32, ETeam::Osasuna, ETeam::Sevilla, 1776610800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 32, ETeam::RayoVallecano, ETeam::RealSociedad, 1776610800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 32, ETeam::RealBetis, ETeam::RealMadrid, 1776610800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 32, ETeam::Valencia, ETeam::Girona, 1776610800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 32, ETeam::Oviedo, ETeam::Elche, 1776610800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 32, ETeam::Alaves, ETeam::Mallorca, 1776610800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 32, ETeam::Getafe, ETeam::Barcelona, 1776610800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 32, ETeam::Villarreal, ETeam::CeltaVigo, 1776610800000 });

    // Week 33
    matches.push_back({ ELeague::LaLiga, "25/26", 33, ETeam::RealMadrid, ETeam::Alaves, 1776870000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 33, ETeam::Oviedo, ETeam::Villarreal, 1776870000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 33, ETeam::Elche, ETeam::AtleticoMadrid, 1776870000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 33, ETeam::Barcelona, ETeam::CeltaVigo, 1776870000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 33, ETeam::Levante, ETeam::Sevilla, 1776870000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 33, ETeam::RealSociedad, ETeam::Getafe, 1776870000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 33, ETeam::RayoVallecano, ETeam::Espanyol, 1776870000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 33, ETeam::AthleticClub, ETeam::Osasuna, 1776870000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 33, ETeam::Mallorca, ETeam::Valencia, 1776870000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 33, ETeam::Girona, ETeam::RealBetis, 1776870000000 });

    // Week 34
    matches.push_back({ ELeague::LaLiga, "25/26", 34, ETeam::Getafe, ETeam::RayoVallecano, 1777820400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 34, ETeam::CeltaVigo, ETeam::Elche, 1777820400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 34, ETeam::Alaves, ETeam::AthleticClub, 1777820400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 34, ETeam::Osasuna, ETeam::Barcelona, 1777820400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 34, ETeam::Espanyol, ETeam::RealMadrid, 1777820400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 34, ETeam::Villarreal, ETeam::Levante, 1777820400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 34, ETeam::RealBetis, ETeam::Oviedo, 1777820400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 34, ETeam::Valencia, ETeam::AtleticoMadrid, 1777820400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 34, ETeam::Sevilla, ETeam::RealSociedad, 1777820400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 34, ETeam::Girona, ETeam::Mallorca, 1777820400000 });

    // Week 35
    matches.push_back({ ELeague::LaLiga, "25/26", 35, ETeam::AthleticClub, ETeam::Valencia, 1778425200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 35, ETeam::Oviedo, ETeam::Getafe, 1778425200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 35, ETeam::Sevilla, ETeam::Espanyol, 1778425200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 35, ETeam::Mallorca, ETeam::Villarreal, 1778425200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 35, ETeam::Elche, ETeam::Alaves, 1778425200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 35, ETeam::AtleticoMadrid, ETeam::CeltaVigo, 1778425200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 35, ETeam::Levante, ETeam::Osasuna, 1778425200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 35, ETeam::Barcelona, ETeam::RealMadrid, 1778425200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 35, ETeam::RealSociedad, ETeam::RealBetis, 1778425200000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 35, ETeam::RayoVallecano, ETeam::Girona, 1778425200000 });

    // Week 36
    matches.push_back({ ELeague::LaLiga, "25/26", 36, ETeam::RealMadrid, ETeam::Oviedo, 1778684400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 36, ETeam::Getafe, ETeam::Mallorca, 1778684400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 36, ETeam::Valencia, ETeam::RayoVallecano, 1778684400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 36, ETeam::Espanyol, ETeam::AthleticClub, 1778684400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 36, ETeam::Girona, ETeam::RealSociedad, 1778684400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 36, ETeam::Osasuna, ETeam::AtleticoMadrid, 1778684400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 36, ETeam::RealBetis, ETeam::Elche, 1778684400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 36, ETeam::Alaves, ETeam::Barcelona, 1778684400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 36, ETeam::CeltaVigo, ETeam::Levante, 1778684400000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 36, ETeam::Villarreal, ETeam::Sevilla, 1778684400000 });

    // Week 37
    matches.push_back({ ELeague::LaLiga, "25/26", 37, ETeam::Elche, ETeam::Getafe, 1779030000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 37, ETeam::Levante, ETeam::Mallorca, 1779030000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 37, ETeam::Osasuna, ETeam::Espanyol, 1779030000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 37, ETeam::Barcelona, ETeam::RealBetis, 1779030000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 37, ETeam::Sevilla, ETeam::RealMadrid, 1779030000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 37, ETeam::RealSociedad, ETeam::Valencia, 1779030000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 37, ETeam::RayoVallecano, ETeam::Villarreal, 1779030000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 37, ETeam::AtleticoMadrid, ETeam::Girona, 1779030000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 37, ETeam::Oviedo, ETeam::Alaves, 1779030000000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 37, ETeam::AthleticClub, ETeam::CeltaVigo, 1779030000000 });

    // Week 38
    matches.push_back({ ELeague::LaLiga, "25/26", 38, ETeam::Girona, ETeam::Elche, 1779634800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 38, ETeam::Valencia, ETeam::Barcelona, 1779634800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 38, ETeam::RealBetis, ETeam::Levante, 1779634800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 38, ETeam::CeltaVigo, ETeam::Sevilla, 1779634800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 38, ETeam::Villarreal, ETeam::AtleticoMadrid, 1779634800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 38, ETeam::Getafe, ETeam::Osasuna, 1779634800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 38, ETeam::Mallorca, ETeam::Oviedo, 1779634800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 38, ETeam::Espanyol, ETeam::RealSociedad, 1779634800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 38, ETeam::Alaves, ETeam::RayoVallecano, 1779634800000 });
    matches.push_back({ ELeague::LaLiga, "25/26", 38, ETeam::RealMadrid, ETeam::AthleticClub, 1779634800000 });

    for (auto& m : matches)
    {
        std::string sql = "insert into matches(league, season, week, team1, team2, match_date) values ("
            + std::to_string(int(m.League)) + ", '"
            + m.Season + "', "
            + std::to_string(m.Week) + ", "
            + std::to_string((int)m.Team1) + ", "
            + std::to_string((int)m.Team2) + ", "
            + std::to_string(m.Date) + ");";

        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitPremierLeague25_26(PGconn* pg)
{
    std::vector<Match> matches;
    // Week 1
    matches.push_back({ ELeague::PremierLeague, "25/26", 1, ETeam::Liverpool, ETeam::AFCBournemouth, 1755284400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 1, ETeam::AstonVilla, ETeam::NewcastleUnited, 1755284400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 1, ETeam::BrightonAndHoveAlbion, ETeam::Fulham, 1755284400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 1, ETeam::Sunderland, ETeam::WestHamUnited, 1755284400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 1, ETeam::TottenhamHotspur, ETeam::Burnley, 1755284400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 1, ETeam::Wolverhampton, ETeam::ManchesterCity, 1755284400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 1, ETeam::NottinghamForest, ETeam::Brentford, 1755284400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 1, ETeam::Chelsea, ETeam::CrystalPalace, 1755284400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 1, ETeam::ManchesterUnited, ETeam::Arsenal, 1755284400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 1, ETeam::Leeds, ETeam::Everton, 1755284400000 });

    // Week 2
    matches.push_back({ ELeague::PremierLeague, "25/26", 2, ETeam::WestHamUnited, ETeam::Chelsea, 1755957600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 2, ETeam::ManchesterCity, ETeam::TottenhamHotspur, 1755957600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 2, ETeam::Fulham, ETeam::ManchesterUnited, 1755957600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 2, ETeam::NewcastleUnited, ETeam::Liverpool, 1755957600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 2, ETeam::Burnley, ETeam::Sunderland, 1755957600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 2, ETeam::Arsenal, ETeam::Leeds, 1755957600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 2, ETeam::Brentford, ETeam::AstonVilla, 1755957600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 2, ETeam::CrystalPalace, ETeam::NottinghamForest, 1755957600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 2, ETeam::AFCBournemouth, ETeam::Wolverhampton, 1755957600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 2, ETeam::Everton, ETeam::BrightonAndHoveAlbion, 1755957600000 });

    // Week 3
    matches.push_back({ ELeague::PremierLeague, "25/26", 3, ETeam::Sunderland, ETeam::Brentford, 1756562400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 3, ETeam::Chelsea, ETeam::Fulham, 1756562400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 3, ETeam::AstonVilla, ETeam::CrystalPalace, 1756562400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 3, ETeam::ManchesterUnited, ETeam::Burnley, 1756562400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 3, ETeam::TottenhamHotspur, ETeam::AFCBournemouth, 1756562400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 3, ETeam::Liverpool, ETeam::Arsenal, 1756562400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 3, ETeam::NottinghamForest, ETeam::WestHamUnited, 1756562400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 3, ETeam::Wolverhampton, ETeam::Everton, 1756562400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 3, ETeam::Leeds, ETeam::NewcastleUnited, 1756562400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 3, ETeam::BrightonAndHoveAlbion, ETeam::ManchesterCity, 1756562400000 });

    // Week 4
    matches.push_back({ ELeague::PremierLeague, "25/26", 4, ETeam::Fulham, ETeam::Leeds, 1757772000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 4, ETeam::Everton, ETeam::AstonVilla, 1757772000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 4, ETeam::CrystalPalace, ETeam::Sunderland, 1757772000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 4, ETeam::Brentford, ETeam::Chelsea, 1757772000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 4, ETeam::WestHamUnited, ETeam::TottenhamHotspur, 1757772000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 4, ETeam::Burnley, ETeam::Liverpool, 1757772000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 4, ETeam::AFCBournemouth, ETeam::BrightonAndHoveAlbion, 1757772000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 4, ETeam::NewcastleUnited, ETeam::Wolverhampton, 1757772000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 4, ETeam::Arsenal, ETeam::NottinghamForest, 1757772000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 4, ETeam::ManchesterCity, ETeam::ManchesterUnited, 1757772000000 });

    // Week 5
    matches.push_back({ ELeague::PremierLeague, "25/26", 5, ETeam::BrightonAndHoveAlbion, ETeam::TottenhamHotspur, 1758376800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 5, ETeam::ManchesterUnited, ETeam::Chelsea, 1758376800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 5, ETeam::Wolverhampton, ETeam::Leeds, 1758376800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 5, ETeam::Arsenal, ETeam::ManchesterCity, 1758376800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 5, ETeam::WestHamUnited, ETeam::CrystalPalace, 1758376800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 5, ETeam::AFCBournemouth, ETeam::NewcastleUnited, 1758376800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 5, ETeam::Liverpool, ETeam::Everton, 1758376800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 5, ETeam::Sunderland, ETeam::AstonVilla, 1758376800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 5, ETeam::Burnley, ETeam::NottinghamForest, 1758376800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 5, ETeam::Fulham, ETeam::Brentford, 1758376800000 });

    // Week 6
    matches.push_back({ ELeague::PremierLeague, "25/26", 6, ETeam::Brentford, ETeam::ManchesterUnited, 1758981600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 6, ETeam::CrystalPalace, ETeam::Liverpool, 1758981600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 6, ETeam::ManchesterCity, ETeam::Burnley, 1758981600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 6, ETeam::Leeds, ETeam::AFCBournemouth, 1758981600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 6, ETeam::Everton, ETeam::WestHamUnited, 1758981600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 6, ETeam::NewcastleUnited, ETeam::Arsenal, 1758981600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 6, ETeam::TottenhamHotspur, ETeam::Wolverhampton, 1758981600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 6, ETeam::AstonVilla, ETeam::Fulham, 1758981600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 6, ETeam::NottinghamForest, ETeam::Sunderland, 1758981600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 6, ETeam::Chelsea, ETeam::BrightonAndHoveAlbion, 1758981600000 });

    // Week 7
    matches.push_back({ ELeague::PremierLeague, "25/26", 7, ETeam::Arsenal, ETeam::WestHamUnited, 1759586400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 7, ETeam::AFCBournemouth, ETeam::Fulham, 1759586400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 7, ETeam::Brentford, ETeam::ManchesterCity, 1759586400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 7, ETeam::Wolverhampton, ETeam::BrightonAndHoveAlbion, 1759586400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 7, ETeam::Leeds, ETeam::TottenhamHotspur, 1759586400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 7, ETeam::AstonVilla, ETeam::Burnley, 1759586400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 7, ETeam::Everton, ETeam::CrystalPalace, 1759586400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 7, ETeam::ManchesterUnited, ETeam::Sunderland, 1759586400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 7, ETeam::Chelsea, ETeam::Liverpool, 1759586400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 7, ETeam::NewcastleUnited, ETeam::NottinghamForest, 1759586400000 });

    // Week 8
    matches.push_back({ ELeague::PremierLeague, "25/26", 8, ETeam::TottenhamHotspur, ETeam::AstonVilla, 1760796000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 8, ETeam::Fulham, ETeam::Arsenal, 1760796000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 8, ETeam::CrystalPalace, ETeam::AFCBournemouth, 1760796000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 8, ETeam::Sunderland, ETeam::Wolverhampton, 1760796000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 8, ETeam::NottinghamForest, ETeam::Chelsea, 1760796000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 8, ETeam::ManchesterCity, ETeam::Everton, 1760796000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 8, ETeam::Liverpool, ETeam::ManchesterUnited, 1760796000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 8, ETeam::BrightonAndHoveAlbion, ETeam::NewcastleUnited, 1760796000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 8, ETeam::WestHamUnited, ETeam::Brentford, 1760796000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 8, ETeam::Burnley, ETeam::Leeds, 1760796000000 });

    // Week 9
    matches.push_back({ ELeague::PremierLeague, "25/26", 9, ETeam::AFCBournemouth, ETeam::NottinghamForest, 1761400800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 9, ETeam::AstonVilla, ETeam::ManchesterCity, 1761400800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 9, ETeam::Leeds, ETeam::WestHamUnited, 1761400800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 9, ETeam::ManchesterUnited, ETeam::BrightonAndHoveAlbion, 1761400800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 9, ETeam::Brentford, ETeam::Liverpool, 1761400800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 9, ETeam::NewcastleUnited, ETeam::Fulham, 1761400800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 9, ETeam::Wolverhampton, ETeam::Burnley, 1761400800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 9, ETeam::Everton, ETeam::TottenhamHotspur, 1761400800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 9, ETeam::Arsenal, ETeam::CrystalPalace, 1761400800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 9, ETeam::Chelsea, ETeam::Sunderland, 1761400800000 });

    // Week 10
    matches.push_back({ ELeague::PremierLeague, "25/26", 10, ETeam::Fulham, ETeam::Wolverhampton, 1762005600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 10, ETeam::CrystalPalace, ETeam::Brentford, 1762005600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 10, ETeam::Sunderland, ETeam::Everton, 1762005600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 10, ETeam::WestHamUnited, ETeam::NewcastleUnited, 1762005600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 10, ETeam::BrightonAndHoveAlbion, ETeam::Leeds, 1762005600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 10, ETeam::NottinghamForest, ETeam::ManchesterUnited, 1762005600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 10, ETeam::Burnley, ETeam::Arsenal, 1762005600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 10, ETeam::ManchesterCity, ETeam::AFCBournemouth, 1762005600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 10, ETeam::Liverpool, ETeam::AstonVilla, 1762005600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 10, ETeam::TottenhamHotspur, ETeam::Chelsea, 1762005600000 });

    // Week 11
    matches.push_back({ ELeague::PremierLeague, "25/26", 11, ETeam::Everton, ETeam::Fulham, 1762610400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 11, ETeam::CrystalPalace, ETeam::BrightonAndHoveAlbion, 1762610400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 11, ETeam::Chelsea, ETeam::Wolverhampton, 1762610400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 11, ETeam::ManchesterCity, ETeam::Liverpool, 1762610400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 11, ETeam::Brentford, ETeam::NewcastleUnited, 1762610400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 11, ETeam::AstonVilla, ETeam::AFCBournemouth, 1762610400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 11, ETeam::WestHamUnited, ETeam::Burnley, 1762610400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 11, ETeam::TottenhamHotspur, ETeam::ManchesterUnited, 1762610400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 11, ETeam::Sunderland, ETeam::Arsenal, 1762610400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 11, ETeam::NottinghamForest, ETeam::Leeds, 1762610400000 });

    // Week 12
    matches.push_back({ ELeague::PremierLeague, "25/26", 12, ETeam::BrightonAndHoveAlbion, ETeam::Brentford, 1762956000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 12, ETeam::Burnley, ETeam::Chelsea, 1762956000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 12, ETeam::Leeds, ETeam::AstonVilla, 1762956000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 12, ETeam::Wolverhampton, ETeam::CrystalPalace, 1762956000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 12, ETeam::AFCBournemouth, ETeam::WestHamUnited, 1762956000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 12, ETeam::Fulham, ETeam::Sunderland, 1762956000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 12, ETeam::Arsenal, ETeam::TottenhamHotspur, 1762956000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 12, ETeam::ManchesterUnited, ETeam::Everton, 1762956000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 12, ETeam::Liverpool, ETeam::AstonVilla, 1762956000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 12, ETeam::NewcastleUnited, ETeam::ManchesterCity, 1762956000000 });

    // Week 13
    matches.push_back({ ELeague::PremierLeague, "25/26", 13, ETeam::Chelsea, ETeam::Arsenal, 1764424800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 13, ETeam::Brentford, ETeam::Burnley, 1764424800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 13, ETeam::ManchesterCity, ETeam::Leeds, 1764424800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 13, ETeam::NottinghamForest, ETeam::BrightonAndHoveAlbion, 1764424800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 13, ETeam::AstonVilla, ETeam::Wolverhampton, 1764424800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 13, ETeam::WestHamUnited, ETeam::Liverpool, 1764424800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 13, ETeam::Everton, ETeam::NewcastleUnited, 1764424800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 13, ETeam::Sunderland, ETeam::AFCBournemouth, 1764424800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 13, ETeam::TottenhamHotspur, ETeam::Fulham, 1764424800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 13, ETeam::CrystalPalace, ETeam::ManchesterUnited, 1764424800000 });

    // Week 14
    matches.push_back({ ELeague::PremierLeague, "25/26", 14, ETeam::Wolverhampton, ETeam::NottinghamForest, 1764856800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 14, ETeam::Arsenal, ETeam::Brentford, 1764856800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 14, ETeam::BrightonAndHoveAlbion, ETeam::AstonVilla, 1764856800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 14, ETeam::Leeds, ETeam::Chelsea, 1764856800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 14, ETeam::Burnley, ETeam::CrystalPalace, 1764856800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 14, ETeam::NewcastleUnited, ETeam::TottenhamHotspur, 1764856800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 14, ETeam::AFCBournemouth, ETeam::Everton, 1764856800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 14, ETeam::Liverpool, ETeam::Sunderland, 1764856800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 14, ETeam::ManchesterUnited, ETeam::WestHamUnited, 1764856800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 14, ETeam::Fulham, ETeam::ManchesterCity, 1764856800000 });

    // Week 15
    matches.push_back({ ELeague::PremierLeague, "25/26", 15, ETeam::NewcastleUnited, ETeam::Burnley, 1765029600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 15, ETeam::Fulham, ETeam::CrystalPalace, 1765029600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 15, ETeam::AFCBournemouth, ETeam::Chelsea, 1765029600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 15, ETeam::BrightonAndHoveAlbion, ETeam::WestHamUnited, 1765029600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 15, ETeam::Leeds, ETeam::Liverpool, 1765029600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 15, ETeam::TottenhamHotspur, ETeam::Brentford, 1765029600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 15, ETeam::Wolverhampton, ETeam::ManchesterUnited, 1765029600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 15, ETeam::ManchesterCity, ETeam::Sunderland, 1765029600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 15, ETeam::AstonVilla, ETeam::Arsenal, 1765029600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 15, ETeam::Everton, ETeam::NottinghamForest, 1765029600000 });

    // Week 16
    matches.push_back({ ELeague::PremierLeague, "25/26", 16, ETeam::Burnley, ETeam::Fulham, 1765634400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 16, ETeam::Brentford, ETeam::Leeds, 1765634400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 16, ETeam::Arsenal, ETeam::Wolverhampton, 1765634400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 16, ETeam::Liverpool, ETeam::BrightonAndHoveAlbion, 1765634400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 16, ETeam::CrystalPalace, ETeam::ManchesterCity, 1765634400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 16, ETeam::Chelsea, ETeam::Everton, 1765634400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 16, ETeam::ManchesterUnited, ETeam::AFCBournemouth, 1765634400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 16, ETeam::NottinghamForest, ETeam::TottenhamHotspur, 1765634400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 16, ETeam::WestHamUnited, ETeam::AstonVilla, 1765634400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 16, ETeam::Sunderland, ETeam::NewcastleUnited, 1765634400000 });

    // Week 17
    matches.push_back({ ELeague::PremierLeague, "25/26", 17, ETeam::ManchesterCity, ETeam::WestHamUnited, 1766239200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 17, ETeam::Fulham, ETeam::NottinghamForest, 1766239200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 17, ETeam::AFCBournemouth, ETeam::Burnley, 1766239200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 17, ETeam::NewcastleUnited, ETeam::Chelsea, 1766239200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 17, ETeam::Everton, ETeam::Arsenal, 1766239200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 17, ETeam::Wolverhampton, ETeam::Brentford, 1766239200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 17, ETeam::BrightonAndHoveAlbion, ETeam::Sunderland, 1766239200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 17, ETeam::AstonVilla, ETeam::ManchesterUnited, 1766239200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 17, ETeam::Leeds, ETeam::CrystalPalace, 1766239200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 17, ETeam::TottenhamHotspur, ETeam::Liverpool, 1766239200000 });

    // Week 18
    matches.push_back({ ELeague::PremierLeague, "25/26", 18, ETeam::CrystalPalace, ETeam::TottenhamHotspur, 1766844000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 18, ETeam::Burnley, ETeam::Everton, 1766844000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 18, ETeam::WestHamUnited, ETeam::Fulham, 1766844000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 18, ETeam::Sunderland, ETeam::Leeds, 1766844000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 18, ETeam::Chelsea, ETeam::AstonVilla, 1766844000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 18, ETeam::NottinghamForest, ETeam::ManchesterCity, 1766844000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 18, ETeam::ManchesterUnited, ETeam::NewcastleUnited, 1766844000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 18, ETeam::Brentford, ETeam::AFCBournemouth, 1766844000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 18, ETeam::Liverpool, ETeam::Wolverhampton, 1766844000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 18, ETeam::Arsenal, ETeam::BrightonAndHoveAlbion, 1766844000000 });

    // Week 19
    matches.push_back({ ELeague::PremierLeague, "25/26", 19, ETeam::Sunderland, ETeam::ManchesterCity, 1767189600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 19, ETeam::CrystalPalace, ETeam::Fulham, 1767189600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 19, ETeam::Liverpool, ETeam::Leeds, 1767189600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 19, ETeam::Burnley, ETeam::NewcastleUnited, 1767189600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 19, ETeam::NottinghamForest, ETeam::Everton, 1767189600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 19, ETeam::WestHamUnited, ETeam::BrightonAndHoveAlbion, 1767189600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 19, ETeam::Brentford, ETeam::TottenhamHotspur, 1767189600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 19, ETeam::ManchesterUnited, ETeam::Wolverhampton, 1767189600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 19, ETeam::Chelsea, ETeam::AFCBournemouth, 1767189600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 19, ETeam::Arsenal, ETeam::AstonVilla, 1767189600000 });

    // Week 20
    matches.push_back({ ELeague::PremierLeague, "25/26", 20, ETeam::Everton, ETeam::Brentford, 1767448800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 20, ETeam::Leeds, ETeam::ManchesterUnited, 1767448800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 20, ETeam::Wolverhampton, ETeam::WestHamUnited, 1767448800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 20, ETeam::Fulham, ETeam::Liverpool, 1767448800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 20, ETeam::AFCBournemouth, ETeam::Arsenal, 1767448800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 20, ETeam::NewcastleUnited, ETeam::CrystalPalace, 1767448800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 20, ETeam::TottenhamHotspur, ETeam::Sunderland, 1767448800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 20, ETeam::AstonVilla, ETeam::NottinghamForest, 1767448800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 20, ETeam::BrightonAndHoveAlbion, ETeam::Burnley, 1767448800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 20, ETeam::ManchesterCity, ETeam::Chelsea, 1767448800000 });

    // Week 21
    matches.push_back({ ELeague::PremierLeague, "25/26", 21, ETeam::Arsenal, ETeam::Liverpool, 1767880800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 21, ETeam::Everton, ETeam::Wolverhampton, 1767880800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 21, ETeam::WestHamUnited, ETeam::NottinghamForest, 1767880800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 21, ETeam::NewcastleUnited, ETeam::Leeds, 1767880800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 21, ETeam::AFCBournemouth, ETeam::TottenhamHotspur, 1767880800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 21, ETeam::Brentford, ETeam::Sunderland, 1767880800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 21, ETeam::CrystalPalace, ETeam::AstonVilla, 1767880800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 21, ETeam::Fulham, ETeam::Chelsea, 1767880800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 21, ETeam::Burnley, ETeam::ManchesterUnited, 1767880800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 21, ETeam::ManchesterCity, ETeam::BrightonAndHoveAlbion, 1767880800000 });

    // Week 22
    matches.push_back({ ELeague::PremierLeague, "25/26", 22, ETeam::Sunderland, ETeam::CrystalPalace, 1769090400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 22, ETeam::Wolverhampton, ETeam::NewcastleUnited, 1769090400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 22, ETeam::ManchesterUnited, ETeam::ManchesterCity, 1769090400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 22, ETeam::Leeds, ETeam::Fulham, 1769090400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 22, ETeam::Chelsea, ETeam::Brentford, 1769090400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 22, ETeam::AstonVilla, ETeam::Everton, 1769090400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 22, ETeam::BrightonAndHoveAlbion, ETeam::AFCBournemouth, 1769090400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 22, ETeam::TottenhamHotspur, ETeam::WestHamUnited, 1769090400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 22, ETeam::Liverpool, ETeam::Burnley, 1769090400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 22, ETeam::NottinghamForest, ETeam::Arsenal, 1769090400000 });

    // Week 23
    matches.push_back({ ELeague::PremierLeague, "25/26", 23, ETeam::AFCBournemouth, ETeam::Liverpool, 1769263200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 23, ETeam::Fulham, ETeam::BrightonAndHoveAlbion, 1769263200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 23, ETeam::Burnley, ETeam::TottenhamHotspur, 1769263200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 23, ETeam::CrystalPalace, ETeam::Chelsea, 1769263200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 23, ETeam::ManchesterCity, ETeam::Wolverhampton, 1769263200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 23, ETeam::WestHamUnited, ETeam::Sunderland, 1769263200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 23, ETeam::Everton, ETeam::Leeds, 1769263200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 23, ETeam::NewcastleUnited, ETeam::AstonVilla, 1769263200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 23, ETeam::Arsenal, ETeam::ManchesterUnited, 1769263200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 23, ETeam::Brentford, ETeam::NottinghamForest, 1769263200000 });

    // Week 24
    matches.push_back({ ELeague::PremierLeague, "25/26", 24, ETeam::Liverpool, ETeam::NewcastleUnited, 1769868000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 24, ETeam::AstonVilla, ETeam::Brentford, 1769868000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 24, ETeam::NottinghamForest, ETeam::CrystalPalace, 1769868000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 24, ETeam::TottenhamHotspur, ETeam::ManchesterCity, 1769868000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 24, ETeam::Chelsea, ETeam::WestHamUnited, 1769868000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 24, ETeam::ManchesterCity, ETeam::Fulham, 1769868000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 24, ETeam::Sunderland, ETeam::Burnley, 1769868000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 24, ETeam::Wolverhampton, ETeam::AFCBournemouth, 1769868000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 24, ETeam::BrightonAndHoveAlbion, ETeam::Everton, 1769868000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 24, ETeam::Leeds, ETeam::Arsenal, 1769868000000 });

    // Week 25
    matches.push_back({ ELeague::PremierLeague, "25/26", 25, ETeam::AFCBournemouth, ETeam::AstonVilla, 1770472800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 25, ETeam::NewcastleUnited, ETeam::Brentford, 1770472800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 25, ETeam::Fulham, ETeam::Everton, 1770472800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 25, ETeam::Liverpool, ETeam::ManchesterCity, 1770472800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 25, ETeam::Leeds, ETeam::NottinghamForest, 1770472800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 25, ETeam::Burnley, ETeam::WestHamUnited, 1770472800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 25, ETeam::BrightonAndHoveAlbion, ETeam::CrystalPalace, 1770472800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 25, ETeam::ManchesterUnited, ETeam::TottenhamHotspur, 1770472800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 25, ETeam::Wolverhampton, ETeam::Chelsea, 1770472800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 25, ETeam::Arsenal, ETeam::Sunderland, 1770472800000 });

    // Week 26
    matches.push_back({ ELeague::PremierLeague, "25/26", 26, ETeam::Everton, ETeam::AFCBournemouth, 1770904800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 26, ETeam::NottinghamForest, ETeam::Wolverhampton, 1770904800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 26, ETeam::CrystalPalace, ETeam::Burnley, 1770904800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 26, ETeam::Chelsea, ETeam::Leeds, 1770904800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 26, ETeam::Brentford, ETeam::Arsenal, 1770904800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 26, ETeam::AstonVilla, ETeam::BrightonAndHoveAlbion, 1770904800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 26, ETeam::WestHamUnited, ETeam::ManchesterUnited, 1770904800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 26, ETeam::ManchesterCity, ETeam::Fulham, 1770904800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 26, ETeam::TottenhamHotspur, ETeam::NewcastleUnited, 1770904800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 26, ETeam::Sunderland, ETeam::Liverpool, 1770904800000 });

    // Week 27
    matches.push_back({ ELeague::PremierLeague, "25/26", 27, ETeam::Everton, ETeam::ManchesterUnited, 1771682400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 27, ETeam::Brentford, ETeam::BrightonAndHoveAlbion, 1771682400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 27, ETeam::AstonVilla, ETeam::Leeds, 1771682400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 27, ETeam::WestHamUnited, ETeam::AFCBournemouth, 1771682400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 27, ETeam::CrystalPalace, ETeam::Wolverhampton, 1771682400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 27, ETeam::Chelsea, ETeam::Burnley, 1771682400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 27, ETeam::NottinghamForest, ETeam::Liverpool, 1771682400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 27, ETeam::ManchesterCity, ETeam::NewcastleUnited, 1771682400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 27, ETeam::TottenhamHotspur, ETeam::Arsenal, 1771682400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 27, ETeam::Sunderland, ETeam::Fulham, 1771682400000 });

    // Week 28
    matches.push_back({ ELeague::PremierLeague, "25/26", 28, ETeam::Fulham, ETeam::TottenhamHotspur, 1772287200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 28, ETeam::Liverpool, ETeam::WestHamUnited, 1772287200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 28, ETeam::ManchesterUnited, ETeam::CrystalPalace, 1772287200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 28, ETeam::BrightonAndHoveAlbion, ETeam::NottinghamForest, 1772287200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 28, ETeam::Burnley, ETeam::Brentford, 1772287200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 28, ETeam::AFCBournemouth, ETeam::Sunderland, 1772287200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 28, ETeam::Wolverhampton, ETeam::AstonVilla, 1772287200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 28, ETeam::NewcastleUnited, ETeam::Everton, 1772287200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 28, ETeam::Arsenal, ETeam::Chelsea, 1772287200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 28, ETeam::Leeds, ETeam::ManchesterCity, 1772287200000 });

    // Week 29
    matches.push_back({ ELeague::PremierLeague, "25/26", 29, ETeam::TottenhamHotspur, ETeam::CrystalPalace, 1772719200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 29, ETeam::AstonVilla, ETeam::Chelsea, 1772719200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 29, ETeam::ManchesterCity, ETeam::NottinghamForest, 1772719200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 29, ETeam::AFCBournemouth, ETeam::Brentford, 1772719200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 29, ETeam::Leeds, ETeam::Sunderland, 1772719200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 29, ETeam::Wolverhampton, ETeam::Liverpool, 1772719200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 29, ETeam::BrightonAndHoveAlbion, ETeam::Arsenal, 1772719200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 29, ETeam::Everton, ETeam::Burnley, 1772719200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 29, ETeam::NewcastleUnited, ETeam::ManchesterUnited, 1772719200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 29, ETeam::Fulham, ETeam::WestHamUnited, 1772719200000 });

    // Week 30
    matches.push_back({ ELeague::PremierLeague, "25/26", 30, ETeam::Sunderland, ETeam::BrightonAndHoveAlbion, 1773496800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 30, ETeam::ManchesterUnited, ETeam::AstonVilla, 1773496800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 30, ETeam::CrystalPalace, ETeam::Leeds, 1773496800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 30, ETeam::Burnley, ETeam::AFCBournemouth, 1773496800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 30, ETeam::WestHamUnited, ETeam::ManchesterCity, 1773496800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 30, ETeam::Chelsea, ETeam::NewcastleUnited, 1773496800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 30, ETeam::Liverpool, ETeam::TottenhamHotspur, 1773496800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 30, ETeam::Brentford, ETeam::Wolverhampton, 1773496800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 30, ETeam::NottinghamForest, ETeam::Fulham, 1773496800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 30, ETeam::Arsenal, ETeam::Everton, 1773496800000 });

    // Week 31
    matches.push_back({ ELeague::PremierLeague, "25/26", 31, ETeam::AFCBournemouth, ETeam::ManchesterUnited, 1774101600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 31, ETeam::Leeds, ETeam::Brentford, 1774101600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 31, ETeam::Fulham, ETeam::Burnley, 1774101600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 31, ETeam::BrightonAndHoveAlbion, ETeam::Liverpool, 1774101600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 31, ETeam::Wolverhampton, ETeam::Arsenal, 1774101600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 31, ETeam::TottenhamHotspur, ETeam::NottinghamForest, 1774101600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 31, ETeam::NewcastleUnited, ETeam::Sunderland, 1774101600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 31, ETeam::Everton, ETeam::Chelsea, 1774101600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 31, ETeam::AstonVilla, ETeam::WestHamUnited, 1774101600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 31, ETeam::ManchesterCity, ETeam::CrystalPalace, 1774101600000 });

    // Week 32
    matches.push_back({ ELeague::PremierLeague, "25/26", 32, ETeam::Sunderland, ETeam::TottenhamHotspur, 1775052000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 32, ETeam::Brentford, ETeam::Everton, 1775052000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 32, ETeam::WestHamUnited, ETeam::Wolverhampton, 1775052000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 32, ETeam::Arsenal, ETeam::AFCBournemouth, 1775052000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 32, ETeam::NottinghamForest, ETeam::AstonVilla, 1775052000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 32, ETeam::Liverpool, ETeam::Fulham, 1775052000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 32, ETeam::Burnley, ETeam::BrightonAndHoveAlbion, 1775052000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 32, ETeam::ManchesterUnited, ETeam::Leeds, 1775052000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 32, ETeam::CrystalPalace, ETeam::NewcastleUnited, 1775052000000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 32, ETeam::Chelsea, ETeam::ManchesterCity, 1775052000000 });

    // Week 33
    matches.push_back({ ELeague::PremierLeague, "25/26", 33, ETeam::NottinghamForest, ETeam::Burnley, 1776520800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 33, ETeam::Brentford, ETeam::Fulham, 1776520800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 33, ETeam::TottenhamHotspur, ETeam::BrightonAndHoveAlbion, 1776520800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 33, ETeam::Leeds, ETeam::Wolverhampton, 1776520800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 33, ETeam::Everton, ETeam::Liverpool, 1776520800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 33, ETeam::NewcastleUnited, ETeam::AFCBournemouth, 1776520800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 33, ETeam::AstonVilla, ETeam::Sunderland, 1776520800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 33, ETeam::Chelsea, ETeam::ManchesterUnited, 1776520800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 33, ETeam::ManchesterCity, ETeam::Arsenal, 1776520800000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 33, ETeam::CrystalPalace, ETeam::WestHamUnited, 1776520800000 });

    // Week 34
    matches.push_back({ ELeague::PremierLeague, "25/26", 34, ETeam::BrightonAndHoveAlbion, ETeam::Chelsea, 1777125600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 34, ETeam::Fulham, ETeam::AstonVilla, 1777125600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 34, ETeam::Liverpool, ETeam::CrystalPalace, 1777125600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 34, ETeam::Arsenal, ETeam::NewcastleUnited, 1777125600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 34, ETeam::AFCBournemouth, ETeam::Leeds, 1777125600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 34, ETeam::WestHamUnited, ETeam::Everton, 1777125600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 34, ETeam::Wolverhampton, ETeam::TottenhamHotspur, 1777125600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 34, ETeam::ManchesterUnited, ETeam::Brentford, 1777125600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 34, ETeam::Sunderland, ETeam::NottinghamForest, 1777125600000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 34, ETeam::Burnley, ETeam::ManchesterCity, 1777125600000 });

    // Week 35
    matches.push_back({ ELeague::PremierLeague, "25/26", 35, ETeam::Leeds, ETeam::Burnley, 1777730400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 35, ETeam::ManchesterUnited, ETeam::Liverpool, 1777730400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 35, ETeam::AFCBournemouth, ETeam::CrystalPalace, 1777730400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 35, ETeam::Wolverhampton, ETeam::Sunderland, 1777730400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 35, ETeam::NewcastleUnited, ETeam::BrightonAndHoveAlbion, 1777730400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 35, ETeam::Brentford, ETeam::WestHamUnited, 1777730400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 35, ETeam::Everton, ETeam::ManchesterCity, 1777730400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 35, ETeam::Chelsea, ETeam::NottinghamForest, 1777730400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 35, ETeam::AstonVilla, ETeam::TottenhamHotspur, 1777730400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 35, ETeam::Arsenal, ETeam::Fulham, 1777730400000 });

    // Week 36
    matches.push_back({ ELeague::PremierLeague, "25/26", 36, ETeam::WestHamUnited, ETeam::Arsenal, 1778335200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 36, ETeam::BrightonAndHoveAlbion, ETeam::Wolverhampton, 1778335200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 36, ETeam::NottinghamForest, ETeam::NewcastleUnited, 1778335200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 36, ETeam::Fulham, ETeam::AFCBournemouth, 1778335200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 36, ETeam::Sunderland, ETeam::ManchesterUnited, 1778335200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 36, ETeam::Burnley, ETeam::AstonVilla, 1778335200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 36, ETeam::TottenhamHotspur, ETeam::Leeds, 1778335200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 36, ETeam::CrystalPalace, ETeam::Everton, 1778335200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 36, ETeam::ManchesterCity, ETeam::Brentford, 1778335200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 36, ETeam::Liverpool, ETeam::Chelsea, 1778335200000 });

    // Week 37
    matches.push_back({ ELeague::PremierLeague, "25/26", 37, ETeam::Leeds, ETeam::BrightonAndHoveAlbion, 1779026400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 37, ETeam::ManchesterUnited, ETeam::NottinghamForest, 1779026400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 37, ETeam::AstonVilla, ETeam::Liverpool, 1779026400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 37, ETeam::Arsenal, ETeam::Burnley, 1779026400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 37, ETeam::AFCBournemouth, ETeam::ManchesterCity, 1779026400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 37, ETeam::Wolverhampton, ETeam::Fulham, 1779026400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 37, ETeam::NewcastleUnited, ETeam::WestHamUnited, 1779026400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 37, ETeam::Chelsea, ETeam::TottenhamHotspur, 1779026400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 37, ETeam::Brentford, ETeam::CrystalPalace, 1779026400000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 37, ETeam::Everton, ETeam::Sunderland, 1779026400000 });

    // Week 38
    matches.push_back({ ELeague::PremierLeague, "25/26", 38, ETeam::BrightonAndHoveAlbion, ETeam::ManchesterUnited, 1779631200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 38, ETeam::Burnley, ETeam::Wolverhampton, 1779631200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 38, ETeam::WestHamUnited, ETeam::Leeds, 1779631200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 38, ETeam::Fulham, ETeam::NewcastleUnited, 1779631200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 38, ETeam::NottinghamForest, ETeam::AFCBournemouth, 1779631200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 38, ETeam::Liverpool, ETeam::Brentford, 1779631200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 38, ETeam::ManchesterCity, ETeam::AstonVilla, 1779631200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 38, ETeam::TottenhamHotspur, ETeam::Everton, 1779631200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 38, ETeam::Sunderland, ETeam::Chelsea, 1779631200000 });
    matches.push_back({ ELeague::PremierLeague, "25/26", 38, ETeam::CrystalPalace, ETeam::Arsenal, 1779631200000 });

    for (auto& m : matches)
    {
        std::string sql = "insert into matches(league, season, week, team1, team2, match_date) values ("
            + std::to_string(int(m.League)) + ", '"
            + m.Season + "', "
            + std::to_string(m.Week) + ", "
            + std::to_string((int)m.Team1) + ", "
            + std::to_string((int)m.Team2) + ", "
            + std::to_string(m.Date) + ");";

        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitCoppaItaliaTeams25_26(PGconn* pg)
{
    std::vector<ETeam> teams;
    teams.push_back(ETeam::InterMilan);
    teams.push_back(ETeam::Torino);
    teams.push_back(ETeam::Atalanta);
    teams.push_back(ETeam::Juventus);
    teams.push_back(ETeam::Napoli);
    teams.push_back(ETeam::Como);
    teams.push_back(ETeam::Bologna);
    teams.push_back(ETeam::Lazio);

    for (ETeam t : teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id) values ("
            + std::to_string(int(ELeague::CoppaItalia)) + ", "
            + std::to_string((int)t) + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitCopaDelReyTeams25_26(PGconn* pg)
{
    std::vector<ETeam> teams;
    teams.push_back(ETeam::Albacete);
    teams.push_back(ETeam::Barcelona);
    teams.push_back(ETeam::Alaves);
    teams.push_back(ETeam::RealSociedad);
    teams.push_back(ETeam::Valencia);
    teams.push_back(ETeam::AthleticClub);
    teams.push_back(ETeam::RealBetis);
    teams.push_back(ETeam::AtleticoMadrid);

    for (ETeam t : teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id) values ("
            + std::to_string(int(ELeague::CopaDelRey)) + ", "
            + std::to_string((int)t) + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}


void MatchesInitializer::InitSuperCupItaliaTeams25_26(PGconn* pg)
{
  
    std::vector<ETeam> teams;
    teams.push_back(ETeam::Napoli);
    teams.push_back(ETeam::ACMilan);
    teams.push_back(ETeam::Bologna);
    teams.push_back(ETeam::InterMilan);
  
    for (ETeam t : teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id) values ("
            + std::to_string(int(ELeague::SuperCupItalia)) + ", "
            + std::to_string((int)t) + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitSuperCupSpainTeams25_26(PGconn* pg)
{

    std::vector<ETeam> teams;
    teams.push_back(ETeam::AthleticClub);
    teams.push_back(ETeam::Barcelona);
    teams.push_back(ETeam::RealMadrid);
    teams.push_back(ETeam::AtleticoMadrid);

    for (ETeam t : teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id) values ("
            + std::to_string(int(ELeague::SuperCupSpain)) + ", "
            + std::to_string((int)t) + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitEFLCupTeams25_26(PGconn* pg)
{

    std::vector<ETeam> teams;
    teams.push_back(ETeam::NewcastleUnited);
    teams.push_back(ETeam::ManchesterCity);
    teams.push_back(ETeam::Chelsea);
    teams.push_back(ETeam::Arsenal);

    for (ETeam t : teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id) values ("
            + std::to_string(int(ELeague::EFLCup)) + ", "
            + std::to_string((int)t) + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitDFLSuperCupTeams25_26(PGconn* pg)
{
    std::vector<ETeam> teams;
    teams.push_back(ETeam::Stuttgart);
    teams.push_back(ETeam::BayernMunich);

    for (ETeam t : teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id) values ("
            + std::to_string(int(ELeague::DFLSuperCup)) + ", "
            + std::to_string((int)t) + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitDFBPokalTeams25_26(PGconn* pg)
{
    std::vector<ETeam> teams;
    teams.push_back(ETeam::BayerLeverkusen);
    teams.push_back(ETeam::StPauli);
    teams.push_back(ETeam::HolsteinKiel);
    teams.push_back(ETeam::Stuttgart);
    teams.push_back(ETeam::Hertha);
    teams.push_back(ETeam::Freiburg);
    teams.push_back(ETeam::BayernMunich);
    teams.push_back(ETeam::RBLeipzig);

    for (ETeam t : teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id) values ("
            + std::to_string(int(ELeague::DFBPokal)) + ", "
            + std::to_string((int)t) + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}


void MatchesInitializer::InitSuperCupFranceTeams25_26(PGconn* pg)
{

    std::vector<ETeam> teams;
    teams.push_back(ETeam::PSG);
    teams.push_back(ETeam::Marseille);

    for (ETeam t : teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id) values ("
            + std::to_string(int(ELeague::SuperCupFrance)) + ", "
            + std::to_string((int)t) + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitCopaDelRey25_26(PGconn* pg)
{
    // Premier League
    std::vector<Match> matches;
    // Week 1
    //matches.push_back({ ELeague::CopaDelRey, "25/26", 1, ETeam::Albacete, ETeam::Barcelona, 1770148800000, EWeekType::QuarterFinal, true });
    //matches.push_back({ ELeague::CopaDelRey, "25/26", 1, ETeam::Alaves, ETeam::RealSociedad, 1770235200000, EWeekType::QuarterFinal, true });
    //matches.push_back({ ELeague::CopaDelRey, "25/26", 1, ETeam::Valencia, ETeam::AthleticClub, 1770235200000, EWeekType::QuarterFinal, true });
    //matches.push_back({ ELeague::CopaDelRey, "25/26", 1, ETeam::RealBetis, ETeam::AtleticoMadrid, 1770321600000, EWeekType::QuarterFinal, true });

   matches.push_back({ ELeague::CopaDelRey, "25/26", 2, ETeam::AthleticClub, ETeam::RealSociedad, 1770840000000, EWeekType::SemiFinal, false });
   matches.push_back({ ELeague::CopaDelRey, "25/26", 2, ETeam::AtleticoMadrid, ETeam::Barcelona, 1770926400000, EWeekType::SemiFinal, false });

   // matches.push_back({ ELeague::CopaDelRey, "24/25", 2, ETeam::RealMadrid, ETeam::RealSociedad, 1743535800000, EWeekType::SemiFinal, true });
   // matches.push_back({ ELeague::CopaDelRey, "24/25", 2, ETeam::AtleticoMadrid, ETeam::Barcelona, 1743622200000, EWeekType::SemiFinal, true });

   // matches.push_back({ ELeague::CopaDelRey, "24/25", 3, ETeam::Barcelona, ETeam::RealMadrid, 1745697600000, EWeekType::Final, true });


    for (auto& m : matches)
    {
        std::string sql = "insert into matches(league, season, week, week_type, team1, team2, match_date, play_off) values ("
            + std::to_string(int(m.League)) + ", '"
            + m.Season + "', "
            + std::to_string(m.Week) + ", "
            + std::to_string((int)m.WeekType) + ", "
            + std::to_string((int)m.Team1) + ", "
            + std::to_string((int)m.Team2) + ", "
            + std::to_string(m.Date) + ", "
            + std::to_string(int(m.PlayOff))
            + ");";

        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}


void MatchesInitializer::InitCoppaItalia25_26(PGconn* pg)
{
    std::vector<Match> matches;
    // Week 1
    matches.push_back({ ELeague::CoppaItalia, "25/26", 1, ETeam::InterMilan, ETeam::Torino, 1770235200000, EWeekType::QuarterFinal, true });
    matches.push_back({ ELeague::CoppaItalia, "25/26", 1, ETeam::Atalanta, ETeam::Juventus, 1770321600000, EWeekType::QuarterFinal, true });
    matches.push_back({ ELeague::CoppaItalia, "25/26", 1, ETeam::Napoli, ETeam::Como, 1770753600000, EWeekType::QuarterFinal, true });
    matches.push_back({ ELeague::CoppaItalia, "25/26", 1, ETeam::Bologna, ETeam::Lazio, 1770840000000, EWeekType::QuarterFinal, true });
  
  //  matches.push_back({ ELeague::CoppaItalia, "24/25", 2, ETeam::Empoli, ETeam::Bologna, 1743534000000, EWeekType::SemiFinal, false });
//    matches.push_back({ ELeague::CoppaItalia, "24/25", 2, ETeam::ACMilan, ETeam::InterMilan, 1743620400000, EWeekType::SemiFinal, false });

  //  matches.push_back({ ELeague::CoppaItalia, "24/25", 2, ETeam::InterMilan, ETeam::ACMilan, 1745434800000, EWeekType::SemiFinal, true });
//    matches.push_back({ ELeague::CoppaItalia, "24/25", 2, ETeam::Bologna, ETeam::Empoli, 1745521200000, EWeekType::SemiFinal, true });

    //matches.push_back({ ELeague::CoppaItalia, "24/25", 3, ETeam::ACMilan, ETeam::Bologna, 1747249200000, EWeekType::Final, true });


    for (auto& m : matches)
    {
        std::string sql = "insert into matches(league, season, week, week_type, team1, team2, match_date, play_off) values ("
            + std::to_string(int(m.League)) + ", '"
            + m.Season + "', "
            + std::to_string(m.Week) + ", "
            + std::to_string((int)m.WeekType) + ", "
            + std::to_string((int)m.Team1) + ", "
            + std::to_string((int)m.Team2) + ", "
            + std::to_string(m.Date) + ", "
            + std::to_string(int(m.PlayOff))
            + ");";

        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitSuperCupItalia25_26(PGconn * pg)
{
    std::vector<Match> matches;
    // Semi final
   // matches.push_back({ ELeague::SuperCupItalia, "25/26", 1, ETeam::Napoli, ETeam::ACMilan, 1766084400000, EWeekType::SemiFinal, true });
    //matches.push_back({ ELeague::SuperCupItalia, "25/26", 1, ETeam::Bologna, ETeam::InterMilan, 1766170800000, EWeekType::SemiFinal, true });

     matches.push_back({ ELeague::SuperCupItalia, "25/26", 2, ETeam::Napoli, ETeam::Bologna, 1766430000000, EWeekType::Final, false });

    for (auto& m : matches)
    {
        std::string sql = "insert into matches(league, season, week, week_type, team1, team2, match_date, play_off) values ("
            + std::to_string(int(m.League)) + ", '"
            + m.Season + "', "
            + std::to_string(m.Week) + ", "
            + std::to_string((int)m.WeekType) + ", "
            + std::to_string((int)m.Team1) + ", "
            + std::to_string((int)m.Team2) + ", "
            + std::to_string(m.Date) + ", "
            + std::to_string(int(m.PlayOff))
            + ");";

        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitSuperCupSpain25_26(PGconn* pg)
{
    std::vector<Match> matches;
    // Semi final
    //matches.push_back({ ELeague::SuperCupSpain, "25/26", 1, ETeam::Barcelona, ETeam::AthleticClub, 1767812400000, EWeekType::SemiFinal, false });
    //matches.push_back({ ELeague::SuperCupSpain, "25/26", 1, ETeam::AtleticoMadrid, ETeam::RealMadrid, 1767898800000, EWeekType::SemiFinal, false });

    matches.push_back({ ELeague::SuperCupSpain, "25/26", 2, ETeam::Barcelona, ETeam::RealMadrid, 1768158000000, EWeekType::Final, false });


    for (auto& m : matches)
    {
        std::string sql = "insert into matches(league, season, week, week_type, team1, team2, match_date, play_off) values ("
            + std::to_string(int(m.League)) + ", '"
            + m.Season + "', "
            + std::to_string(m.Week) + ", "
            + std::to_string((int)m.WeekType) + ", "
            + std::to_string((int)m.Team1) + ", "
            + std::to_string((int)m.Team2) + ", "
            + std::to_string(m.Date) + ", "
            + std::to_string(int(m.PlayOff))
            + ");";

        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitEFLCup25_26(PGconn* pg)
{
    std::vector<Match> matches;
    // Semi final
    matches.push_back({ ELeague::EFLCup, "25/26", 1, ETeam::NewcastleUnited, ETeam::ManchesterCity, 1768334400000, EWeekType::SemiFinal, false });
    matches.push_back({ ELeague::EFLCup, "25/26", 1, ETeam::Chelsea, ETeam::Arsenal, 1768420800000, EWeekType::SemiFinal, false });

    matches.push_back({ ELeague::EFLCup, "25/26", 1, ETeam::Arsenal, ETeam::Chelsea, 1770148800000, EWeekType::SemiFinal, false });
    matches.push_back({ ELeague::EFLCup, "25/26", 1, ETeam::ManchesterCity, ETeam::NewcastleUnited, 1770235200000, EWeekType::SemiFinal, false });


    for (auto& m : matches)
    {
        std::string sql = "insert into matches(league, season, week, week_type, team1, team2, match_date, play_off) values ("
            + std::to_string(int(m.League)) + ", '"
            + m.Season + "', "
            + std::to_string(m.Week) + ", "
            + std::to_string((int)m.WeekType) + ", "
            + std::to_string((int)m.Team1) + ", "
            + std::to_string((int)m.Team2) + ", "
            + std::to_string(m.Date) + ", "
            + std::to_string(int(m.PlayOff))
            + ");";

        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitDFLSuperCup25_26(PGconn* pg)
{
    std::vector<Match> matches;
    matches.push_back({ ELeague::DFLSuperCup, "25/26", 1, ETeam::Stuttgart, ETeam::BayernMunich, 1755369000000, EWeekType::Final, true });

    for (auto& m : matches)
    {
        std::string sql = "insert into matches(league, season, week, week_type, team1, team2, match_date, play_off) values ("
            + std::to_string(int(m.League)) + ", '"
            + m.Season + "', "
            + std::to_string(m.Week) + ", "
            + std::to_string((int)m.WeekType) + ", "
            + std::to_string((int)m.Team1) + ", "
            + std::to_string((int)m.Team2) + ", "
            + std::to_string(m.Date) + ", "
            + std::to_string(int(m.PlayOff))
            + ");";

        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitDFBPokal25_26(PGconn* pg)
{
    std::vector<Match> matches;
    matches.push_back({ ELeague::DFBPokal, "25/26", 1, ETeam::BayerLeverkusen, ETeam::StPauli, 1770147900000, EWeekType::QuarterFinal, true });
    matches.push_back({ ELeague::DFBPokal, "25/26", 1, ETeam::HolsteinKiel, ETeam::Stuttgart, 1770234300000, EWeekType::QuarterFinal, true });
    matches.push_back({ ELeague::DFBPokal, "25/26", 1, ETeam::Hertha, ETeam::Freiburg, 1770752700000, EWeekType::QuarterFinal, true });
    matches.push_back({ ELeague::DFBPokal, "25/26", 1, ETeam::BayernMunich, ETeam::RBLeipzig, 1770839100000, EWeekType::QuarterFinal, true });

    for (auto& m : matches)
    {
        std::string sql = "insert into matches(league, season, week, week_type, team1, team2, match_date, play_off) values ("
            + std::to_string(int(m.League)) + ", '"
            + m.Season + "', "
            + std::to_string(m.Week) + ", "
            + std::to_string((int)m.WeekType) + ", "
            + std::to_string((int)m.Team1) + ", "
            + std::to_string((int)m.Team2) + ", "
            + std::to_string(m.Date) + ", "
            + std::to_string(int(m.PlayOff))
            + ");";

        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}


void MatchesInitializer::InitSuperCupFrance25_26(PGconn* pg)
{
    std::vector<Match> matches;
    // Semi final
    matches.push_back({ ELeague::SuperCupFrance, "25/26", 1, ETeam::PSG, ETeam::Marseille, 1767895200000, EWeekType::Final, false });

    for (auto& m : matches)
    {
        std::string sql = "insert into matches(league, season, week, week_type, team1, team2, match_date, play_off) values ("
            + std::to_string(int(m.League)) + ", '"
            + m.Season + "', "
            + std::to_string(m.Week) + ", "
            + std::to_string((int)m.WeekType) + ", "
            + std::to_string((int)m.Team1) + ", "
            + std::to_string((int)m.Team2) + ", "
            + std::to_string(m.Date) + ", "
            + std::to_string(int(m.PlayOff))
            + ");";

        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitUEFAWCQualifiersTeams(PGconn* pg)
{
    int groupIndex = 0;

    // Group A
    std::vector group1Teams =
    {
        ETeam::Luxemburg,
        ETeam::NorthernIreland,
        ETeam::Slovakia,
        ETeam::Germany
    };

    for (auto team : group1Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex)
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group B
    std::vector group2Teams =
    {
        ETeam::Kosovo,
        ETeam::Slovenia,
        ETeam::Sweden,
        ETeam::Switzerland
    };

    for (auto team : group2Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex)
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group C
    std::vector group3Teams =
    {
        ETeam::Belarus,
        ETeam::Denmark,
        ETeam::Greece,
        ETeam::Scotland
    };

    for (auto team : group3Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex)
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group D
    std::vector group4Teams =
    {
        ETeam::Azerbaijan,
        ETeam::France,
        ETeam::Iceland,
        ETeam::Ukraine
    };

    for (auto team : group4Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex)
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group E
    std::vector group5Teams =
    {
        ETeam::Bulgaria,
        ETeam::Georgia,
        ETeam::Spain,
        ETeam::Turkiye
    };

    for (auto team : group5Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex)
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group F
    std::vector group6Teams =
    {
        ETeam::Armenia,
        ETeam::Hungary,
        ETeam::Portugal,
        ETeam::RepublicOfIreland
    };

    for (auto team : group6Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex)
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group G
    std::vector group7Teams =
    {
        ETeam::Finland,
        ETeam::Netherlands,
        ETeam::Poland,
        ETeam::Lithuania,
        ETeam::Malta
    };

    for (auto team : group7Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex)
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group H
    std::vector group8Teams =
    {
        ETeam::BosniaAndHerzegovina,
        ETeam::Austria,
        ETeam::Romania,
        ETeam::Cyprus,
        ETeam::SanMarino
    };

    for (auto team : group8Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex)
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group I
    std::vector group9Teams =
    {
        ETeam::Norway,
        ETeam::Israel,
        ETeam::Italy,
        ETeam::Estonia,
        ETeam::Moldova
    };

    for (auto team : group9Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex)
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group J
    std::vector group10Teams =
    {
        ETeam::NorthMacedonia,
        ETeam::Wales,
        ETeam::Belgium,
        ETeam::Kazakhstan,
        ETeam::Liechtenstein
    };

    for (auto team : group10Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex)
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group K
    std::vector group11Teams =
    {
        ETeam::England,
        ETeam::Albania,
        ETeam::Serbia,
        ETeam::Latvia,
        ETeam::Andorra
    };

    for (auto team : group11Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex)
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group L
    std::vector group12Teams =
    {
        ETeam::Czechia,
        ETeam::Croatia,
        ETeam::Montenegro,
        ETeam::FaroeIslands,
        ETeam::Gibraltar
    };

    for (auto team : group12Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex)
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;
}

void MatchesInitializer::InitUEFAWCQualifiersTables(PGconn* pg)
{
    int groupIndex = 0;

    // Group A
    std::vector group1Teams =
    {
        ETeam::Luxemburg,
        ETeam::NorthernIreland,
        ETeam::Slovakia,
        ETeam::Germany
    };

    for (auto team : group1Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex) + ", '25/26'"
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group B
    std::vector group2Teams =
    {
        ETeam::Kosovo,
        ETeam::Slovenia,
        ETeam::Sweden,
        ETeam::Switzerland
    };

    for (auto team : group2Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex) + ", '25/26'"
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group C
    std::vector group3Teams =
    {
        ETeam::Belarus,
        ETeam::Denmark,
        ETeam::Greece,
        ETeam::Scotland
    };

    for (auto team : group3Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex) + ", '25/26'"
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group D
    std::vector group4Teams =
    {
        ETeam::Azerbaijan,
        ETeam::France,
        ETeam::Iceland,
        ETeam::Ukraine
    };

    for (auto team : group4Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex) + ", '25/26'"
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group E
    std::vector group5Teams =
    {
        ETeam::Bulgaria,
        ETeam::Georgia,
        ETeam::Spain,
        ETeam::Turkiye
    };

    for (auto team : group5Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex) + ", '25/26'"
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group F
    std::vector group6Teams =
    {
        ETeam::Armenia,
        ETeam::Hungary,
        ETeam::Portugal,
        ETeam::RepublicOfIreland
    };

    for (auto team : group6Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex) + ", '25/26'"
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group G
    std::vector group7Teams =
    {
        ETeam::Finland,
        ETeam::Netherlands,
        ETeam::Poland,
        ETeam::Lithuania,
        ETeam::Malta
    };

    for (auto team : group7Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex) + ", '25/26'"
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group H
    std::vector group8Teams =
    {
        ETeam::BosniaAndHerzegovina,
        ETeam::Austria,
        ETeam::Romania,
        ETeam::Cyprus,
        ETeam::SanMarino
    };

    for (auto team : group8Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex) + ", '25/26'"
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group I
    std::vector group9Teams =
    {
        ETeam::Norway,
        ETeam::Israel,
        ETeam::Italy,
        ETeam::Estonia,
        ETeam::Moldova
    };

    for (auto team : group9Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex) + ", '25/26'"
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group J
    std::vector group10Teams =
    {
        ETeam::NorthMacedonia,
        ETeam::Wales,
        ETeam::Belgium,
        ETeam::Kazakhstan,
        ETeam::Liechtenstein
    };

    for (auto team : group10Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex) + ", '25/26'"
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group K
    std::vector group11Teams =
    {
        ETeam::England,
        ETeam::Albania,
        ETeam::Serbia,
        ETeam::Latvia,
        ETeam::Andorra
    };

    for (auto team : group11Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex) + ", '25/26'"
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;

    // Group L
    std::vector group12Teams =
    {
        ETeam::Czechia,
        ETeam::Croatia,
        ETeam::Montenegro,
        ETeam::FaroeIslands,
        ETeam::Gibraltar
    };

    for (auto team : group12Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::UEFAWorldClubQualification)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex) + ", '25/26'"
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;
}

void MatchesInitializer::InitUEFAWCQualifiers(PGconn* pg)
{
    std::vector<Match> matches;

    // Week 9
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::Azerbaijan, ETeam::Iceland, 1763053200000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::France, ETeam::Ukraine, 1763053200000 });

    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::Armenia, ETeam::Hungary, 1763053200000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::RepublicOfIreland, ETeam::Portugal, 1763053200000 });

    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::Norway, ETeam::Estonia, 1763053200000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::Moldova, ETeam::Italy, 1763053200000 });

    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::Andorra, ETeam::Albania, 1763053200000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::England, ETeam::Serbia, 1763053200000 });

    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::Luxemburg, ETeam::Germany, 1763053200000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::Slovakia, ETeam::NorthernIreland, 1763053200000 });

    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::Finland, ETeam::Malta, 1763053200000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::Poland, ETeam::Netherlands, 1763053200000 });

    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::Croatia, ETeam::FaroeIslands, 1763053200000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::Gibraltar, ETeam::Montenegro, 1763053200000 });

    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::Slovenia, ETeam::Kosovo, 1763053200000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::Switzerland, ETeam::Sweden, 1763053200000 });

    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::Denmark, ETeam::Belarus, 1763053200000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::Greece, ETeam::Scotland, 1763053200000 });

    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::Georgia, ETeam::Spain, 1763053200000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::Turkiye, ETeam::Bulgaria, 1763053200000 });

    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::Cyprus, ETeam::Austria, 1763053200000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::BosniaAndHerzegovina, ETeam::Romania, 1763053200000 });

    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::Kazakhstan, ETeam::Belgium, 1763053200000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 9, ETeam::Liechtenstein, ETeam::Wales, 1763053200000 });

    // Week 10
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::Azerbaijan, ETeam::France, 1763312400000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::Ukraine, ETeam::Iceland, 1763312400000 });

    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::Hungary, ETeam::RepublicOfIreland, 1763312400000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::Portugal, ETeam::Armenia, 1763312400000 });
    
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::Israel, ETeam::Moldova, 1763312400000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::Italy, ETeam::Norway, 1763312400000 });

    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::Albania, ETeam::England, 1763312400000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::Serbia, ETeam::Latvia, 1763312400000 });

    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::Germany, ETeam::Slovakia, 1763312400000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::NorthernIreland, ETeam::Luxemburg, 1763312400000 });

    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::Malta, ETeam::Poland, 1763312400000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::Netherlands, ETeam::Lithuania, 1763312400000 });

    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::Czechia, ETeam::Gibraltar, 1763312400000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::Montenegro, ETeam::Croatia, 1763312400000 });

    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::Kosovo, ETeam::Switzerland, 1763312400000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::Sweden, ETeam::Slovenia, 1763312400000 });

    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::Belarus, ETeam::Greece, 1763312400000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::Scotland, ETeam::Denmark, 1763312400000 });

    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::Bulgaria, ETeam::Georgia, 1763312400000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::Spain, ETeam::Turkiye, 1763312400000 });

    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::Austria, ETeam::BosniaAndHerzegovina, 1763312400000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::Romania, ETeam::SanMarino, 1763312400000 });

    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::Belgium, ETeam::Liechtenstein, 1763312400000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 10, ETeam::Wales, ETeam::NorthMacedonia, 1763312400000 });

    for (auto& m : matches)
    {
        std::string sql = "insert into matches(league, season, week, team1, team2, match_date) values ("
            + std::to_string(int(m.League)) + ", '"
            + m.Season + "', "
            + std::to_string(m.Week) + ", "
            + std::to_string((int)m.Team1) + ", "
            + std::to_string((int)m.Team2) + ", "
            + std::to_string(m.Date) + ");";

        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}


void MatchesInitializer::FillAwards(PGconn* pg)
{
    for (int league = 1; league <= 3; ++league)
    {
        std::string sql = "SELECT u.id, u.points_24_25, COUNT(p.id) AS total_predictions "
            "FROM users u "
            "INNER JOIN predicts_24_25 p ON u.id = p.user_id "
            "WHERE p.status != 4 AND u.league = " + std::to_string(league) +
            " GROUP BY u.id, u.name, u.points_24_25 "
            "HAVING COUNT(p.id) > 0 "
            "ORDER BY points_24_25 DESC, total_predictions DESC, u.id ASC "
            "LIMIT 20;";

        PGresult* ret = PQexec(pg, sql.c_str());
        int nrows = PQntuples(ret);
        for (int i = 0; i < nrows; ++i)
        {
            int id = atoi(PQgetvalue(ret, i, 0));

            sql = "INSERT INTO awards (user_id, league, place, season) VALUES ("
                + std::to_string(id) + ", "
                + std::to_string(league) + ", "
                + std::to_string(i + 1) + ", '24/25');";

            PGresult* ret = PQexec(pg, sql.c_str());
            PQclear(ret);
        }
        PQclear(ret);
    }

    return;
}