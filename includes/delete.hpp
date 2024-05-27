#pragma once

#include "../includes/consts.hpp"
#include "../includes/method.hpp"
#include "../includes/major.hpp"

class Delete : public Method
{
private:
public:
    Delete();
    ~Delete();
    void identify_command(string line, vector<User *> &users, User *&currentUser, int &lessonID_,
                          vector<Lesson *> &lessons, vector<Course *> &courses, vector<Major *> &majors);

    void handle_post(string line, vector<User *> &users, User *&currentUser, int &lessonID_,
                     vector<Lesson *> &lessons, vector<Course *> &courses, vector<Major *> &majors, istringstream &iss2);

    void handle_my_courses(string line, vector<User *> &users, User *&currentUser, int &lessonID_,
                           vector<Lesson *> &lessons, vector<Course *> &courses, vector<Major *> &majors, istringstream &iss2);
};