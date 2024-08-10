#include "MatchesInitializer.h"
#include <vector>

void MatchesInitializer::InitPremierLeagueTeams24_25(PGconn* pg)
{
    for (int i = (int)ETeam::PremierLeagueStart; i <= (int)ETeam::PremierLeagueEnd; ++i)
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

void MatchesInitializer::InitLaLigaTeams24_25(PGconn* pg)
{
    for (int i = (int)ETeam::LaLigaStart; i <= (int)ETeam::LaLigaEnd; ++i)
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

void MatchesInitializer::InitSerieATeams24_25(PGconn* pg)
{
    for (int i = (int)ETeam::SerieAStart; i <= (int)ETeam::SerieAEnd; ++i)
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

void MatchesInitializer::InitBundesligaTeams24_25(PGconn* pg)
{
    for (int i = (int)ETeam::BundesligaStart; i <= (int)ETeam::BundesligaEnd; ++i)
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

void MatchesInitializer::InitLigue1Teams24_25(PGconn* pg)
{
    for (int i = (int)ETeam::Ligue1Start; i <= (int)ETeam::Ligue1End; ++i)
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

void MatchesInitializer::InitLigue124_25(PGconn* pg)
{
    std::vector<Match> matches;
    // Week 1
    matches.push_back({ ELeague::Ligue1, "24/25", 1, ETeam::LaHavre, ETeam::PSG, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 1, ETeam::Brest, ETeam::Marseille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 1, ETeam::Reims, ETeam::Lille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 1, ETeam::Monaco, ETeam::SaintEtienne, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 1, ETeam::Auxerre, ETeam::Nice, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 1, ETeam::Montpellier, ETeam::Strasbourg, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 1, ETeam::Toulouse, ETeam::Nantes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 1, ETeam::Angers, ETeam::Lens, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 1, ETeam::Rennes, ETeam::Lyon, 1722985200000 });

    // Week 2
    matches.push_back({ ELeague::Ligue1, "24/25", 2, ETeam::PSG, ETeam::Montpellier, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 2, ETeam::Strasbourg, ETeam::Rennes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 2, ETeam::Nantes, ETeam::Auxerre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 2, ETeam::SaintEtienne, ETeam::LaHavre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 2, ETeam::Lille, ETeam::Angers, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 2, ETeam::Nice, ETeam::Toulouse, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 2, ETeam::Lens, ETeam::Brest, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 2, ETeam::Lyon, ETeam::Monaco, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 2, ETeam::Marseille, ETeam::Reims, 1722985200000 });

    // Week 3
    matches.push_back({ ELeague::Ligue1, "24/25", 3, ETeam::Lille, ETeam::PSG, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 3, ETeam::Lyon, ETeam::Strasbourg, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 3, ETeam::Brest, ETeam::SaintEtienne, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 3, ETeam::Montpellier, ETeam::Nantes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 3, ETeam::Angers, ETeam::Nice, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 3, ETeam::Monaco, ETeam::Lens, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 3, ETeam::LaHavre, ETeam::Auxerre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 3, ETeam::Reims, ETeam::Rennes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 3, ETeam::Toulouse, ETeam::Marseille, 1722985200000 });

    // Week 4
    matches.push_back({ ELeague::Ligue1, "24/25", 4, ETeam::Auxerre, ETeam::Monaco, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 4, ETeam::Rennes, ETeam::Montpellier, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 4, ETeam::Lens, ETeam::Lyon, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 4, ETeam::Nantes, ETeam::Reims, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 4, ETeam::Toulouse, ETeam::LaHavre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 4, ETeam::Strasbourg, ETeam::Angers, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 4, ETeam::SaintEtienne, ETeam::Lille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 4, ETeam::Marseille, ETeam::Nice, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 4, ETeam::PSG, ETeam::Brest, 1722985200000 });

    // Week 5
    matches.push_back({ ELeague::Ligue1, "24/25", 5, ETeam::Lyon, ETeam::Marseille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 5, ETeam::Nice, ETeam::SaintEtienne, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 5, ETeam::Reims, ETeam::PSG, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 5, ETeam::Brest, ETeam::Toulouse, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 5, ETeam::Angers, ETeam::Nantes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 5, ETeam::Montpellier, ETeam::Auxerre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 5, ETeam::Lille, ETeam::Strasbourg, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 5, ETeam::Rennes, ETeam::Lens, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 5, ETeam::Monaco, ETeam::LaHavre, 1722985200000 });

    // Week 6
    matches.push_back({ ELeague::Ligue1, "24/25", 6, ETeam::Strasbourg, ETeam::Marseille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 6, ETeam::PSG, ETeam::Rennes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 6, ETeam::Auxerre, ETeam::Brest, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 6, ETeam::Lens, ETeam::Nice, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 6, ETeam::Nantes, ETeam::SaintEtienne, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 6, ETeam::LaHavre, ETeam::Lille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 6, ETeam::Toulouse, ETeam::Lyon, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 6, ETeam::Monaco, ETeam::Montpellier, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 6, ETeam::Angers, ETeam::Reims, 1722985200000 });

    // Week 7
    matches.push_back({ ELeague::Ligue1, "24/25", 7, ETeam::Lyon, ETeam::Nantes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 7, ETeam::Nice, ETeam::PSG, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 7, ETeam::Lille, ETeam::Toulouse, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 7, ETeam::SaintEtienne, ETeam::Auxerre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 7, ETeam::Brest, ETeam::LaHavre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 7, ETeam::Marseille, ETeam::Angers, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 7, ETeam::Rennes, ETeam::Monaco, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 7, ETeam::Strasbourg, ETeam::Lens, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 7, ETeam::Reims, ETeam::Montpellier, 1722985200000 });

    // Week 8
    matches.push_back({ ELeague::Ligue1, "24/25", 8, ETeam::Auxerre, ETeam::Reims, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 8, ETeam::Toulouse, ETeam::Angers, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 8, ETeam::LaHavre, ETeam::Lyon, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 8, ETeam::Nantes, ETeam::Nice, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 8, ETeam::Montpellier, ETeam::Marseille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 8, ETeam::Monaco, ETeam::Lille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 8, ETeam::SaintEtienne, ETeam::Lens, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 8, ETeam::Brest, ETeam::Rennes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 8, ETeam::PSG, ETeam::Strasbourg, 1722985200000 });

    // Week 9
    matches.push_back({ ELeague::Ligue1, "24/25", 9, ETeam::Nice, ETeam::Monaco, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 9, ETeam::Lens, ETeam::Lille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 9, ETeam::Marseille, ETeam::PSG, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 9, ETeam::Lyon, ETeam::Auxerre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 9, ETeam::Montpellier, ETeam::Toulouse, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 9, ETeam::Strasbourg, ETeam::Nantes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 9, ETeam::Rennes, ETeam::LaHavre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 9, ETeam::Angers, ETeam::SaintEtienne, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 9, ETeam::Reims, ETeam::Brest, 1722985200000 });

    // Week 10
    matches.push_back({ ELeague::Ligue1, "24/25", 10, ETeam::Auxerre, ETeam::Rennes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 10, ETeam::Toulouse, ETeam::Reims, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 10, ETeam::Monaco, ETeam::Angers, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 10, ETeam::LaHavre, ETeam::Montpellier, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 10, ETeam::Nantes, ETeam::Marseille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 10, ETeam::Lille, ETeam::Lyon, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 10, ETeam::SaintEtienne, ETeam::Strasbourg, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 10, ETeam::Brest, ETeam::Nice, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 10, ETeam::PSG, ETeam::Lens, 1722985200000 });

    // Week 11
    matches.push_back({ ELeague::Ligue1, "24/25", 11, ETeam::Marseille, ETeam::Auxerre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 11, ETeam::Lyon, ETeam::SaintEtienne, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 11, ETeam::Montpellier, ETeam::Brest, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 11, ETeam::LaHavre, ETeam::Reims, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 11, ETeam::Strasbourg, ETeam::Monaco, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 11, ETeam::Lens, ETeam::Nantes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 11, ETeam::Rennes, ETeam::Toulouse, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 11, ETeam::Nice, ETeam::Lille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 11, ETeam::Angers, ETeam::PSG, 1722985200000 });

    // Week 12
    matches.push_back({ ELeague::Ligue1, "24/25", 12, ETeam::PSG, ETeam::Toulouse, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 12, ETeam::Lens, ETeam::Marseille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 12, ETeam::Nice, ETeam::Strasbourg, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 12, ETeam::SaintEtienne, ETeam::Montpellier, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 12, ETeam::Lille, ETeam::Rennes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 12, ETeam::Nantes, ETeam::LaHavre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 12, ETeam::Monaco, ETeam::Brest, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 12, ETeam::Auxerre, ETeam::Angers, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 12, ETeam::Reims, ETeam::Lyon, 1722985200000 });

    // Week 13
    matches.push_back({ ELeague::Ligue1, "24/25", 13, ETeam::Reims, ETeam::Lens, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 13, ETeam::Rennes, ETeam::SaintEtienne, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 13, ETeam::LaHavre, ETeam::Angers, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 13, ETeam::Toulouse, ETeam::Auxerre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 13, ETeam::Brest, ETeam::Strasbourg, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 13, ETeam::Montpellier, ETeam::Lille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 13, ETeam::PSG, ETeam::Nantes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 13, ETeam::Marseille, ETeam::Monaco, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 13, ETeam::Lyon, ETeam::Nice, 1722985200000 });

    // Week 14
    matches.push_back({ ELeague::Ligue1, "24/25", 14, ETeam::Nice, ETeam::LaHavre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 14, ETeam::Auxerre, ETeam::PSG, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 14, ETeam::SaintEtienne, ETeam::Marseille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 14, ETeam::Angers, ETeam::Lyon, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 14, ETeam::Lille, ETeam::Brest, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 14, ETeam::Lens, ETeam::Montpellier, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 14, ETeam::Strasbourg, ETeam::Reims, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 14, ETeam::Nantes, ETeam::Rennes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 14, ETeam::Monaco, ETeam::Toulouse, 1722985200000 });

    // Week 15
    matches.push_back({ ELeague::Ligue1, "24/25", 15, ETeam::Rennes, ETeam::Angers, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 15, ETeam::LaHavre, ETeam::Strasbourg, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 15, ETeam::Reims, ETeam::Monaco, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 15, ETeam::Auxerre, ETeam::Lens, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 15, ETeam::Toulouse, ETeam::SaintEtienne, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 15, ETeam::Montpellier, ETeam::Nice, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 15, ETeam::Brest, ETeam::Nantes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 15, ETeam::Marseille, ETeam::Lille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 15, ETeam::PSG, ETeam::Lyon, 1722985200000 });

    // Week 16
    matches.push_back({ ELeague::Ligue1, "24/25", 16, ETeam::Monaco, ETeam::PSG, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 16, ETeam::Lyon, ETeam::Montpellier, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 16, ETeam::Lens, ETeam::Toulouse, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 16, ETeam::SaintEtienne, ETeam::Reims, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 16, ETeam::Angers, ETeam::Brest, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 16, ETeam::Lille, ETeam::Nantes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 16, ETeam::Marseille, ETeam::LaHavre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 16, ETeam::Strasbourg, ETeam::Auxerre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 16, ETeam::Nice, ETeam::Rennes, 1722985200000 });

    // Week 17
    matches.push_back({ ELeague::Ligue1, "24/25", 17, ETeam::Toulouse, ETeam::Strasbourg, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 17, ETeam::Nantes, ETeam::Monaco, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 17, ETeam::Auxerre, ETeam::Lille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 17, ETeam::Reims, ETeam::Nice, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 17, ETeam::LaHavre, ETeam::Lens, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 17, ETeam::Montpellier, ETeam::Angers, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 17, ETeam::Brest, ETeam::Lyon, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 17, ETeam::PSG, ETeam::SaintEtienne, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 17, ETeam::Rennes, ETeam::Marseille, 1722985200000 });

    // Week 18
    matches.push_back({ ELeague::Ligue1, "24/25", 18, ETeam::Marseille, ETeam::Strasbourg, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 18, ETeam::Lens, ETeam::PSG, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 18, ETeam::Lille, ETeam::Nice, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 18, ETeam::Lyon, ETeam::Toulouse, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 18, ETeam::SaintEtienne, ETeam::Nantes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 18, ETeam::Montpellier, ETeam::Monaco, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 18, ETeam::Reims, ETeam::LaHavre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 18, ETeam::Angers, ETeam::Auxerre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 18, ETeam::Rennes, ETeam::Brest, 1722985200000 });

    // Week 19
    matches.push_back({ ELeague::Ligue1, "24/25", 19, ETeam::Strasbourg, ETeam::Lille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 19, ETeam::Nantes, ETeam::Lyon, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 19, ETeam::Monaco, ETeam::Rennes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 19, ETeam::Toulouse, ETeam::Montpellier, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 19, ETeam::LaHavre, ETeam::Brest, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 19, ETeam::Auxerre, ETeam::SaintEtienne, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 19, ETeam::Lens, ETeam::Angers, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 19, ETeam::PSG, ETeam::Reims, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 19, ETeam::Nice, ETeam::Marseille, 1722985200000 });

    // Week 20
    matches.push_back({ ELeague::Ligue1, "24/25", 20, ETeam::Marseille, ETeam::Lyon, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 20, ETeam::Brest, ETeam::PSG, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 20, ETeam::Montpellier, ETeam::Lens, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 20, ETeam::Lille, ETeam::SaintEtienne, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 20, ETeam::Reims, ETeam::Nantes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 20, ETeam::Angers, ETeam::LaHavre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 20, ETeam::Toulouse, ETeam::Nice, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 20, ETeam::Rennes, ETeam::Strasbourg, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 20, ETeam::Monaco, ETeam::Auxerre, 1722985200000 });

    // Week 21
    matches.push_back({ ELeague::Ligue1, "24/25", 21, ETeam::Auxerre, ETeam::Toulouse, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 21, ETeam::Nantes, ETeam::Brest, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 21, ETeam::Strasbourg, ETeam::Montpellier, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 21, ETeam::Lille, ETeam::LaHavre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 21, ETeam::SaintEtienne, ETeam::Rennes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 21, ETeam::PSG, ETeam::Monaco, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 21, ETeam::Lyon, ETeam::Reims, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 21, ETeam::Angers, ETeam::Marseille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 21, ETeam::Nice, ETeam::Lens, 1722985200000 });

    // Week 22
    matches.push_back({ ELeague::Ligue1, "24/25", 22, ETeam::Toulouse, ETeam::PSG, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 22, ETeam::Marseille, ETeam::SaintEtienne, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 22, ETeam::Montpellier, ETeam::Lyon, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 22, ETeam::Lens, ETeam::Strasbourg, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 22, ETeam::Brest, ETeam::Auxerre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 22, ETeam::Rennes, ETeam::Lille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 22, ETeam::Reims, ETeam::Angers, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 22, ETeam::LaHavre, ETeam::Nice, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 22, ETeam::Monaco, ETeam::Nantes, 1722985200000 });

    // Week 23
    matches.push_back({ ELeague::Ligue1, "24/25", 23, ETeam::Rennes, ETeam::Reims, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 23, ETeam::LaHavre, ETeam::Toulouse, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 23, ETeam::Lille, ETeam::Monaco, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 23, ETeam::Strasbourg, ETeam::Brest, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 23, ETeam::Nantes, ETeam::Lens, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 23, ETeam::SaintEtienne, ETeam::Angers, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 23, ETeam::Auxerre, ETeam::Marseille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 23, ETeam::Nice, ETeam::Montpellier, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 23, ETeam::Lyon, ETeam::PSG, 1722985200000 });

    // Week 24
    matches.push_back({ ELeague::Ligue1, "24/25", 24, ETeam::PSG, ETeam::Lille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 24, ETeam::Marseille, ETeam::Nantes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 24, ETeam::Lyon, ETeam::Brest, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 24, ETeam::Montpellier, ETeam::Rennes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 24, ETeam::SaintEtienne, ETeam::Nice, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 24, ETeam::Lens, ETeam::LaHavre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 24, ETeam::Auxerre, ETeam::Strasbourg, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 24, ETeam::Monaco, ETeam::Reims, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 24, ETeam::Angers, ETeam::Toulouse, 1722985200000 });

    // Week 25
    matches.push_back({ ELeague::Ligue1, "24/25", 25, ETeam::LaHavre, ETeam::SaintEtienne, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 25, ETeam::Reims, ETeam::Auxerre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 25, ETeam::Nantes, ETeam::Strasbourg, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 25, ETeam::Toulouse, ETeam::Monaco, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 25, ETeam::Nice, ETeam::Lyon, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 25, ETeam::Brest, ETeam::Angers, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 25, ETeam::Lille, ETeam::Montpellier, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 25, ETeam::Rennes, ETeam::PSG, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 25, ETeam::Marseille, ETeam::Lens, 1722985200000 });

    // Week 26
    matches.push_back({ ELeague::Ligue1, "24/25", 26, ETeam::PSG, ETeam::Marseille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 26, ETeam::Nice, ETeam::Auxerre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 26, ETeam::Montpellier, ETeam::SaintEtienne, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 26, ETeam::Brest, ETeam::Reims, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 26, ETeam::Lyon, ETeam::LaHavre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 26, ETeam::Lens, ETeam::Rennes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 26, ETeam::Strasbourg, ETeam::Toulouse, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 26, ETeam::Nantes, ETeam::Lille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 26, ETeam::Angers, ETeam::Monaco, 1722985200000 });

    // Week 27
    matches.push_back({ ELeague::Ligue1, "24/25", 27, ETeam::Angers, ETeam::Rennes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 27, ETeam::Auxerre, ETeam::Montpellier, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 27, ETeam::LaHavre, ETeam::Nantes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 27, ETeam::Strasbourg, ETeam::Lyon, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 27, ETeam::Toulouse, ETeam::Brest, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 27, ETeam::SaintEtienne, ETeam::PSG, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 27, ETeam::Reims, ETeam::Marseille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 27, ETeam::Lille, ETeam::Lens, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 27, ETeam::Monaco, ETeam::Nice, 1722985200000 });

    // Week 28
    matches.push_back({ ELeague::Ligue1, "24/25", 28, ETeam::Marseille, ETeam::Toulouse, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 28, ETeam::Nice, ETeam::Nantes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 28, ETeam::Brest, ETeam::Monaco, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 28, ETeam::Montpellier, ETeam::LaHavre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 28, ETeam::Lyon, ETeam::Lille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 28, ETeam::Lens, ETeam::SaintEtienne, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 28, ETeam::PSG, ETeam::Angers, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 28, ETeam::Reims, ETeam::Strasbourg, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 28, ETeam::Rennes, ETeam::Auxerre, 1722985200000 });

    // Week 29
    matches.push_back({ ELeague::Ligue1, "24/25", 29, ETeam::Toulouse, ETeam::Lille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 29, ETeam::LaHavre, ETeam::Rennes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 29, ETeam::Auxerre, ETeam::Lyon, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 29, ETeam::Nantes, ETeam::PSG, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 29, ETeam::Strasbourg, ETeam::Nice, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 29, ETeam::SaintEtienne, ETeam::Brest, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 29, ETeam::Angers, ETeam::Montpellier, 1722985200000});
    matches.push_back({ ELeague::Ligue1, "24/25", 29, ETeam::Lens, ETeam::Reims, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 29, ETeam::Monaco, ETeam::Marseille, 1722985200000 });

    // Week 30
    matches.push_back({ ELeague::Ligue1, "24/25", 30, ETeam::SaintEtienne, ETeam::Lyon, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 30, ETeam::Nice, ETeam::Angers, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 30, ETeam::Brest, ETeam::Lens, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 30, ETeam::Lille, ETeam::Auxerre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 30, ETeam::PSG, ETeam::LaHavre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 30, ETeam::Marseille, ETeam::Montpellier, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 30, ETeam::Reims, ETeam::Toulouse, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 30, ETeam::Monaco, ETeam::Strasbourg, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 30, ETeam::Rennes, ETeam::Nantes, 1722985200000 });

    // Week 31
    matches.push_back({ ELeague::Ligue1, "24/25", 31, ETeam::LaHavre, ETeam::Monaco, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 31, ETeam::Strasbourg, ETeam::SaintEtienne, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 31, ETeam::Nantes, ETeam::Toulouse, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 31, ETeam::Montpellier, ETeam::Reims, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 31, ETeam::Lens, ETeam::Auxerre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 31, ETeam::Angers, ETeam::Lille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 31, ETeam::PSG, ETeam::Nice, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 31, ETeam::Marseille, ETeam::Brest, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 31, ETeam::Lyon, ETeam::Rennes, 1722985200000 });

    // Week 32
    matches.push_back({ ELeague::Ligue1, "24/25", 32, ETeam::Lyon, ETeam::Lens, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 32, ETeam::Lille, ETeam::Marseille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 32, ETeam::Nice, ETeam::Reims, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 32, ETeam::Brest, ETeam::Montpellier, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 32, ETeam::SaintEtienne, ETeam::Monaco, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 32, ETeam::Nantes, ETeam::Angers, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 32, ETeam::Toulouse, ETeam::Rennes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 32, ETeam::Strasbourg, ETeam::PSG, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 32, ETeam::Auxerre, ETeam::LaHavre, 1722985200000 });

    // Week 33
    matches.push_back({ ELeague::Ligue1, "24/25", 33, ETeam::Reims, ETeam::SaintEtienne, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 33, ETeam::Auxerre, ETeam::Nantes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 33, ETeam::Angers, ETeam::Strasbourg, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 33, ETeam::LaHavre, ETeam::Marseille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 33, ETeam::Rennes, ETeam::Nice, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 33, ETeam::Montpellier, ETeam::PSG, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 33, ETeam::Toulouse, ETeam::Lens, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 33, ETeam::Brest, ETeam::Lille, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 33, ETeam::Monaco, ETeam::Lyon, 1722985200000 });

    // Week 34
    matches.push_back({ ELeague::Ligue1, "24/25", 34, ETeam::Marseille, ETeam::Rennes, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 34, ETeam::Lyon, ETeam::Angers, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 34, ETeam::Nice, ETeam::Brest, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 34, ETeam::SaintEtienne, ETeam::Toulouse, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 34, ETeam::Lille, ETeam::Reims, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 34, ETeam::Strasbourg, ETeam::LaHavre, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 34, ETeam::Nantes, ETeam::Montpellier, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 34, ETeam::Lens, ETeam::Monaco, 1722985200000 });
    matches.push_back({ ELeague::Ligue1, "24/25", 34, ETeam::PSG, ETeam::Auxerre, 1722985200000 });


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

void MatchesInitializer::InitBundesliga24_25(PGconn* pg)
{
    std::vector<Match> matches;
    // Week 1
    matches.push_back({ ELeague::Bundesliga, "24/25", 1, ETeam::BorussiaMgladbach, ETeam::BayerLeverkusen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 1, ETeam::RBLeipzig, ETeam::Bochum, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 1, ETeam::Hoffenheim, ETeam::HolsteinKiel, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 1, ETeam::Freiburg, ETeam::Stuttgart, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 1, ETeam::Augsburg, ETeam::WerderBremen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 1, ETeam::Mainz, ETeam::UnionBerlin, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 1, ETeam::BorussiaDortmund, ETeam::EintrachtFrankfurt, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 1, ETeam::Wolfsburg, ETeam::BayernMunich, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 1, ETeam::StPauli, ETeam::Heidenheim, 1722985200000 });

    // Week 2
    matches.push_back({ ELeague::Bundesliga, "24/25", 2, ETeam::UnionBerlin, ETeam::StPauli, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 2, ETeam::Stuttgart, ETeam::Mainz, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 2, ETeam::EintrachtFrankfurt, ETeam::Hoffenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 2, ETeam::WerderBremen, ETeam::BorussiaDortmund, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 2, ETeam::Bochum, ETeam::BorussiaMgladbach, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 2, ETeam::HolsteinKiel, ETeam::Wolfsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 2, ETeam::BayerLeverkusen, ETeam::RBLeipzig, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 2, ETeam::Heidenheim, ETeam::Augsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 2, ETeam::BayernMunich, ETeam::Freiburg, 1722985200000 });

    // Week 3
    matches.push_back({ ELeague::Bundesliga, "24/25", 3, ETeam::BorussiaDortmund, ETeam::Heidenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 3, ETeam::RBLeipzig, ETeam::UnionBerlin, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 3, ETeam::Hoffenheim, ETeam::BayerLeverkusen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 3, ETeam::Freiburg, ETeam::Bochum, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 3, ETeam::Wolfsburg, ETeam::EintrachtFrankfurt, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 3, ETeam::BorussiaMgladbach, ETeam::Stuttgart, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 3, ETeam::HolsteinKiel, ETeam::BayernMunich, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 3, ETeam::Augsburg, ETeam::StPauli, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 3, ETeam::Mainz, ETeam::WerderBremen, 1722985200000 });

    // Week 4
    matches.push_back({ ELeague::Bundesliga, "24/25", 4, ETeam::Augsburg, ETeam::Mainz, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 4, ETeam::Heidenheim, ETeam::Freiburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 4, ETeam::WerderBremen, ETeam::BayernMunich, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 4, ETeam::UnionBerlin, ETeam::Hoffenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 4, ETeam::Bochum, ETeam::HolsteinKiel, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 4, ETeam::EintrachtFrankfurt, ETeam::BorussiaMgladbach, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 4, ETeam::BayerLeverkusen, ETeam::Wolfsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 4, ETeam::Stuttgart, ETeam::BorussiaDortmund, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 4, ETeam::StPauli, ETeam::RBLeipzig, 1722985200000 });

    // Week 5
    matches.push_back({ ELeague::Bundesliga, "24/25", 5, ETeam::BorussiaDortmund, ETeam::Bochum, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 5, ETeam::RBLeipzig, ETeam::Augsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 5, ETeam::Freiburg, ETeam::StPauli, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 5, ETeam::Wolfsburg, ETeam::Stuttgart, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 5, ETeam::Mainz, ETeam::Heidenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 5, ETeam::BorussiaMgladbach, ETeam::UnionBerlin, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 5, ETeam::BayernMunich, ETeam::BayerLeverkusen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 5, ETeam::HolsteinKiel, ETeam::EintrachtFrankfurt, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 5, ETeam::Hoffenheim, ETeam::WerderBremen, 1722985200000 });

    // Week 6
    matches.push_back({ ELeague::Bundesliga, "24/25", 6, ETeam::BayerLeverkusen, ETeam::HolsteinKiel, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 6, ETeam::Stuttgart, ETeam::Hoffenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 6, ETeam::EintrachtFrankfurt, ETeam::BayernMunich, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 6, ETeam::Heidenheim, ETeam::RBLeipzig, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 6, ETeam::WerderBremen, ETeam::Freiburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 6, ETeam::Augsburg, ETeam::BorussiaMgladbach, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 6, ETeam::UnionBerlin, ETeam::BorussiaDortmund, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 6, ETeam::Bochum, ETeam::Wolfsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 6, ETeam::StPauli, ETeam::Mainz, 1722985200000 });

    // Week 7
    matches.push_back({ ELeague::Bundesliga, "24/25", 7, ETeam::BayerLeverkusen, ETeam::EintrachtFrankfurt, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 7, ETeam::BayernMunich, ETeam::Stuttgart, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 7, ETeam::BorussiaDortmund, ETeam::StPauli, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 7, ETeam::Hoffenheim, ETeam::Bochum, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 7, ETeam::Freiburg, ETeam::Augsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 7, ETeam::Wolfsburg, ETeam::WerderBremen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 7, ETeam::Mainz, ETeam::RBLeipzig, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 7, ETeam::BorussiaMgladbach, ETeam::Heidenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 7, ETeam::HolsteinKiel, ETeam::UnionBerlin, 1722985200000 });

    // Week 8
    matches.push_back({ ELeague::Bundesliga, "24/25", 8, ETeam::Stuttgart, ETeam::HolsteinKiel, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 8, ETeam::RBLeipzig, ETeam::Freiburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 8, ETeam::Heidenheim, ETeam::Hoffenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 8, ETeam::WerderBremen, ETeam::BayerLeverkusen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 8, ETeam::Augsburg, ETeam::BorussiaDortmund, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 8, ETeam::Mainz, ETeam::BorussiaMgladbach, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 8, ETeam::UnionBerlin, ETeam::EintrachtFrankfurt, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 8, ETeam::Bochum, ETeam::BayernMunich, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 8, ETeam::StPauli, ETeam::Wolfsburg, 1722985200000 });

    // Week 9
    matches.push_back({ ELeague::Bundesliga, "24/25", 9, ETeam::BayerLeverkusen, ETeam::Stuttgart, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 9, ETeam::BayernMunich, ETeam::UnionBerlin, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 9, ETeam::BorussiaDortmund, ETeam::RBLeipzig, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 9, ETeam::EintrachtFrankfurt, ETeam::Bochum, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 9, ETeam::Hoffenheim, ETeam::StPauli, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 9, ETeam::Freiburg, ETeam::Mainz, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 9, ETeam::Wolfsburg, ETeam::Augsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 9, ETeam::BorussiaMgladbach, ETeam::WerderBremen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 9, ETeam::HolsteinKiel, ETeam::Heidenheim, 1722985200000 });

    // Week 10
    matches.push_back({ ELeague::Bundesliga, "24/25", 10, ETeam::Stuttgart, ETeam::EintrachtFrankfurt, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 10, ETeam::RBLeipzig, ETeam::BorussiaMgladbach, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 10, ETeam::Heidenheim, ETeam::Wolfsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 10, ETeam::WerderBremen, ETeam::HolsteinKiel, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 10, ETeam::Augsburg, ETeam::Hoffenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 10, ETeam::Mainz, ETeam::BorussiaDortmund, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 10, ETeam::UnionBerlin, ETeam::Freiburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 10, ETeam::Bochum, ETeam::BayerLeverkusen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 10, ETeam::StPauli, ETeam::BayernMunich, 1722985200000 });

    // Week 11
    matches.push_back({ ELeague::Bundesliga, "24/25", 11, ETeam::BayerLeverkusen, ETeam::Heidenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 11, ETeam::Stuttgart, ETeam::Bochum, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 11, ETeam::BayernMunich, ETeam::Augsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 11, ETeam::BorussiaDortmund, ETeam::Freiburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 11, ETeam::EintrachtFrankfurt, ETeam::WerderBremen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 11, ETeam::Hoffenheim, ETeam::RBLeipzig, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 11, ETeam::Wolfsburg, ETeam::UnionBerlin, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 11, ETeam::BorussiaMgladbach, ETeam::StPauli, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 11, ETeam::HolsteinKiel, ETeam::Mainz, 1722985200000 });

    // Week 12
    matches.push_back({ ELeague::Bundesliga, "24/25", 12, ETeam::RBLeipzig, ETeam::Wolfsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 12, ETeam::BorussiaDortmund, ETeam::BayernMunich, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 12, ETeam::Heidenheim, ETeam::EintrachtFrankfurt, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 12, ETeam::WerderBremen, ETeam::Stuttgart, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 12, ETeam::Freiburg, ETeam::BorussiaMgladbach, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 12, ETeam::Augsburg, ETeam::Bochum, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 12, ETeam::Mainz, ETeam::Hoffenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 12, ETeam::UnionBerlin, ETeam::BayerLeverkusen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 12, ETeam::StPauli, ETeam::HolsteinKiel, 1722985200000 });

    // Week 13
    matches.push_back({ ELeague::Bundesliga, "24/25", 13, ETeam::BayerLeverkusen, ETeam::StPauli, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 13, ETeam::Stuttgart, ETeam::UnionBerlin, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 13, ETeam::BayernMunich, ETeam::Heidenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 13, ETeam::EintrachtFrankfurt, ETeam::Augsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 13, ETeam::Hoffenheim, ETeam::Freiburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 13, ETeam::Wolfsburg, ETeam::Mainz, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 13, ETeam::BorussiaMgladbach, ETeam::BorussiaDortmund, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 13, ETeam::Bochum, ETeam::WerderBremen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 13, ETeam::HolsteinKiel, ETeam::RBLeipzig, 1722985200000 });

    // Week 14
    matches.push_back({ ELeague::Bundesliga, "24/25", 14, ETeam::RBLeipzig, ETeam::EintrachtFrankfurt, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 14, ETeam::BorussiaDortmund, ETeam::Hoffenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 14, ETeam::Heidenheim, ETeam::Stuttgart, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 14, ETeam::Freiburg, ETeam::Wolfsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 14, ETeam::Augsburg, ETeam::BayerLeverkusen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 14, ETeam::Mainz, ETeam::BayernMunich, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 14, ETeam::BorussiaMgladbach, ETeam::HolsteinKiel, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 14, ETeam::UnionBerlin, ETeam::Bochum, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 14, ETeam::StPauli, ETeam::WerderBremen, 1722985200000 });

    // Week 15
    matches.push_back({ ELeague::Bundesliga, "24/25", 15, ETeam::BayerLeverkusen, ETeam::Freiburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 15, ETeam::Stuttgart, ETeam::StPauli, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 15, ETeam::BayernMunich, ETeam::RBLeipzig, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 15, ETeam::EintrachtFrankfurt, ETeam::Mainz, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 15, ETeam::Hoffenheim, ETeam::BorussiaMgladbach, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 15, ETeam::WerderBremen, ETeam::UnionBerlin, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 15, ETeam::Wolfsburg, ETeam::BorussiaDortmund, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 15, ETeam::Bochum, ETeam::Heidenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 15, ETeam::HolsteinKiel, ETeam::Augsburg, 1722985200000 });

    // Week 16
    matches.push_back({ ELeague::Bundesliga, "24/25", 16, ETeam::RBLeipzig, ETeam::WerderBremen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 16, ETeam::BorussiaDortmund, ETeam::BayerLeverkusen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 16, ETeam::Hoffenheim, ETeam::Wolfsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 16, ETeam::Heidenheim, ETeam::UnionBerlin, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 16, ETeam::Freiburg, ETeam::HolsteinKiel, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 16, ETeam::Augsburg, ETeam::Stuttgart, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 16, ETeam::Mainz, ETeam::Bochum, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 16, ETeam::BorussiaMgladbach, ETeam::BayernMunich, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 16, ETeam::StPauli, ETeam::EintrachtFrankfurt, 1722985200000 });

    // Week 17
    matches.push_back({ ELeague::Bundesliga, "24/25", 17, ETeam::BayerLeverkusen, ETeam::Mainz, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 17, ETeam::Stuttgart, ETeam::RBLeipzig, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 17, ETeam::BayernMunich, ETeam::Hoffenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 17, ETeam::EintrachtFrankfurt, ETeam::Freiburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 17, ETeam::WerderBremen, ETeam::Heidenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 17, ETeam::Wolfsburg, ETeam::BorussiaMgladbach, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 17, ETeam::UnionBerlin, ETeam::Augsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 17, ETeam::Bochum, ETeam::StPauli, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 17, ETeam::HolsteinKiel, ETeam::BorussiaDortmund, 1722985200000 });

    // Week 18
    matches.push_back({ ELeague::Bundesliga, "24/25", 18, ETeam::BayerLeverkusen, ETeam::BorussiaMgladbach, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 18, ETeam::Stuttgart, ETeam::Freiburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 18, ETeam::BayernMunich, ETeam::Wolfsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 18, ETeam::EintrachtFrankfurt, ETeam::BorussiaDortmund, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 18, ETeam::Heidenheim, ETeam::StPauli, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 18, ETeam::WerderBremen, ETeam::Augsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 18, ETeam::UnionBerlin, ETeam::Mainz, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 18, ETeam::Bochum, ETeam::RBLeipzig, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 18, ETeam::HolsteinKiel, ETeam::Hoffenheim, 1722985200000 });

    // Week 19
    matches.push_back({ ELeague::Bundesliga, "24/25", 19, ETeam::RBLeipzig, ETeam::BayerLeverkusen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 19, ETeam::BorussiaDortmund, ETeam::WerderBremen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 19, ETeam::Hoffenheim, ETeam::EintrachtFrankfurt, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 19, ETeam::Freiburg, ETeam::BayernMunich, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 19, ETeam::Augsburg, ETeam::Heidenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 19, ETeam::Wolfsburg, ETeam::HolsteinKiel, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 19, ETeam::Mainz, ETeam::Stuttgart, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 19, ETeam::BorussiaMgladbach, ETeam::Bochum, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 19, ETeam::StPauli, ETeam::UnionBerlin, 1722985200000 });

    // Week 20
    matches.push_back({ ELeague::Bundesliga, "24/25", 20, ETeam::BayerLeverkusen, ETeam::Hoffenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 20, ETeam::Stuttgart, ETeam::BorussiaMgladbach, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 20, ETeam::BayernMunich, ETeam::HolsteinKiel, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 20, ETeam::EintrachtFrankfurt, ETeam::Wolfsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 20, ETeam::Heidenheim, ETeam::BorussiaDortmund, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 20, ETeam::WerderBremen, ETeam::Mainz, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 20, ETeam::UnionBerlin, ETeam::RBLeipzig, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 20, ETeam::Bochum, ETeam::Freiburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 20, ETeam::StPauli, ETeam::Augsburg, 1722985200000 });

    // Week 21
    matches.push_back({ ELeague::Bundesliga, "24/25", 21, ETeam::BayernMunich, ETeam::WerderBremen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 21, ETeam::RBLeipzig, ETeam::StPauli, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 21, ETeam::BorussiaDortmund, ETeam::Stuttgart, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 21, ETeam::Hoffenheim, ETeam::UnionBerlin, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 21, ETeam::Freiburg, ETeam::Heidenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 21, ETeam::Wolfsburg, ETeam::BayerLeverkusen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 21, ETeam::Mainz, ETeam::Augsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 21, ETeam::EintrachtFrankfurt, ETeam::ACMilan, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 21, ETeam::Bochum, ETeam::Venezia, 1722985200000 });

    // Week 22
    matches.push_back({ ELeague::Bundesliga, "24/25", 22, ETeam::BayerLeverkusen, ETeam::BayernMunich, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 22, ETeam::Stuttgart, ETeam::Wolfsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 22, ETeam::EintrachtFrankfurt, ETeam::HolsteinKiel, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 22, ETeam::Heidenheim, ETeam::Mainz, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 22, ETeam::WerderBremen, ETeam::Hoffenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 22, ETeam::Augsburg, ETeam::RBLeipzig, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 22, ETeam::UnionBerlin, ETeam::BorussiaMgladbach, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 22, ETeam::Bochum, ETeam::BorussiaDortmund, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 22, ETeam::StPauli, ETeam::Freiburg, 1722985200000 });

    // Week 23
    matches.push_back({ ELeague::Bundesliga, "24/25", 23, ETeam::BayernMunich, ETeam::Torino, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 23, ETeam::RBLeipzig, ETeam::Como, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 23, ETeam::BorussiaDortmund, ETeam::Lazio, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 23, ETeam::Hoffenheim, ETeam::Genoa, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 23, ETeam::Freiburg, ETeam::Empoli, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 23, ETeam::Wolfsburg, ETeam::InterMilan, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 23, ETeam::Mainz, ETeam::Verona, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 23, ETeam::BorussiaMgladbach, ETeam::Lecce, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 23, ETeam::HolsteinKiel, ETeam::Napoli, 1722985200000 });

    // Week 24
    matches.push_back({ ELeague::Bundesliga, "24/25", 24, ETeam::Stuttgart, ETeam::BayernMunich, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 24, ETeam::RBLeipzig, ETeam::Mainz, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 24, ETeam::EintrachtFrankfurt, ETeam::BayerLeverkusen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 24, ETeam::Heidenheim, ETeam::BorussiaMgladbach, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 24, ETeam::WerderBremen, ETeam::Wolfsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 24, ETeam::Augsburg, ETeam::Freiburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 24, ETeam::UnionBerlin, ETeam::HolsteinKiel, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 24, ETeam::Bochum, ETeam::Hoffenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 24, ETeam::StPauli, ETeam::BorussiaDortmund, 1722985200000 });

    // Week 25
    matches.push_back({ ELeague::Bundesliga, "24/25", 25, ETeam::BayerLeverkusen, ETeam::WerderBremen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 25, ETeam::BayernMunich, ETeam::Bochum, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 25, ETeam::BorussiaDortmund, ETeam::Augsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 25, ETeam::EintrachtFrankfurt, ETeam::UnionBerlin, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 25, ETeam::Hoffenheim, ETeam::Heidenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 25, ETeam::Freiburg, ETeam::RBLeipzig, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 25, ETeam::Wolfsburg, ETeam::StPauli, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 25, ETeam::BorussiaMgladbach, ETeam::Mainz, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 25, ETeam::HolsteinKiel, ETeam::Stuttgart, 1722985200000 });

    // Week 26
    matches.push_back({ ELeague::Bundesliga, "24/25", 26, ETeam::Stuttgart, ETeam::BayerLeverkusen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 26, ETeam::RBLeipzig, ETeam::BorussiaDortmund, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 26, ETeam::Heidenheim, ETeam::HolsteinKiel, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 26, ETeam::WerderBremen, ETeam::BorussiaMgladbach, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 26, ETeam::Augsburg, ETeam::Wolfsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 26, ETeam::Mainz, ETeam::Freiburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 26, ETeam::UnionBerlin, ETeam::BayernMunich, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 26, ETeam::Bochum, ETeam::EintrachtFrankfurt, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 26, ETeam::StPauli, ETeam::Hoffenheim, 1722985200000 });

    // Week 27
    matches.push_back({ ELeague::Bundesliga, "24/25", 27, ETeam::BayerLeverkusen, ETeam::Bochum, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 27, ETeam::BayernMunich, ETeam::StPauli, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 27, ETeam::BorussiaDortmund, ETeam::Mainz, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 27, ETeam::EintrachtFrankfurt, ETeam::Stuttgart, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 27, ETeam::Hoffenheim, ETeam::Augsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 27, ETeam::Freiburg, ETeam::UnionBerlin, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 27, ETeam::Wolfsburg, ETeam::Heidenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 27, ETeam::BorussiaMgladbach, ETeam::RBLeipzig, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 27, ETeam::HolsteinKiel, ETeam::WerderBremen, 1722985200000 });

    // Week 28
    matches.push_back({ ELeague::Bundesliga, "24/25", 28, ETeam::RBLeipzig, ETeam::Hoffenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 28, ETeam::Heidenheim, ETeam::BayerLeverkusen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 28, ETeam::WerderBremen, ETeam::EintrachtFrankfurt, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 28, ETeam::Freiburg, ETeam::BorussiaDortmund, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 28, ETeam::Augsburg, ETeam::BayernMunich, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 28, ETeam::Mainz, ETeam::HolsteinKiel, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 28, ETeam::UnionBerlin, ETeam::Wolfsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 28, ETeam::Bochum, ETeam::Stuttgart, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 28, ETeam::StPauli, ETeam::BorussiaMgladbach, 1722985200000 });

    // Week 29
    matches.push_back({ ELeague::Bundesliga, "24/25", 29, ETeam::BayerLeverkusen, ETeam::UnionBerlin, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 29, ETeam::Stuttgart, ETeam::WerderBremen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 29, ETeam::BayernMunich, ETeam::BorussiaDortmund, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 29, ETeam::EintrachtFrankfurt, ETeam::Heidenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 29, ETeam::Hoffenheim, ETeam::Mainz, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 29, ETeam::Wolfsburg, ETeam::RBLeipzig, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 29, ETeam::BorussiaMgladbach, ETeam::Freiburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 29, ETeam::Bochum, ETeam::Augsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 29, ETeam::HolsteinKiel, ETeam::StPauli, 1722985200000 });

    // Week 30
    matches.push_back({ ELeague::Bundesliga, "24/25", 30, ETeam::RBLeipzig, ETeam::HolsteinKiel, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 30, ETeam::BorussiaDortmund, ETeam::BorussiaMgladbach, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 30, ETeam::Heidenheim, ETeam::BayernMunich, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 30, ETeam::WerderBremen, ETeam::Bochum, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 30, ETeam::Freiburg, ETeam::Hoffenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 30, ETeam::Augsburg, ETeam::EintrachtFrankfurt, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 30, ETeam::Mainz, ETeam::Wolfsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 30, ETeam::UnionBerlin, ETeam::Stuttgart, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 30, ETeam::StPauli, ETeam::BayerLeverkusen, 1722985200000 });

    // Week 31
    matches.push_back({ ELeague::Bundesliga, "24/25", 31, ETeam::BayerLeverkusen, ETeam::Augsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 31, ETeam::Stuttgart, ETeam::Heidenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 31, ETeam::BayernMunich, ETeam::Mainz, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 31, ETeam::EintrachtFrankfurt, ETeam::RBLeipzig, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 31, ETeam::Hoffenheim, ETeam::BorussiaDortmund, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 31, ETeam::WerderBremen, ETeam::StPauli, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 31, ETeam::Wolfsburg, ETeam::Freiburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 31, ETeam::Bochum, ETeam::UnionBerlin, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 31, ETeam::HolsteinKiel, ETeam::BorussiaMgladbach, 1722985200000 });

    // Week 32
    matches.push_back({ ELeague::Bundesliga, "24/25", 32, ETeam::RBLeipzig, ETeam::BayernMunich, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 32, ETeam::BorussiaDortmund, ETeam::Wolfsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 32, ETeam::Heidenheim, ETeam::Bochum, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 32, ETeam::Freiburg, ETeam::BayerLeverkusen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 32, ETeam::Augsburg, ETeam::HolsteinKiel, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 32, ETeam::Mainz, ETeam::EintrachtFrankfurt, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 32, ETeam::BorussiaMgladbach, ETeam::Hoffenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 32, ETeam::UnionBerlin, ETeam::WerderBremen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 32, ETeam::StPauli, ETeam::Stuttgart, 1722985200000 });

    // Week 33
    matches.push_back({ ELeague::Bundesliga, "24/25", 33, ETeam::BayerLeverkusen, ETeam::BorussiaDortmund, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 33, ETeam::Stuttgart, ETeam::Augsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 33, ETeam::BayernMunich, ETeam::BorussiaMgladbach, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 33, ETeam::EintrachtFrankfurt, ETeam::StPauli, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 33, ETeam::WerderBremen, ETeam::RBLeipzig, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 33, ETeam::Wolfsburg, ETeam::Hoffenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 33, ETeam::UnionBerlin, ETeam::Heidenheim, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 33, ETeam::Bochum, ETeam::Mainz, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 33, ETeam::HolsteinKiel, ETeam::Freiburg, 1722985200000 });

    // Week 34
    matches.push_back({ ELeague::Bundesliga, "24/25", 34, ETeam::RBLeipzig, ETeam::Stuttgart, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 34, ETeam::BorussiaDortmund, ETeam::HolsteinKiel, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 34, ETeam::Hoffenheim, ETeam::BayernMunich, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 34, ETeam::Heidenheim, ETeam::WerderBremen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 34, ETeam::Freiburg, ETeam::EintrachtFrankfurt, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 34, ETeam::Augsburg, ETeam::UnionBerlin, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 34, ETeam::Mainz, ETeam::BayerLeverkusen, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 34, ETeam::BorussiaMgladbach, ETeam::Wolfsburg, 1722985200000 });
    matches.push_back({ ELeague::Bundesliga, "24/25", 34, ETeam::StPauli, ETeam::Bochum, 1722985200000 });

   
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

void MatchesInitializer::InitSerieA24_25(PGconn* pg)
{
    // Serie A
    std::vector<Match> matches;
    // Week 1
    matches.push_back({ ELeague::SerieA, "24/25", 1, ETeam::Genoa, ETeam::InterMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 1, ETeam::Parma, ETeam::Fiorentina, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 1, ETeam::Empoli, ETeam::Monza, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 1, ETeam::ACMilan, ETeam::Torino, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 1, ETeam::Bologna, ETeam::Udinese, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 1, ETeam::Verona, ETeam::Napoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 1, ETeam::Cagliari, ETeam::Roma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 1, ETeam::Lazio, ETeam::Venezia, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 1, ETeam::Lecce, ETeam::Atalanta, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 1, ETeam::Juventus, ETeam::Como, 1722985200000 });

    // Week 2
    matches.push_back({ ELeague::SerieA, "24/25", 2, ETeam::Parma, ETeam::ACMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 2, ETeam::Udinese, ETeam::Lazio, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 2, ETeam::InterMilan, ETeam::Lecce, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 2, ETeam::Monza, ETeam::Genoa, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 2, ETeam::Fiorentina, ETeam::Venezia, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 2, ETeam::Torino, ETeam::Atalanta, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 2, ETeam::Napoli, ETeam::Bologna, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 2, ETeam::Roma, ETeam::Empoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 2, ETeam::Cagliari, ETeam::Como, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 2, ETeam::Verona, ETeam::Juventus, 1722985200000 });

    // Week 3
    matches.push_back({ ELeague::SerieA, "24/25", 3, ETeam::Venezia, ETeam::Torino, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 3, ETeam::InterMilan, ETeam::Atalanta, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 3, ETeam::Bologna, ETeam::Empoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 3, ETeam::Lecce, ETeam::Cagliari, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 3, ETeam::Lazio, ETeam::ACMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 3, ETeam::Napoli, ETeam::Parma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 3, ETeam::Fiorentina, ETeam::Monza, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 3, ETeam::Genoa, ETeam::Verona, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 3, ETeam::Juventus, ETeam::Roma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 3, ETeam::Udinese, ETeam::Como, 1722985200000 });

    // Week 4
    matches.push_back({ ELeague::SerieA, "24/25", 4, ETeam::Atalanta, ETeam::Fiorentina, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 4, ETeam::Cagliari, ETeam::Napoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 4, ETeam::Como, ETeam::Bologna, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 4, ETeam::Empoli, ETeam::Juventus, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 4, ETeam::Genoa, ETeam::Roma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 4, ETeam::Lazio, ETeam::Verona, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 4, ETeam::ACMilan, ETeam::Venezia, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 4, ETeam::Monza, ETeam::InterMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 4, ETeam::Parma, ETeam::Udinese, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 4, ETeam::Torino, ETeam::Lecce, 1722985200000 });

    // Week 5
    matches.push_back({ ELeague::SerieA, "24/25", 5, ETeam::Atalanta, ETeam::Como, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 5, ETeam::Cagliari, ETeam::Empoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 5, ETeam::Fiorentina, ETeam::Lazio, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 5, ETeam::Verona, ETeam::Torino, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 5, ETeam::InterMilan, ETeam::ACMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 5, ETeam::Juventus, ETeam::Napoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 5, ETeam::Lecce, ETeam::Parma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 5, ETeam::Monza, ETeam::Bologna, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 5, ETeam::Roma, ETeam::Udinese, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 5, ETeam::Venezia, ETeam::Genoa, 1722985200000 });

    // Week 6
    matches.push_back({ ELeague::SerieA, "24/25", 6, ETeam::Bologna, ETeam::Atalanta, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 6, ETeam::Como, ETeam::Verona, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 6, ETeam::Empoli, ETeam::Fiorentina, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 6, ETeam::Genoa, ETeam::Juventus, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 6, ETeam::ACMilan, ETeam::Lecce, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 6, ETeam::Napoli, ETeam::Monza, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 6, ETeam::Parma, ETeam::Cagliari, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 6, ETeam::Roma, ETeam::Venezia, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 6, ETeam::Torino, ETeam::Lazio, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 6, ETeam::Udinese, ETeam::InterMilan, 1722985200000 });

    // Week 7
    matches.push_back({ ELeague::SerieA, "24/25", 7, ETeam::Atalanta, ETeam::Genoa, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 7, ETeam::Bologna, ETeam::Parma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 7, ETeam::Fiorentina, ETeam::ACMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 7, ETeam::Verona, ETeam::Venezia, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 7, ETeam::InterMilan, ETeam::Torino, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 7, ETeam::Juventus, ETeam::Cagliari, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 7, ETeam::Lazio, ETeam::Empoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 7, ETeam::Monza, ETeam::Roma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 7, ETeam::Napoli, ETeam::Como, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 7, ETeam::Udinese, ETeam::Lecce, 1722985200000 });

    // Week 8
    matches.push_back({ ELeague::SerieA, "24/25", 8, ETeam::Cagliari, ETeam::Torino, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 8, ETeam::Como, ETeam::Parma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 8, ETeam::Empoli, ETeam::Napoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 8, ETeam::Genoa, ETeam::Bologna, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 8, ETeam::Verona, ETeam::Monza, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 8, ETeam::Juventus, ETeam::Lazio, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 8, ETeam::Lecce, ETeam::Fiorentina, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 8, ETeam::ACMilan, ETeam::Udinese, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 8, ETeam::Roma, ETeam::InterMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 8, ETeam::Venezia, ETeam::Atalanta, 1722985200000 });

    // Week 9
    matches.push_back({ ELeague::SerieA, "24/25", 9, ETeam::Atalanta, ETeam::Verona, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 9, ETeam::Bologna, ETeam::ACMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 9, ETeam::Fiorentina, ETeam::Roma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 9, ETeam::InterMilan, ETeam::Juventus, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 9, ETeam::Lazio, ETeam::Genoa, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 9, ETeam::Monza, ETeam::Venezia, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 9, ETeam::Napoli, ETeam::Lecce, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 9, ETeam::Parma, ETeam::Empoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 9, ETeam::Torino, ETeam::Como, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 9, ETeam::Udinese, ETeam::Cagliari, 1722985200000 });

    // Week 10
    matches.push_back({ ELeague::SerieA, "24/25", 10, ETeam::Atalanta, ETeam::Monza, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 10, ETeam::Cagliari, ETeam::Bologna, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 10, ETeam::Como, ETeam::Lazio, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 10, ETeam::Empoli, ETeam::InterMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 10, ETeam::Genoa, ETeam::Fiorentina, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 10, ETeam::Juventus, ETeam::Parma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 10, ETeam::Lecce, ETeam::Verona, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 10, ETeam::ACMilan, ETeam::Napoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 10, ETeam::Roma, ETeam::Torino, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 10, ETeam::Venezia, ETeam::Udinese, 1722985200000 });

    // Week 11
    matches.push_back({ ELeague::SerieA, "24/25", 11, ETeam::Bologna, ETeam::Lecce, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 11, ETeam::Empoli, ETeam::Como, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 11, ETeam::Verona, ETeam::Roma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 11, ETeam::InterMilan, ETeam::Venezia, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 11, ETeam::Lazio, ETeam::Cagliari, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 11, ETeam::Monza, ETeam::ACMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 11, ETeam::Napoli, ETeam::Atalanta, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 11, ETeam::Parma, ETeam::Genoa, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 11, ETeam::Torino, ETeam::Fiorentina, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 11, ETeam::Udinese, ETeam::Juventus, 1722985200000 });

    // Week 12
    matches.push_back({ ELeague::SerieA, "24/25", 12, ETeam::Atalanta, ETeam::Udinese, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 12, ETeam::Cagliari, ETeam::ACMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 12, ETeam::Fiorentina, ETeam::Verona, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 12, ETeam::Genoa, ETeam::Como, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 12, ETeam::InterMilan, ETeam::Napoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 12, ETeam::Juventus, ETeam::Torino, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 12, ETeam::Lecce, ETeam::Empoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 12, ETeam::Monza, ETeam::Lazio, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 12, ETeam::Roma, ETeam::Bologna, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 12, ETeam::Venezia, ETeam::Parma, 1722985200000 });

    // Week 13
    matches.push_back({ ELeague::SerieA, "24/25", 13, ETeam::Como, ETeam::Fiorentina, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 13, ETeam::Empoli, ETeam::Udinese, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 13, ETeam::Genoa, ETeam::Cagliari, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 13, ETeam::Verona, ETeam::InterMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 13, ETeam::Lazio, ETeam::Bologna, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 13, ETeam::ACMilan, ETeam::Juventus, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 13, ETeam::Napoli, ETeam::Roma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 13, ETeam::Parma, ETeam::Atalanta, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 13, ETeam::Torino, ETeam::Monza, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 13, ETeam::Venezia, ETeam::Lecce, 1722985200000 });

    // Week 14
    matches.push_back({ ELeague::SerieA, "24/25", 14, ETeam::Bologna, ETeam::Venezia, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 14, ETeam::Cagliari, ETeam::Verona, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 14, ETeam::Como, ETeam::Monza, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 14, ETeam::Fiorentina, ETeam::InterMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 14, ETeam::Lecce, ETeam::Juventus, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 14, ETeam::ACMilan, ETeam::Empoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 14, ETeam::Parma, ETeam::Lazio, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 14, ETeam::Roma, ETeam::Atalanta, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 14, ETeam::Torino, ETeam::Napoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 14, ETeam::Udinese, ETeam::Genoa, 1722985200000 });

    // Week 15
    matches.push_back({ ELeague::SerieA, "24/25", 15, ETeam::Atalanta, ETeam::ACMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 15, ETeam::Fiorentina, ETeam::Cagliari, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 15, ETeam::Genoa, ETeam::Torino, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 15, ETeam::Verona, ETeam::Empoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 15, ETeam::InterMilan, ETeam::Parma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 15, ETeam::Juventus, ETeam::Bologna, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 15, ETeam::Monza, ETeam::Udinese, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 15, ETeam::Napoli, ETeam::Lazio, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 15, ETeam::Roma, ETeam::Lecce, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 15, ETeam::Venezia, ETeam::Como, 1722985200000 });

    // Week 16
    matches.push_back({ ELeague::SerieA, "24/25", 16, ETeam::Bologna, ETeam::Fiorentina, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 16, ETeam::Cagliari, ETeam::Atalanta, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 16, ETeam::Como, ETeam::Roma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 16, ETeam::Empoli, ETeam::Torino, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 16, ETeam::Juventus, ETeam::Venezia, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 16, ETeam::Lazio, ETeam::InterMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 16, ETeam::Lecce, ETeam::Monza, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 16, ETeam::ACMilan, ETeam::Genoa, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 16, ETeam::Parma, ETeam::Verona, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 16, ETeam::Udinese, ETeam::Napoli, 1722985200000 });

    // Week 17
    matches.push_back({ ELeague::SerieA, "24/25", 17, ETeam::Atalanta, ETeam::Empoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 17, ETeam::Fiorentina, ETeam::Udinese, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 17, ETeam::Genoa, ETeam::Napoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 17, ETeam::Verona, ETeam::ACMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 17, ETeam::InterMilan, ETeam::Como, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 17, ETeam::Lecce, ETeam::Lazio, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 17, ETeam::Monza, ETeam::Juventus, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 17, ETeam::Roma, ETeam::Parma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 17, ETeam::Torino, ETeam::Bologna, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 17, ETeam::Venezia, ETeam::Cagliari, 1722985200000 });

    // Week 18
    matches.push_back({ ELeague::SerieA, "24/25", 18, ETeam::Bologna, ETeam::Verona, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 18, ETeam::Cagliari, ETeam::InterMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 18, ETeam::Como, ETeam::Lecce, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 18, ETeam::Empoli, ETeam::Genoa, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 18, ETeam::Juventus, ETeam::Fiorentina, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 18, ETeam::Lazio, ETeam::Atalanta, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 18, ETeam::ACMilan, ETeam::Roma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 18, ETeam::Napoli, ETeam::Venezia, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 18, ETeam::Parma, ETeam::Monza, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 18, ETeam::Udinese, ETeam::Torino, 1722985200000 });

    // Week 19
    matches.push_back({ ELeague::SerieA, "24/25", 19, ETeam::Atalanta, ETeam::Juventus, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 19, ETeam::Como, ETeam::ACMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 19, ETeam::Fiorentina, ETeam::Napoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 19, ETeam::Verona, ETeam::Udinese, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 19, ETeam::InterMilan, ETeam::Bologna, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 19, ETeam::Lecce, ETeam::Genoa, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 19, ETeam::Monza, ETeam::Cagliari, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 19, ETeam::Roma, ETeam::Lazio, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 19, ETeam::Torino, ETeam::Parma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 19, ETeam::Venezia, ETeam::Empoli, 1722985200000 });

    // Week 20
    matches.push_back({ ELeague::SerieA, "24/25", 20, ETeam::Bologna, ETeam::Roma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 20, ETeam::Empoli, ETeam::Lecce, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 20, ETeam::Genoa, ETeam::Parma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 20, ETeam::Lazio, ETeam::Como, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 20, ETeam::ACMilan, ETeam::Cagliari, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 20, ETeam::Monza, ETeam::Fiorentina, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 20, ETeam::Napoli, ETeam::Verona, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 20, ETeam::Torino, ETeam::Juventus, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 20, ETeam::Udinese, ETeam::Atalanta, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 20, ETeam::Venezia, ETeam::InterMilan, 1722985200000 });

    // Week 21
    matches.push_back({ ELeague::SerieA, "24/25", 21, ETeam::Atalanta, ETeam::Napoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 21, ETeam::Bologna, ETeam::Monza, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 21, ETeam::Cagliari, ETeam::Lecce, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 21, ETeam::Como, ETeam::Udinese, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 21, ETeam::Fiorentina, ETeam::Torino, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 21, ETeam::Verona, ETeam::Lazio, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 21, ETeam::InterMilan, ETeam::Empoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 21, ETeam::Juventus, ETeam::ACMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 21, ETeam::Parma, ETeam::Venezia, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 21, ETeam::Roma, ETeam::Genoa, 1722985200000 });

    // Week 22
    matches.push_back({ ELeague::SerieA, "24/25", 22, ETeam::Como, ETeam::Atalanta, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 22, ETeam::Empoli, ETeam::Bologna, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 22, ETeam::Genoa, ETeam::Monza, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 22, ETeam::Lazio, ETeam::Fiorentina, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 22, ETeam::Lecce, ETeam::InterMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 22, ETeam::ACMilan, ETeam::Parma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 22, ETeam::Napoli, ETeam::Juventus, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 22, ETeam::Torino, ETeam::Cagliari, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 22, ETeam::Udinese, ETeam::Roma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 22, ETeam::Venezia, ETeam::Verona, 1722985200000 });

    // Week 23
    matches.push_back({ ELeague::SerieA, "24/25", 23, ETeam::Atalanta, ETeam::Torino, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 23, ETeam::Bologna, ETeam::Como, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 23, ETeam::Cagliari, ETeam::Lazio, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 23, ETeam::Fiorentina, ETeam::Genoa, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 23, ETeam::Juventus, ETeam::Empoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 23, ETeam::ACMilan, ETeam::InterMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 23, ETeam::Monza, ETeam::Verona, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 23, ETeam::Parma, ETeam::Lecce, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 23, ETeam::Roma, ETeam::Napoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 23, ETeam::Udinese, ETeam::Venezia, 1722985200000 });

    // Week 24
    matches.push_back({ ELeague::SerieA, "24/25", 24, ETeam::Cagliari, ETeam::Parma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 24, ETeam::Como, ETeam::Juventus, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 24, ETeam::Empoli, ETeam::ACMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 24, ETeam::Verona, ETeam::Atalanta, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 24, ETeam::InterMilan, ETeam::Fiorentina, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 24, ETeam::Lazio, ETeam::Monza, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 24, ETeam::Lecce, ETeam::Bologna, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 24, ETeam::Napoli, ETeam::Udinese, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 24, ETeam::Torino, ETeam::Genoa, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 24, ETeam::Venezia, ETeam::Roma, 1722985200000 });

    // Week 25
    matches.push_back({ ELeague::SerieA, "24/25", 25, ETeam::Atalanta, ETeam::Cagliari, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 25, ETeam::Bologna, ETeam::Torino, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 25, ETeam::Fiorentina, ETeam::Como, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 25, ETeam::Genoa, ETeam::Venezia, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 25, ETeam::Juventus, ETeam::InterMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 25, ETeam::Lazio, ETeam::Napoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 25, ETeam::ACMilan, ETeam::Verona, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 25, ETeam::Monza, ETeam::Lecce, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 25, ETeam::Parma, ETeam::Roma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 25, ETeam::Udinese, ETeam::Empoli, 1722985200000 });

    // Week 26
    matches.push_back({ ELeague::SerieA, "24/25", 26, ETeam::Cagliari, ETeam::Juventus, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 26, ETeam::Como, ETeam::Napoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 26, ETeam::Empoli, ETeam::Atalanta, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 26, ETeam::Verona, ETeam::Fiorentina, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 26, ETeam::InterMilan, ETeam::Genoa, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 26, ETeam::Lecce, ETeam::Udinese, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 26, ETeam::Parma, ETeam::Bologna, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 26, ETeam::Roma, ETeam::Monza, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 26, ETeam::Torino, ETeam::ACMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 26, ETeam::Venezia, ETeam::Lazio, 1722985200000 });

    // Week 27
    matches.push_back({ ELeague::SerieA, "24/25", 27, ETeam::Atalanta, ETeam::Venezia, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 27, ETeam::Bologna, ETeam::Cagliari, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 27, ETeam::Fiorentina, ETeam::Lecce, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 27, ETeam::Genoa, ETeam::Empoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 27, ETeam::Juventus, ETeam::Verona, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 27, ETeam::ACMilan, ETeam::Lazio, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 27, ETeam::Monza, ETeam::Torino, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 27, ETeam::Napoli, ETeam::InterMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 27, ETeam::Roma, ETeam::Como, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 27, ETeam::Udinese, ETeam::Parma, 1722985200000 });

    // Week 28
    matches.push_back({ ELeague::SerieA, "24/25", 28, ETeam::Cagliari, ETeam::Genoa, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 28, ETeam::Como, ETeam::Venezia, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 28, ETeam::Empoli, ETeam::Roma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 28, ETeam::Verona, ETeam::Bologna, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 28, ETeam::InterMilan, ETeam::Monza, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 28, ETeam::Juventus, ETeam::Atalanta, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 28, ETeam::Lazio, ETeam::Udinese, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 28, ETeam::Lecce, ETeam::ACMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 28, ETeam::Napoli, ETeam::Fiorentina, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 28, ETeam::Parma, ETeam::Torino, 1722985200000 });

    // Week 29
    matches.push_back({ ELeague::SerieA, "24/25", 29, ETeam::Atalanta, ETeam::InterMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 29, ETeam::Bologna, ETeam::Lazio, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 29, ETeam::Fiorentina, ETeam::Juventus, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 29, ETeam::Genoa, ETeam::Lecce, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 29, ETeam::ACMilan, ETeam::Como, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 29, ETeam::Monza, ETeam::Parma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 29, ETeam::Roma, ETeam::Cagliari, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 29, ETeam::Torino, ETeam::Empoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 29, ETeam::Udinese, ETeam::Verona, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 29, ETeam::Venezia, ETeam::Napoli, 1722985200000 });

    // Week 30
    matches.push_back({ ELeague::SerieA, "24/25", 30, ETeam::Cagliari, ETeam::Monza, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 30, ETeam::Como, ETeam::Empoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 30, ETeam::Fiorentina, ETeam::Atalanta, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 30, ETeam::Verona, ETeam::Parma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 30, ETeam::InterMilan, ETeam::Udinese, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 30, ETeam::Juventus, ETeam::Genoa, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 30, ETeam::Lazio, ETeam::Torino, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 30, ETeam::Lecce, ETeam::Roma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 30, ETeam::Napoli, ETeam::ACMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 30, ETeam::Venezia, ETeam::Bologna, 1722985200000 });

    // Week 31
    matches.push_back({ ELeague::SerieA, "24/25", 31, ETeam::Atalanta, ETeam::Lazio, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 31, ETeam::Bologna, ETeam::Napoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 31, ETeam::Empoli, ETeam::Cagliari, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 31, ETeam::Genoa, ETeam::Udinese, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 31, ETeam::Lecce, ETeam::Venezia, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 31, ETeam::ACMilan, ETeam::Fiorentina, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 31, ETeam::Monza, ETeam::Como, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 31, ETeam::Parma, ETeam::InterMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 31, ETeam::Roma, ETeam::Juventus, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 31, ETeam::Torino, ETeam::Verona, 1722985200000 });

    // Week 32
    matches.push_back({ ELeague::SerieA, "24/25", 32, ETeam::Atalanta, ETeam::Bologna, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 32, ETeam::Como, ETeam::Torino, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 32, ETeam::Fiorentina, ETeam::Parma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 32, ETeam::Verona, ETeam::Genoa, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 32, ETeam::InterMilan, ETeam::Cagliari, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 32, ETeam::Juventus, ETeam::Lecce, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 32, ETeam::Lazio, ETeam::Roma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 32, ETeam::Napoli, ETeam::Empoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 32, ETeam::Udinese, ETeam::ACMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 32, ETeam::Venezia, ETeam::Monza, 1722985200000 });

    // Week 33
    matches.push_back({ ELeague::SerieA, "24/25", 33, ETeam::Bologna, ETeam::InterMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 33, ETeam::Cagliari, ETeam::Fiorentina, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 33, ETeam::Empoli, ETeam::Venezia, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 33, ETeam::Genoa, ETeam::Lazio, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 33, ETeam::Lecce, ETeam::Como, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 33, ETeam::ACMilan, ETeam::Atalanta, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 33, ETeam::Monza, ETeam::Napoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 33, ETeam::Parma, ETeam::Juventus, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 33, ETeam::Roma, ETeam::Verona, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 33, ETeam::Torino, ETeam::Udinese, 1722985200000 });

    // Week 34
    matches.push_back({ ELeague::SerieA, "24/25", 34, ETeam::Atalanta, ETeam::Lecce, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 34, ETeam::Como, ETeam::Genoa, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 34, ETeam::Fiorentina, ETeam::Empoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 34, ETeam::Verona, ETeam::Cagliari, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 34, ETeam::InterMilan, ETeam::Roma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 34, ETeam::Juventus, ETeam::Monza, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 34, ETeam::Lazio, ETeam::Parma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 34, ETeam::Napoli, ETeam::Torino, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 34, ETeam::Udinese, ETeam::Bologna, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 34, ETeam::Venezia, ETeam::ACMilan, 1722985200000 });

    // Week 35
    matches.push_back({ ELeague::SerieA, "24/25", 35, ETeam::Bologna, ETeam::Juventus, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 35, ETeam::Cagliari, ETeam::Udinese, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 35, ETeam::Empoli, ETeam::Lazio, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 35, ETeam::Genoa, ETeam::ACMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 35, ETeam::InterMilan, ETeam::Verona, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 35, ETeam::Lecce, ETeam::Napoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 35, ETeam::Monza, ETeam::Atalanta, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 35, ETeam::Parma, ETeam::Como, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 35, ETeam::Roma, ETeam::Fiorentina, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 35, ETeam::Torino, ETeam::Venezia, 1722985200000 });

    // Week 36
    matches.push_back({ ELeague::SerieA, "24/25", 36, ETeam::Atalanta, ETeam::Roma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 36, ETeam::Como, ETeam::Cagliari, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 36, ETeam::Empoli, ETeam::Parma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 36, ETeam::Verona, ETeam::Lecce, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 36, ETeam::Lazio, ETeam::Juventus, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 36, ETeam::ACMilan, ETeam::Bologna, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 36, ETeam::Napoli, ETeam::Genoa, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 36, ETeam::Torino, ETeam::InterMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 36, ETeam::Udinese, ETeam::Monza, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 36, ETeam::Venezia, ETeam::Fiorentina, 1722985200000 });

    // Week 37
    matches.push_back({ ELeague::SerieA, "24/25", 37, ETeam::Cagliari, ETeam::Venezia, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 37, ETeam::Fiorentina, ETeam::Bologna, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 37, ETeam::Genoa, ETeam::Atalanta, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 37, ETeam::Verona, ETeam::Como, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 37, ETeam::InterMilan, ETeam::Lazio, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 37, ETeam::Juventus, ETeam::Udinese, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 37, ETeam::Lecce, ETeam::Torino, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 37, ETeam::Monza, ETeam::Empoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 37, ETeam::Parma, ETeam::Napoli, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 37, ETeam::Roma, ETeam::ACMilan, 1722985200000 });

    // Week 38
    matches.push_back({ ELeague::SerieA, "24/25", 38, ETeam::Atalanta, ETeam::Parma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 38, ETeam::Bologna, ETeam::Genoa, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 38, ETeam::Como, ETeam::InterMilan, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 38, ETeam::Empoli, ETeam::Verona, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 38, ETeam::Lazio, ETeam::Lecce, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 38, ETeam::ACMilan, ETeam::Monza, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 38, ETeam::Napoli, ETeam::Cagliari, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 38, ETeam::Torino, ETeam::Roma, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 38, ETeam::Udinese, ETeam::Fiorentina, 1722985200000 });
    matches.push_back({ ELeague::SerieA, "24/25", 38, ETeam::Venezia, ETeam::Juventus, 1722985200000 });

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

void MatchesInitializer::InitLaLiga24_25(PGconn* pg)
{
    // Premier League
    std::vector<Match> matches;
    // Week 1
    matches.push_back({ ELeague::LaLiga, "24/25", 1, ETeam::AthleticBilbao, ETeam::Getafe, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 1, ETeam::RealBetis, ETeam::Girona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 1, ETeam::CeltaVigo, ETeam::Alaves, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 1, ETeam::LasPalmas, ETeam::Sevilla, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 1, ETeam::Osasuna, ETeam::Leganes, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 1, ETeam::Valencia, ETeam::Barcelona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 1, ETeam::RealSociedad, ETeam::RayoVallecano, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 1, ETeam::Mallorca, ETeam::RealMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 1, ETeam::RealValladolid, ETeam::Espanyol, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 1, ETeam::Villareal, ETeam::AtleticoMadrid, 1722985200000 });
    
    // Week 2
    matches.push_back({ ELeague::LaLiga, "24/25", 2, ETeam::CeltaVigo, ETeam::Valencia, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 2, ETeam::Sevilla, ETeam::Villareal, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 2, ETeam::Osasuna, ETeam::Mallorca, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 2, ETeam::Barcelona, ETeam::AthleticBilbao, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 2, ETeam::Getafe, ETeam::RayoVallecano, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 2, ETeam::Espanyol, ETeam::RealSociedad, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 2, ETeam::RealMadrid, ETeam::RealValladolid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 2, ETeam::Leganes, ETeam::LasPalmas, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 2, ETeam::Alaves, ETeam::RealBetis, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 2, ETeam::AtleticoMadrid, ETeam::Girona, 1722985200000 });

    // Week 3
    matches.push_back({ ELeague::LaLiga, "24/25", 3, ETeam::Villareal, ETeam::CeltaVigo, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 3, ETeam::Mallorca, ETeam::Sevilla, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 3, ETeam::RayoVallecano, ETeam::Barcelona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 3, ETeam::RealBetis, ETeam::Getafe, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 3, ETeam::AthleticBilbao, ETeam::Valencia, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 3, ETeam::RealValladolid, ETeam::Leganes, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 3, ETeam::RealSociedad, ETeam::Alaves, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 3, ETeam::AtleticoMadrid, ETeam::Espanyol, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 3, ETeam::Girona, ETeam::Osasuna, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 3, ETeam::LasPalmas, ETeam::RealMadrid, 1722985200000 });

    // Week 4
    matches.push_back({ ELeague::LaLiga, "24/25", 4, ETeam::Barcelona, ETeam::RealValladolid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 4, ETeam::AthleticBilbao, ETeam::AtleticoMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 4, ETeam::Espanyol, ETeam::RayoVallecano, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 4, ETeam::Valencia, ETeam::Villareal, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 4, ETeam::Leganes, ETeam::Mallorca, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 4, ETeam::Alaves, ETeam::LasPalmas, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 4, ETeam::Osasuna, ETeam::CeltaVigo, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 4, ETeam::Sevilla, ETeam::Girona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 4, ETeam::Getafe, ETeam::RealSociedad, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 4, ETeam::RealMadrid, ETeam::RealBetis, 1722985200000 });

    // Week 5
    matches.push_back({ ELeague::LaLiga, "24/25", 5, ETeam::AtleticoMadrid, ETeam::Valencia, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 5, ETeam::RealBetis, ETeam::Leganes, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 5, ETeam::CeltaVigo, ETeam::RealValladolid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 5, ETeam::Mallorca, ETeam::Villareal, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 5, ETeam::LasPalmas, ETeam::AthleticBilbao, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 5, ETeam::Girona, ETeam::Barcelona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 5, ETeam::Sevilla, ETeam::Getafe, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 5, ETeam::RayoVallecano, ETeam::Osasuna, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 5, ETeam::RealSociedad, ETeam::RealMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 5, ETeam::Espanyol, ETeam::Alaves, 1722985200000 });

    // Week 6
    matches.push_back({ ELeague::LaLiga, "24/25", 6, ETeam::AthleticBilbao, ETeam::CeltaVigo, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 6, ETeam::RealBetis, ETeam::Mallorca, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 6, ETeam::Getafe, ETeam::Leganes, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 6, ETeam::Alaves, ETeam::Sevilla, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 6, ETeam::RayoVallecano, ETeam::AtleticoMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 6, ETeam::Villareal, ETeam::Barcelona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 6, ETeam::Valencia, ETeam::Girona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 6, ETeam::RealValladolid, ETeam::RealSociedad, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 6, ETeam::Osasuna, ETeam::LasPalmas, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 6, ETeam::RealMadrid, ETeam::Espanyol, 1722985200000 });

    // Week 7
    matches.push_back({ ELeague::LaLiga, "24/25", 7, ETeam::Barcelona, ETeam::Getafe, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 7, ETeam::Girona, ETeam::RayoVallecano, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 7, ETeam::Mallorca, ETeam::RealSociedad, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 7, ETeam::Sevilla, ETeam::RealValladolid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 7, ETeam::Espanyol, ETeam::Valencia, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 7, ETeam::Leganes, ETeam::AthleticBilbao, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 7, ETeam::CeltaVigo, ETeam::AtleticoMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 7, ETeam::LasPalmas, ETeam::RealBetis, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 7, ETeam::Valencia, ETeam::Osasuna, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 7, ETeam::RealMadrid, ETeam::Alaves, 1722985200000 });

    // Week 8
    matches.push_back({ ELeague::LaLiga, "24/25", 8, ETeam::AthleticBilbao, ETeam::Sevilla, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 8, ETeam::AtleticoMadrid, ETeam::RealMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 8, ETeam::CeltaVigo, ETeam::Girona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 8, ETeam::RealSociedad, ETeam::Valencia, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 8, ETeam::Osasuna, ETeam::Barcelona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 8, ETeam::RealValladolid, ETeam::Mallorca, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 8, ETeam::Villareal, ETeam::LasPalmas, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 8, ETeam::Getafe, ETeam::Alaves, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 8, ETeam::RayoVallecano, ETeam::Leganes, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 8, ETeam::RealBetis, ETeam::Espanyol, 1722985200000 });

    // Week 9
    matches.push_back({ ELeague::LaLiga, "24/25", 9, ETeam::Getafe, ETeam::Osasuna, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 9, ETeam::RealMadrid, ETeam::Villareal, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 9, ETeam::Alaves, ETeam::Barcelona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 9, ETeam::Leganes, ETeam::Valencia, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 9, ETeam::Espanyol, ETeam::Mallorca, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 9, ETeam::Girona, ETeam::AthleticBilbao, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 9, ETeam::RealSociedad, ETeam::AtleticoMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 9, ETeam::Sevilla, ETeam::RealBetis, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 9, ETeam::LasPalmas, ETeam::CeltaVigo, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 9, ETeam::RealValladolid, ETeam::RayoVallecano, 1722985200000 });

    // Week 10
    matches.push_back({ ELeague::LaLiga, "24/25", 10, ETeam::AtleticoMadrid, ETeam::Leganes, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 10, ETeam::Barcelona, ETeam::Sevilla, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 10, ETeam::CeltaVigo, ETeam::RealMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 10, ETeam::Girona, ETeam::RealSociedad, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 10, ETeam::Mallorca, ETeam::RayoVallecano, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 10, ETeam::Alaves, ETeam::RealValladolid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 10, ETeam::Osasuna, ETeam::RealBetis, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 10, ETeam::Villareal, ETeam::Getafe, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 10, ETeam::Valencia, ETeam::LasPalmas, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 10, ETeam::AthleticBilbao, ETeam::Espanyol, 1722985200000 });

    // Week 11
    matches.push_back({ ELeague::LaLiga, "24/25", 11, ETeam::Getafe, ETeam::Valencia, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 11, ETeam::Espanyol, ETeam::Sevilla, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 11, ETeam::Mallorca, ETeam::AthleticBilbao, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 11, ETeam::RealBetis, ETeam::AtleticoMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 11, ETeam::RealMadrid, ETeam::Barcelona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 11, ETeam::Leganes, ETeam::CeltaVigo, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 11, ETeam::LasPalmas, ETeam::Girona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 11, ETeam::RealSociedad, ETeam::Osasuna, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 11, ETeam::RealValladolid, ETeam::Villareal, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 11, ETeam::RayoVallecano, ETeam::Alaves, 1722985200000 });

    // Week 12
    matches.push_back({ ELeague::LaLiga, "24/25", 12, ETeam::AthleticBilbao, ETeam::RealBetis, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 12, ETeam::AtleticoMadrid, ETeam::LasPalmas, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 12, ETeam::CeltaVigo, ETeam::Getafe, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 12, ETeam::Girona, ETeam::Leganes, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 12, ETeam::Osasuna, ETeam::RealValladolid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 12, ETeam::Alaves, ETeam::Mallorca, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 12, ETeam::Villareal, ETeam::RayoVallecano, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 12, ETeam::Valencia, ETeam::RealMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 12, ETeam::Sevilla, ETeam::RealSociedad, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 12, ETeam::Barcelona, ETeam::Espanyol, 1722985200000 });

    // Week 13
    matches.push_back({ ELeague::LaLiga, "24/25", 13, ETeam::RealBetis, ETeam::CeltaVigo, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 13, ETeam::Getafe, ETeam::Girona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 13, ETeam::Leganes, ETeam::Sevilla, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 13, ETeam::Espanyol, ETeam::Valencia, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 13, ETeam::RealValladolid, ETeam::AthleticBilbao, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 13, ETeam::Mallorca, ETeam::AtleticoMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 13, ETeam::RealSociedad, ETeam::Barcelona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 13, ETeam::RealMadrid, ETeam::Osasuna, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 13, ETeam::RayoVallecano, ETeam::LasPalmas, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 13, ETeam::Villareal, ETeam::Alaves, 1722985200000 });

    // Week 14
    matches.push_back({ ELeague::LaLiga, "24/25", 14, ETeam::AthleticBilbao, ETeam::RealSociedad, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 14, ETeam::Getafe, ETeam::RealValladolid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 14, ETeam::Osasuna, ETeam::Villareal, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 14, ETeam::LasPalmas, ETeam::Mallorca, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 14, ETeam::Leganes, ETeam::RealMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 14, ETeam::CeltaVigo, ETeam::Barcelona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 14, ETeam::Valencia, ETeam::RealBetis, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 14, ETeam::Sevilla, ETeam::RayoVallecano, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 14, ETeam::AtleticoMadrid, ETeam::Alaves, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 14, ETeam::Girona, ETeam::Espanyol, 1722985200000 });

    // Week 15
    matches.push_back({ ELeague::LaLiga, "24/25", 15, ETeam::Barcelona, ETeam::LasPalmas, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 15, ETeam::Mallorca, ETeam::Valencia, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 15, ETeam::Alaves, ETeam::Leganes, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 15, ETeam::Espanyol, ETeam::CeltaVigo, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 15, ETeam::RayoVallecano, ETeam::AthleticBilbao, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 15, ETeam::RealValladolid, ETeam::AtleticoMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 15, ETeam::RealSociedad, ETeam::RealBetis, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 15, ETeam::RealMadrid, ETeam::Getafe, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 15, ETeam::Villareal, ETeam::Girona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 15, ETeam::Sevilla, ETeam::Osasuna, 1722985200000 });

    // Week 16
    matches.push_back({ ELeague::LaLiga, "24/25", 16, ETeam::AthleticBilbao, ETeam::Villareal, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 16, ETeam::AtleticoMadrid, ETeam::Sevilla, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 16, ETeam::CeltaVigo, ETeam::Mallorca, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 16, ETeam::Girona, ETeam::RealMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 16, ETeam::LasPalmas, ETeam::RealValladolid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 16, ETeam::Leganes, ETeam::RealSociedad, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 16, ETeam::RealBetis, ETeam::Barcelona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 16, ETeam::Valencia, ETeam::RayoVallecano, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 16, ETeam::Osasuna, ETeam::Alaves, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 16, ETeam::Getafe, ETeam::Espanyol, 1722985200000 });

    // Week 17
    matches.push_back({ ELeague::LaLiga, "24/25", 17, ETeam::AtleticoMadrid, ETeam::Getafe, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 17, ETeam::Barcelona, ETeam::Leganes, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 17, ETeam::RayoVallecano, ETeam::RealMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 17, ETeam::Alaves, ETeam::AthleticBilbao, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 17, ETeam::Espanyol, ETeam::Osasuna, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 17, ETeam::Villareal, ETeam::RealBetis, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 17, ETeam::Sevilla, ETeam::CeltaVigo, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 17, ETeam::Mallorca, ETeam::Girona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 17, ETeam::RealValladolid, ETeam::Valencia, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 17, ETeam::RealSociedad, ETeam::LasPalmas, 1722985200000 });

    // Week 18
    matches.push_back({ ELeague::LaLiga, "24/25", 18, ETeam::RealBetis, ETeam::RayoVallecano, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 18, ETeam::CeltaVigo, ETeam::RealSociedad, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 18, ETeam::Getafe, ETeam::Mallorca, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 18, ETeam::Girona, ETeam::RealValladolid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 18, ETeam::RealMadrid, ETeam::Sevilla, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 18, ETeam::Leganes, ETeam::Villareal, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 18, ETeam::Osasuna, ETeam::AthleticBilbao, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 18, ETeam::Barcelona, ETeam::AtleticoMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 18, ETeam::Valencia, ETeam::Alaves, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 18, ETeam::LasPalmas, ETeam::Espanyol, 1722985200000 });

    // Week 19
    matches.push_back({ ELeague::LaLiga, "24/25", 19, ETeam::AthleticBilbao, ETeam::RealMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 19, ETeam::AtleticoMadrid, ETeam::Osasuna, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 19, ETeam::RealSociedad, ETeam::Villareal, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 19, ETeam::Sevilla, ETeam::Valencia, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 19, ETeam::Alaves, ETeam::Girona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 19, ETeam::Espanyol, ETeam::Leganes, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 19, ETeam::Mallorca, ETeam::Barcelona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 19, ETeam::RealValladolid, ETeam::RealBetis, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 19, ETeam::RayoVallecano, ETeam::CeltaVigo, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 19, ETeam::LasPalmas, ETeam::Getafe, 1722985200000 });

    // Week 20
    matches.push_back({ ELeague::LaLiga, "24/25", 20, ETeam::Girona, ETeam::Sevilla, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 20, ETeam::Osasuna, ETeam::RayoVallecano, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 20, ETeam::Espanyol, ETeam::RealValladolid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 20, ETeam::CeltaVigo, ETeam::AthleticBilbao, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 20, ETeam::Leganes, ETeam::AtleticoMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 20, ETeam::Getafe, ETeam::Barcelona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 20, ETeam::Villareal, ETeam::Mallorca, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 20, ETeam::Valencia, ETeam::RealSociedad, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 20, ETeam::RealMadrid, ETeam::LasPalmas, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 20, ETeam::RealBetis, ETeam::Alaves, 1722985200000 });

    // Week 21
    matches.push_back({ ELeague::LaLiga, "24/25", 21, ETeam::AthleticBilbao, ETeam::Leganes, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 21, ETeam::AtleticoMadrid, ETeam::Villareal, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 21, ETeam::Barcelona, ETeam::Valencia, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 21, ETeam::LasPalmas, ETeam::Osasuna, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 21, ETeam::Alaves, ETeam::CeltaVigo, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 21, ETeam::Mallorca, ETeam::RealBetis, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 21, ETeam::RealSociedad, ETeam::Getafe, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 21, ETeam::RayoVallecano, ETeam::Girona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 21, ETeam::RealValladolid, ETeam::RealMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 21, ETeam::Sevilla, ETeam::Espanyol, 1722985200000 });

    // Week 22
    matches.push_back({ ELeague::LaLiga, "24/25", 22, ETeam::AtleticoMadrid, ETeam::Mallorca, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 22, ETeam::Getafe, ETeam::Sevilla, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 22, ETeam::Girona, ETeam::LasPalmas, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 22, ETeam::Osasuna, ETeam::RealSociedad, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 22, ETeam::Villareal, ETeam::RealValladolid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 22, ETeam::Leganes, ETeam::RayoVallecano, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 22, ETeam::Espanyol, ETeam::RealMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 22, ETeam::RealBetis, ETeam::AthleticBilbao, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 22, ETeam::Valencia, ETeam::CeltaVigo, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 22, ETeam::Barcelona, ETeam::Alaves, 1722985200000 });

    // Week 23
    matches.push_back({ ELeague::LaLiga, "24/25", 23, ETeam::AthleticBilbao, ETeam::Girona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 23, ETeam::Mallorca, ETeam::Osasuna, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 23, ETeam::RayoVallecano, ETeam::RealValladolid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 23, ETeam::LasPalmas, ETeam::Villareal, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 23, ETeam::Alaves, ETeam::Getafe, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 23, ETeam::RealMadrid, ETeam::AtleticoMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 23, ETeam::Sevilla, ETeam::Barcelona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 23, ETeam::CeltaVigo, ETeam::RealBetis, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 23, ETeam::Valencia, ETeam::Leganes, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 23, ETeam::RealSociedad, ETeam::Espanyol, 1722985200000 });

    // Week 24
    matches.push_back({ ELeague::LaLiga, "24/25", 24, ETeam::AtleticoMadrid, ETeam::CeltaVigo, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 24, ETeam::Barcelona, ETeam::RayoVallecano, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 24, ETeam::RealBetis, ETeam::RealSociedad, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 24, ETeam::Osasuna, ETeam::RealMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 24, ETeam::Espanyol, ETeam::AthleticBilbao, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 24, ETeam::Girona, ETeam::Getafe, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 24, ETeam::RealValladolid, ETeam::Sevilla, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 24, ETeam::Villareal, ETeam::Valencia, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 24, ETeam::Mallorca, ETeam::LasPalmas, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 24, ETeam::Leganes, ETeam::Alaves, 1722985200000 });

    // Week 25
    matches.push_back({ ELeague::LaLiga, "24/25", 25, ETeam::AthleticBilbao, ETeam::RealValladolid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 25, ETeam::CeltaVigo, ETeam::Osasuna, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 25, ETeam::RayoVallecano, ETeam::Villareal, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 25, ETeam::Alaves, ETeam::Espanyol, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 25, ETeam::Valencia, ETeam::AtleticoMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 25, ETeam::LasPalmas, ETeam::Barcelona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 25, ETeam::Getafe, ETeam::RealBetis, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 25, ETeam::RealMadrid, ETeam::Girona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 25, ETeam::Sevilla, ETeam::Mallorca, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 25, ETeam::RealSociedad, ETeam::Leganes, 1722985200000 });

    // Week 26
    matches.push_back({ ELeague::LaLiga, "24/25", 26, ETeam::Barcelona, ETeam::RealSociedad, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 26, ETeam::RealBetis, ETeam::RealMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 26, ETeam::Osasuna, ETeam::Valencia, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 26, ETeam::RayoVallecano, ETeam::Sevilla, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 26, ETeam::AtleticoMadrid, ETeam::AthleticBilbao, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 26, ETeam::Girona, ETeam::CeltaVigo, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 26, ETeam::Leganes, ETeam::Getafe, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 26, ETeam::RealValladolid, ETeam::LasPalmas, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 26, ETeam::Mallorca, ETeam::Alaves, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 26, ETeam::Villareal, ETeam::Espanyol, 1722985200000 });

    // Week 27
    matches.push_back({ ELeague::LaLiga, "24/25", 27, ETeam::AthleticBilbao, ETeam::Mallorca, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 27, ETeam::Barcelona, ETeam::Osasuna, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 27, ETeam::RealBetis, ETeam::LasPalmas, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 27, ETeam::CeltaVigo, ETeam::Leganes, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 27, ETeam::RealSociedad, ETeam::Sevilla, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 27, ETeam::Valencia, ETeam::RealValladolid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 27, ETeam::Alaves, ETeam::Villareal, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 27, ETeam::Espanyol, ETeam::Girona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 27, ETeam::Getafe, ETeam::AtleticoMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 27, ETeam::RealMadrid, ETeam::RayoVallecano, 1722985200000 });

    // Week 28
    matches.push_back({ ELeague::LaLiga, "24/25", 28, ETeam::AtleticoMadrid, ETeam::Barcelona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 28, ETeam::Girona, ETeam::Valencia, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 28, ETeam::RayoVallecano, ETeam::RealSociedad, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 28, ETeam::Sevilla, ETeam::AthleticBilbao, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 28, ETeam::Leganes, ETeam::RealBetis, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 28, ETeam::RealValladolid, ETeam::CeltaVigo, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 28, ETeam::Osasuna, ETeam::Getafe, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 28, ETeam::Villareal, ETeam::RealMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 28, ETeam::LasPalmas, ETeam::Alaves, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 28, ETeam::Mallorca, ETeam::Espanyol, 1722985200000 });

    // Week 29
    matches.push_back({ ELeague::LaLiga, "24/25", 29, ETeam::AthleticBilbao, ETeam::Osasuna, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 29, ETeam::Barcelona, ETeam::Girona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 29, ETeam::RealBetis, ETeam::Sevilla, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 29, ETeam::CeltaVigo, ETeam::LasPalmas, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 29, ETeam::Getafe, ETeam::Villareal, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 29, ETeam::RealSociedad, ETeam::RealValladolid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 29, ETeam::Alaves, ETeam::RayoVallecano, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 29, ETeam::Espanyol, ETeam::AtleticoMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 29, ETeam::Valencia, ETeam::Mallorca, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 29, ETeam::RealMadrid, ETeam::Leganes, 1722985200000 });

    // Week 30
    matches.push_back({ ELeague::LaLiga, "24/25", 30, ETeam::Barcelona, ETeam::RealBetis, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 30, ETeam::RealMadrid, ETeam::Valencia, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 30, ETeam::LasPalmas, ETeam::RealSociedad, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 30, ETeam::Leganes, ETeam::Osasuna, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 30, ETeam::Villareal, ETeam::AthleticBilbao, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 30, ETeam::Sevilla, ETeam::AtleticoMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 30, ETeam::Mallorca, ETeam::CeltaVigo, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 30, ETeam::RealValladolid, ETeam::Getafe, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 30, ETeam::Girona, ETeam::Alaves, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 30, ETeam::RayoVallecano, ETeam::Espanyol, 1722985200000 });

    // Week 31
    matches.push_back({ ELeague::LaLiga, "24/25", 31, ETeam::AthleticBilbao, ETeam::RayoVallecano, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 31, ETeam::AtleticoMadrid, ETeam::RealValladolid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 31, ETeam::RealBetis, ETeam::Villareal, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 31, ETeam::Getafe, ETeam::LasPalmas, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 31, ETeam::Alaves, ETeam::RealMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 31, ETeam::Leganes, ETeam::Barcelona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 31, ETeam::Osasuna, ETeam::Girona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 31, ETeam::RealSociedad, ETeam::Mallorca, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 31, ETeam::Valencia, ETeam::Sevilla, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 31, ETeam::CeltaVigo, ETeam::Espanyol, 1722985200000 });

    // Week 32
    matches.push_back({ ELeague::LaLiga, "24/25", 32, ETeam::Barcelona, ETeam::CeltaVigo, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 32, ETeam::RayoVallecano, ETeam::Valencia, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 32, ETeam::Espanyol, ETeam::Getafe, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 32, ETeam::RealMadrid, ETeam::AthleticBilbao, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 32, ETeam::LasPalmas, ETeam::AtleticoMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 32, ETeam::Girona, ETeam::RealBetis, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 32, ETeam::RealValladolid, ETeam::Osasuna, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 32, ETeam::Villareal, ETeam::RealSociedad, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 32, ETeam::Sevilla, ETeam::Alaves, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 32, ETeam::Mallorca, ETeam::Leganes, 1722985200000 });

    // Week 33
    matches.push_back({ ELeague::LaLiga, "24/25", 33, ETeam::AthleticBilbao, ETeam::LasPalmas, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 33, ETeam::AtleticoMadrid, ETeam::RayoVallecano, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 33, ETeam::Barcelona, ETeam::Mallorca, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 33, ETeam::RealBetis, ETeam::RealValladolid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 33, ETeam::CeltaVigo, ETeam::Villareal, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 33, ETeam::Getafe, ETeam::RealMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 33, ETeam::Osasuna, ETeam::Sevilla, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 33, ETeam::Alaves, ETeam::RealSociedad, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 33, ETeam::Leganes, ETeam::Girona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 33, ETeam::Valencia, ETeam::Espanyol, 1722985200000 });

    // Week 34
    matches.push_back({ ELeague::LaLiga, "24/25", 34, ETeam::Girona, ETeam::Mallorca, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 34, ETeam::LasPalmas, ETeam::Valencia, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 34, ETeam::Alaves, ETeam::AtleticoMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 34, ETeam::Espanyol, ETeam::RealBetis, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 34, ETeam::RealSociedad, ETeam::AthleticBilbao, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 34, ETeam::RealValladolid, ETeam::Barcelona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 34, ETeam::RealMadrid, ETeam::CeltaVigo, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 34, ETeam::RayoVallecano, ETeam::Getafe, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 34, ETeam::Villareal, ETeam::Osasuna, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 34, ETeam::Sevilla, ETeam::Leganes, 1722985200000 });

    // Week 35
    matches.push_back({ ELeague::LaLiga, "24/25", 35, ETeam::AtleticoMadrid, ETeam::RealSociedad, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 35, ETeam::Barcelona, ETeam::RealMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 35, ETeam::RealBetis, ETeam::Osasuna, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 35, ETeam::CeltaVigo, ETeam::Sevilla, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 35, ETeam::Girona, ETeam::Villareal, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 35, ETeam::Mallorca, ETeam::RealValladolid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 35, ETeam::LasPalmas, ETeam::RayoVallecano, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 35, ETeam::Valencia, ETeam::Getafe, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 35, ETeam::AthleticBilbao, ETeam::Alaves, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 35, ETeam::Leganes, ETeam::Espanyol, 1722985200000 });

    // Week 36
    matches.push_back({ ELeague::LaLiga, "24/25", 36, ETeam::Alaves, ETeam::Valencia, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 36, ETeam::Espanyol, ETeam::Barcelona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 36, ETeam::Getafe, ETeam::AthleticBilbao, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 36, ETeam::Osasuna, ETeam::AtleticoMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 36, ETeam::RayoVallecano, ETeam::RealBetis, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 36, ETeam::RealSociedad, ETeam::CeltaVigo, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 36, ETeam::RealValladolid, ETeam::Girona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 36, ETeam::RealMadrid, ETeam::Mallorca, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 36, ETeam::Sevilla, ETeam::LasPalmas, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 36, ETeam::Villareal, ETeam::Leganes, 1722985200000 });

    // Week 37
    matches.push_back({ ELeague::LaLiga, "24/25", 37, ETeam::AtleticoMadrid, ETeam::RealBetis, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 37, ETeam::Barcelona, ETeam::Villareal, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 37, ETeam::CeltaVigo, ETeam::RayoVallecano, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 37, ETeam::Valencia, ETeam::AthleticBilbao, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 37, ETeam::Mallorca, ETeam::Getafe, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 37, ETeam::RealSociedad, ETeam::Girona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 37, ETeam::Sevilla, ETeam::RealMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 37, ETeam::RealValladolid, ETeam::Alaves, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 37, ETeam::LasPalmas, ETeam::Leganes, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 37, ETeam::Osasuna, ETeam::Espanyol, 1722985200000 });

    // Week 38
    matches.push_back({ ELeague::LaLiga, "24/25", 38, ETeam::AthleticBilbao, ETeam::Barcelona, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 38, ETeam::RealBetis, ETeam::Valencia, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 38, ETeam::RealMadrid, ETeam::RealSociedad, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 38, ETeam::Alaves, ETeam::Osasuna, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 38, ETeam::Leganes, ETeam::RealValladolid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 38, ETeam::Espanyol, ETeam::LasPalmas, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 38, ETeam::Girona, ETeam::AtleticoMadrid, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 38, ETeam::Getafe, ETeam::CeltaVigo, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 38, ETeam::RayoVallecano, ETeam::Mallorca, 1722985200000 });
    matches.push_back({ ELeague::LaLiga, "24/25", 38, ETeam::Villareal, ETeam::Sevilla, 1722985200000 });

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

void MatchesInitializer::InitPremierLeague24_25(PGconn* pg)
{
    // Premier League
    std::vector<Match> matches;
    // Week 1
    matches.push_back({ ELeague::PremierLeague, "24/25", 1, ETeam::ManchesterUnited, ETeam::Fulham, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 1, ETeam::IpswichTown, ETeam::Liverpool, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 1, ETeam::Arsenal, ETeam::Wolverhampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 1, ETeam::Everton, ETeam::BrightonAndHoveAlbion, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 1, ETeam::NewcastleUnited, ETeam::Southampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 1, ETeam::NottinghamForest, ETeam::AFCBournemouth, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 1, ETeam::WestHamUnited, ETeam::AstonVilla, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 1, ETeam::Brentford, ETeam::CrystalPalace, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 1, ETeam::Chelsea, ETeam::ManchesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 1, ETeam::LeicesterCity, ETeam::TottenhamHotspur, 1722985200000 });

    // Week 2
    matches.push_back({ ELeague::PremierLeague, "24/25", 2, ETeam::BrightonAndHoveAlbion, ETeam::ManchesterUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 2, ETeam::CrystalPalace, ETeam::WestHamUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 2, ETeam::Fulham, ETeam::LeicesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 2, ETeam::ManchesterCity, ETeam::IpswichTown, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 2, ETeam::Southampton, ETeam::NottinghamForest, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 2, ETeam::TottenhamHotspur, ETeam::Everton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 2, ETeam::AstonVilla, ETeam::Arsenal, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 2, ETeam::AFCBournemouth, ETeam::NewcastleUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 2, ETeam::Wolverhampton, ETeam::Chelsea, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 2, ETeam::Liverpool, ETeam::Brentford, 1722985200000 });

    // Week 3
    matches.push_back({ ELeague::PremierLeague, "24/25", 3, ETeam::Arsenal, ETeam::BrightonAndHoveAlbion, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 3, ETeam::Brentford, ETeam::Southampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 3, ETeam::Everton, ETeam::AFCBournemouth, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 3, ETeam::IpswichTown, ETeam::Fulham, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 3, ETeam::LeicesterCity, ETeam::AstonVilla, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 3, ETeam::NottinghamForest, ETeam::Wolverhampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 3, ETeam::WestHamUnited, ETeam::ManchesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 3, ETeam::Chelsea, ETeam::CrystalPalace, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 3, ETeam::NewcastleUnited, ETeam::TottenhamHotspur, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 3, ETeam::ManchesterUnited, ETeam::Liverpool, 1722985200000 });

    // Week 4
    matches.push_back({ ELeague::PremierLeague, "24/25", 4, ETeam::Southampton, ETeam::ManchesterUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 4, ETeam::BrightonAndHoveAlbion, ETeam::IpswichTown, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 4, ETeam::CrystalPalace, ETeam::LeicesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 4, ETeam::Fulham, ETeam::WestHamUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 4, ETeam::Liverpool, ETeam::NottinghamForest, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 4, ETeam::ManchesterCity, ETeam::Brentford, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 4, ETeam::AstonVilla, ETeam::Everton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 4, ETeam::AFCBournemouth, ETeam::Chelsea, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 4, ETeam::TottenhamHotspur, ETeam::Arsenal, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 4, ETeam::Wolverhampton, ETeam::NewcastleUnited, 1722985200000 });

    // Week 5
    matches.push_back({ ELeague::PremierLeague, "24/25", 5, ETeam::WestHamUnited, ETeam::Chelsea, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 5, ETeam::AstonVilla, ETeam::Wolverhampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 5, ETeam::Fulham, ETeam::NewcastleUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 5, ETeam::LeicesterCity, ETeam::Everton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 5, ETeam::Liverpool, ETeam::AFCBournemouth, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 5, ETeam::Southampton, ETeam::IpswichTown, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 5, ETeam::TottenhamHotspur, ETeam::Brentford, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 5, ETeam::CrystalPalace, ETeam::ManchesterUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 5, ETeam::Liverpool, ETeam::AFCBournemouth, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 5, ETeam::BrightonAndHoveAlbion, ETeam::NottinghamForest, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 5, ETeam::ManchesterCity, ETeam::Arsenal, 1722985200000 });

    // Week 6
    matches.push_back({ ELeague::PremierLeague, "24/25", 6, ETeam::NewcastleUnited, ETeam::ManchesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 6, ETeam::Arsenal, ETeam::LeicesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 6, ETeam::Brentford, ETeam::WestHamUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 6, ETeam::Chelsea, ETeam::BrightonAndHoveAlbion, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 6, ETeam::Everton, ETeam::CrystalPalace, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 6, ETeam::NottinghamForest, ETeam::Fulham, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 6, ETeam::Wolverhampton, ETeam::Liverpool, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 6, ETeam::IpswichTown, ETeam::AstonVilla, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 6, ETeam::ManchesterUnited, ETeam::TottenhamHotspur, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 6, ETeam::AFCBournemouth, ETeam::Southampton, 1722985200000 });

    // Week 7
    matches.push_back({ ELeague::PremierLeague, "24/25", 7, ETeam::Arsenal, ETeam::Southampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 7, ETeam::AstonVilla, ETeam::ManchesterUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 7, ETeam::Brentford, ETeam::Wolverhampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 7, ETeam::BrightonAndHoveAlbion, ETeam::TottenhamHotspur, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 7, ETeam::Chelsea, ETeam::NottinghamForest, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 7, ETeam::CrystalPalace, ETeam::Liverpool, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 7, ETeam::Everton, ETeam::NewcastleUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 7, ETeam::LeicesterCity, ETeam::AFCBournemouth, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 7, ETeam::ManchesterCity, ETeam::Fulham, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 7, ETeam::WestHamUnited, ETeam::IpswichTown, 1722985200000 });

    // Week 8
    matches.push_back({ ELeague::PremierLeague, "24/25", 8, ETeam::AFCBournemouth, ETeam::Arsenal, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 8, ETeam::Fulham, ETeam::AstonVilla, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 8, ETeam::IpswichTown, ETeam::Everton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 8, ETeam::Liverpool, ETeam::Chelsea, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 8, ETeam::ManchesterUnited, ETeam::Brentford, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 8, ETeam::NewcastleUnited, ETeam::BrightonAndHoveAlbion, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 8, ETeam::NottinghamForest, ETeam::CrystalPalace, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 8, ETeam::Southampton, ETeam::LeicesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 8, ETeam::TottenhamHotspur, ETeam::WestHamUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 8, ETeam::Wolverhampton, ETeam::ManchesterCity, 1722985200000 });

    // Week 9
    matches.push_back({ ELeague::PremierLeague, "24/25", 9, ETeam::Arsenal, ETeam::Liverpool, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 9, ETeam::AstonVilla, ETeam::AFCBournemouth, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 9, ETeam::Brentford, ETeam::IpswichTown, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 9, ETeam::BrightonAndHoveAlbion, ETeam::Wolverhampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 9, ETeam::Chelsea, ETeam::NewcastleUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 9, ETeam::CrystalPalace, ETeam::TottenhamHotspur, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 9, ETeam::Everton, ETeam::Fulham, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 9, ETeam::LeicesterCity, ETeam::NottinghamForest, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 9, ETeam::ManchesterCity, ETeam::Southampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 9, ETeam::WestHamUnited, ETeam::ManchesterUnited, 1722985200000 });

    // Week 10
    matches.push_back({ ELeague::PremierLeague, "24/25", 10, ETeam::AFCBournemouth, ETeam::ManchesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 10, ETeam::Fulham, ETeam::Brentford, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 10, ETeam::IpswichTown, ETeam::LeicesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 10, ETeam::Liverpool, ETeam::BrightonAndHoveAlbion, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 10, ETeam::ManchesterUnited, ETeam::Chelsea, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 10, ETeam::NewcastleUnited, ETeam::Arsenal, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 10, ETeam::NottinghamForest, ETeam::WestHamUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 10, ETeam::Southampton, ETeam::Everton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 10, ETeam::TottenhamHotspur, ETeam::AstonVilla, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 10, ETeam::Wolverhampton, ETeam::CrystalPalace, 1722985200000 });

    // Week 11
    matches.push_back({ ELeague::PremierLeague, "24/25", 11, ETeam::Brentford, ETeam::AFCBournemouth, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 11, ETeam::BrightonAndHoveAlbion, ETeam::ManchesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 11, ETeam::Chelsea, ETeam::Arsenal, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 11, ETeam::CrystalPalace, ETeam::Fulham, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 11, ETeam::Liverpool, ETeam::AstonVilla, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 11, ETeam::ManchesterUnited, ETeam::LeicesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 11, ETeam::NottinghamForest, ETeam::NewcastleUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 11, ETeam::TottenhamHotspur, ETeam::IpswichTown, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 11, ETeam::WestHamUnited, ETeam::Everton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 11, ETeam::Wolverhampton, ETeam::Southampton, 1722985200000 });

    // Week 12
    matches.push_back({ ELeague::PremierLeague, "24/25", 12, ETeam::AFCBournemouth, ETeam::BrightonAndHoveAlbion, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 12, ETeam::Arsenal, ETeam::NottinghamForest, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 12, ETeam::AstonVilla, ETeam::CrystalPalace, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 12, ETeam::Everton, ETeam::Brentford, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 12, ETeam::Fulham, ETeam::Wolverhampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 12, ETeam::IpswichTown, ETeam::ManchesterUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 12, ETeam::LeicesterCity, ETeam::Chelsea, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 12, ETeam::ManchesterCity, ETeam::TottenhamHotspur, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 12, ETeam::NewcastleUnited, ETeam::WestHamUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 12, ETeam::Southampton, ETeam::Liverpool, 1722985200000 });

    // Week 13
    matches.push_back({ ELeague::PremierLeague, "24/25", 13, ETeam::Brentford, ETeam::LeicesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 13, ETeam::BrightonAndHoveAlbion, ETeam::Southampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 13, ETeam::Chelsea, ETeam::AstonVilla, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 13, ETeam::CrystalPalace, ETeam::NewcastleUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 13, ETeam::Liverpool, ETeam::ManchesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 13, ETeam::ManchesterUnited, ETeam::Everton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 13, ETeam::NottinghamForest, ETeam::IpswichTown, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 13, ETeam::TottenhamHotspur, ETeam::Fulham, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 13, ETeam::WestHamUnited, ETeam::Arsenal, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 13, ETeam::Wolverhampton, ETeam::AFCBournemouth, 1722985200000 });

    // Week 14
    matches.push_back({ ELeague::PremierLeague, "24/25", 14, ETeam::AFCBournemouth, ETeam::TottenhamHotspur, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 14, ETeam::Arsenal, ETeam::ManchesterUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 14, ETeam::AstonVilla, ETeam::Brentford, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 14, ETeam::Everton, ETeam::Wolverhampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 14, ETeam::Fulham, ETeam::BrightonAndHoveAlbion, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 14, ETeam::IpswichTown, ETeam::CrystalPalace, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 14, ETeam::LeicesterCity, ETeam::WestHamUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 14, ETeam::ManchesterCity, ETeam::NottinghamForest, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 14, ETeam::NewcastleUnited, ETeam::Liverpool, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 14, ETeam::Southampton, ETeam::Chelsea, 1722985200000 });

    // Week 15
    matches.push_back({ ELeague::PremierLeague, "24/25", 15, ETeam::AstonVilla, ETeam::Southampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 15, ETeam::Brentford, ETeam::NewcastleUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 15, ETeam::CrystalPalace, ETeam::ManchesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 15, ETeam::Everton, ETeam::Liverpool, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 15, ETeam::Fulham, ETeam::Arsenal, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 15, ETeam::IpswichTown, ETeam::AFCBournemouth, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 15, ETeam::LeicesterCity, ETeam::BrightonAndHoveAlbion, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 15, ETeam::ManchesterUnited, ETeam::NottinghamForest, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 15, ETeam::TottenhamHotspur, ETeam::Chelsea, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 15, ETeam::WestHamUnited, ETeam::Wolverhampton, 1722985200000 });

    // Week 16
    matches.push_back({ ELeague::PremierLeague, "24/25", 16, ETeam::AFCBournemouth, ETeam::WestHamUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 16, ETeam::Arsenal, ETeam::Everton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 16, ETeam::BrightonAndHoveAlbion, ETeam::CrystalPalace, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 16, ETeam::Chelsea, ETeam::Brentford, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 16, ETeam::Liverpool, ETeam::Fulham, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 16, ETeam::ManchesterCity, ETeam::ManchesterUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 16, ETeam::NewcastleUnited, ETeam::LeicesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 16, ETeam::NottinghamForest, ETeam::AstonVilla, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 16, ETeam::Southampton, ETeam::TottenhamHotspur, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 16, ETeam::Wolverhampton, ETeam::IpswichTown, 1722985200000 });

    // Week 17
    matches.push_back({ ELeague::PremierLeague, "24/25", 17, ETeam::AstonVilla, ETeam::ManchesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 17, ETeam::Brentford, ETeam::NottinghamForest, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 17, ETeam::CrystalPalace, ETeam::Arsenal, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 17, ETeam::Everton, ETeam::Chelsea, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 17, ETeam::Fulham, ETeam::Southampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 17, ETeam::IpswichTown, ETeam::NewcastleUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 17, ETeam::LeicesterCity, ETeam::Wolverhampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 17, ETeam::ManchesterUnited, ETeam::AFCBournemouth, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 17, ETeam::TottenhamHotspur, ETeam::Liverpool, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 17, ETeam::WestHamUnited, ETeam::BrightonAndHoveAlbion, 1722985200000 });

    // Week 18
    matches.push_back({ ELeague::PremierLeague, "24/25", 18, ETeam::AFCBournemouth, ETeam::CrystalPalace, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 18, ETeam::Arsenal, ETeam::IpswichTown, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 18, ETeam::BrightonAndHoveAlbion, ETeam::Arsenal, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 18, ETeam::Chelsea, ETeam::Fulham, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 18, ETeam::Liverpool, ETeam::LeicesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 18, ETeam::ManchesterCity, ETeam::Everton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 18, ETeam::NewcastleUnited, ETeam::AstonVilla, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 18, ETeam::NottinghamForest, ETeam::TottenhamHotspur, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 18, ETeam::Southampton, ETeam::WestHamUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 18, ETeam::Wolverhampton, ETeam::ManchesterUnited, 1722985200000 });

    // Week 19
    matches.push_back({ ELeague::PremierLeague, "24/25", 19, ETeam::AstonVilla, ETeam::BrightonAndHoveAlbion, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 19, ETeam::Brentford, ETeam::Arsenal, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 19, ETeam::CrystalPalace, ETeam::Southampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 19, ETeam::Everton, ETeam::NottinghamForest, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 19, ETeam::Fulham, ETeam::AFCBournemouth, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 19, ETeam::IpswichTown, ETeam::Chelsea, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 19, ETeam::LeicesterCity, ETeam::ManchesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 19, ETeam::ManchesterUnited, ETeam::NewcastleUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 19, ETeam::TottenhamHotspur, ETeam::Wolverhampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 19, ETeam::WestHamUnited, ETeam::Liverpool, 1722985200000 });

    // Week 20
    matches.push_back({ ELeague::PremierLeague, "24/25", 20, ETeam::AFCBournemouth, ETeam::Everton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 20, ETeam::AstonVilla, ETeam::LeicesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 20, ETeam::BrightonAndHoveAlbion, ETeam::Arsenal, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 20, ETeam::CrystalPalace, ETeam::Chelsea, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 20, ETeam::Fulham, ETeam::IpswichTown, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 20, ETeam::Liverpool, ETeam::ManchesterUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 20, ETeam::ManchesterCity, ETeam::WestHamUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 20, ETeam::Southampton, ETeam::Brentford, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 20, ETeam::TottenhamHotspur, ETeam::NewcastleUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 20, ETeam::Wolverhampton, ETeam::NottinghamForest, 1722985200000 });

    // Week 21
    matches.push_back({ ELeague::PremierLeague, "24/25", 21, ETeam::Arsenal, ETeam::TottenhamHotspur, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 21, ETeam::Brentford, ETeam::ManchesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 21, ETeam::Everton, ETeam::AstonVilla, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 21, ETeam::IpswichTown, ETeam::BrightonAndHoveAlbion, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 21, ETeam::LeicesterCity, ETeam::CrystalPalace, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 21, ETeam::NottinghamForest, ETeam::Liverpool, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 21, ETeam::WestHamUnited, ETeam::Fulham, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 21, ETeam::Chelsea, ETeam::AFCBournemouth, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 21, ETeam::NewcastleUnited, ETeam::Wolverhampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 21, ETeam::ManchesterUnited, ETeam::Southampton, 1722985200000 });

    // Week 22
    matches.push_back({ ELeague::PremierLeague, "24/25", 22, ETeam::Arsenal, ETeam::AstonVilla, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 22, ETeam::Brentford, ETeam::Liverpool, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 22, ETeam::Chelsea, ETeam::Wolverhampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 22, ETeam::Everton, ETeam::TottenhamHotspur, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 22, ETeam::IpswichTown, ETeam::ManchesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 22, ETeam::LeicesterCity, ETeam::Fulham, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 22, ETeam::ManchesterUnited, ETeam::BrightonAndHoveAlbion, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 22, ETeam::NewcastleUnited, ETeam::AFCBournemouth, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 22, ETeam::NottinghamForest, ETeam::Southampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 22, ETeam::WestHamUnited, ETeam::CrystalPalace, 1722985200000 });

    // Week 23
    matches.push_back({ ELeague::PremierLeague, "24/25", 23, ETeam::AFCBournemouth, ETeam::NottinghamForest, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 23, ETeam::AstonVilla, ETeam::WestHamUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 23, ETeam::BrightonAndHoveAlbion, ETeam::Everton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 23, ETeam::CrystalPalace, ETeam::Brentford, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 23, ETeam::Fulham, ETeam::ManchesterUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 23, ETeam::Liverpool, ETeam::IpswichTown, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 23, ETeam::ManchesterCity, ETeam::Chelsea, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 23, ETeam::Southampton, ETeam::NewcastleUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 23, ETeam::TottenhamHotspur, ETeam::LeicesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 23, ETeam::Wolverhampton, ETeam::Arsenal, 1722985200000 });

    // Week 24
    matches.push_back({ ELeague::PremierLeague, "24/25", 24, ETeam::AFCBournemouth, ETeam::Liverpool, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 24, ETeam::Arsenal, ETeam::ManchesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 24, ETeam::Brentford, ETeam::TottenhamHotspur, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 24, ETeam::Chelsea, ETeam::WestHamUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 24, ETeam::Everton, ETeam::LeicesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 24, ETeam::IpswichTown, ETeam::Southampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 24, ETeam::ManchesterUnited, ETeam::CrystalPalace, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 24, ETeam::NewcastleUnited, ETeam::Fulham, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 24, ETeam::NottinghamForest, ETeam::BrightonAndHoveAlbion, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 24, ETeam::Wolverhampton, ETeam::AstonVilla, 1722985200000 });

    // Week 25
    matches.push_back({ ELeague::PremierLeague, "24/25", 25, ETeam::AstonVilla, ETeam::IpswichTown, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 25, ETeam::BrightonAndHoveAlbion, ETeam::Chelsea, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 25, ETeam::CrystalPalace, ETeam::Everton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 25, ETeam::Fulham, ETeam::NottinghamForest, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 25, ETeam::LeicesterCity, ETeam::Arsenal, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 25, ETeam::Liverpool, ETeam::Wolverhampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 25, ETeam::ManchesterCity, ETeam::NewcastleUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 25, ETeam::Southampton, ETeam::AFCBournemouth, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 25, ETeam::TottenhamHotspur, ETeam::ManchesterUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 25, ETeam::WestHamUnited, ETeam::Brentford, 1722985200000 });

    // Week 26
    matches.push_back({ ELeague::PremierLeague, "24/25", 26, ETeam::AFCBournemouth, ETeam::Wolverhampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 26, ETeam::Arsenal, ETeam::WestHamUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 26, ETeam::AstonVilla, ETeam::Chelsea, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 26, ETeam::Everton, ETeam::ManchesterUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 26, ETeam::Fulham, ETeam::CrystalPalace, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 26, ETeam::IpswichTown, ETeam::TottenhamHotspur, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 26, ETeam::LeicesterCity, ETeam::Brentford, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 26, ETeam::ManchesterCity, ETeam::Liverpool, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 26, ETeam::NewcastleUnited, ETeam::NottinghamForest, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 26, ETeam::Southampton, ETeam::BrightonAndHoveAlbion, 1722985200000 });

    // Week 27
    matches.push_back({ ELeague::PremierLeague, "24/25", 27, ETeam::Brentford, ETeam::Everton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 27, ETeam::BrightonAndHoveAlbion, ETeam::AFCBournemouth, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 27, ETeam::NottinghamForest, ETeam::Arsenal, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 27, ETeam::TottenhamHotspur, ETeam::ManchesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 27, ETeam::WestHamUnited, ETeam::LeicesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 27, ETeam::Wolverhampton, ETeam::Fulham, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 27, ETeam::CrystalPalace, ETeam::AstonVilla, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 27, ETeam::Chelsea, ETeam::Southampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 27, ETeam::Liverpool, ETeam::NewcastleUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 27, ETeam::ManchesterUnited, ETeam::IpswichTown, 1722985200000 });

    // Week 28
    matches.push_back({ ELeague::PremierLeague, "24/25", 28, ETeam::Brentford, ETeam::AstonVilla, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 28, ETeam::BrightonAndHoveAlbion, ETeam::Fulham, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 28, ETeam::Chelsea, ETeam::LeicesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 28, ETeam::CrystalPalace, ETeam::IpswichTown, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 28, ETeam::Liverpool, ETeam::Southampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 28, ETeam::ManchesterUnited, ETeam::Arsenal, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 28, ETeam::NottinghamForest, ETeam::ManchesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 28, ETeam::TottenhamHotspur, ETeam::AFCBournemouth, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 28, ETeam::WestHamUnited, ETeam::NewcastleUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 28, ETeam::Wolverhampton, ETeam::Everton, 1722985200000 });

    // Week 29
    matches.push_back({ ELeague::PremierLeague, "24/25", 29, ETeam::AFCBournemouth, ETeam::Brentford, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 29, ETeam::Arsenal, ETeam::Chelsea, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 29, ETeam::AstonVilla, ETeam::Liverpool, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 29, ETeam::Everton, ETeam::WestHamUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 29, ETeam::Fulham, ETeam::TottenhamHotspur, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 29, ETeam::IpswichTown, ETeam::NottinghamForest, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 29, ETeam::LeicesterCity, ETeam::ManchesterUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 29, ETeam::ManchesterCity, ETeam::BrightonAndHoveAlbion, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 29, ETeam::NewcastleUnited, ETeam::CrystalPalace, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 29, ETeam::Southampton, ETeam::Wolverhampton, 1722985200000 });

    // Week 30
    matches.push_back({ ELeague::PremierLeague, "24/25", 30, ETeam::AFCBournemouth, ETeam::IpswichTown, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 30, ETeam::Arsenal, ETeam::Fulham, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 30, ETeam::BrightonAndHoveAlbion, ETeam::AstonVilla, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 30, ETeam::NottinghamForest, ETeam::ManchesterUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 30, ETeam::Wolverhampton, ETeam::WestHamUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 30, ETeam::Chelsea, ETeam::TottenhamHotspur, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 30, ETeam::ManchesterCity, ETeam::LeicesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 30, ETeam::NewcastleUnited, ETeam::Brentford, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 30, ETeam::Southampton, ETeam::CrystalPalace, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 30, ETeam::Liverpool, ETeam::Everton, 1722985200000 });

    // Week 31
    matches.push_back({ ELeague::PremierLeague, "24/25", 31, ETeam::AstonVilla, ETeam::NottinghamForest, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 31, ETeam::Brentford, ETeam::Chelsea, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 31, ETeam::CrystalPalace, ETeam::BrightonAndHoveAlbion, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 31, ETeam::Everton, ETeam::Arsenal, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 31, ETeam::Fulham, ETeam::Liverpool, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 31, ETeam::IpswichTown, ETeam::Wolverhampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 31, ETeam::LeicesterCity, ETeam::NewcastleUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 31, ETeam::ManchesterUnited, ETeam::ManchesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 31, ETeam::TottenhamHotspur, ETeam::Southampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 31, ETeam::WestHamUnited, ETeam::AFCBournemouth, 1722985200000 });

    // Week 32
    matches.push_back({ ELeague::PremierLeague, "24/25", 32, ETeam::AFCBournemouth, ETeam::Fulham, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 32, ETeam::Arsenal, ETeam::Brentford, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 32, ETeam::BrightonAndHoveAlbion, ETeam::LeicesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 32, ETeam::Chelsea, ETeam::IpswichTown, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 32, ETeam::Liverpool, ETeam::WestHamUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 32, ETeam::ManchesterCity, ETeam::CrystalPalace, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 32, ETeam::NewcastleUnited, ETeam::ManchesterUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 32, ETeam::NottinghamForest, ETeam::Everton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 32, ETeam::Southampton, ETeam::AstonVilla, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 32, ETeam::Wolverhampton, ETeam::TottenhamHotspur, 1722985200000 });

    // Week 33
    matches.push_back({ ELeague::PremierLeague, "24/25", 33, ETeam::AstonVilla, ETeam::NewcastleUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 33, ETeam::Brentford, ETeam::BrightonAndHoveAlbion, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 33, ETeam::CrystalPalace, ETeam::AFCBournemouth, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 33, ETeam::Everton, ETeam::ManchesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 33, ETeam::Fulham, ETeam::Chelsea, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 33, ETeam::IpswichTown, ETeam::Arsenal, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 33, ETeam::LeicesterCity, ETeam::Liverpool, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 33, ETeam::ManchesterUnited, ETeam::Wolverhampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 33, ETeam::TottenhamHotspur, ETeam::NottinghamForest, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 33, ETeam::WestHamUnited, ETeam::Southampton, 1722985200000 });

    // Week 34
    matches.push_back({ ELeague::PremierLeague, "24/25", 34, ETeam::AFCBournemouth, ETeam::ManchesterUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 34, ETeam::Arsenal, ETeam::CrystalPalace, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 34, ETeam::BrightonAndHoveAlbion, ETeam::WestHamUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 34, ETeam::Chelsea, ETeam::Everton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 34, ETeam::Liverpool, ETeam::TottenhamHotspur, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 34, ETeam::ManchesterCity, ETeam::AstonVilla, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 34, ETeam::NewcastleUnited, ETeam::IpswichTown, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 34, ETeam::NottinghamForest, ETeam::Brentford, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 34, ETeam::Southampton, ETeam::Fulham, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 34, ETeam::Wolverhampton, ETeam::LeicesterCity, 1722985200000 });

    // Week 35
    matches.push_back({ ELeague::PremierLeague, "24/25", 35, ETeam::Arsenal, ETeam::AFCBournemouth, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 35, ETeam::AstonVilla, ETeam::Fulham, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 35, ETeam::Brentford, ETeam::ManchesterUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 35, ETeam::BrightonAndHoveAlbion, ETeam::NewcastleUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 35, ETeam::Chelsea, ETeam::Liverpool, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 35, ETeam::CrystalPalace, ETeam::NottinghamForest, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 35, ETeam::Everton, ETeam::IpswichTown, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 35, ETeam::LeicesterCity, ETeam::Southampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 35, ETeam::ManchesterCity, ETeam::Wolverhampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 35, ETeam::WestHamUnited, ETeam::TottenhamHotspur, 1722985200000 });

    // Week 36
    matches.push_back({ ELeague::PremierLeague, "24/25", 36, ETeam::AFCBournemouth, ETeam::AstonVilla, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 36, ETeam::Fulham, ETeam::Everton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 36, ETeam::IpswichTown, ETeam::Brentford, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 36, ETeam::Liverpool, ETeam::Arsenal, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 36, ETeam::ManchesterUnited, ETeam::WestHamUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 36, ETeam::NewcastleUnited, ETeam::Chelsea, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 36, ETeam::NottinghamForest, ETeam::LeicesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 36, ETeam::Southampton, ETeam::ManchesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 36, ETeam::TottenhamHotspur, ETeam::CrystalPalace, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 36, ETeam::Wolverhampton, ETeam::BrightonAndHoveAlbion, 1722985200000 });

    // Week 37
    matches.push_back({ ELeague::PremierLeague, "24/25", 37, ETeam::Arsenal, ETeam::NewcastleUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 37, ETeam::AstonVilla, ETeam::TottenhamHotspur, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 37, ETeam::Brentford, ETeam::Fulham, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 37, ETeam::BrightonAndHoveAlbion, ETeam::Liverpool, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 37, ETeam::Chelsea, ETeam::ManchesterUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 37, ETeam::CrystalPalace, ETeam::Wolverhampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 37, ETeam::Everton, ETeam::Southampton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 37, ETeam::LeicesterCity, ETeam::IpswichTown, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 37, ETeam::ManchesterCity, ETeam::AFCBournemouth, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 37, ETeam::WestHamUnited, ETeam::NottinghamForest, 1722985200000 });

    // Week 38
    matches.push_back({ ELeague::PremierLeague, "24/25", 38, ETeam::AFCBournemouth, ETeam::LeicesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 38, ETeam::Fulham, ETeam::ManchesterCity, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 38, ETeam::IpswichTown, ETeam::WestHamUnited, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 38, ETeam::Liverpool, ETeam::CrystalPalace, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 38, ETeam::ManchesterUnited, ETeam::AstonVilla, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 38, ETeam::NewcastleUnited, ETeam::Everton, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 38, ETeam::NottinghamForest, ETeam::Chelsea, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 38, ETeam::Southampton, ETeam::Arsenal, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 38, ETeam::TottenhamHotspur, ETeam::BrightonAndHoveAlbion, 1722985200000 });
    matches.push_back({ ELeague::PremierLeague, "24/25", 38, ETeam::Wolverhampton, ETeam::Brentford, 1722985200000 });

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