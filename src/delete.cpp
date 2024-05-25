#include "../includes/delete.hpp"

Delete::Delete() : Method()
{
}

Delete::~Delete()
{
}

void Delete::identify_command(string line, vector<User *> &users, User *&currentUser, int &lessonID_,
                              vector<Lesson *> &lessons, vector<Course *> &courses, vector<Major *> &majors)
{
    istringstream iss(line);
    string command;
    iss >> command;
    size_t i = line.find("?");
    if (i != string::npos)
    {
        line = line.substr(i + 2);
    }

    else
    {
        throw BadRequest();
    }

    istringstream iss2(line);
    string title;
    string key;
    iss2 >> title;
    iss2 >> key;
    if (command == "post")
    {
        if (line == EMPTY)
        {
            throw Absence();
        }

        else
        {
            if (title == "id")
            {
                if (!can_convert_to_int(key))
                {
                    throw BadRequest();
                }

                currentUser->delete_post(stoi(key));
                cout << "OK" << endl;
            }

            else
            {
                throw BadRequest();
            }
        }
    }

    else if (command == "my_courses")
    {
    }

    else
    {
        throw Absence();
    }
}
