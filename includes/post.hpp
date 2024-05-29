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
    void logout(User *&currentUser, string line);

    void handle_course_offer(string line, vector<User *> &users, User *&currentUser, int &lessonID_,
                             vector<Lesson *> &lessons, vector<Course *> &courses, vector<Major *> &majors);

    void handle_post(string line, vector<User *> &users, User *&currentUser, int &lessonID_,
                     vector<Lesson *> &lessons, vector<Course *> &courses, vector<Major *> &majors, istringstream &iss2);

    void course_offer(LessonStruct lesson, int &lessonID, User *&currentUser, vector<Lesson *> &lessons,
                      vector<Course *> &courses, vector<Major *> &majors, vector<User *> &users);

    void handle_login(string line, vector<User *> &users, User *&currentUser, int &lessonID_,
                       vector<Lesson *> &lessons, vector<Course *> &courses, vector<Major *> &majors, istringstream &iss2);
    
    void handle_connect(string line, vector<User *> &users, User *&currentUser, int &lessonID_,
                        vector<Lesson *> &lessons, vector<Course *> &courses, vector<Major *> &majors, istringstream &iss2);

    bool course_exists(string courseId, vector<Course *> courses);
    bool is_prof(string userId, vector<User *> users);
    void connect_users(User *currentUser, User *chosenUser);
    void send_notif_to_all(Notification notif, vector<User*> &users);
};