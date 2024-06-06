#pragma once

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

typedef struct StudentData {
    string SID;
    string name;
    string majorID;
    string semester;
    string password;
} SD;

typedef struct ProfessorData {
    string PID;
    string name;
    string majorID;
    string position;
    string password;
} PD;

typedef struct MajorData {
    string MID;
    string name;
} MD;

typedef struct CourseData {
    string CID;
    string name;
    string credit;
    string prereq;
    vector<string> majors_id;

} CD;

struct Argument {
    string title;
    string key;
};

struct Time {
    string weekDay;
    string startTime;
    string endTime;
};

struct LessonStruct {
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
    string prereq;
    vector<string> majors_id;
    int lessonID;
};

struct Notification {
    string id = "nothing";
    string name;
    string message;
};

struct PostStruct {
    int id = -2;
    string type = "ordinary";
    string title;
    string message;
    string image = "NO IMAGE";
    string sender = "NO NAME";
    string lessonId = "NO ID";
};

const char COMMA = ',',
           SEMI_COLON = ';',
           SPACE = ' ',
           COLON = ':',
           HYPHEN = '-',
           QUESTION_MARK = '?';
const char DOUBLE_QUOTATION = '"';
const string EMPTY = "";
const string QUESTION_MARK_STRING = "?";

const string MANAGER_ID = "0";
const string MANAGER_PASSWORD = "UT_account";
const string MANAGER_NAME = "UT_account";
const string MANAGER_MAJOR_ID = "managerMajorId";
const string COURSE_OFFER_NOTIF = "New Course Offering";
const string NEW_POST_NOTIF = "New Post";
const string DELETE_COURSE_NOTIF = "Delete Course";
const string GET_COURSE_NOTIF = "Get Course";
const string NEW_FORM_NOTIF = "New Form";
const string NEW_COURSE_POST_NOTIF = "New Course Post";
const string TA_REJECT_NOTIF = "Your request to be a teaching assistant has been rejected";
const string TA_ACCEPT_NOTIF = "Your request to be a teaching assistant has been accepted";
const string SUCCESS_MESSAGE = "OK";
const string FORM_POST_PRE_TITLE = "TA form for ";
const string FORM_POST_END_TITLE = " course";
const string SHOW_REQUESTS_PRE_TITLE = "We have received ";
const string SHOW_REQUESTS_END_TITLE = " requests for the teaching assistant position";
const string ORD_POST_TYPE = "ordinary";
const string TA_FORM_TYPE = "ta_form";
const string REJECT_REPLY = "reject";
const string ACCEPT_REPLY = "accept";

const vector<string> SUPPORTED_FORMATS = { ".jpg", ".JPG", ".GIF", ".gif", ".JPEG", ".jpeg",
    ".PNG", ".png", ".WEBP", ".webp", ".XPS", ".xps", ".tiff", ".TIFF", ".svg", ".SVG" };

const string INVALID_FORMAT = "foramt is not supported!";