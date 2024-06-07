#pragma once

#include "../includes/consts.hpp"
#include "../includes/major.hpp"
#include "../includes/media.hpp"
#include "../includes/method.hpp"

class Post : public Method {
private:
public:
    Post();
    ~Post();
    void identify_command(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
        vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors);
    void login(Argument id, Argument password, vector<User*>& users, User*& currentUser);
    void logout(User*& currentUser, string line);

    void handle_course_offer(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
        vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors);

    void handle_post(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
        vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2);

    void course_offer(LessonStruct lesson, int& lessonID, User*& currentUser, vector<Lesson*>& lessons,
        vector<Course*>& courses, vector<Major*>& majors, vector<User*>& users);

    void handle_login(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
        vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2);

    void handle_connect(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
        vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2);

    void handle_profile_photo(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
        vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2);

    void handle_course_post(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
        vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2);

    void handle_ta_form(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
        vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2);

    void handle_closing_ta_form(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
        vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2);

    void handle_ta_request(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
        vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2);

    bool course_exists(string courseId, vector<Course*> courses);
    bool is_prof(string userId, vector<User*> users);
    void connect_users(User* currentUser, User* chosenUser);
    void send_notif_to_all(Notification notif, vector<User*>& users);
    void read_post_title(string& line, PostStruct& post);
    void read_post_message(string& line, PostStruct& post);
    void read_post_image(string& line, PostStruct& post);
    void handle_title_first(string& line, PostStruct& post);
    void handle_message_first(string& line, PostStruct& post);
    void handle_image_first(string& line, PostStruct& post);
    void send_post_notification(User*& currentUser, PostStruct& post, vector<User*>& users);
    string read_profile_path(string& line);
    void handle_channel_post(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
        vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2, PostStruct& post);

    void ta_post(User*& currentUser, Lesson*& chosenLesson, string& line, PostStruct& post, vector<User*>& users);
    void professor_post(Professor*& professor, Lesson*& chosenLesson, string& line, PostStruct& post, vector<User*>& users, User*& currentUser);
    void send_course_notif(vector<User*>& users, Lesson*& chosenLesson, User*& currentUser, Notification courseNotif);
    Notification construct_course_notif(Lesson*& chosenLesson);
    Lesson* read_course_id(string& id_, vector<Lesson*>& lessons, User*& currentUser);
    void close_ta_form(Professor*& prof, vector<User*>& users, string id);
    void check_is_professor(string profID, vector<User*>& users);
    void check_form_existance(Professor*& prof, string formID);
    void add_new_ta_request(istringstream& iss2, vector<User*>& users, Student*& student);
    void pre_check_for_ta_request(User*& currentUser);
};