#include "../includes/user.hpp"

User::User(){
    is_signed_in = false;
    postID = 1;
};

User::~User()
{
}

string User::get_id() { return ID; };
string User::get_name() { return name; };
string User::get_majorID() { return majorID; };
string User::get_password() { return password; };
bool User::signed_in() { return is_signed_in; };
int User::get_postID() {return postID;};

void User::login(){
    is_signed_in = true;
}

void User::logout(){
    is_signed_in = false;
}

void User::test(){

}

bool User::does_interfere(string startTime){
    for(Lesson* l : activeLessons){
        if(l->get_end_time()>stoi(startTime)){
            return true;
        }
    }
    return false;
}

void User::add_lesson(Lesson* &newLesson){
    activeLessons.push_back(newLesson);
}

void User::add_post(PostStruct post){
    posts.push_back(post);
    postID++;
}

Student::Student(SD student) : User()
{
    ID = student.SID;
    name = student.name;
    majorID = student.majorID;
    password = student.password;
    semester = student.semester;
}

Student::~Student()
{
}

void Student::test(){

}


Professor::Professor(PD professor) : User()
{
    ID = professor.PID;
    name = professor.name;
    majorID = professor.majorID;
    password = professor.password;
    position = professor.position;
}

Professor::~Professor()
{
}

void Professor::test(){

}

Manager::Manager() : User()
{
    ID = MANAGER_ID;
    name = MANAGER_NAME;
    majorID = MANAGER_MAJOR_ID;
    password = MANAGER_PASSWORD;
}

Manager::~Manager()
{
}

void Manager::test(){

}