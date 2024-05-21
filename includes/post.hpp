#pragma once

#include "../includes/consts.hpp"
#include "../includes/method.hpp"

class Post : public Method {
    private:
    
    public:
    Post();
    ~Post();
    void identify_command(string line, vector<User*> &users, User* &currentUser);
    void login(Argument id, Argument password, vector<User*> &users, User* &currentUser);
};