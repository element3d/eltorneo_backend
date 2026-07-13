#include "MatchesInitializer.h"
#include <vector>
#include <unordered_map>

void MatchesInitializer::InitWorldCupTeams25_26(PGconn* pg)
{
    std::vector<ETeam> newTeams =
    {
        ETeam::Canada,
        ETeam::Mexico,
        ETeam::USA,
        ETeam::Algeria,
        ETeam::Argentina,
        ETeam::Australia,
        ETeam::Brazil,
        ETeam::CaboVerde,
        ETeam::Colombia,
        ETeam::CongoDR,
        ETeam::IvoryCoast,
        ETeam::Curacao,
        ETeam::Ecuador,
        ETeam::Egypt,
        ETeam::Ghana,
        ETeam::Haiti,
        ETeam::Iran,
        ETeam::Iraq,
        ETeam::Japan,
        ETeam::Jordan,
        ETeam::KoreaRepublic,
        ETeam::Morocco,
        ETeam::NewZealand,
        ETeam::Panama,
        ETeam::Paraguay,
        ETeam::Qatar,
        ETeam::SaudiArabia,
        ETeam::Senegal,
        ETeam::SouthAfrica,
        ETeam::Tunisia,
        ETeam::Uruguay,
        ETeam::Uzbekistan
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
        ETeam::Mexico,
        ETeam::SouthAfrica,
        ETeam::KoreaRepublic,
        ETeam::Czechia
    };

    for (auto team : group1Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
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
        ETeam::Canada,
        ETeam::BosniaAndHerzegovina,
        ETeam::Qatar,
        ETeam::Switzerland
    };

    for (auto team : group2Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
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
        ETeam::Brazil,
        ETeam::Morocco,
        ETeam::Haiti,
        ETeam::Scotland
    };

    for (auto team : group3Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
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
        ETeam::USA,
        ETeam::Paraguay,
        ETeam::Australia,
        ETeam::Turkiye
    };

    for (auto team : group4Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
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
        ETeam::Germany,
        ETeam::Curacao,
        ETeam::IvoryCoast,
        ETeam::Ecuador
    };

    for (auto team : group5Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
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
        ETeam::Netherlands,
        ETeam::Japan,
        ETeam::Sweden,
        ETeam::Tunisia
    };

    for (auto team : group6Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
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
        ETeam::Belgium,
        ETeam::Egypt,
        ETeam::Iran,
        ETeam::NewZealand
    };

    for (auto team : group7Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
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
        ETeam::Spain,
        ETeam::CaboVerde,
        ETeam::SaudiArabia,
        ETeam::Uruguay
    };

    for (auto team : group8Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
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
        ETeam::France,
        ETeam::Senegal,
        ETeam::Iraq,
        ETeam::Norway
    };

    for (auto team : group9Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
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
        ETeam::Argentina,
        ETeam::Algeria,
        ETeam::Austria,
        ETeam::Jordan
    };

    for (auto team : group10Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
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
        ETeam::Portugal,
        ETeam::CongoDR,
        ETeam::Uzbekistan,
        ETeam::Colombia
    };

    for (auto team : group11Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
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
        ETeam::England,
        ETeam::Croatia,
        ETeam::Ghana,
        ETeam::Panama
    };

    for (auto team : group12Teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id, group_index) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex)
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;
}

