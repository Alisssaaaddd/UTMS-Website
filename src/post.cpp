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
            if (u->get_id() == id.key and u->get_password() == password.key ||
                u->get_id() == MANAGER_ID and u->get_password() == MANAGER_PASSWORD)
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

void Post::identify_command(string line, vector<User *> &users, User *&currentUser, int &lessonID_,
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
            if (end != EMPTY)
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
            if (end != EMPTY)
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
        logout(currentUser);
    }

    else if (command == "post")
    {
        PostStruct post;
        string title1;
        iss2 >> title1;

        if (title1 == "title")
        {
            size_t i = line.find(DOUNLE_QUOTATION);
            line = line.substr(i + 1);
            cout << "line Jadid: " << line << endl;
            istringstream iss3(line);
            string temp;
            getline(iss3, temp, DOUNLE_QUOTATION);
            post.title = temp;
            i = line.find(DOUNLE_QUOTATION);
            line = line.substr(i + 1);

            istringstream iss4(line);
            iss4 >> temp;
            if (temp == "message")
            {
                i = line.find(DOUNLE_QUOTATION);
                line = line.substr(i + 1);
                cout << "line Jadid: " << line << endl;
                istringstream iss5(line);
                getline(iss5, temp, DOUNLE_QUOTATION);
                post.message = temp;
            }
            else
            {
                throw BadRequest();
            }
        }

        else if (title1 == "message")
        {
            size_t i = line.find(DOUNLE_QUOTATION);
            line = line.substr(i + 1);
            istringstream iss3(line);
            string temp;
            getline(iss3, temp, DOUNLE_QUOTATION);
            post.message = temp;
            i = line.find(DOUNLE_QUOTATION);
            line = line.substr(i + 1);

            istringstream iss4(line);
            iss4 >> temp;
            if (temp == "title")
            {
                i = line.find(DOUNLE_QUOTATION);
                line = line.substr(i + 1);
                istringstream iss5(line);
                getline(iss5, temp, DOUNLE_QUOTATION);
                post.title = temp;
            }
            else
            {
                throw BadRequest();
            }
        }

        else
        {
            throw BadRequest();
        }

        post.id = currentUser->get_postID();
        currentUser->add_post(post);
        cout << "OK" << endl;
        cout << post.id << " " << post.title << " " << post.message << endl;
    }

    else if (command == "connect")
    {
    }

    else if (command == "course_offer")
    {
        vector<string> parts = split(line, SPACE);
        LessonStruct lesson;
        lesson.lessonID = lessonID_;

        if (parts.size() != 12)
        {
            throw BadRequest();
        }

        for (int i = 0; i < parts.size(); i += 2)
        {
            if (parts[i] == "course_id")
            {
                if (course_exists(parts[i + 1], courses))
                {
                    lesson.courseId = parts[i + 1];
                    Course *relatedCourse = find_course_by_id(courses, lesson.courseId);
                    lesson.courseName = relatedCourse->get_name();
                }
                else
                {
                    throw Absence();
                }
            }

            else if (parts[i] == "professor_id")
            {
                if (user_exists(parts[i + 1], users))
                {
                    lesson.profId = parts[i + 1];
                    User *prof = find_user_by_id(lesson.profId, users);
                    lesson.profName = prof->get_name();
                }
                else
                {
                    throw Absence();
                }
            }

            else if (parts[i] == "capacity")
            {
                lesson.capacity = parts[i + 1];
            }

            else if (parts[i] == "time")
            {
                lesson.weekDay = parts[i + 1];
                vector<string> timeParts = split(lesson.weekDay, ':');
                lesson.weekDay = timeParts[0];
                vector<string> hourParts = split(timeParts[1], '-');
                lesson.startTime = hourParts[0];
                lesson.endTime = hourParts[1];
            }

            else if (parts[i] == "exam_date")
            {
                lesson.date = parts[i + 1];
            }

            else if (parts[i] == "class_number")
            {
                lesson.classNumber = parts[i + 1];
            }
        }
        course_offer(lesson, lessonID_, currentUser, lessons, courses, majors, users);
    }

    else
    {
        throw Absence();
    }
}

void Post::logout(User *&currentUser)
{
    if (currentUser != nullptr)
    {
        currentUser->logout();
        currentUser = nullptr;
        cout << "OK" << endl;
    }
    else
    {
        throw Inaccessibility();
    }
}

void Post::course_offer(LessonStruct lesson, int &lessonID, User *&currentUser, vector<Lesson *> &lessons,
                        vector<Course *> &courses, vector<Major *> &majors, vector<User *> &users)
{
    Manager *UTaccount = dynamic_cast<Manager *>(currentUser);
    if (UTaccount)
    {
        // cout << "course: " << course_exists(lesson.courseId, courses) << endl;
        // cout << "user: " << user_exists(lesson.profId, users) << endl;
        if (!can_convert_to_int(lesson.courseId) || !can_convert_to_int(lesson.profId) ||
            !can_convert_to_int(lesson.capacity) || !can_convert_to_int(lesson.classNumber))
        {
            cout << "Adad Nist!" << endl;
            throw BadRequest();
        }

        if (!is_prof(lesson.profId, users))
        {
            cout << "Ostad Nist!" << endl;
            throw Inaccessibility();
        }

        if (!is_major_valid(users, majors))
        {
            cout << "Reshte kharab!" << endl;
            throw Inaccessibility();
        }

        User *chosenProf = find_user_by_id(lesson.profId, users);
        if (chosenProf->does_interfere(lesson.startTime))
        {
            cout << "Tadakghod Dare" << endl;
            throw Inaccessibility();
        }

        cout << "OK" << endl;
        Lesson *newLesson = new Lesson(lesson, lessonID);
        lessons.push_back(newLesson);
        chosenProf->add_lesson(newLesson);

        // send notification of a new lesson to all users of the website and add the lesson to folder of all of them
    }

    else
    {
        throw Inaccessibility();
    }
}

bool Post::course_exists(string courseId, vector<Course *> courses)
{
    for (Course *c : courses)
    {
        if (c->get_CID() == courseId)
        {
            return true;
        }
    }

    return false;
}

bool Post::user_exists(string userId, vector<User *> users)
{
    for (User *u : users)
    {
        if (u->get_id() == userId)
        {
            return true;
        }
    }

    return false;
}

bool Post::is_prof(string userId, vector<User *> users)
{
    for (User *u : users)
    {
        if (u->get_id() == userId)
        {
            Professor *prof = dynamic_cast<Professor *>(u);
            if (prof)
            {
                return true;
            }
        }
    }

    return false;
}

bool Post::is_major_valid(vector<User *> users, vector<Major *> majors)
{
    for (User *u : users)
    {
        for (Major *m : majors)
        {
            if (u->get_majorID() == m->get_MID())
            {
                return true;
            }
        }
    }

    return false;
}