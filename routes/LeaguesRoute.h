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


private:
    static LeaguesRoute* sInstance;
};