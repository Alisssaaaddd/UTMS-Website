#pragma once

#include "../includes/user.hpp"
#include "../includes/course.hpp"
#include "../includes/major.hpp"
#include "../includes/error.hpp"
#include "../includes/method.hpp"
#include "../includes/post.hpp"
#include "../includes/get.hpp"
#include "../includes/delete.hpp"
#include "../includes/put.hpp"
#include "../includes/lesson.hpp"

class Website
{
private:
    vector<User *> users;
    vector<Course *> courses;
    vector<Major *> majors;
    vector<Method *> methods;
    vector<Lesson *> lessons;
    User *currentUser;
    int lessonId_current;
    MD manager_major;
    bool exit;

public:
    Website(char *majorsfile, char *studentsFile,
            char *coursesFile, char *professorsFile);
    ~Website();
    void import();
    void read_files(char *majorsfile, char *studentsFile,
                    char *coursesFile, char *professorsFile);
    void read_majors(char *majorsFileName);
    void read_students(char *studentsFileName);
    void read_courses(char *courses);
    void read_professors(char *professorsFileName);
    vector<string> split(const string &str, const char delim);
    void identify_method(string &method);
    MD find_MajorData_by_id(string userMajorId);
};