void MatchesInitializer::InitWorldCupTable25_26(PGconn* pg)
{
    int groupIndex = 0;

    // Group A
    std::vector group1Teams =
    {
        ETeam::Mexico,
        ETeam::SouthAfrica,
        ETeam::KoreaRepublic,
        ETeam::Czechia
    };

    for (auto team : group1Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
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
        ETeam::Canada,
        ETeam::BosniaAndHerzegovina,
        ETeam::Qatar,
        ETeam::Switzerland
    };

    for (auto team : group2Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
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
        ETeam::Brazil,
        ETeam::Morocco,
        ETeam::Haiti,
        ETeam::Scotland
    };

    for (auto team : group3Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
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
        ETeam::USA,
        ETeam::Paraguay,
        ETeam::Australia,
        ETeam::Turkiye
    };

    for (auto team : group4Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
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
        ETeam::Germany,
        ETeam::Curacao,
        ETeam::IvoryCoast,
        ETeam::Ecuador
    };

    for (auto team : group5Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
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
        ETeam::Netherlands,
        ETeam::Japan,
        ETeam::Sweden,
        ETeam::Tunisia
    };

    for (auto team : group6Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
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
        ETeam::Belgium,
        ETeam::Egypt,
        ETeam::Iran,
        ETeam::NewZealand
    };

    for (auto team : group7Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
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
        ETeam::Spain,
        ETeam::CaboVerde,
        ETeam::SaudiArabia,
        ETeam::Uruguay
    };

    for (auto team : group8Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
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
        ETeam::France,
        ETeam::Senegal,
        ETeam::Iraq,
        ETeam::Norway
    };

    for (auto team : group9Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
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
        ETeam::Argentina,
        ETeam::Algeria,
        ETeam::Austria,
        ETeam::Jordan
    };

    for (auto team : group10Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
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
        ETeam::Portugal,
        ETeam::CongoDR,
        ETeam::Uzbekistan,
        ETeam::Colombia
    };

    for (auto team : group11Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
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
        ETeam::England,
        ETeam::Croatia,
        ETeam::Ghana,
        ETeam::Panama
    };

    for (auto team : group12Teams)
    {
        std::string sql = "insert into tables(league_id, team_id, group_index, season) values ("
            + std::to_string(int(ELeague::WorldCup)) + ", "
            + std::to_string(int(team)) + ", "
            + std::to_string(groupIndex) + ", '25/26'"
            + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
    ++groupIndex;
}


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

void MatchesInitializer::InitEuropaLeagueTeams25_26(PGconn* pg)
{
    std::vector<ETeam> newTeams =
    {
        ETeam::Panathinaikos,
        ETeam::Ferencvaros,
        ETeam::Genk,
        ETeam::Midtjylland,
        ETeam::Braga
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
        ETeam::Bologna,
        ETeam::Roma,
        ETeam::Lille,
        ETeam::AstonVilla,
        ETeam::Panathinaikos,
        ETeam::RealBetis,
        ETeam::Stuttgart,
        ETeam::Porto,
        ETeam::CeltaVigo,
        ETeam::Lyon,
        ETeam::Ferencvaros,
        ETeam::Braga,
        ETeam::Genk,
        ETeam::Freiburg,
        ETeam::NottinghamForest,
        ETeam::Midtjylland
    };

    for (auto team : clTeams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id) values ("
            + std::to_string(int(ELeague::EuropaLeague)) + ", "
            + std::to_string(int(team)) + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitConfLeagueTeams25_26(PGconn* pg)
{
    std::vector<ETeam> newTeams =
    {
        ETeam::AEKAthens,
        ETeam::AZAlkmaar
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
        ETeam::RayoVallecano,
        ETeam::AEKAthens,
        ETeam::CrystalPalace,
        ETeam::Fiorentina,
        ETeam::Mainz,
        ETeam::Strasbourg,
        ETeam::ShakhtarDonetsk,
        ETeam::AZAlkmaar
    };

    for (auto team : clTeams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id) values ("
            + std::to_string(int(ELeague::ConferenceLeague)) + ", "
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

void MatchesInitializer::InitPremierLeagueTeams26_27(PGconn* pg)
{
    for (int i = (int)ETeam::PremierLeague2026Start; i <= (int)ETeam::PremierLeague2026End; ++i)
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
        ETeam::Coventry,
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
        ETeam::Hull,
        ETeam::IpswichTown
    };
    for (ETeam i : teams)
    {
        sql = "insert into tables(team_id, league_id, season) values ("
            + std::to_string(int(i)) + ", "
            + std::to_string(int(ELeague::PremierLeague)) + " ,'"
            + "26/27" 
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


void MatchesInitializer::InitLaLigaTeams26_27(PGconn* pg)
{
    for (int i = (int)ETeam::LaLiga2026Start; i <= (int)ETeam::LaLiga2026End; ++i)
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
        ETeam::RacingSantander,
        ETeam::Levante,
        ETeam::Malaga,
        ETeam::Osasuna,
        ETeam::RayoVallecano,
        ETeam::RealBetis,
        ETeam::RealMadrid,
        ETeam::DepCoruna,
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
            + "26/27"
            + "');";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::FillLaLigaTable(PGconn* pg)
{
    FillLeagueTable(pg, int(ELeague::LaLiga));
}

void MatchesInitializer::InitSerieATeams26_27(PGconn* pg)
{

    for (int i = (int)ETeam::SerieA2026Start; i <= (int)ETeam::SerieA2026End; ++i)
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
        ETeam::Monza,
        ETeam::Fiorentina,
        ETeam::Genoa,
        ETeam::InterMilan,
        ETeam::Juventus,
        ETeam::Lazio,
        ETeam::Lecce,
        ETeam::Napoli,
        ETeam::Parma,
        ETeam::Frosinone,
        ETeam::Roma,
        ETeam::Sassuolo,
        ETeam::Torino,
        ETeam::Udinese,
        ETeam::Venezia
    };
    for (ETeam i : teams)
    {
        std::string sql = "insert into tables(team_id, league_id, season) values ("
            + std::to_string((int)i) + ", "
            + std::to_string(int(ELeague::SerieA)) + " ,'"
            + "26/27"
            + "');";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::FillSeriaATable(PGconn* pg) 
{
    FillLeagueTable(pg, int(ELeague::SerieA));
}

void MatchesInitializer::InitBundesligaTeams26_27(PGconn* pg)
{
    for (int i = (int)ETeam::Bundesliga2026Start; i <= (int)ETeam::Bundesliga2026End; ++i)
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
        ETeam::Schalke,
        ETeam::Hoffenheim,
        ETeam::Mainz,
        ETeam::RBLeipzig,
        ETeam::Elversberg,
        ETeam::Stuttgart,
        ETeam::UnionBerlin,
        ETeam::WerderBremen,
        ETeam::Pederborn
    };
    for (ETeam i : teams)
    {
        std::string sql = "insert into tables(team_id, league_id, season) values ("
            + std::to_string(int(i)) + ", "
            + std::to_string(int(ELeague::Bundesliga)) + " ,'"
            + "26/27"
            + "');";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::FillBundesligaTable(PGconn* pg) 
{
    FillLeagueTable(pg, int(ELeague::Bundesliga));
}


void MatchesInitializer::InitLigue1Teams26_27(PGconn* pg)
{
    for (int i = (int)ETeam::Ligue12026Start; i <= (int)ETeam::Ligue12026End; ++i)
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

void MatchesInitializer::InitWorldCupPO25_26(PGconn* pg)
{
    // ClubWorldCup
    std::vector<Match> matches;
    // 1/16
   // matches.push_back({ ELeague::WorldCup, "25/26", 4, ETeam::SouthAfrica, ETeam::Canada, 1782673200000, EWeekType::RoundOf32, true });
   // matches.push_back({ ELeague::WorldCup, "25/26", 4, ETeam::Brazil, ETeam::Japan, 1782673200000, EWeekType::RoundOf32, true });
   // matches.push_back({ ELeague::WorldCup, "25/26", 4, ETeam::Netherlands, ETeam::Morocco, 1782673200000, EWeekType::RoundOf32, true });
   // matches.push_back({ ELeague::WorldCup, "25/26", 4, ETeam::IvoryCoast, ETeam::Norway, 1782673200000, EWeekType::RoundOf32, true });
   // matches.push_back({ ELeague::WorldCup, "25/26", 4, ETeam::USA, ETeam::BosniaAndHerzegovina, 1782673200000, EWeekType::RoundOf32, true });
        
   // matches.push_back({ ELeague::WorldCup, "25/26", 4, ETeam::Germany, ETeam::Paraguay, 1782673200000, EWeekType::RoundOf32, true });
   // matches.push_back({ ELeague::WorldCup, "25/26", 4, ETeam::France, ETeam::Sweden, 1782673200000, EWeekType::RoundOf32, true });
   // matches.push_back({ ELeague::WorldCup, "25/26", 4, ETeam::Australia, ETeam::Egypt, 1782673200000, EWeekType::RoundOf32, true });
   // matches.push_back({ ELeague::WorldCup, "25/26", 4, ETeam::Argentina, ETeam::CaboVerde, 1782673200000, EWeekType::RoundOf32, true });
   
   // matches.push_back({ ELeague::WorldCup, "25/26", 4, ETeam::Mexico, ETeam::Ecuador, 1782673200000, EWeekType::RoundOf32, true });
   // matches.push_back({ ELeague::WorldCup, "25/26", 4, ETeam::England, ETeam::CongoDR, 1782673200000, EWeekType::RoundOf32, true });
   // matches.push_back({ ELeague::WorldCup, "25/26", 4, ETeam::Belgium, ETeam::Senegal, 1782673200000, EWeekType::RoundOf32, true });
   // matches.push_back({ ELeague::WorldCup, "25/26", 4, ETeam::Spain, ETeam::Austria, 1782673200000, EWeekType::RoundOf32, true });
   // matches.push_back({ ELeague::WorldCup, "25/26", 4, ETeam::Portugal, ETeam::Croatia, 1782673200000, EWeekType::RoundOf32, true });
   // matches.push_back({ ELeague::WorldCup, "25/26", 4, ETeam::Switzerland, ETeam::Algeria, 1782673200000, EWeekType::RoundOf32, true });
   // matches.push_back({ ELeague::WorldCup, "25/26", 4, ETeam::Colombia, ETeam::Ghana, 1782673200000, EWeekType::RoundOf32, true });

  

  //  matches.push_back({ ELeague::WorldCup, "25/26", 7, ETeam::France, ETeam::Spain, 1784055600000, EWeekType::SemiFinal, true });
    matches.push_back({ ELeague::WorldCup, "25/26", 7, ETeam::England, ETeam::Argentina, 1784142000000, EWeekType::SemiFinal, true });

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

void MatchesInitializer::InitWorldCup25_26(PGconn* pg)
{
    std::vector<Match> matches;
    // Group A
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::Mexico, ETeam::SouthAfrica, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::KoreaRepublic, ETeam::Czechia, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::Czechia, ETeam::SouthAfrica, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::Mexico, ETeam::KoreaRepublic, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::Czechia, ETeam::Mexico, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::SouthAfrica, ETeam::KoreaRepublic, 1781204400000 });

    // Group B
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::Canada, ETeam::BosniaAndHerzegovina, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::Qatar, ETeam::Switzerland, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::Switzerland, ETeam::BosniaAndHerzegovina, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::Canada, ETeam::Qatar, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::Switzerland, ETeam::Canada, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::BosniaAndHerzegovina, ETeam::Qatar, 1781204400000 });

    // Group C
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::Brazil, ETeam::Morocco, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::Haiti, ETeam::Scotland, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::Scotland, ETeam::Morocco, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::Brazil, ETeam::Haiti, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::Scotland, ETeam::Brazil, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::Morocco, ETeam::Haiti, 1781204400000 });

    // Group D
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::USA, ETeam::Paraguay, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::Australia, ETeam::Turkiye, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::USA, ETeam::Australia, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::Turkiye, ETeam::Paraguay, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::Turkiye, ETeam::USA, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::Paraguay, ETeam::Australia, 1781204400000 });

    // Group E
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::Germany, ETeam::Curacao, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::IvoryCoast, ETeam::Ecuador, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::Germany, ETeam::IvoryCoast, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::Ecuador, ETeam::Curacao, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::Curacao, ETeam::IvoryCoast, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::Ecuador, ETeam::Germany, 1781204400000 });

    // Group F
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::Netherlands, ETeam::Japan, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::Sweden, ETeam::Tunisia, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::Netherlands, ETeam::Sweden, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::Tunisia, ETeam::Japan, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::Japan, ETeam::Sweden, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::Tunisia, ETeam::Netherlands, 1781204400000 });

    // Group G
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::Belgium, ETeam::Egypt, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::Iran, ETeam::NewZealand, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::Belgium, ETeam::Iran, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::NewZealand, ETeam::Egypt, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::Egypt, ETeam::Iran, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::NewZealand, ETeam::Belgium, 1781204400000 });

    // Group H
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::Spain, ETeam::CaboVerde, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::SaudiArabia, ETeam::Uruguay, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::Spain, ETeam::SaudiArabia, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::Uruguay, ETeam::CaboVerde, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::CaboVerde, ETeam::SaudiArabia, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::Uruguay, ETeam::Spain, 1781204400000 });

    // Group I
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::France, ETeam::Senegal, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::Iraq, ETeam::Norway, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::France, ETeam::Iraq, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::Norway, ETeam::Senegal, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::Norway, ETeam::France, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::Senegal, ETeam::Iraq, 1781204400000 });

    // Group J
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::Argentina, ETeam::Algeria, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::Austria, ETeam::Jordan, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::Argentina, ETeam::Austria, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::Jordan, ETeam::Algeria, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::Algeria, ETeam::Austria, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::Jordan, ETeam::Argentina, 1781204400000 });

    // Group K
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::Portugal, ETeam::CongoDR, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::Uzbekistan, ETeam::Colombia, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::Portugal, ETeam::Uzbekistan, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::Colombia, ETeam::CongoDR, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::Colombia, ETeam::Portugal, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::CongoDR, ETeam::Uzbekistan, 1781204400000 });

    // Group L
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::England, ETeam::Croatia, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 1, ETeam::Ghana, ETeam::Panama, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::England, ETeam::Ghana, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 2, ETeam::Panama, ETeam::Croatia, 1781204400000 });

    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::Panama, ETeam::England, 1781204400000 });
    matches.push_back({ ELeague::WorldCup, "25/26", 3, ETeam::Croatia, ETeam::Ghana, 1781204400000 });

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
        ETeam::LeMans,
        ETeam::Monaco,
        ETeam::Troyes,
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
            + "26/27"
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

    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::AtleticoMadrid, ETeam::ClubBrugge, 1771955100000, EWeekType::RoundOf16, true });
    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::BayerLeverkusen, ETeam::Olympiakos, 1771963200000, EWeekType::RoundOf16, true });
    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::InterMilan, ETeam::BodoGlimt, 1771963200000, EWeekType::RoundOf16, true });
    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::NewcastleUnited, ETeam::Qarabag, 1771963200000, EWeekType::RoundOf16, true });
    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::Atalanta, ETeam::BorussiaDortmund, 1772048700000, EWeekType::RoundOf16, true });
    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::Juventus, ETeam::Galatasaray, 1772049600000, EWeekType::RoundOf16, true });
    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::PSG, ETeam::Monaco, 1772049600000, EWeekType::RoundOf16, true });
    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 9, ETeam::RealMadrid, ETeam::Benfica, 1772049600000, EWeekType::RoundOf16, true });


    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 10, ETeam::PSG, ETeam::Chelsea, 1773172800000, EWeekType::RoundOf8, false });
    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 10, ETeam::Galatasaray, ETeam::Liverpool, 1773172800000, EWeekType::RoundOf8, false });
    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 10, ETeam::RealMadrid, ETeam::ManchesterCity, 1773172800000, EWeekType::RoundOf8, false });
    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 10, ETeam::Atalanta, ETeam::BayernMunich, 1773172800000, EWeekType::RoundOf8, false });
    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 10, ETeam::NewcastleUnited, ETeam::Barcelona, 1773172800000, EWeekType::RoundOf8, false });
    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 10, ETeam::AtleticoMadrid, ETeam::TottenhamHotspur, 1773172800000, EWeekType::RoundOf8, false });
    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 10, ETeam::BodoGlimt, ETeam::SportingLisbon, 1773172800000, EWeekType::RoundOf8, false });
    // matches.push_back({ ELeague::ChampionsLeague, "25/26", 10, ETeam::BayerLeverkusen, ETeam::Arsenal, 1773172800000, EWeekType::RoundOf8, false });

  // matches.push_back({ ELeague::ChampionsLeague, "25/26", 10, ETeam::SportingLisbon, ETeam::BodoGlimt, 1773769500000, EWeekType::RoundOf8, true });
  // matches.push_back({ ELeague::ChampionsLeague, "25/26", 10, ETeam::Chelsea, ETeam::PSG, 1773777600000, EWeekType::RoundOf8, true });
  // matches.push_back({ ELeague::ChampionsLeague, "25/26", 10, ETeam::ManchesterCity, ETeam::RealMadrid, 1773777600000, EWeekType::RoundOf8, true });
  // matches.push_back({ ELeague::ChampionsLeague, "25/26", 10, ETeam::Arsenal, ETeam::BayerLeverkusen, 1773777600000, EWeekType::RoundOf8, true });
  // matches.push_back({ ELeague::ChampionsLeague, "25/26", 10, ETeam::Barcelona, ETeam::NewcastleUnited, 1773855900000, EWeekType::RoundOf8, true });
  // matches.push_back({ ELeague::ChampionsLeague, "25/26", 10, ETeam::Liverpool, ETeam::Galatasaray, 1773864000000, EWeekType::RoundOf8, true });
  // matches.push_back({ ELeague::ChampionsLeague, "25/26", 10, ETeam::BayernMunich, ETeam::Atalanta, 1773864000000, EWeekType::RoundOf8, true });
  // matches.push_back({ ELeague::ChampionsLeague, "25/26", 10, ETeam::TottenhamHotspur, ETeam::AtleticoMadrid, 1773864000000, EWeekType::RoundOf8, true });

   // matches.push_back({ ELeague::ChampionsLeague, "25/26", 11, ETeam::PSG, ETeam::Liverpool, 1775592000000, EWeekType::QuarterFinal, false });
   // matches.push_back({ ELeague::ChampionsLeague, "25/26", 11, ETeam::RealMadrid, ETeam::BayernMunich, 1775592000000, EWeekType::QuarterFinal, false });
   // matches.push_back({ ELeague::ChampionsLeague, "25/26", 11, ETeam::Barcelona, ETeam::AtleticoMadrid, 1775592000000, EWeekType::QuarterFinal, false });
   // matches.push_back({ ELeague::ChampionsLeague, "25/26", 11, ETeam::SportingLisbon, ETeam::Arsenal, 1775592000000, EWeekType::QuarterFinal, false });

   // matches.push_back({ ELeague::ChampionsLeague, "25/26", 11, ETeam::AtleticoMadrid, ETeam::Barcelona, 1776193200000, EWeekType::QuarterFinal, true });
   // matches.push_back({ ELeague::ChampionsLeague, "25/26", 11, ETeam::Liverpool, ETeam::PSG, 1776193200000, EWeekType::QuarterFinal, true });
   // matches.push_back({ ELeague::ChampionsLeague, "25/26", 11, ETeam::Arsenal, ETeam::SportingLisbon, 1776279600000, EWeekType::QuarterFinal, true });
   // matches.push_back({ ELeague::ChampionsLeague, "25/26", 11, ETeam::BayernMunich, ETeam::RealMadrid, 1776279600000, EWeekType::QuarterFinal, true });

   // matches.push_back({ ELeague::ChampionsLeague, "25/26", 12, ETeam::PSG, ETeam::BayernMunich, 1777402800000, EWeekType::SemiFinal, false });
   // matches.push_back({ ELeague::ChampionsLeague, "25/26", 12, ETeam::AtleticoMadrid, ETeam::Arsenal, 1777489200000, EWeekType::SemiFinal, false });

   // matches.push_back({ ELeague::ChampionsLeague, "25/26", 12, ETeam::BayernMunich, ETeam::PSG, 1778094000000, EWeekType::SemiFinal, true });
 //   matches.push_back({ ELeague::ChampionsLeague, "25/26", 12, ETeam::Arsenal, ETeam::AtleticoMadrid, 1778007600000, EWeekType::SemiFinal, true });

        matches.push_back({ ELeague::ChampionsLeague, "25/26", 13, ETeam::PSG, ETeam::Arsenal, 1780156800000, EWeekType::Final, true });
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

