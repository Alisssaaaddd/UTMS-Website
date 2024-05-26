#pragma once

#include "../includes/consts.hpp"
#include "../includes/method.hpp"

class Put : public Method
{
private:
public:
    Put();
    ~Put();
    void identify_command(string line, vector<User *> &users, User *&currentUser, int &lessonID_,
                          vector<Lesson *> &lessons, vector<Course *> &courses, vector<Major *> &majors);

    void handle_my_courses(string line, vector<User *> &users, User *&currentUser,
                        vector<Lesson *> &lessons, vector<Course *> &courses, vector<Major *> &majors, istringstream &iss2);

};