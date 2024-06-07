#include "../includes/course.hpp"

Course::Course(CD course)
{
    CID = course.CID;
    name = course.name;
    credit = course.credit;
    prereq = course.prereq;
    majorsID = course.majors_id;
}

Course::~Course()
{
}

string Course::get_CID() { return CID; };
string Course::get_name() { return name; };
string Course::get_credit() { return credit; };
string Course::get_prereq() { return prereq; };
vector<string> Course::get_majors_id() { return majorsID; };

bool Course::valid_major(string majorId_)
{
    for (auto m : majorsID)
    {
        if (m == majorId_)
        {
            return true;
        }
    }
    return false;
}
