#pragma once

#include "../includes/consts.hpp"
#include "../includes/course.hpp"

class Lesson {
private:
    string courseName;
    string profName;
    string courseId;
    string profId;
    string capacity;
    Time time;
    string date;
    string classNumber;
    string prereq;
    vector<string> majorsId;
    int lessonID;
    vector<PostStruct> informing_channel;
    vector<string> TA_IDs;
    int postID;

public:
    Lesson(LessonStruct ls, int& lessonID);
    ~Lesson();
    string get_course_name();
    string get_prof_name();
    string get_course_id();
    string get_prof_id();
    string get_capacity();
    string get_week_day();
    string get_prereq();
    string get_start_time();
    string get_end_time();
    int get_class_num();
    string get_date();
    int get_lessonID();
    void show();
    void show_detailed();
    bool can_accept_this_major(string majorID_);
    void display();
    bool is_TA(string studentId);
    void add_post_to_channel(PostStruct& newPost);
    void show_channel();
    void show_channel_post(PostStruct cPost);
    void show_channel_post_detailed(int postId_);
    bool is_accessable(string userId, bool userHaveLesson);
    bool course_post_exists(int postId_);
    PostStruct find_course_post_by_postId(int postId_);
};
