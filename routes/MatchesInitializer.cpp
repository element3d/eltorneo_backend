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