#pragma once

#include <vector>
#include <map>
#include <mutex>

class CachedTable 
{
public:
	static CachedTable* Get();

	void Cache();
	int GetPosition(int userId, int league);

private:
	static CachedTable* sInstance;
	std::map<int, int> mTable;
	std::map<int, int> mTableLeague2;
	std::map<int, int> mTableLeague3;

	std::mutex mMutex;
};