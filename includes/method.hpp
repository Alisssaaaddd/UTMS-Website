#pragma once

#include "../includes/consts.hpp"
#include "../includes/error.hpp"
#include "../includes/user.hpp"
#include "../includes/major.hpp"

class Method
{
protected:
    vector<string> commands;

public:
    Method();
    ~Method();
    virtual void identify_command(string line, vector<User *> &users, User *&currentUser, int &lessonID_,
                                  vector<Lesson *> &lessons, vector<Course *> &courses, vector<Major *> &majors);
    vector<string> split(const string &str, const char delim);
    User *find_user_by_id(string id, vector<User *> &users);
    Course *find_course_by_id(vector<Course *> &courses, string courseId);
    Lesson* find_lesson_by_id(vector<Lesson *> &Lessons, string lessonID);
    bool can_convert_to_int(const std::string &str);
    bool lesson_exists(int lessonID, vector<Lesson* > &lessons);
    bool user_exists(string userId, vector<User *> users);
};
