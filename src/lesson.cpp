
#include "../includes/lesson.hpp"

Lesson::Lesson(LessonStruct ls, int &lessonID)
{
    courseName = ls.courseName;
    profName = ls.profName;
    courseId = ls.courseId;
    profId = ls.profId;
    capacity = ls.capacity;
    time.weekDay = ls.weekDay;
    time.startTime = ls.startTime;
    time.endTime = ls.endTime;
    date = ls.date;
    classNumber = ls.classNumber;
    lessonID = ls.lessonID;
    lessonID++;
}

Lesson::~Lesson()
{
}

string  Lesson::get_course_name(){return courseName;};
string  Lesson::get_prof_name(){return profName;};
string  Lesson::get_course_id(){return courseId;};
string Lesson::get_capacity(){return capacity;};
string  Lesson::get_week_day(){return time.weekDay;};
int Lesson::get_start_time(){return stoi(time.startTime);};
int  Lesson::get_end_time(){return stoi(time.endTime);};
int  Lesson::get_class_num(){return stoi(classNumber);};
string Lesson::get_date(){return date;};
