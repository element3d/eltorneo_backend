#include <string>
#include "managers/PQManager.h"

int main()
{
	PGconn* pg = ConnectionPool::Get()->getConnection();
	
    auto now = std::chrono::system_clock::now();
    auto ts = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

    // Calculate start and end of the day in milliseconds
    time_t rawtime = ts / 1000;  // Convert to seconds
    struct tm timeinfo = *localtime(&rawtime);

    // Start of day
    timeinfo.tm_hour = 0;
    timeinfo.tm_min = 0;
    timeinfo.tm_sec = 0;
    auto dayStart = std::mktime(&timeinfo) * 1000;  // Convert back to milliseconds

    // End of day
    timeinfo.tm_mday += 4;  // Move to the next day
    timeinfo.tm_hour = 23;
    timeinfo.tm_min = 59;
    timeinfo.tm_sec = 59;
    auto dayEnd = std::mktime(&timeinfo) * 1000;  // Convert back to milliseconds

    // Connect to the database
    std::string sql = "SELECT m.id, "
        "t1.id AS team1_id, t1.short_name AS team1_short_name, "
        "t2.id AS team2_id, t2.short_name AS team2_short_name, m.league "
        "FROM matches m "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "JOIN leagues l ON m.league = l.id "  // Join with leagues table
        "WHERE m.status = '' and l.id > 1 and l.id < 7 and m.match_date >= " + std::to_string(dayStart) + " AND m.match_date <= " + std::to_string(dayEnd) + " "
        "ORDER BY m.league ASC, m.match_date ASC, m.id ASC;";

    PGresult* ret = PQexec(pg, sql.c_str());
    if (PQresultStatus(ret) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Failed to fetch matches: %s", PQerrorMessage(pg));
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    }

    int nrows = PQntuples(ret);
    for (int i = 0; i < nrows; i++) 
    {
        int id = atoi(PQgetvalue(ret, i, 0));
        int team1Id = atoi(PQgetvalue(ret, i, 1));
        std::string team1 = PQgetvalue(ret, i, 2);
        int team2Id = atoi(PQgetvalue(ret, i, 3));
        std::string team2 = PQgetvalue(ret, i, 4);
        int leagueId = atoi(PQgetvalue(ret, i, 5));

        printf("%s - %s\n", team1.c_str(), team2.c_str());
        std::string filename = "/var/www/beatbet/" + team1 + " - " + team2 + ".txt";
        FILE* file = nullptr;

        sql = "SELECT predicts.*, users.name FROM predicts "
            "INNER JOIN users ON predicts.user_id = users.id "
            "WHERE predicts.match_id = " + std::to_string(id) + ";";
        PGresult* predictsRet = PQexec(pg, sql.c_str());
        int numPredicts = PQntuples(predictsRet);
        for (int p = 0; p < numPredicts; ++p) 
        {
            int predictId = atoi(PQgetvalue(predictsRet, p, 0));
            int userId = atoi(PQgetvalue(predictsRet, p, 1));
            int t1Score = atoi(PQgetvalue(predictsRet, p, 3));
            int t2Score = atoi(PQgetvalue(predictsRet, p, 4));
            std::string userName = PQgetvalue(predictsRet, p, 6);
            bool usernameWritten = false;
            {
                // Get team1 matches
                sql = "SELECT p.team1_score, p.team2_score, p.status, "
                    "m.team1_score, m.team2_score, t1.short_name as team1_short_name, "
                    "t2.short_name as team2_short_name "
                    "FROM predicts p "
                    "INNER JOIN matches m ON p.match_id = m.id "
                    "LEFT JOIN leagues l ON m.league = l.id "
                    "LEFT JOIN teams t1 ON m.team1 = t1.id "
                    "LEFT JOIN teams t2 ON m.team2 = t2.id "
                    "WHERE m.team1_score <> -1 and m.team2_score <> -1 and m.status <> 'PST' and p.status <> 4 "
                    "AND m.league = " + std::to_string(leagueId) +
                    " AND (team1 = " + std::to_string(team1Id) + " OR team2 = " + std::to_string(team1Id) + ")"
                    " AND p.user_id = " + std::to_string(userId) +
                    " ORDER BY p.id DESC "
                    "LIMIT " + std::to_string(20) + ";";

                PGresult* userPredictsRet = PQexec(pg, sql.c_str());
                int numUserPredicts = PQntuples(userPredictsRet);
                if (numUserPredicts < 5)
                {
                    PQclear(userPredictsRet);
                    continue;
                }

                //            printf("%s %i - %i\n\n", userName.c_str(), t1Score, t2Score);

                int sum = 0;
                for (int up = 0; up < numUserPredicts; ++up)
                {
                    int predictStatus = atoi(PQgetvalue(userPredictsRet, up, 2));
                    int k = 0;
                    if (predictStatus == 1 || predictStatus == 2) k = 1;
                    if (predictStatus == 3) k = -1;
                    if (sum == 0)
                    {
                    }
                    else if (sum > 0 && k == -1) break;
                    else if (sum < 0 && k == 1) break;

                    sum += k;

                    std::string team1 = PQgetvalue(userPredictsRet, up, 5);
                    std::string team2 = PQgetvalue(userPredictsRet, up, 6);

                    //                printf("%s - %s\n", team1.c_str(), team2.c_str());
                }

                if (sum >= 5)
                {
                    if (file == nullptr) file = fopen(filename.c_str(), "w");
                    if (!usernameWritten) fprintf(file, "%s %i - %i\n", userName.c_str(), t1Score, t2Score);
                    fprintf(file, "%s %i win\n", team1.c_str(), sum);
                    usernameWritten = true;
                }
                if (sum <= -5)
                {
                    if (file == nullptr) file = fopen(filename.c_str(), "w");
                    if (!usernameWritten) fprintf(file, "%s %i - %i\n", userName.c_str(), t1Score, t2Score);
                    fprintf(file ,"%s %i loose\n", team1.c_str(), sum);
                    usernameWritten = true;
                }

                PQclear(userPredictsRet);
            }

            {
                // Get team1 home matches
                sql = "SELECT p.team1_score, p.team2_score, p.status, "
                    "m.team1_score, m.team2_score, t1.short_name as team1_short_name, "
                    "t2.short_name as team2_short_name "
                    "FROM predicts p "
                    "INNER JOIN matches m ON p.match_id = m.id "
                    "LEFT JOIN leagues l ON m.league = l.id "
                    "LEFT JOIN teams t1 ON m.team1 = t1.id "
                    "LEFT JOIN teams t2 ON m.team2 = t2.id "
                    "WHERE m.team1_score <> -1 and m.team2_score <> -1 and m.status <> 'PST' and p.status <> 4 "
                    "AND m.league = " + std::to_string(leagueId) +
                    " AND team1 = " + std::to_string(team1Id) + 
                    " AND p.user_id = " + std::to_string(userId) +
                    " ORDER BY p.id DESC "
                    "LIMIT " + std::to_string(20) + ";";

                PGresult* userPredictsRet = PQexec(pg, sql.c_str());
                int numUserPredicts = PQntuples(userPredictsRet);
                if (numUserPredicts < 5)
                {
                    PQclear(userPredictsRet);
                    continue;
                }

                //            printf("%s %i - %i\n\n", userName.c_str(), t1Score, t2Score);

                int sum = 0;
                for (int up = 0; up < numUserPredicts; ++up)
                {
                    int predictStatus = atoi(PQgetvalue(userPredictsRet, up, 2));
                    int k = 0;
                    if (predictStatus == 1 || predictStatus == 2) k = 1;
                    if (predictStatus == 3) k = -1;
                    if (sum == 0)
                    {
                    }
                    else if (sum > 0 && k == -1) break;
                    else if (sum < 0 && k == 1) break;

                    sum += k;

                    std::string team1 = PQgetvalue(userPredictsRet, up, 5);
                    std::string team2 = PQgetvalue(userPredictsRet, up, 6);

                    //                printf("%s - %s\n", team1.c_str(), team2.c_str());
                }

                if (sum >= 5)
                {
                    if (file == nullptr) file = fopen(filename.c_str(), "w");
                    if (!usernameWritten) fprintf(file, "%s %i - %i\n", userName.c_str(), t1Score, t2Score);
                    fprintf(file, "%s home %i win\n", team1.c_str(), sum);
                    usernameWritten = true;
                }
                if (sum <= -5)
                {
                    if (file == nullptr) file = fopen(filename.c_str(), "w");
                    if (!usernameWritten) fprintf(file, "%s %i - %i\n", userName.c_str(), t1Score, t2Score);
                    fprintf(file, "%s home %i loose\n", team1.c_str(), sum);
                    usernameWritten = true;
                }

                PQclear(userPredictsRet);
            }

            {
                // Get team2 matches
                sql = "SELECT p.team1_score, p.team2_score, p.status, "
                    "m.team1_score, m.team2_score, t1.short_name as team1_short_name, "
                    "t2.short_name as team2_short_name "
                    "FROM predicts p "
                    "INNER JOIN matches m ON p.match_id = m.id "
                    "LEFT JOIN leagues l ON m.league = l.id "
                    "LEFT JOIN teams t1 ON m.team1 = t1.id "
                    "LEFT JOIN teams t2 ON m.team2 = t2.id "
                    "WHERE m.team1_score <> -1 and m.team2_score <> -1 and m.status <> 'PST' and p.status <> 4 "
                    "AND m.league = " + std::to_string(leagueId) +
                    " AND (team1 = " + std::to_string(team2Id) + " OR team2 = " + std::to_string(team2Id) + ")"
                    " AND p.user_id = " + std::to_string(userId) +
                    " ORDER BY p.id DESC "
                    "LIMIT " + std::to_string(20) + ";";

                PGresult* userPredictsRet = PQexec(pg, sql.c_str());
                int numUserPredicts = PQntuples(userPredictsRet);
                if (numUserPredicts < 5)
                {
                    PQclear(userPredictsRet);
                    continue;
                }

                //            printf("%s %i - %i\n\n", userName.c_str(), t1Score, t2Score);

                int sum = 0;
                for (int up = 0; up < numUserPredicts; ++up)
                {
                    int predictStatus = atoi(PQgetvalue(userPredictsRet, up, 2));
                    int k = 0;
                    if (predictStatus == 1 || predictStatus == 2) k = 1;
                    if (predictStatus == 3) k = -1;
                    if (sum == 0)
                    {
                    }
                    else if (sum > 0 && k == -1) break;
                    else if (sum < 0 && k == 1) break;

                    sum += k;

                    // std::string team1 = PQgetvalue(userPredictsRet, up, 5);
                    // std::string team2 = PQgetvalue(userPredictsRet, up, 6);

                    //                printf("%s - %s\n", team1.c_str(), team2.c_str());
                }

                if (sum >= 5)
                {
                    if (file == nullptr) file = fopen(filename.c_str(), "w");
                    if (!usernameWritten) fprintf(file, "%s %i - %i\n", userName.c_str(), t1Score, t2Score);
                    fprintf(file, "%s %i win\n", team2.c_str(), sum);
                    usernameWritten = true;
                }
                if (sum <= -5)
                {
                    if (file == nullptr) file = fopen(filename.c_str(), "w");
                    if (!usernameWritten) fprintf(file, "%s %i - %i\n", userName.c_str(), t1Score, t2Score);
                    fprintf(file, "%s %i loose\n", team2.c_str(), sum);
                    usernameWritten = true;
                }

                PQclear(userPredictsRet);
            }

            {
                // Get team2 away matches
                sql = "SELECT p.team1_score, p.team2_score, p.status, "
                    "m.team1_score, m.team2_score, t1.short_name as team1_short_name, "
                    "t2.short_name as team2_short_name "
                    "FROM predicts p "
                    "INNER JOIN matches m ON p.match_id = m.id "
                    "LEFT JOIN leagues l ON m.league = l.id "
                    "LEFT JOIN teams t1 ON m.team1 = t1.id "
                    "LEFT JOIN teams t2 ON m.team2 = t2.id "
                    "WHERE m.team1_score <> -1 and m.team2_score <> -1 and m.status <> 'PST' and p.status <> 4 "
                    "AND m.league = " + std::to_string(leagueId) +
                    " AND team2 = " + std::to_string(team2Id) +
                    " AND p.user_id = " + std::to_string(userId) +
                    " ORDER BY p.id DESC "
                    "LIMIT " + std::to_string(20) + ";";

                PGresult* userPredictsRet = PQexec(pg, sql.c_str());
                int numUserPredicts = PQntuples(userPredictsRet);
                if (numUserPredicts < 5)
                {
                    PQclear(userPredictsRet);
                    continue;
                }

                //            printf("%s %i - %i\n\n", userName.c_str(), t1Score, t2Score);

                int sum = 0;
                for (int up = 0; up < numUserPredicts; ++up)
                {
                    int predictStatus = atoi(PQgetvalue(userPredictsRet, up, 2));
                    int k = 0;
                    if (predictStatus == 1 || predictStatus == 2) k = 1;
                    if (predictStatus == 3) k = -1;
                    if (sum == 0)
                    {
                    }
                    else if (sum > 0 && k == -1) break;
                    else if (sum < 0 && k == 1) break;

                    sum += k;

                    std::string team1 = PQgetvalue(userPredictsRet, up, 5);
                    std::string team2 = PQgetvalue(userPredictsRet, up, 6);

                    //                printf("%s - %s\n", team1.c_str(), team2.c_str());
                }

                if (sum >= 5)
                {
                    if (file == nullptr) file = fopen(filename.c_str(), "w");
                    if (!usernameWritten) fprintf(file, "%s %i - %i\n", userName.c_str(), t1Score, t2Score);
                    fprintf(file, "%s away %i win\n", team2.c_str(), sum);
                    usernameWritten = true;
                }
                if (sum <= -5)
                {
                    if (file == nullptr) file = fopen(filename.c_str(), "w");
                    if (!usernameWritten) fprintf(file, "%s %i - %i\n", userName.c_str(), t1Score, t2Score);
                    fprintf(file, "%s away %i loose\n", team2.c_str(), sum);
                    usernameWritten = true;
                }

                PQclear(userPredictsRet);
            }

            if (file) fprintf(file, "\n\n");
        }
        PQclear(predictsRet);

        if (file) fclose(file);
    }

	return 0;
}