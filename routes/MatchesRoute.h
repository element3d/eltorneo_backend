#pragma once

#include "../httplib.h"

#include "Team.h"

class MatchesRoute
{
public:
    static MatchesRoute* Get();

    std::function<void(const httplib::Request&, httplib::Response&)> PostMatch();
    std::function<void(const httplib::Request&, httplib::Response&)> EditMatch();
    std::function<void(const httplib::Request&, httplib::Response&)> GetMatches();
    std::function<void(const httplib::Request&, httplib::Response&)> GetMatchesByDay();
    std::function<void(const httplib::Request&, httplib::Response&)> GetMatchesLive();

    std::function<void(const httplib::Request&, httplib::Response&)> GetMatch();


private:
    static MatchesRoute* sInstance;
};