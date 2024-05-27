#include "../includes/get.hpp"

Get::Get() : Method()
{
}

Get::~Get()
{
}

void Get::identify_command(string line, vector<User *> &users, User *&currentUser, int &lessonID_,
                           vector<Lesson *> &lessons, vector<Course *> &courses, vector<Major *> &majors)
{
    istringstream iss(line);
    string command;
    iss >> command;
    size_t i = line.find("?");
    if (i != string::npos)
    {
        line = line.substr(i + 1);
        while (!line.empty() && line[0] == '?')
        {
            line = line.substr(1);
        }
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
    if (command == "courses")
    {
        if (line == EMPTY)
        {
            show_all_lessons(lessons, courses);
        }

        else
        {
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
                chosenLesson->show_detailed();
            }
            else
            {
                throw BadRequest();
            }
        }
    }

    else if (command == "personal_page")
    {
        if (line == EMPTY)
        {
            throw BadRequest();
        }

        if (currentUser == nullptr)
        {
            throw Inaccessibility();
        }

        else
        {
            if (title == "id")
            {
                if (!can_convert_to_int(key))
                {
                    throw BadRequest();
                }

                if (!user_exists(key, users))
                {
                    throw Absence();
                }

                User *chosenUser = find_user_by_id(key, users);
                chosenUser->show_personal_page();
            }

            else
            {
                throw BadRequest();
            }
        }
    }

    else if (command == "post")
    {
        istringstream iss2(line);
        Argument user;
        Argument post;
        string title;
        string key;
        iss2>>title;
        iss2>>key;
        if (currentUser == nullptr)
        {
            throw Inaccessibility();
        }

        if (title == "id")
        {
            user.title = title;
            user.key = key;
            iss2>>title;
            iss2>>key;
            if (title == "post_id")
            {
                post.title = title;
                post.key = key;
            }
            else
            {
                throw BadRequest();
            }
        }

        else if (title == "post_id")
        {
            post.title = title;
            post.key = key;
            iss2>>title;
            iss2>>key;
            if (title == "id")
            {
                user.title = title;
                user.key = key;
            }
            else
            {
                throw BadRequest();
            }
        }

        if (!user_exists(user.key, users))
        {
            throw Absence();
        }

        User *chosenUser = find_user_by_id(user.key, users);

        if (!can_convert_to_int(post.key) || !can_convert_to_int(user.key))
        {
            throw BadRequest();
        }

        if (!chosenUser->have_this_post(stoi(post.key)))
        {
            throw Absence();
        }

        show_post(chosenUser, stoi(post.key));
    }

    else if (command == "notification")
    {
        handle_notif(line, currentUser);
    }

    else if (command == "my_courses")
    {
        if (currentUser == nullptr)
        {
            throw Inaccessibility();
        }

        if(currentUser->no_active_lessons()){
            throw EmptyException();
        }

        currentUser->display_all_lessons();
    }

    else
    {
        throw Absence();
    }
}

void Get::show_all_lessons(vector<Lesson *> &lessons, vector<Course *> &courses)
{
    if (lessons.size() != 0)
    {
        for (Lesson *l : lessons)
        {
            l->show();
        }
    }

    else
    {
        throw EmptyException();
    }
}

void Get::show_post(User *chosenUser, int postID_)
{
    chosenUser->show_personal_info();
    chosenUser->show_post(postID_);
}

void Get::handle_notif(string line, User* &currentUser)
{
    if (currentUser == nullptr)
    {
        throw Inaccessibility();
    }

    if (line != EMPTY)
    {
        throw BadRequest();
    }

    currentUser->display_all_notifs();
}