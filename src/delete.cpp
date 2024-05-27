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
    if (command == "post")
    {
        handle_post(line, users, currentUser, lessonID_, lessons, courses, majors, iss2);
    }

    else if (command == "my_courses")
    {
        handle_my_courses(line, users, currentUser, lessonID_, lessons, courses, majors, iss2);
    }

    else
    {
        throw Absence();
    }
}

void Delete::handle_post(string line, vector<User *> &users, User *&currentUser, int &lessonID_,
                         vector<Lesson *> &lessons, vector<Course *> &courses, vector<Major *> &majors, istringstream &iss2)
{
    string title;
    string key;
    iss2 >> title;
    iss2 >> key;
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

void Delete::handle_my_courses(string line, vector<User *> &users, User *&currentUser, int &lessonID_,
                               vector<Lesson *> &lessons, vector<Course *> &courses, vector<Major *> &majors, istringstream &iss2)
{
    string title;
    string key;
    iss2 >> title;
    iss2 >> key;
    if (currentUser == nullptr)
    {
        throw Inaccessibility();
    }

    if (title == "id")
    {
        if (!can_convert_to_int(key))
        {
            throw BadRequest();
        }

        if (!lesson_exists(stoi(key), lessons))
        {
            throw Absence();
        }

        Lesson *chosenLesson = find_lesson_by_id(lessons, key);

        Student *currentStudent = dynamic_cast<Student *>(currentUser);

        if (currentStudent)
        {
            if (!currentStudent->have_this_lesson(stoi(key)))
            {
                throw Absence();
            }

            currentStudent->delete_lesson(stoi(key));
            Notification newNotif = construct_notif(currentStudent, DELETE_COURSE_NOTIF);
            currentStudent->send_notif(newNotif);
            cout << "OK" << endl;
        }
    }

    else{
        throw BadRequest();
    }
}