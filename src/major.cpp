#include "../includes/major.hpp"

Major::Major(MD majorStruct)
{
    MID = majorStruct.MID;
    name = majorStruct.name;
}

Major::~Major()
{
}

string Major::get_MID(){
    return MID;
}

string Major::get_name(){
    return name;
}