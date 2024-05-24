#include "../includes/method.hpp"

Method::Method()
{
}

Method::~Method()
{
}

void Method::identify_command(string command, vector<User*> users, User* &currentUser){

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