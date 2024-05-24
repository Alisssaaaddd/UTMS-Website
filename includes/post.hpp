#pragma once

#include "../includes/consts.hpp"
#include "../includes/method.hpp"
#include "../includes/major.hpp"

class Post : public Method
{
private:
public:
    Post();
    ~Post();
    void identify_command(string line, vector<User *> &users, User *&currentUser, int &lessonID_,
                          vector<Lesson *> &lessons, vector<Course *> &courses, vector<Major *> &majors);
    void login(Argument id, Argument password, vector<User *> &users, User *&currentUser);
    void logout(User *&currentUser);
    void course_offer(LessonStruct lesson, int &lessonID, User *&currentUser, vector<Lesson *> &lessons,
                      vector<Course *> &courses, vector<Major *> &majors, vector<User *> &users);
    bool course_exists(string courseId, vector<Course *> courses);
    bool user_exists(string userId, vector<User *> users);
    bool is_prof(string userId, vector<User *> users);
    bool can_convert_to_int(const std::string &str);
    bool is_major_valid(vector<User *> users, vector<Major *> majors);
    void activate_for_prof();
    User* find_user_by_id(string id, vector<User*> users);
};