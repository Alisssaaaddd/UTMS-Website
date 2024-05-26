#pragma once

#include "../includes/consts.hpp"
#include "../includes/lesson.hpp"
#include "../includes/error.hpp"

class User
{
protected:
    string ID;
    string name;
    string majorID;
    MajorData major;
    string password;
    bool is_signed_in;
    int postID;
    vector<Notification> notifs;
    vector<Lesson *> activeLessons;
    vector<PostStruct> posts;
    vector<User*> connections;

public:
    User(MD major_);
    ~User();
    string get_id();
    string get_name();
    string get_majorID();
    string get_password();
    bool signed_in();
    void login();
    void logout();
    bool does_interfere(string startTime);
    void add_lesson(Lesson *&newLesson);
    void add_post(PostStruct newPost);
    void delete_post(int postID_);
    int get_postID();
    virtual void show_personal_page();
    virtual void show_personal_info();
    void show_post(int postID_);
    string lessons_in_line();
    void show_post_titles();
    bool have_this_post(int postID_);
    bool already_connected(string userID_);
    void connect(User* chosenUser);
    void receive_notif(Notification notif);
    void display_all_notifs();
    void display_notif(Notification notif);
};

class Student : public User
{
private:
    string semester;

public:
    Student(SD student, MD major_);
    ~Student();
    void show_personal_page();
    void show_personal_info();
};

class Professor : public User
{
private:
    string position;

public:
    Professor(PD professor, MD major_);
    ~Professor();
    void show_personal_page();
    void show_personal_info();
};

class Manager : public User
{
private:
public:
    Manager(MD major_);
    ~Manager();
    void show_personal_page();
    void show_personal_info();
};