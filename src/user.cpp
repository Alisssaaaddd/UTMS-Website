#include "../includes/user.hpp"

User::User(){
    
};

User::~User(){

}

Student::Student(SD student) : User() {
    ID = student.SID;
    name = student.name;
    majorID = student.majorID;
    password = student.password;
    semester = student.semester;
}

Student::~Student(){

}

Professor::Professor(PD professor): User() {
    ID = professor.PID;
    name = professor.name;
    majorID = professor.majorID;
    password = professor.password;
    position = professor.position;
}

Professor::~Professor(){

}

Manager::Manager() : User() {
    ID = MANAGER_ID;
    name = MANAGER_NAME;
    majorID = MANAGER_MAJOR_ID;
    password = MANAGER_PASSWORD;
}

Manager::~Manager(){
    
}