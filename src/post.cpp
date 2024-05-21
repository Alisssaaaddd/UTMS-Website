#include "../includes/post.hpp"

Post::Post() : Method()
{
}

Post::~Post()
{
}

void Post::login(Argument id, Argument password, vector<User *> &users, User *&currentUser)
{
    bool id_found = false;
    bool password_found = false;
    for (User *u : users)
    {
        if (!u->signed_in())
        {
            if (u->get_id() == id.key and u->get_password() == password.key)
            {
                id_found = true;
                password_found = true;
                u->login();
                currentUser = u;

                break;
            }
        }

        else
        {
            throw Inaccessibility();
        }
    }

    if (id_found == false)
    {
        throw Absence();
    }

    if (password_found == false)
    {
        throw Inaccessibility();
    }

    cout << "OK" << endl;
}

void Post::identify_command(string line, vector<User *> &users, User *&currentUser)
{
    istringstream iss(line);
    string command;
    iss >> command;
    size_t i = line.find("?");
    if (i != string::npos)
    {
        line = line.substr(i + 1);
    }

    else
    {
        throw BadRequest();
    }

    istringstream iss2(line);
    if (command == "login")
    {
        Argument id;
        Argument password;
        string title;
        string key;
        string end;
        iss2 >> title;

        if (title == "id")
        {
            iss2 >> key;
            id.title = title;
            id.key = key;

            iss2 >> title;
            password.title = title;
            iss2 >> key;
            password.key = key;

            iss2 >> end;
            if (end != "")
                throw BadRequest();
        }

        else if (title == "password")
        {
            iss2 >> key;
            password.title = title;
            password.key = key;

            iss2 >> title;
            id.title = title;
            iss2 >> key;
            id.key = key;

            iss2 >> end;
            if (end != "")
                throw BadRequest();
        }

        else
        {
            throw BadRequest();
        }
        login(id, password, users, currentUser);
    }

    else if (command == "logout")
    {
    }

    else if (command == "post")
    {
    }

    else if (command == "connect")
    {
    }

    else if (command == "course_offer")
    {
    }

    else
    {
        throw Absence();
    }
}