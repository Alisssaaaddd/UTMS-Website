#include "../includes/method.hpp"

Method::Method()
{
}

Method::~Method()
{
}

void Method::identify_command(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
    vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors)
{
}

vector<string> Method::split(const string& str, const char delim)
{
    vector<string> strings;
    string::size_type pos = 0;
    string::size_type prev = 0;

    while ((pos = str.find(delim, prev)) != string::npos) {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + sizeof(char);
    }
    strings.push_back(str.substr(prev));
    return strings;
}

Course* Method::find_course_by_id(vector<Course*>& courses, string courseId)
{
    for (Course* c : courses) {
        if (c->get_CID() == courseId) {
            return c;
        }
    }
}

User* Method::find_user_by_id(string id, vector<User*>& users)
{
    for (User* u : users) {
        if (u->get_id() == id) {
            return u;
        }
    }
}

bool Method::can_convert_to_int(const std::string& str)
{
    try {
        size_t pos;
        int value = std::stoi(str, &pos);

        if (pos == str.length() && value >= 0) {
            return true;
        } else {
            return false;
        }
    } catch (const std::exception&) {
        return false;
    }
}

Lesson* Method::find_lesson_by_id(vector<Lesson*>& lessons, string lessonID)
{
    for (Lesson* l : lessons) {
        if (l->get_lessonID() == stoi(lessonID)) {
            return l;
        }
    }
}

bool Method::lesson_exists(int lessonID, vector<Lesson*>& lessons)
{
    for (Lesson* l : lessons) {
        if (l->get_lessonID() == lessonID) {
            return true;
        }
    }

    return false;
}

bool Method::user_exists(string userId, vector<User*> users)
{
    for (User* u : users) {
        if (u->get_id() == userId) {
            return true;
        }
    }

    return false;
}

Notification Method::construct_notif(User* userData, string message)
{
    Notification notif;
    notif.id = userData->get_id();
    notif.name = userData->get_name();
    notif.message = message;
    return notif;
}

bool Method::all_is_space(const std::string& line)
{
    bool isSpace = true;

    for (char c : line) {
        if (c != SPACE) {
            isSpace = false;
            break;
        }
    }

    return isSpace;
}

void Method::check_question_mark(string& line)
{
    istringstream iss(line);
    size_t i = line.find(QUESTION_MARK_STRING);
    if (i != string::npos) {
        line = line.substr(i + 1);
        while (!line.empty() && line[0] == QUESTION_MARK) {
            line = line.substr(1);
        }
    }

    else {
        throw BadRequest();
    }
}

void Method::successful_request()
{
    cout << SUCCESS_MESSAGE << endl;
}

string Method::image_format(string line)
{
    for (string format : SUPPORTED_FORMATS) {
        size_t pos = line.find(format);
        if (pos != string::npos) {
            return format;
        }
    }
    return INVALID_FORMAT;
}

void Method::check_lesson_existance(int lessonID_, vector<Lesson*>& lessons)
{
    if (!lesson_exists(lessonID_, lessons))
        throw Absence();
}

void Method::check_natural_number(string& id)
{
    if (!can_convert_to_int(id))
        throw BadRequest();
}