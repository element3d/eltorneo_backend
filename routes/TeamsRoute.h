#pragma once

#include "../httplib.h"

class TeamsRoute
{
public:
    static TeamsRoute* Get();

    std::function<void(const httplib::Request&, httplib::Response&)> PostTeam();
    std::function<void(const httplib::Request&, httplib::Response&)> GetTeams();


private:
    static TeamsRoute* sInstance;
};