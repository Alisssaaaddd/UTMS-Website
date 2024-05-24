#pragma once

#include "../includes/consts.hpp"
#include "../includes/lesson.hpp"

class User{
    protected:
        string ID;
        string name;
        string majorID;
        string password;
        bool is_signed_in;
        vector<Notification* > notifs;
        vector<Lesson*> activeLessons;

    public:
        User();
        ~User();
        string get_id();
        string get_name();
        string get_majorID();
        string get_password();
        bool signed_in();
        void login();
        void logout();
        virtual void test();
        bool does_interfere(string startTime);
};


class Student : public User{
    private:
        string semester;

    public:
        Student(SD student);
        ~Student();
        void test();
};

class Professor : public User{
    private:
        string position;

    public:
        Professor(PD professor);
        ~Professor();
        void test();
};

class Manager : public User{
    private:

    public:
        Manager();
        ~Manager();
        void test();
};