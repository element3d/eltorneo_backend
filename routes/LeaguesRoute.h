#pragma once

#include "../httplib.h"

class LeaguesRoute
{
public:
    static LeaguesRoute* Get();

    LeaguesRoute();
    void Init();

    std::function<void(const httplib::Request&, httplib::Response&)> GetSettings();
    std::function<void(const httplib::Request&, httplib::Response&)> GetLeagues();
    std::function<void(const httplib::Request&, httplib::Response&)> GetLeague();
    std::function<void(const httplib::Request&, httplib::Response&)> PostLeague();
    std::function<void(const httplib::Request&, httplib::Response&)> GetWeeks();
    std::function<void(const httplib::Request&, httplib::Response&)> SetCurrentWeek();
    std::function<void(const httplib::Request&, httplib::Response&)> GetLeagueTable();
    std::function<void(const httplib::Request&, httplib::Response&)> GetTopScorers();

private:
    static LeaguesRoute* sInstance;
};