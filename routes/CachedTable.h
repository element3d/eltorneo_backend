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
	int GetBeatBetPosition(int userId);

private:
	static CachedTable* sInstance;
	std::map<int, int> mTable;
	std::map<int, int> mTableLeague2;
	std::map<int, int> mTableLeague3;
	std::map<int, int> mTableLeague4;

	std::map<int, int> mBeatBetTable;

	std::mutex mMutex;
	std::mutex mBeatBetMutex;

};