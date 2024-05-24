#pragma once

#include "../includes/consts.hpp"
#include "../includes/error.hpp"
#include "../includes/user.hpp"

class Method{
    protected:
        vector<string> commands;
        
    public:
    Method();
    ~Method();
    virtual void identify_command(string command, vector<User*> users, User* &currentUser);
    vector<string> split(const string &str, const char delim);
};
