#pragma once

#include "../includes/user.hpp"
#include "../includes/course.hpp"
#include "../includes/major.hpp"
#include "../includes/error.hpp"
#include "../includes/date.hpp"

class Website
{
private:
    vector<User *> users;
    vector<Course *> courses;
    vector<Major *> majors;

public:
    Website(char *majorsfile, char *studentsFile,
            char *coursesFile, char *professorsFile);
    ~Website();
    void import();
    int check_controll_arguments(int argc);
    void read_files(char *majorsfile, char *studentsFile,
                    char *coursesFile, char *professorsFile);
    void read_majors(char* majorsFileName);
    void read_students(char* studentsFileName);
    void read_courses(char* courses);
    void read_professors(char* professorsFileName);
    vector<string> split(const string &str, const char delim);
    void identify_method(string mehod);
};