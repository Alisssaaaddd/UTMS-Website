#pragma once

#include "../includes/consts.hpp"
#include "../includes/course.hpp"

class Lesson
{
private:
    string courseName;
    string profName;
    string courseId;
    string profId;
    string capacity;
    Time time;
    string date;
    string classNumber;
    int lessonID;
    
public:
    Lesson(LessonStruct ls, int &lessonID);
    ~Lesson();
    string get_course_name();
    string get_prof_name();
    string get_course_id();
    string get_prof_id();
    string get_capacity();
    string get_week_day();
    int get_start_time();
    int get_end_time();
    int get_class_num();
    string get_date();
    int get_lessonID();
    void show();
    void show_detailed();
};


