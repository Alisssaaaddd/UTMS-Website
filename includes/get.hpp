#pragma once

#include "../includes/consts.hpp"
#include "../includes/major.hpp"
#include "../includes/method.hpp"

class Get : public Method {
private:
public:
    Get();
    ~Get();
    void show_all_lessons(vector<Lesson*>& lessons, vector<Course*>& courses);
    void identify_command(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
        vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors);
    void handle_notif(string line, User*& currentUser);
    void show_post(User* chosenUser, int postID_, vector<Lesson*> &lessons);
    void handle_courses(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
        vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2);

    void handle_personal_page(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
        vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2);

    void handle_my_courses(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
        vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2);

    void handle_post(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
        vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2);

    void handle_course_channel(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
        vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2);

    void handle_course_post(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
        vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2);
};