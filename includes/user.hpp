#pragma once

#include "../includes/consts.hpp"
#include "../includes/error.hpp"
#include "../includes/lesson.hpp"
#include "../includes/media.hpp"

class User {
protected:
    string ID;
    string name;
    string majorID;
    MajorData major;
    string password;
    bool is_signed_in;
    int postID;
    vector<Notification> notifs;
    vector<Lesson*> activeLessons;
    vector<PostStruct> posts;
    vector<User*> connections;
    string profile_photo_path;

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
    bool does_interfere(Lesson* lesson_);
    void add_lesson(Lesson*& newLesson);
    void delete_lesson(int lessId_);
    void add_post(PostStruct& newPost);
    void delete_post(int postID_);
    int get_postID();
    virtual void show_personal_page();
    virtual void show_personal_info();
    void show_post(int postID_, vector<Lesson*>& lessons);
    string lessons_in_line();
    void show_post_titles();
    bool have_this_post(int postID_);
    bool already_connected(string userID_);
    void connect(User* chosenUser);
    void receive_notif(Notification notif);
    void display_all_notifs();
    void display_notif(Notification notif);
    void send_notif(Notification postNotif);
    bool have_this_lesson(int lessId_);
    bool no_active_lessons();
    void display_all_lessons();
    string get_profile_photo_path();
    void set_profile(string newPath);
    void show_lesson_info(vector<Lesson*>& lessons, int lessonId_);
};

class Student : public User {
private:
    string semester;
    StudentData studentStruct;

public:
    Student(SD student, MD major_);
    ~Student();
    void show_personal_page();
    void show_personal_info();
    bool can_take_lesson(Lesson*& lesson_);
    bool exam_interfers(string examDate_);
    StudentData get_studentData();
    string get_semester();
};

class Professor : public User {
private:
    string position;
    vector<TaForm*> forms;

public:
    Professor(PD professor, MD major_);
    ~Professor();
    void show_personal_page();
    void show_personal_info();
    void add_ta_form(TaForm* newForm);
    void show_number_of_requests(int formId);
    void handle_requests_of_form(int formId);
    void send_reject_notifs(vector<User*>& users, string formId);
    void send_accept_notifs(vector<User*>& users, string formId);
    void delete_ta_form(int formId);
    TaForm* find_ta_form_by_id(int formID);
    bool have_this_form(int formID);
};

class Manager : public User {
private:
public:
    Manager(MD major_);
    ~Manager();
    void show_personal_page();
    void show_personal_info();
};