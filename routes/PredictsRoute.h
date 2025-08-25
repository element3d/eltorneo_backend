#pragma once

#include "../httplib.h"

class PredictsRoute
{
public:
    static PredictsRoute* Get();

    std::function<void(const httplib::Request&, httplib::Response&)> GetUserPredict();
    std::function<void(const httplib::Request&, httplib::Response&)> GetUserBet();

    std::function<void(const httplib::Request&, httplib::Response&)> GetUserPredicts();
    std::function<void(const httplib::Request&, httplib::Response&)> GetUserBets();
    std::function<void(const httplib::Request&, httplib::Response&)> GetUserScorePredicts();
    std::function<void(const httplib::Request&, httplib::Response&)> GetUserWinnerPredicts();

    std::function<void(const httplib::Request&, httplib::Response&)> GetMatchPredicts();
    std::function<void(const httplib::Request&, httplib::Response&)> GetMatchPredictsTop3();
    std::function<void(const httplib::Request&, httplib::Response&)> PostPredict();
    std::function<void(const httplib::Request&, httplib::Response&)> EditPredict();

    std::function<void(const httplib::Request&, httplib::Response&)> PostBet();
    std::function<void(const httplib::Request&, httplib::Response&)> DeleteBet();

    std::function<void(const httplib::Request&, httplib::Response&)> GetTableByPoints();
    std::function<void(const httplib::Request&, httplib::Response&)> GetBeatBetTable();

    std::function<void(const httplib::Request&, httplib::Response&)> GetTableByScore();
    std::function<void(const httplib::Request&, httplib::Response&)> GetTableByWinner();

    std::function<void(const httplib::Request&, httplib::Response&)> GetBeatBet();


private:
   // void CacheTable();

private:
    static PredictsRoute* sInstance;
 //   std::vector<int> mCachedTable;
};