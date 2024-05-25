#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <exception>

#include "../includes/date.hpp"

using namespace std;

typedef struct StudentData
{
    string SID;
    string name;
    string majorID;
    string semester;
    string password;
} SD;

typedef struct ProfessorData
{
    string PID;
    string name;
    string majorID;
    string position;
    string password;
} PD;

typedef struct MajorData
{
    string MID;
    string name;
} MD;

typedef struct CourseData
{
    string CID;
    string name;
    string credit;
    string prereq;
    vector<string> majors_id;

} CD;

struct Argument
{
    string title;
    string key;
};

struct Time
{
    string weekDay;
    string startTime;
    string endTime;
};

struct LessonStruct
{
    string courseName;
    string profName;
    string courseId;
    string profId;
    string capacity;
    string weekDay;
    string startTime;
    string endTime;
    string date;
    string classNumber;
    int lessonID;   
};

struct Notification{
    string test;
    string salam;
};

struct PostStruct
{
    int id;
    string title;
    string message;
};



const string MAJORS_FILE_PATH = "./files/majors.csv",
             STUDENTS_FILE_PATH = "./files/students.csv",
             COURSES_FILE_PATH = "./files/courses.csv",
             PROFESSORS_FILE_PATH = "./files/professors.csv";

const char COMMA = ',',
           SEMI_COLON = ';',
           SPACE = ' ';
const string EMPTY = "";

const string MANAGER_ID = "0";
const string MANAGER_PASSWORD = "UT_account";
const string MANAGER_NAME = "defaultUser";
const string MANAGER_MAJOR_ID = "managerMajorId";
const char DOUNLE_QUOTATION = '"';


