#include "../includes/post.hpp"

Post::Post() : Method()
{
}

Post::~Post()
{
}

void Post::login(Argument id, Argument password, vector<User *> &users, User *&currentUser)
{
    bool id_found = user_exists(id.key, users);
    if (!id_found)
    {
        throw Absence();
    }

    User *chosenUser = find_user_by_id(id.key, users);

    if (chosenUser->get_password() != password.key)
    {
        throw Inaccessibility();
    }

    if (chosenUser->signed_in())
    {
        throw Inaccessibility();
    }

    chosenUser->login();
    currentUser = chosenUser;
    successful_request();
}

void Post::identify_command(string line, vector<User *> &users, User *&currentUser, int &lessonID_,
                            vector<Lesson *> &lessons, vector<Course *> &courses, vector<Major *> &majors)
{
    istringstream iss(line);
    string command;
    iss >> command;
    
    check_question_mark(line);

    istringstream iss2(line);
    if (command == "login")
    {
        handle_login(line, users, currentUser, lessonID_, lessons, courses, majors, iss2);
    }

    else if (command == "logout")
    {
        logout(currentUser, line);
    }

    else if (command == "post")
    {
        handle_post(line, users, currentUser, lessonID_, lessons, courses, majors, iss2);
    }

    else if (command == "connect")
    {
        handle_connect(line, users, currentUser, lessonID_, lessons, courses, majors, iss2);
    }

    else if (command == "course_offer")
    {
        handle_course_offer(line, users, currentUser, lessonID_, lessons, courses, majors);
    }

    else
    {
        throw Absence();
    }
}

void Post::logout(User *&currentUser, string line)
{
    if (line != EMPTY and !all_is_space(line))
    {
        throw BadRequest();
    }

    if (currentUser != nullptr)
    {
        currentUser->logout();
        currentUser = nullptr;
        successful_request();;
    }


    else
    {
        throw Inaccessibility();
    }
}

