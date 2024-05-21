#pragma once

#include "../includes/consts.hpp"

class Major
{
private:
    string MID;
    string name;

public:
    Major(MD majorStruct);
    ~Major();
    string get_MID();
    string get_name();
};


