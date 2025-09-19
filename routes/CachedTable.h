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
	int GetFireballPosition(int userId);
	int GetCareerPosition(int userId);

private:
	static CachedTable* sInstance;
	std::map<int, int> mTable;
	std::map<int, int> mTableLeague2;
	std::map<int, int> mTableLeague3;
	std::map<int, int> mTableLeague4;

	std::map<int, int> mBeatBetTable;
	std::map<int, int> mFireballTable;
	std::map<int, int> mCareerTable;

	std::mutex mMutex;
	std::mutex mBeatBetMutex;

};