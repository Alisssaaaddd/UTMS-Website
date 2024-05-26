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
    string get_name();
    string get_credit();
    string get_prereq();
    vector<string> get_majors_id();
};