void Post::course_offer(LessonStruct lesson, int &lessonID, User *&currentUser, vector<Lesson *> &lessons,
                        vector<Course *> &courses, vector<Major *> &majors, vector<User *> &users)
{
    Manager *admin = dynamic_cast<Manager *>(currentUser);
    if (admin)
    {
        if (!can_convert_to_int(lesson.courseId) || !can_convert_to_int(lesson.profId) ||
            !can_convert_to_int(lesson.capacity) || !can_convert_to_int(lesson.classNumber))
        {
            throw BadRequest();
        }

        User *chosenUser = find_user_by_id(lesson.profId, users);
        Professor *professor = dynamic_cast<Professor *>(chosenUser);

        if (professor == nullptr)
        {
            throw Inaccessibility();
        }

        Course *chosenCourse = find_course_by_id(courses, lesson.courseId);

        if (!chosenCourse->valid_major(professor->get_majorID()))
        {
            throw Inaccessibility();
        }

        Lesson *newLesson = new Lesson(lesson, lessonID);
        if (professor->does_interfere(newLesson))
        {
            throw Inaccessibility();
        }

        lessons.push_back(newLesson);
        lessonID++;
        professor->add_lesson(newLesson);
        Notification newNotif = construct_notif(professor, COURSE_OFFER_NOTIF);
        send_notif_to_all(newNotif, users);
        successful_request();
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

void Post::connect_users(User *currentUser, User *chosenUser)
{
    currentUser->connect(chosenUser);
    chosenUser->connect(currentUser);
    successful_request();
}

void Post::handle_course_offer(string line, vector<User *> &users, User *&currentUser, int &lessonID_,
                               vector<Lesson *> &lessons, vector<Course *> &courses, vector<Major *> &majors)
{
    vector<string> parts = split(line, SPACE);
    LessonStruct lesson;
    lesson.lessonID = lessonID_;
    int i = 0;
    if (parts.size() != 13)
    {
        throw BadRequest();
    }

    for (int i = 1; i < 13; i += 2)
    {
        if (parts[i] == "course_id")
        {
            if (course_exists(parts[i + 1], courses))
            {
                lesson.courseId = parts[i + 1];
                Course *relatedCourse = find_course_by_id(courses, lesson.courseId);
                lesson.courseName = relatedCourse->get_name();
                lesson.prereq = relatedCourse->get_prereq();
                lesson.majors_id = relatedCourse->get_majors_id();
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
            vector<string> timeParts = split(lesson.weekDay, COLON);
            lesson.weekDay = timeParts[0];
            vector<string> hourParts = split(timeParts[1], HYPHEN);
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

void Post::handle_post(string line, vector<User *> &users, User *&currentUser, int &lessonID_,
                       vector<Lesson *> &lessons, vector<Course *> &courses, vector<Major *> &majors, istringstream &iss2)
{

    PostStruct post;
    string title1;
    iss2 >> title1;

    if (currentUser == nullptr)
    {
        throw Inaccessibility();
    }

    if (title1 == "title")
    {
        size_t i = line.find(DOUBLE_QUOTATION);
        if (i == string::npos)
        {
            throw BadRequest();
        }
        line = line.substr(i + 1);
        istringstream iss3(line);
        string temp;
        getline(iss3, temp, DOUBLE_QUOTATION);
        post.title = temp;

        i = line.find(DOUBLE_QUOTATION);
        if (i == string::npos)
        {
            throw BadRequest();
        }
        line = line.substr(i + 1);

        istringstream iss4(line);
        iss4 >> temp;

        if (temp == "message")
        {
            i = line.find(DOUBLE_QUOTATION);
            if (i == string::npos)
            {
                throw BadRequest();
            }
            line = line.substr(i + 1);
            istringstream iss5(line);
            getline(iss5, temp, DOUBLE_QUOTATION);
            post.message = temp;
        }
        else
        {
            throw BadRequest();
        }
    }
    else if (title1 == "message")
    {
        size_t i = line.find(DOUBLE_QUOTATION);
        if (i == string::npos)
        {
            throw BadRequest();
        }
        line = line.substr(i + 1);
        istringstream iss3(line);
        string temp;
        getline(iss3, temp, DOUBLE_QUOTATION);
        post.message = temp;

        i = line.find(DOUBLE_QUOTATION);
        if (i == string::npos)
        {
            throw BadRequest();
        }
        line = line.substr(i + 1);

        istringstream iss4(line);
        iss4 >> temp;

        if (temp == "title")
        {
            i = line.find(DOUBLE_QUOTATION);
            if (i == string::npos)
            {
                throw BadRequest();
            }
            line = line.substr(i + 1);
            istringstream iss5(line);
            getline(iss5, temp, DOUBLE_QUOTATION);
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

    Notification postNotif = construct_notif(currentUser, NEW_POST_NOTIF);
    post.id = currentUser->get_postID();
    currentUser->add_post(post);
    Manager *admin = dynamic_cast<Manager *>(currentUser);
    if (admin)
    {
        send_notif_to_all(postNotif, users);
    }
    else
    {
        currentUser->send_notif(postNotif);
    }
    successful_request();
}

void Post::handle_login(string line, vector<User *> &users, User *&currentUser, int &lessonID_,
                        vector<Lesson *> &lessons, vector<Course *> &courses, vector<Major *> &majors, istringstream &iss2)
{
    Argument id;
    Argument password;
    string title;
    string key;
    string end;
    iss2 >> title;

    if (currentUser != nullptr)
    {
        throw Inaccessibility();
    }

    if (title == "id")
    {
        iss2 >> key;
        id.title = title;
        id.key = key;

        iss2 >> title;
        if (title == "password")
        {
            password.title = title;
            iss2 >> key;
            password.key = key;
        }

        else
        {
            throw BadRequest();
        }

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
        if (title == "id")
        {
            id.title = title;
            iss2 >> key;
            id.key = key;
        }

        else
        {
            throw BadRequest();
        }

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

void Post::handle_connect(string line, vector<User *> &users, User *&currentUser, int &lessonID_,
                          vector<Lesson *> &lessons, vector<Course *> &courses, vector<Major *> &majors, istringstream &iss2)
{
    string title;
    string userID_;
    iss2 >> title;
    iss2 >> userID_;

    if (currentUser == nullptr)
    {
        throw Inaccessibility();
    }

    if (title == "id")
    {

        if (!can_convert_to_int(userID_))
        {
            throw BadRequest();
        }

        if (currentUser->already_connected(userID_))
        {
            throw BadRequest();
        }

        if (!user_exists(userID_, users))
        {
            throw Absence();
        }

        User *chosenUser = find_user_by_id(userID_, users);
        connect_users(currentUser, chosenUser);
    }

    else
    {
        throw BadRequest();
    }
}

void Post::send_notif_to_all(Notification notif, vector<User *> &users)
{
    for (User *u : users)
    {
        u->receive_notif(notif);
    }
}