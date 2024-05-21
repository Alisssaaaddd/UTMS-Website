#pragma once

#include "../includes/consts.hpp"

class Course{
    private:
    string CID;
    string name;
    string credit;
    string prereq;
    vector<string> majorsID;

    public:
    Course(CD course);
    ~Course();
    

    string get_CID();

};



