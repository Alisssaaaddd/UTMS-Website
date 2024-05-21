#pragma once

#include "../includes/consts.hpp"

class User{
    protected:
        string ID;
        string name;
        string majorID;
        string password;

    public:
        User();
        ~User();
};


class Student : public User{
    private:
        string semester;

    public:
        Student(SD student);
        ~Student();
};

class Professor : public User{
    private:
        string position;

    public:
        Professor(PD professor);
        ~Professor();
};

class Manager : public User{
    private:

    public:
        Manager();
        ~Manager();
};