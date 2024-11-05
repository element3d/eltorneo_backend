#include "CachedTable.h"
#include "../managers/PQManager.h"
#include <mutex>

CachedTable* CachedTable::sInstance = nullptr;

CachedTable* CachedTable::Get() 
{
	if (!sInstance) sInstance = new CachedTable();
	return sInstance;
}

void CachedTable::Cache() 
{
    PGconn* pg = ConnectionPool::Get()->getConnection();

    {
        std::string sql = "SELECT u.id, COUNT(p.id) AS total_predictions FROM users u INNER JOIN predicts p ON u.id = p.user_id WHERE p.status != 4 AND u.league = 1 GROUP BY u.id, u.name, u.avatar, u.points HAVING COUNT(p.id) > 0 ORDER BY u.points DESC, total_predictions DESC;";

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
        std::string sql = "SELECT u.id, COUNT(p.id) AS total_predictions FROM users u INNER JOIN predicts p ON u.id = p.user_id WHERE p.status != 4 AND u.league = 2 GROUP BY u.id, u.name, u.avatar, u.points HAVING COUNT(p.id) > 0 ORDER BY u.points DESC, total_predictions DESC;";

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
    return -1;
}