void MatchesInitializer::InitEuropaLeaguePO25_26(PGconn* pg)
{
    std::vector<Match> matches;

    //matches.push_back({ ELeague::EuropaLeague, "25/26", 11, ETeam::CeltaVigo, ETeam::Freiburg, 1776357900000, EWeekType::QuarterFinal, true });
    //matches.push_back({ ELeague::EuropaLeague, "25/26", 11, ETeam::AstonVilla, ETeam::Bologna, 1776366000000, EWeekType::QuarterFinal, true });
    //matches.push_back({ ELeague::EuropaLeague, "25/26", 11, ETeam::NottinghamForest, ETeam::Porto, 1776366000000, EWeekType::QuarterFinal, true });
    //matches.push_back({ ELeague::EuropaLeague, "25/26", 11, ETeam::RealBetis, ETeam::Braga, 1776366000000, EWeekType::QuarterFinal, true });

   // matches.push_back({ ELeague::EuropaLeague, "25/26", 12, ETeam::AstonVilla, ETeam::NottinghamForest, 1778180400000, EWeekType::SemiFinal, true });
   // matches.push_back({ ELeague::EuropaLeague, "25/26", 12, ETeam::Freiburg, ETeam::Braga, 1778180400000, EWeekType::SemiFinal, true });

    matches.push_back({ ELeague::EuropaLeague, "25/26", 13, ETeam::Freiburg, ETeam::AstonVilla, 1779303600000, EWeekType::Final, true });

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

void MatchesInitializer::InitConfLeaguePO25_26(PGconn* pg)
{
    std::vector<Match> matches;

   // matches.push_back({ ELeague::ConferenceLeague, "25/26", 11, ETeam::AZAlkmaar, ETeam::ShakhtarDonetsk, 1776357900000, EWeekType::QuarterFinal, true });
   // matches.push_back({ ELeague::ConferenceLeague, "25/26", 11, ETeam::AEKAthens, ETeam::RayoVallecano, 1776366000000, EWeekType::QuarterFinal, true });
   // matches.push_back({ ELeague::ConferenceLeague, "25/26", 11, ETeam::Fiorentina, ETeam::CrystalPalace, 1776366000000, EWeekType::QuarterFinal, true });
   // matches.push_back({ ELeague::ConferenceLeague, "25/26", 11, ETeam::Strasbourg, ETeam::Mainz, 1776366000000, EWeekType::QuarterFinal, true });

    //matches.push_back({ ELeague::ConferenceLeague, "25/26", 12, ETeam::Strasbourg, ETeam::RayoVallecano, 1778180400000, EWeekType::SemiFinal, true });
  //  matches.push_back({ ELeague::ConferenceLeague, "25/26", 12, ETeam::CrystalPalace, ETeam::ShakhtarDonetsk, 1778180400000, EWeekType::SemiFinal, true });
    matches.push_back({ ELeague::ConferenceLeague, "25/26", 13, ETeam::CrystalPalace, ETeam::RayoVallecano, 1779908400000, EWeekType::Final, true });


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


void MatchesInitializer::InitLigue126_27(PGconn* pg)
{
    std::vector<Match> matches;
    // Week 1
    matches.push_back({ ELeague::Ligue1, "26/27", 1, ETeam::Marseille, ETeam::Strasbourg, 1787329800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 1, ETeam::Lens, ETeam::Auxerre, 1787329800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 1, ETeam::LeMans, ETeam::Brest, 1787329800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 1, ETeam::Nice, ETeam::Lorient, 1787329800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 1, ETeam::Toulouse, ETeam::Lyon, 1787329800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 1, ETeam::Troyes, ETeam::ParisFC, 1787329800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 1, ETeam::Angers, ETeam::Lille, 1787329800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 1, ETeam::LeHavre, ETeam::Monaco, 1787329800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 1, ETeam::PSG, ETeam::Rennes, 1787329800000 });

    // Week 2
    matches.push_back({ ELeague::Ligue1, "26/27", 2, ETeam::Lille, ETeam::PSG, 1787934600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 2, ETeam::Strasbourg, ETeam::Lens, 1787934600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 2, ETeam::Auxerre, ETeam::Angers, 1787934600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 2, ETeam::Brest, ETeam::Toulouse, 1787934600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 2, ETeam::Lorient, ETeam::Troyes, 1787934600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 2, ETeam::Lyon, ETeam::LeHavre, 1787934600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 2, ETeam::ParisFC, ETeam::Nice, 1787934600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 2, ETeam::Rennes, ETeam::LeMans, 1787934600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 2, ETeam::Monaco, ETeam::Marseille, 1787934600000 });

    // Week 3
    matches.push_back({ ELeague::Ligue1, "26/27", 3, ETeam::Angers, ETeam::Rennes, 1788625800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 3, ETeam::LeHavre, ETeam::Brest, 1788625800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 3, ETeam::Lens, ETeam::Lorient, 1788625800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 3, ETeam::Lyon, ETeam::Auxerre, 1788625800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 3, ETeam::Marseille, ETeam::ParisFC, 1788625800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 3, ETeam::Nice, ETeam::LeMans, 1788625800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 3, ETeam::PSG, ETeam::Monaco, 1788625800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 3, ETeam::Toulouse, ETeam::Lille, 1788625800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 3, ETeam::Troyes, ETeam::Strasbourg, 1788625800000 });

    // Week 4
    matches.push_back({ ELeague::Ligue1, "26/27", 4, ETeam::Auxerre, ETeam::Nice, 1789230600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 4, ETeam::Brest, ETeam::PSG, 1789230600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 4, ETeam::LeHavre, ETeam::Angers, 1789230600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 4, ETeam::LeMans, ETeam::Lens, 1789230600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 4, ETeam::Lille, ETeam::Troyes, 1789230600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 4, ETeam::Lorient, ETeam::Toulouse, 1789230600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 4, ETeam::ParisFC, ETeam::Lyon, 1789230600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 4, ETeam::Rennes, ETeam::Marseille, 1789230600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 4, ETeam::Strasbourg, ETeam::Monaco, 1789230600000 });

    // Week 5
    matches.push_back({ ELeague::Ligue1, "26/27", 5, ETeam::Angers, ETeam::Troyes, 1789835400000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 5, ETeam::Auxerre, ETeam::Brest, 1789835400000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 5, ETeam::LeMans, ETeam::Lorient, 1789835400000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 5, ETeam::Lyon, ETeam::Rennes, 1789835400000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 5, ETeam::Monaco, ETeam::Lens, 1789835400000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 5, ETeam::Nice, ETeam::Lille, 1789835400000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 5, ETeam::ParisFC, ETeam::Strasbourg, 1789835400000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 5, ETeam::Toulouse, ETeam::LeHavre, 1789835400000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 5, ETeam::Marseille, ETeam::PSG, 1789835400000 });

    // Week 6
    matches.push_back({ ELeague::Ligue1, "26/27", 6, ETeam::Brest, ETeam::Angers, 1791649800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 6, ETeam::Lens, ETeam::Lyon, 1791649800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 6, ETeam::Lille, ETeam::LeHavre, 1791649800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 6, ETeam::Lorient, ETeam::ParisFC, 1791649800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 6, ETeam::Monaco, ETeam::Toulouse, 1791649800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 6, ETeam::Nice, ETeam::Strasbourg, 1791649800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 6, ETeam::PSG, ETeam::LeMans, 1791649800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 6, ETeam::Rennes, ETeam::Auxerre, 1791649800000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 6, ETeam::Troyes, ETeam::Marseille, 1791649800000 });

    // Week 7
    matches.push_back({ ELeague::Ligue1, "26/27", 7, ETeam::Angers, ETeam::Marseille, 1792254600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 7, ETeam::LeHavre, ETeam::Auxerre, 1792254600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 7, ETeam::LeMans, ETeam::Toulouse, 1792254600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 7, ETeam::Lille, ETeam::Brest, 1792254600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 7, ETeam::Lorient, ETeam::Monaco, 1792254600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 7, ETeam::Lyon, ETeam::Nice, 1792254600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 7, ETeam::ParisFC, ETeam::Rennes, 1792254600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 7, ETeam::Strasbourg, ETeam::PSG, 1792254600000 });
    matches.push_back({ ELeague::Ligue1, "26/27", 7, ETeam::Troyes, ETeam::Lens, 1792254600000 });


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

void MatchesInitializer::InitBundesliga26_27(PGconn* pg)
{
    std::vector<Match> matches;
    // Week 1
    matches.push_back({ ELeague::Bundesliga, "26/27", 1, ETeam::BayernMunich, ETeam::Stuttgart, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 1, ETeam::Augsburg, ETeam::Schalke, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 1, ETeam::BorussiaDortmund, ETeam::Hamburg, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 1, ETeam::Elversberg, ETeam::BayerLeverkusen, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 1, ETeam::Koln, ETeam::Hoffenheim, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 1, ETeam::Freiburg, ETeam::WerderBremen, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 1, ETeam::Mainz, ETeam::Pederborn, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 1, ETeam::RBLeipzig, ETeam::BorussiaMgladbach, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 1, ETeam::UnionBerlin, ETeam::EintrachtFrankfurt, 1755874800000 });

    // Week 2
    matches.push_back({ ELeague::Bundesliga, "26/27", 2, ETeam::BorussiaMgladbach, ETeam::Elversberg, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 2, ETeam::BayerLeverkusen, ETeam::UnionBerlin, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 2, ETeam::EintrachtFrankfurt, ETeam::Augsburg, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 2, ETeam::Hamburg, ETeam::Mainz, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 2, ETeam::Hoffenheim, ETeam::BorussiaDortmund, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 2, ETeam::Pederborn, ETeam::Freiburg, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 2, ETeam::Schalke, ETeam::BayernMunich, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 2, ETeam::Stuttgart, ETeam::Koln, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 2, ETeam::WerderBremen, ETeam::RBLeipzig, 1755874800000 });

    // Week 3
    matches.push_back({ ELeague::Bundesliga, "26/27", 3, ETeam::Augsburg, ETeam::BayerLeverkusen, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 3, ETeam::BorussiaDortmund, ETeam::Pederborn, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 3, ETeam::Elversberg, ETeam::BayernMunich, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 3, ETeam::Koln, ETeam::BorussiaMgladbach, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 3, ETeam::Freiburg, ETeam::BorussiaDortmund, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 3, ETeam::Hoffenheim, ETeam::Stuttgart, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 3, ETeam::Mainz, ETeam::EintrachtFrankfurt, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 3, ETeam::RBLeipzig, ETeam::Hamburg, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 3, ETeam::UnionBerlin, ETeam::Schalke, 1755874800000 });

    // Week 4
    matches.push_back({ ELeague::Bundesliga, "26/27", 4, ETeam::BorussiaMgladbach, ETeam::Mainz, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 4, ETeam::BayerLeverkusen, ETeam::RBLeipzig, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 4, ETeam::BayernMunich, ETeam::UnionBerlin, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 4, ETeam::EintrachtFrankfurt, ETeam::Freiburg, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 4, ETeam::Hamburg, ETeam::Koln, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 4, ETeam::Pederborn, ETeam::Hoffenheim, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 4, ETeam::Schalke, ETeam::Elversberg, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 4, ETeam::Stuttgart, ETeam::BorussiaDortmund, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 4, ETeam::WerderBremen, ETeam::Augsburg, 1755874800000 });

    // Week 5
    matches.push_back({ ELeague::Bundesliga, "26/27", 5, ETeam::Augsburg, ETeam::BayernMunich, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 5, ETeam::BorussiaDortmund, ETeam::WerderBremen, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 5, ETeam::Koln, ETeam::BorussiaMgladbach, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 5, ETeam::Freiburg, ETeam::Schalke, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 5, ETeam::Hoffenheim, ETeam::Hamburg, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 5, ETeam::Mainz, ETeam::BayerLeverkusen, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 5, ETeam::Pederborn, ETeam::Stuttgart, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 5, ETeam::RBLeipzig, ETeam::EintrachtFrankfurt, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 5, ETeam::UnionBerlin, ETeam::Elversberg, 1755874800000 });

    // Week 6
    matches.push_back({ ELeague::Bundesliga, "26/27", 6, ETeam::BorussiaMgladbach, ETeam::Hoffenheim, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 6, ETeam::BayerLeverkusen, ETeam::Freiburg, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 6, ETeam::BayernMunich, ETeam::RBLeipzig, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 6, ETeam::EintrachtFrankfurt, ETeam::Koln, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 6, ETeam::Elversberg, ETeam::Augsburg, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 6, ETeam::Hamburg, ETeam::Stuttgart, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 6, ETeam::Schalke, ETeam::Mainz, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 6, ETeam::UnionBerlin, ETeam::BorussiaDortmund, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 6, ETeam::WerderBremen, ETeam::Pederborn, 1755874800000 });

    // Week 7
    matches.push_back({ ELeague::Bundesliga, "26/27", 7, ETeam::Augsburg, ETeam::UnionBerlin, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 7, ETeam::BorussiaDortmund, ETeam::EintrachtFrankfurt, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 7, ETeam::Koln, ETeam::Schalke, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 7, ETeam::Freiburg, ETeam::BayernMunich, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 7, ETeam::Hoffenheim, ETeam::BayerLeverkusen, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 7, ETeam::Mainz, ETeam::WerderBremen, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 7, ETeam::Pederborn, ETeam::Hamburg, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 7, ETeam::RBLeipzig, ETeam::Elversberg, 1755874800000 });
    matches.push_back({ ELeague::Bundesliga, "26/27", 7, ETeam::Stuttgart, ETeam::BorussiaMgladbach, 1755874800000 });

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

void MatchesInitializer::InitSerieA26_27(PGconn* pg)
{
    std::vector<Match> matches;
    // Week 1
    matches.push_back({ ELeague::SerieA, "26/27", 1, ETeam::InterMilan, ETeam::Monza, 1787416200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 1, ETeam::Udinese, ETeam::Como, 1787416200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 1, ETeam::Genoa, ETeam::Napoli, 1787416200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 1, ETeam::Parma, ETeam::Cagliari, 1787416200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 1, ETeam::Frosinone, ETeam::Juventus, 1787416200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 1, ETeam::Venezia, ETeam::Lecce, 1787416200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 1, ETeam::Atalanta, ETeam::Sassuolo, 1787416200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 1, ETeam::Torino, ETeam::ACMilan, 1787416200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 1, ETeam::Bologna, ETeam::Lazio, 1787416200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 1, ETeam::Roma, ETeam::Fiorentina, 1787416200000 });

    // Week 2
    matches.push_back({ ELeague::SerieA, "26/27", 2, ETeam::ACMilan, ETeam::Venezia, 1787934600000 });
    matches.push_back({ ELeague::SerieA, "26/27", 2, ETeam::Fiorentina, ETeam::Frosinone, 1787934600000 });
    matches.push_back({ ELeague::SerieA, "26/27", 2, ETeam::Monza, ETeam::Udinese, 1787934600000 });
    matches.push_back({ ELeague::SerieA, "26/27", 2, ETeam::Sassuolo, ETeam::Torino, 1787934600000 });
    matches.push_back({ ELeague::SerieA, "26/27", 2, ETeam::Juventus, ETeam::Parma, 1787934600000 });
    matches.push_back({ ELeague::SerieA, "26/27", 2, ETeam::Napoli, ETeam::Como, 1787934600000 });
    matches.push_back({ ELeague::SerieA, "26/27", 2, ETeam::Cagliari, ETeam::InterMilan, 1787934600000 });
    matches.push_back({ ELeague::SerieA, "26/27", 2, ETeam::Lazio, ETeam::Genoa, 1787934600000 });
    matches.push_back({ ELeague::SerieA, "26/27", 2, ETeam::Lecce, ETeam::Roma, 1787934600000 });
    matches.push_back({ ELeague::SerieA, "26/27", 2, ETeam::Atalanta, ETeam::Bologna, 1787934600000 });

    // Week 3
    matches.push_back({ ELeague::SerieA, "26/27", 3, ETeam::Genoa, ETeam::Como, 1788539400000 });
    matches.push_back({ ELeague::SerieA, "26/27", 3, ETeam::Fiorentina, ETeam::Torino, 1788539400000 });
    matches.push_back({ ELeague::SerieA, "26/27", 3, ETeam::InterMilan, ETeam::Napoli, 1788539400000 });
    matches.push_back({ ELeague::SerieA, "26/27", 3, ETeam::Roma, ETeam::Atalanta, 1788539400000 });
    matches.push_back({ ELeague::SerieA, "26/27", 3, ETeam::Frosinone, ETeam::Venezia, 1788539400000 });
    matches.push_back({ ELeague::SerieA, "26/27", 3, ETeam::Parma, ETeam::Monza, 1788539400000 });
    matches.push_back({ ELeague::SerieA, "26/27", 3, ETeam::Bologna, ETeam::Sassuolo, 1788539400000 });
    matches.push_back({ ELeague::SerieA, "26/27", 3, ETeam::Juventus, ETeam::ACMilan, 1788539400000 });
    matches.push_back({ ELeague::SerieA, "26/27", 3, ETeam::Cagliari, ETeam::Lecce, 1788539400000 });
    matches.push_back({ ELeague::SerieA, "26/27", 3, ETeam::Udinese, ETeam::Lazio, 1788539400000 });

    // Week 4
    matches.push_back({ ELeague::SerieA, "26/27", 4, ETeam::Venezia, ETeam::Fiorentina, 1789144200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 4, ETeam::Genoa, ETeam::Frosinone, 1789144200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 4, ETeam::Sassuolo, ETeam::Juventus, 1789144200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 4, ETeam::Atalanta, ETeam::Cagliari, 1789144200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 4, ETeam::Torino, ETeam::Roma, 1789144200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 4, ETeam::Como, ETeam::Parma, 1789144200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 4, ETeam::Lecce, ETeam::Monza, 1789144200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 4, ETeam::Napoli, ETeam::Bologna, 1789144200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 4, ETeam::Lazio, ETeam::ACMilan, 1789144200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 4, ETeam::InterMilan, ETeam::Udinese, 1789144200000 });

    // Week 5
    matches.push_back({ ELeague::SerieA, "26/27", 5, ETeam::Monza, ETeam::Sassuolo, 1789749000000 });
    matches.push_back({ ELeague::SerieA, "26/27", 5, ETeam::Bologna, ETeam::Torino, 1789749000000 });
    matches.push_back({ ELeague::SerieA, "26/27", 5, ETeam::Udinese, ETeam::Cagliari, 1789749000000 });
    matches.push_back({ ELeague::SerieA, "26/27", 5, ETeam::Roma, ETeam::InterMilan, 1789749000000 });
    matches.push_back({ ELeague::SerieA, "26/27", 5, ETeam::Venezia, ETeam::Lazio, 1789749000000 });
    matches.push_back({ ELeague::SerieA, "26/27", 5, ETeam::Fiorentina, ETeam::Napoli, 1789749000000 });
    matches.push_back({ ELeague::SerieA, "26/27", 5, ETeam::Frosinone, ETeam::Como, 1789749000000 });
    matches.push_back({ ELeague::SerieA, "26/27", 5, ETeam::Parma, ETeam::Genoa, 1789749000000 });
    matches.push_back({ ELeague::SerieA, "26/27", 5, ETeam::Juventus, ETeam::Atalanta, 1789749000000 });
    matches.push_back({ ELeague::SerieA, "26/27", 5, ETeam::ACMilan, ETeam::Lecce, 1789749000000 });

    // Week 6
    matches.push_back({ ELeague::SerieA, "26/27", 6, ETeam::Atalanta, ETeam::Venezia, 1791736200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 6, ETeam::Cagliari, ETeam::Juventus, 1791736200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 6, ETeam::Como, ETeam::Roma, 1791736200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 6, ETeam::Genoa, ETeam::Fiorentina, 1791736200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 6, ETeam::InterMilan, ETeam::Parma, 1791736200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 6, ETeam::Lazio, ETeam::Monza, 1791736200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 6, ETeam::Lecce, ETeam::Bologna, 1791736200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 6, ETeam::Napoli, ETeam::Frosinone, 1791736200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 6, ETeam::Sassuolo, ETeam::ACMilan, 1791736200000 });
    matches.push_back({ ELeague::SerieA, "26/27", 6, ETeam::Torino, ETeam::Udinese, 1791736200000 });

    // Week 7
    matches.push_back({ ELeague::SerieA, "26/27", 7, ETeam::ACMilan, ETeam::Atalanta, 1792341000000 });
    matches.push_back({ ELeague::SerieA, "26/27", 7, ETeam::Roma, ETeam::Genoa, 1792341000000 });
    matches.push_back({ ELeague::SerieA, "26/27", 7, ETeam::Bologna, ETeam::InterMilan, 1792341000000 });
    matches.push_back({ ELeague::SerieA, "26/27", 7, ETeam::Fiorentina, ETeam::Como, 1792341000000 });
    matches.push_back({ ELeague::SerieA, "26/27", 7, ETeam::Frosinone, ETeam::Sassuolo, 1792341000000 });
    matches.push_back({ ELeague::SerieA, "26/27", 7, ETeam::Juventus, ETeam::Lazio, 1792341000000 });
    matches.push_back({ ELeague::SerieA, "26/27", 7, ETeam::Monza, ETeam::Cagliari, 1792341000000 });
    matches.push_back({ ELeague::SerieA, "26/27", 7, ETeam::Parma, ETeam::Torino, 1792341000000 });
    matches.push_back({ ELeague::SerieA, "26/27", 7, ETeam::Udinese, ETeam::Lecce, 1792341000000 });
    matches.push_back({ ELeague::SerieA, "26/27", 7, ETeam::Venezia, ETeam::Napoli, 1792341000000 });
   

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

void MatchesInitializer::InitLaLiga26_27(PGconn* pg)
{
    std::vector<Match> matches;
    // Week 1
    matches.push_back({ ELeague::LaLiga, "26/27", 1, ETeam::Alaves, ETeam::Getafe, 1786892400000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 1, ETeam::AtleticoMadrid, ETeam::Malaga, 1786892400000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 1, ETeam::Barcelona, ETeam::AthleticClub, 1786892400000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 1, ETeam::CeltaVigo, ETeam::Osasuna, 1786892400000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 1, ETeam::DepCoruna, ETeam::Elche, 1786892400000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 1, ETeam::Espanyol, ETeam::Levante, 1786892400000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 1, ETeam::RacingSantander, ETeam::Villarreal, 1786892400000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 1, ETeam::RealMadrid, ETeam::RealSociedad, 1786892400000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 1, ETeam::Sevilla, ETeam::RayoVallecano, 1786892400000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 1, ETeam::Valencia, ETeam::RealBetis, 1786892400000 });

    // Week 2
    matches.push_back({ ELeague::LaLiga, "26/27", 2, ETeam::AthleticClub, ETeam::Sevilla, 1787497200000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 2, ETeam::AtleticoMadrid, ETeam::Villarreal, 1787497200000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 2, ETeam::RealBetis, ETeam::RealSociedad, 1787497200000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 2, ETeam::Elche, ETeam::Barcelona, 1787497200000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 2, ETeam::Espanyol, ETeam::RealMadrid, 1787497200000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 2, ETeam::Getafe, ETeam::RacingSantander, 1787497200000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 2, ETeam::Malaga, ETeam::DepCoruna, 1787497200000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 2, ETeam::Osasuna, ETeam::Levante, 1787497200000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 2, ETeam::RayoVallecano, ETeam::Alaves, 1787497200000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 2, ETeam::Valencia, ETeam::CeltaVigo, 1787497200000 });

    // Week 3
    matches.push_back({ ELeague::LaLiga, "26/27", 3, ETeam::Alaves, ETeam::Villarreal, 1788102000000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 3, ETeam::Barcelona, ETeam::RayoVallecano, 1788102000000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 3, ETeam::CeltaVigo, ETeam::AthleticClub, 1788102000000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 3, ETeam::DepCoruna, ETeam::Valencia, 1788102000000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 3, ETeam::Levante, ETeam::RealBetis, 1788102000000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 3, ETeam::Osasuna, ETeam::Getafe, 1788102000000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 3, ETeam::RacingSantander, ETeam::Elche, 1788102000000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 3, ETeam::RealMadrid, ETeam::Malaga, 1788102000000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 3, ETeam::RealSociedad, ETeam::Espanyol, 1788102000000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 3, ETeam::Sevilla, ETeam::AtleticoMadrid, 1788102000000 });

    // Week 4
    matches.push_back({ ELeague::LaLiga, "26/27", 4, ETeam::Alaves, ETeam::Osasuna, 1788706800000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 4, ETeam::AthleticClub, ETeam::AtleticoMadrid, 1788706800000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 4, ETeam::RealBetis, ETeam::RealMadrid, 1788706800000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 4, ETeam::Elche, ETeam::RealSociedad, 1788706800000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 4, ETeam::Espanyol, ETeam::Sevilla, 1788706800000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 4, ETeam::Getafe, ETeam::CeltaVigo, 1788706800000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 4, ETeam::Malaga, ETeam::Levante, 1788706800000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 4, ETeam::RayoVallecano, ETeam::RacingSantander, 1788706800000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 4, ETeam::Valencia, ETeam::Barcelona, 1788706800000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 4, ETeam::Villarreal, ETeam::DepCoruna, 1788706800000 });

    // Week 5
    matches.push_back({ ELeague::LaLiga, "26/27", 5, ETeam::AthleticClub, ETeam::Elche, 1789311600000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 5, ETeam::CeltaVigo, ETeam::Malaga, 1789311600000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 5, ETeam::Getafe, ETeam::DepCoruna, 1789311600000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 5, ETeam::Levante, ETeam::Barcelona, 1789311600000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 5, ETeam::Osasuna, ETeam::Espanyol, 1789311600000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 5, ETeam::RacingSantander, ETeam::Alaves, 1789311600000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 5, ETeam::RealMadrid, ETeam::RayoVallecano, 1789311600000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 5, ETeam::RealSociedad, ETeam::AtleticoMadrid, 1789311600000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 5, ETeam::Sevilla, ETeam::Valencia, 1789311600000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 5, ETeam::Villarreal, ETeam::RealBetis, 1789311600000 });

    // Week 6
    matches.push_back({ ELeague::LaLiga, "26/27", 6, ETeam::Alaves, ETeam::Valencia, 1789570800000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 6, ETeam::AtleticoMadrid, ETeam::Osasuna, 1789570800000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 6, ETeam::Barcelona, ETeam::RacingSantander, 1789570800000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 6, ETeam::RealBetis, ETeam::Getafe, 1789570800000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 6, ETeam::DepCoruna, ETeam::Sevilla, 1789570800000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 6, ETeam::Elche, ETeam::RealMadrid, 1789570800000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 6, ETeam::Levante, ETeam::AthleticClub, 1789570800000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 6, ETeam::Malaga, ETeam::Villarreal, 1789570800000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 6, ETeam::RayoVallecano, ETeam::Espanyol, 1789570800000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 6, ETeam::RealSociedad, ETeam::CeltaVigo, 1789570800000 });

    // Week 7
    matches.push_back({ ELeague::LaLiga, "26/27", 7, ETeam::AthleticClub, ETeam::Alaves, 1789916400000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 7, ETeam::AtleticoMadrid, ETeam::RealMadrid, 1789916400000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 7, ETeam::CeltaVigo, ETeam::RacingSantander, 1789916400000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 7, ETeam::DepCoruna, ETeam::RealBetis, 1789916400000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 7, ETeam::Espanyol, ETeam::Elche, 1789916400000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 7, ETeam::Getafe, ETeam::Malaga, 1789916400000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 7, ETeam::Osasuna, ETeam::RayoVallecano, 1789916400000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 7, ETeam::Sevilla, ETeam::Barcelona, 1789916400000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 7, ETeam::Valencia, ETeam::RealSociedad, 1789916400000 });
    matches.push_back({ ELeague::LaLiga, "26/27", 7, ETeam::Villarreal, ETeam::Levante, 1789916400000 });

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

void MatchesInitializer::InitPremierLeague26_27(PGconn* pg)
{
    std::vector<Match> matches;
    // Week 1
    matches.push_back({ ELeague::PremierLeague, "26/27", 1, ETeam::Arsenal, ETeam::Coventry, 1787338800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 1, ETeam::Hull, ETeam::ManchesterUnited, 1787338800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 1, ETeam::Everton, ETeam::CrystalPalace, 1787338800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 1, ETeam::IpswichTown, ETeam::Sunderland, 1787338800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 1, ETeam::NottinghamForest, ETeam::Leeds, 1787338800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 1, ETeam::Brentford, ETeam::TottenhamHotspur, 1787338800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 1, ETeam::BrightonAndHoveAlbion, ETeam::AstonVilla, 1787338800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 1, ETeam::ManchesterCity, ETeam::AFCBournemouth, 1787338800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 1, ETeam::NewcastleUnited, ETeam::Liverpool, 1787338800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 1, ETeam::Fulham, ETeam::Chelsea, 1787338800000 });

    // Week 2
    matches.push_back({ ELeague::PremierLeague, "26/27", 2, ETeam::CrystalPalace, ETeam::ManchesterCity, 1787943600000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 2, ETeam::Liverpool, ETeam::NottinghamForest, 1787943600000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 2, ETeam::AFCBournemouth, ETeam::Everton, 1787943600000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 2, ETeam::Coventry, ETeam::Hull, 1787943600000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 2, ETeam::TottenhamHotspur, ETeam::NewcastleUnited, 1787943600000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 2, ETeam::Chelsea, ETeam::BrightonAndHoveAlbion, 1787943600000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 2, ETeam::Leeds, ETeam::Brentford, 1787943600000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 2, ETeam::Sunderland, ETeam::Fulham, 1787943600000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 2, ETeam::ManchesterUnited, ETeam::IpswichTown, 1787943600000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 2, ETeam::AstonVilla, ETeam::Arsenal, 1787943600000 });

    // Week 3
    matches.push_back({ ELeague::PremierLeague, "26/27", 3, ETeam::IpswichTown, ETeam::Liverpool, 1788548400000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 3, ETeam::NewcastleUnited, ETeam::AFCBournemouth, 1788548400000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 3, ETeam::Brentford, ETeam::Sunderland, 1788548400000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 3, ETeam::BrightonAndHoveAlbion, ETeam::Leeds, 1788548400000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 3, ETeam::Fulham, ETeam::CrystalPalace, 1788548400000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 3, ETeam::ManchesterCity, ETeam::Coventry, 1788548400000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 3, ETeam::NottinghamForest, ETeam::TottenhamHotspur, 1788548400000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 3, ETeam::Hull, ETeam::AstonVilla, 1788548400000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 3, ETeam::Everton, ETeam::ManchesterUnited, 1788548400000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 3, ETeam::Arsenal, ETeam::Chelsea, 1788548400000 });

    // Week 4
    matches.push_back({ ELeague::PremierLeague, "26/27", 4, ETeam::AstonVilla, ETeam::NottinghamForest, 1789239600000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 4, ETeam::AFCBournemouth, ETeam::Brentford, 1789239600000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 4, ETeam::Chelsea, ETeam::Hull, 1789239600000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 4, ETeam::CrystalPalace, ETeam::IpswichTown, 1789239600000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 4, ETeam::Liverpool, ETeam::Fulham, 1789239600000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 4, ETeam::TottenhamHotspur, ETeam::Everton, 1789239600000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 4, ETeam::Sunderland, ETeam::Arsenal, 1789239600000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 4, ETeam::Coventry, ETeam::BrightonAndHoveAlbion, 1789239600000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 4, ETeam::ManchesterUnited, ETeam::ManchesterCity, 1789239600000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 4, ETeam::Leeds, ETeam::NewcastleUnited, 1789239600000 });

    // Week 5
    matches.push_back({ ELeague::PremierLeague, "26/27", 5, ETeam::Brentford, ETeam::Chelsea, 1789758000000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 5, ETeam::TottenhamHotspur, ETeam::AstonVilla, 1789758000000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 5, ETeam::BrightonAndHoveAlbion, ETeam::Arsenal, 1789758000000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 5, ETeam::Everton, ETeam::IpswichTown, 1789758000000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 5, ETeam::Leeds, ETeam::CrystalPalace, 1789758000000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 5, ETeam::ManchesterCity, ETeam::Sunderland, 1789758000000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 5, ETeam::NewcastleUnited, ETeam::Hull, 1789758000000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 5, ETeam::NottinghamForest, ETeam::Coventry, 1789758000000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 5, ETeam::AFCBournemouth, ETeam::Liverpool, 1789758000000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 5, ETeam::Fulham, ETeam::ManchesterUnited, 1789758000000 });

    // Week 6
    matches.push_back({ ELeague::PremierLeague, "26/27", 6, ETeam::Arsenal, ETeam::Leeds, 1791658800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 6, ETeam::AstonVilla, ETeam::Brentford, 1791658800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 6, ETeam::Chelsea, ETeam::AFCBournemouth, 1789758000000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 6, ETeam::Coventry, ETeam::NewcastleUnited, 1791658800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 6, ETeam::CrystalPalace, ETeam::NottinghamForest, 1791658800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 6, ETeam::Hull, ETeam::Everton, 1791658800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 6, ETeam::IpswichTown, ETeam::Fulham, 1791658800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 6, ETeam::Liverpool, ETeam::ManchesterCity, 1791658800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 6, ETeam::ManchesterUnited, ETeam::TottenhamHotspur, 1791658800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 6, ETeam::Sunderland, ETeam::BrightonAndHoveAlbion, 1791658800000 });

    // Week 7
    matches.push_back({ ELeague::PremierLeague, "26/27", 7, ETeam::AFCBournemouth, ETeam::Sunderland, 1791658800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 7, ETeam::Brentford, ETeam::Liverpool, 1791658800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 7, ETeam::BrightonAndHoveAlbion, ETeam::CrystalPalace, 1789758000000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 7, ETeam::Everton, ETeam::Chelsea, 1791658800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 7, ETeam::Fulham, ETeam::Hull, 1791658800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 7, ETeam::Leeds, ETeam::ManchesterUnited, 1791658800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 7, ETeam::ManchesterCity, ETeam::IpswichTown, 1791658800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 7, ETeam::NewcastleUnited, ETeam::AstonVilla, 1791658800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 7, ETeam::NottinghamForest, ETeam::Arsenal, 1791658800000 });
    matches.push_back({ ELeague::PremierLeague, "26/27", 7, ETeam::TottenhamHotspur, ETeam::Coventry, 1791658800000 });

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

void MatchesInitializer::InitCopaDeFranceTeams25_26(PGconn* pg)
{
    std::vector<ETeam> teams;
    teams.push_back(ETeam::Strasbourg);
    teams.push_back(ETeam::Reims);
    teams.push_back(ETeam::Lorient);
    teams.push_back(ETeam::Nice);
    teams.push_back(ETeam::Marseille);
    teams.push_back(ETeam::Toulouse);
    teams.push_back(ETeam::Lyon);
    teams.push_back(ETeam::Lens);

    for (ETeam t : teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id) values ("
            + std::to_string(int(ELeague::CoupeDeFrance)) + ", "
            + std::to_string((int)t) + ");";
        PGresult* ret = PQexec(pg, sql.c_str());
        PQclear(ret);
    }
}

void MatchesInitializer::InitFACupTeams25_26(PGconn* pg)
{
    std::vector<ETeam> teams;
    teams.push_back(ETeam::ManchesterCity);
    teams.push_back(ETeam::Liverpool);
    teams.push_back(ETeam::PortVale);
    teams.push_back(ETeam::Chelsea);
    teams.push_back(ETeam::Southampton);
    teams.push_back(ETeam::Arsenal);
    teams.push_back(ETeam::WestHamUnited);
    teams.push_back(ETeam::Leeds);

    for (ETeam t : teams)
    {
        std::string sql = "insert into leagues_teams(league_id, team_id) values ("
            + std::to_string(int(ELeague::FACup)) + ", "
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

void MatchesInitializer::InitCopaDeFrance25_26(PGconn* pg)
{
    // Premier League
    std::vector<Match> matches;
    // Week 1
  // matches.push_back({ ELeague::CoupeDeFrance, "25/26", 1, ETeam::Strasbourg, ETeam::Reims, 1772568000000, EWeekType::QuarterFinal, true });
  // matches.push_back({ ELeague::CoupeDeFrance, "25/26", 1, ETeam::Lorient, ETeam::Nice, 1772652600000, EWeekType::QuarterFinal, true });
  // matches.push_back({ ELeague::CoupeDeFrance, "25/26", 1, ETeam::Marseille, ETeam::Toulouse, 1772654400000, EWeekType::QuarterFinal, true });
  // matches.push_back({ ELeague::CoupeDeFrance, "25/26", 1, ETeam::Lyon, ETeam::Lens, 1772741400000, EWeekType::QuarterFinal, true });
  
   // matches.push_back({ ELeague::CoupeDeFrance, "25/26", 2, ETeam::Lens, ETeam::Toulouse, 1776798000000, EWeekType::SemiFinal, true });
    //matches.push_back({ ELeague::CoupeDeFrance, "25/26", 2, ETeam::Strasbourg, ETeam::Nice, 1776884400000, EWeekType::SemiFinal, true });

    matches.push_back({ ELeague::CoupeDeFrance, "25/26", 3, ETeam::Lens, ETeam::Nice, 1779476400000, EWeekType::Final, true });


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

void MatchesInitializer::InitFACup25_26(PGconn* pg)
{
    // Premier League
    std::vector<Match> matches;
    // Week 1
   //matches.push_back({ ELeague::FACup, "25/26", 1, ETeam::ManchesterCity, ETeam::Liverpool, 1775303100000, EWeekType::QuarterFinal, true });
   //matches.push_back({ ELeague::FACup, "25/26", 1, ETeam::Chelsea, ETeam::PortVale, 1775319300000, EWeekType::QuarterFinal, true });
   //matches.push_back({ ELeague::FACup, "25/26", 1, ETeam::Southampton, ETeam::Arsenal, 1775329200000, EWeekType::QuarterFinal, true });
   //matches.push_back({ ELeague::FACup, "25/26", 1, ETeam::WestHamUnited, ETeam::Leeds, 1775403000000, EWeekType::QuarterFinal, true });

   //matches.push_back({ ELeague::FACup, "25/26", 2, ETeam::ManchesterCity, ETeam::Southampton, 1777133700000, EWeekType::SemiFinal, true });
  // matches.push_back({ ELeague::FACup, "25/26", 2, ETeam::Chelsea, ETeam::Leeds, 1777212000000, EWeekType::SemiFinal, true });

   // matches.push_back({ ELeague::CopaDelRey, "25/26", 2, ETeam::Barcelona, ETeam::AtleticoMadrid, 1772568000000, EWeekType::SemiFinal, true });
   // matches.push_back({ ELeague::CopaDelRey, "25/26", 2, ETeam::RealSociedad, ETeam::AthleticClub, 1772654400000, EWeekType::SemiFinal, true });

    matches.push_back({ ELeague::FACup, "25/26", 3, ETeam::Chelsea, ETeam::ManchesterCity, 1778940000000, EWeekType::Final, true });


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


void MatchesInitializer::InitCopaDelRey25_26(PGconn* pg)
{
    // Premier League
    std::vector<Match> matches;
    // Week 1
    //matches.push_back({ ELeague::CopaDelRey, "25/26", 1, ETeam::Albacete, ETeam::Barcelona, 1770148800000, EWeekType::QuarterFinal, true });
    //matches.push_back({ ELeague::CopaDelRey, "25/26", 1, ETeam::Alaves, ETeam::RealSociedad, 1770235200000, EWeekType::QuarterFinal, true });
    //matches.push_back({ ELeague::CopaDelRey, "25/26", 1, ETeam::Valencia, ETeam::AthleticClub, 1770235200000, EWeekType::QuarterFinal, true });
    //matches.push_back({ ELeague::CopaDelRey, "25/26", 1, ETeam::RealBetis, ETeam::AtleticoMadrid, 1770321600000, EWeekType::QuarterFinal, true });

   //matches.push_back({ ELeague::CopaDelRey, "25/26", 2, ETeam::AthleticClub, ETeam::RealSociedad, 1770840000000, EWeekType::SemiFinal, false });
   //matches.push_back({ ELeague::CopaDelRey, "25/26", 2, ETeam::AtleticoMadrid, ETeam::Barcelona, 1770926400000, EWeekType::SemiFinal, false });

   // matches.push_back({ ELeague::CopaDelRey, "25/26", 2, ETeam::Barcelona, ETeam::AtleticoMadrid, 1772568000000, EWeekType::SemiFinal, true });
   // matches.push_back({ ELeague::CopaDelRey, "25/26", 2, ETeam::RealSociedad, ETeam::AthleticClub, 1772654400000, EWeekType::SemiFinal, true });

    matches.push_back({ ELeague::CopaDelRey, "25/26", 3, ETeam::AtleticoMadrid, ETeam::RealSociedad, 1776538800000, EWeekType::Final, true });


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
    // matches.push_back({ ELeague::CoppaItalia, "25/26", 1, ETeam::InterMilan, ETeam::Torino, 1770235200000, EWeekType::QuarterFinal, true });
    // matches.push_back({ ELeague::CoppaItalia, "25/26", 1, ETeam::Atalanta, ETeam::Juventus, 1770321600000, EWeekType::QuarterFinal, true });
    // matches.push_back({ ELeague::CoppaItalia, "25/26", 1, ETeam::Napoli, ETeam::Como, 1770753600000, EWeekType::QuarterFinal, true });
    // matches.push_back({ ELeague::CoppaItalia, "25/26", 1, ETeam::Bologna, ETeam::Lazio, 1770840000000, EWeekType::QuarterFinal, true });
  
 //  matches.push_back({ ELeague::CoppaItalia, "25/26", 2, ETeam::Como, ETeam::InterMilan, 1772568000000, EWeekType::SemiFinal, false });
 //  matches.push_back({ ELeague::CoppaItalia, "25/26", 2, ETeam::Lazio, ETeam::Atalanta, 1772654400000, EWeekType::SemiFinal, false });

   // matches.push_back({ ELeague::CoppaItalia, "25/26", 2, ETeam::InterMilan, ETeam::Como, 1776798000000, EWeekType::SemiFinal, true });
   // matches.push_back({ ELeague::CoppaItalia, "25/26", 2, ETeam::Atalanta, ETeam::Lazio, 1776884400000, EWeekType::SemiFinal, true });

    matches.push_back({ ELeague::CoppaItalia, "25/26", 3, ETeam::Lazio, ETeam::InterMilan, 1778713200000, EWeekType::Final, true });


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
   // matches.push_back({ ELeague::EFLCup, "25/26", 1, ETeam::NewcastleUnited, ETeam::ManchesterCity, 1768334400000, EWeekType::SemiFinal, false });
  //  matches.push_back({ ELeague::EFLCup, "25/26", 1, ETeam::Chelsea, ETeam::Arsenal, 1768420800000, EWeekType::SemiFinal, false });

//    matches.push_back({ ELeague::EFLCup, "25/26", 1, ETeam::Arsenal, ETeam::Chelsea, 1770148800000, EWeekType::SemiFinal, false });
   // matches.push_back({ ELeague::EFLCup, "25/26", 1, ETeam::ManchesterCity, ETeam::NewcastleUnited, 1770235200000, EWeekType::SemiFinal, false });

    matches.push_back({ ELeague::EFLCup, "25/26", 2, ETeam::Arsenal, ETeam::ManchesterCity, 1774197000000, EWeekType::Final, true });


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
  //  matches.push_back({ ELeague::DFBPokal, "25/26", 2, ETeam::BayerLeverkusen, ETeam::BayernMunich, 1776883500000, EWeekType::SemiFinal, true });
//    matches.push_back({ ELeague::DFBPokal, "25/26", 2, ETeam::Stuttgart, ETeam::Freiburg, 1776969900000, EWeekType::SemiFinal, true });
    matches.push_back({ ELeague::DFBPokal, "25/26", 3, ETeam::BayernMunich, ETeam::Stuttgart, 1779559200000, EWeekType::Final, true });

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

    // Finals
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 12, ETeam::BosniaAndHerzegovina, ETeam::Italy, 1774982700000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 12, ETeam::Czechia, ETeam::Denmark, 1774982700000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 12, ETeam::Kosovo, ETeam::Turkiye, 1774982700000 });
    matches.push_back({ ELeague::UEFAWorldClubQualification, "25/26", 12, ETeam::Sweden, ETeam::Poland, 1774982700000 });

    for (auto& m : matches)
    {
        std::string sql = "insert into matches(league, season, week, week_type, team1, team2, play_off, match_date) values ("
            + std::to_string(int(m.League)) + ", '"
            + m.Season + "', "
            + std::to_string(m.Week) + ", 4, "
            + std::to_string((int)m.Team1) + ", "
            + std::to_string((int)m.Team2) + ", 1, "
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