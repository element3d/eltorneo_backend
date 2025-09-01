#include "CachedTable.h"
#include "../managers/PQManager.h"
#include <mutex>
#include <string>

CachedTable* CachedTable::sInstance = nullptr;

CachedTable* CachedTable::Get() 
{
	if (!sInstance) sInstance = new CachedTable();
	return sInstance;
}

void CachedTable::Cache() 
{
    PGconn* pg = ConnectionPool::Get()->getConnection();
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    long long timestamp = ms.count();
    long long ten_days_ms = 20LL * 24 * 60 * 60 * 1000;

    {
        std::string sql =
            "SELECT u.id, COUNT(p.id) AS total_predictions "
            "FROM users u "
            "INNER JOIN predicts p ON u.id = p.user_id "
            "WHERE p.status != 4 "
            "AND u.league = 1 "
            "AND u.last_predict_ts >= " + std::to_string(timestamp - ten_days_ms) + " "
            "GROUP BY u.id, u.name, u.avatar, u.points "
            "HAVING COUNT(p.id) > 0 "
            "ORDER BY u.points DESC, total_predictions DESC, u.id ASC;";

        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to cache table: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }
        {
            std::lock_guard<std::mutex> l(mMutex);
            mTable.clear();

            int nrows = PQntuples(ret);
            for (int i = 0; i < nrows; ++i)
            {
                int pos = i + 1;
                int uid = atoi(PQgetvalue(ret, i, 0));
                mTable[uid] = pos;
            }
        }
        PQclear(ret);
    }

    {
        std::string sql =
            "SELECT u.id, COUNT(p.id) AS total_predictions "
            "FROM users u "
            "INNER JOIN predicts p ON u.id = p.user_id "
            "WHERE p.status != 4 "
            "AND u.league = 2 "
            "AND u.last_predict_ts >= " + std::to_string(timestamp - ten_days_ms) + " "
            "GROUP BY u.id, u.name, u.avatar, u.points "
            "HAVING COUNT(p.id) > 0 "
            "ORDER BY u.points DESC, total_predictions DESC, u.id ASC;";

        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to cache table: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }
        {
            std::lock_guard<std::mutex> l(mMutex);
            mTableLeague2.clear();

            int nrows = PQntuples(ret);
            for (int i = 0; i < nrows; ++i)
            {
                int pos = i + 1;
                int uid = atoi(PQgetvalue(ret, i, 0));
                mTableLeague2[uid] = pos;
            }
        }
        PQclear(ret);
    }

    {
        std::string sql =
            "SELECT u.id, COUNT(p.id) AS total_predictions "
            "FROM users u "
            "INNER JOIN predicts p ON u.id = p.user_id "
            "WHERE p.status != 4 "
            "AND u.league = 3 "
            "AND u.last_predict_ts >= " + std::to_string(timestamp - ten_days_ms) + " "
            "GROUP BY u.id, u.name, u.avatar, u.points "
            "HAVING COUNT(p.id) > 0 "
            "ORDER BY u.points DESC, total_predictions DESC, u.id ASC;";

        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to cache table: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }
        {
            std::lock_guard<std::mutex> l(mMutex);
            mTableLeague3.clear();

            int nrows = PQntuples(ret);
            for (int i = 0; i < nrows; ++i)
            {
                int pos = i + 1;
                int uid = atoi(PQgetvalue(ret, i, 0));
                mTableLeague3[uid] = pos;
            }
        }
        PQclear(ret);
    }

    {
        std::string sql =
            "SELECT u.id, COUNT(p.id) AS total_predictions "
            "FROM users u "
            "INNER JOIN predicts p ON u.id = p.user_id "
            "WHERE p.status != 4 "
            "AND u.league = 4 "
            "AND u.last_predict_ts >= " + std::to_string(timestamp - ten_days_ms) + " "
            "GROUP BY u.id, u.name, u.avatar, u.points "
            "HAVING COUNT(p.id) > 0 "
            "ORDER BY u.points DESC, total_predictions DESC, u.id ASC;";

        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to cache table: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }
        {
            std::lock_guard<std::mutex> l(mMutex);
            mTableLeague4.clear();

            int nrows = PQntuples(ret);
            for (int i = 0; i < nrows; ++i)
            {
                int pos = i + 1;
                int uid = atoi(PQgetvalue(ret, i, 0));
                mTableLeague4[uid] = pos;
            }
        }
        PQclear(ret);
    }

    // Beat Bet
    {
        std::string sql =
            "SELECT u.id, COUNT(b.id) AS total_bets "
            "FROM users u "
            "INNER JOIN bets b ON u.id = b.user_id "
            "WHERE u.last_bet_ts >= " + std::to_string(timestamp - ten_days_ms) + " "
            "GROUP BY u.id, u.name, u.avatar, u.balance "
            "HAVING COUNT(b.id) > 0 "
            "ORDER BY u.balance DESC, total_bets DESC, u.id ASC;";

        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to cache table: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }
        {
            std::lock_guard<std::mutex> l(mMutex);
            mBeatBetTable.clear();

            int nrows = PQntuples(ret);
            for (int i = 0; i < nrows; ++i)
            {
                int pos = i + 1;
                int uid = atoi(PQgetvalue(ret, i, 0));
                mBeatBetTable[uid] = pos;
            }
        }
        PQclear(ret);
    }

    // Fireball
    {
        std::string sql =
            "SELECT u.user_id, COUNT(p.id) AS total_predicts "
            "FROM fireball_users u "
            "INNER JOIN fireball_predicts p ON u.user_id = p.user_id "
            "WHERE u.last_predict_ts >= " + std::to_string(timestamp - ten_days_ms) + " "
            "GROUP BY u.user_id, u.points "
            "HAVING COUNT(p.id) > 0 "
            "ORDER BY u.points DESC, total_predicts DESC, u.user_id ASC;";

        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to cache fireball table: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }
        {
            std::lock_guard<std::mutex> l(mMutex);
            mFireballTable.clear();

            int nrows = PQntuples(ret);
            for (int i = 0; i < nrows; ++i)
            {
                int pos = i + 1;
                int uid = atoi(PQgetvalue(ret, i, 0));
                mFireballTable[uid] = pos;
            }
        }
        PQclear(ret);
    }

    ConnectionPool::Get()->releaseConnection(pg);
}

int CachedTable::GetPosition(int userId, int league)
{
    std::lock_guard<std::mutex> l(mMutex);
    if (league == 1)
    {
        if (mTable.find(userId) == mTable.end()) return -1;
        return mTable[userId];
    }
    if (league == 2)
    {
        if (mTableLeague2.find(userId) == mTableLeague2.end()) return -1;
        return mTableLeague2[userId];
    }
    if (league == 3)
    {
        if (mTableLeague3.find(userId) == mTableLeague3.end()) return -1;
        return mTableLeague3[userId];
    }
    if (league == 4)
    {
        if (mTableLeague4.find(userId) == mTableLeague4.end()) return -1;
        return mTableLeague4[userId];
    }
    return -1;
}

int CachedTable::GetBeatBetPosition(int userId)
{
    std::lock_guard<std::mutex> l(mMutex);

    if (mBeatBetTable.find(userId) == mBeatBetTable.end()) return -1;
    return mBeatBetTable[userId];

    return -1;
}

int CachedTable::GetFireballPosition(int userId)
{
    std::lock_guard<std::mutex> l(mMutex);

    if (mFireballTable.find(userId) == mFireballTable.end()) return -1;
    return mFireballTable[userId];

    return -1;
}