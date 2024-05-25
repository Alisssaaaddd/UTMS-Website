#include "../includes/method.hpp"

Method::Method()
{
}

Method::~Method()
{
}

void Method::identify_command(string line, vector<User *> &users, User *&currentUser, int &lessonID_,
                            vector<Lesson *> &lessons, vector<Course *> &courses, vector<Major *> &majors){
    
}

vector<string> Method::split(const string &str, const char delim)
{
    vector<string> strings;
    string::size_type pos = 0;
    string::size_type prev = 0;

    while ((pos = str.find(delim, prev)) != string::npos)
    {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + sizeof(char);
    }
    strings.push_back(str.substr(prev));
    return strings;
}

Course* Method::find_course_by_id(vector<Course *> &courses, string courseId){
    for(Course* c: courses){
        if(c->get_CID()==courseId){
            return c;
        }
    }
}

User* Method::find_user_by_id(string id ,vector<User*> &users){
    for(User* u: users){
        if(u->get_id()==id){
            return u;
        }
    }
}

bool Method::can_convert_to_int(const std::string &str)
{
    try
    {
        size_t pos;
        std::stoi(str, &pos);

        if (pos == str.length())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    catch (const std::exception &)
    {
        return false;
    }
}

Lesson* Method::find_lesson_by_id(vector<Lesson *> &lessons, string lessonID){
    for(Lesson* l: lessons){
        if(l->get_lessonID()==stoi(lessonID)){
            return l;
        }
    }
}

bool Method::lesson_exists(int lessonID, vector<Lesson* > &lessons){
    for(Lesson* l: lessons){
        if(l->get_lessonID()==lessonID){
            return true;
        }
    }
    
    return false;
}