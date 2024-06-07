#include "../includes/get.hpp"

Get::Get()
    : Method()
{
}

Get::~Get()
{
}

void Get::identify_command(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
    vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors)
{
    istringstream iss(line);
    string command;
    iss >> command;

    check_question_mark(line);

    istringstream iss2(line);

    if (command == "courses") {
        handle_courses(line, users, currentUser, lessonID_, lessons, courses, majors, iss2);
    }

    else if (command == "personal_page") {
        handle_personal_page(line, users, currentUser, lessonID_, lessons, courses, majors, iss2);
    }

    else if (command == "post") {
        handle_post(line, users, currentUser, lessonID_, lessons, courses, majors, iss2);
    }

    else if (command == "notification") {
        handle_notif(line, currentUser);
    }

    else if (command == "my_courses") {
        handle_my_courses(line, users, currentUser, lessonID_, lessons, courses, majors, iss2);
    }

    else if (command == "course_channel") {
        handle_course_channel(line, users, currentUser, lessonID_, lessons, courses, majors, iss2);
    }

    else if (command == "course_post") {
        handle_course_post(line, users, currentUser, lessonID_, lessons, courses, majors, iss2);
    }

    else {
        throw Absence();
    }
}

void Get::show_all_lessons(vector<Lesson*>& lessons, vector<Course*>& courses)
{
    if (lessons.size() != 0) {
        for (Lesson* l : lessons) {
            l->show();
        }
    }

    else {
        throw EmptyException();
    }
}

void Get::show_post(User* chosenUser, int postID_, vector<Lesson*>& lessons)
{
    chosenUser->show_personal_info();
    chosenUser->show_post(postID_, lessons);
}

void Get::handle_notif(string line, User*& currentUser)
{
    if (currentUser == nullptr) {
        throw Inaccessibility();
    }

    if (line != EMPTY and !all_is_space(line)) {
        throw BadRequest();
    }

    currentUser->display_all_notifs();
}

void Get::handle_courses(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
    vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2)
{
    string title;
    string key;
    iss2 >> title;
    iss2 >> key;
    if (line == EMPTY || all_is_space(line)) {
        show_all_lessons(lessons, courses);
    }

    else {
        if (title == "id") {
            check_natural_number(key);
            check_lesson_existance(stoi(key), lessons);
            Lesson* chosenLesson = find_lesson_by_id(lessons, key);
            chosenLesson->show_detailed();
        } else {
            throw BadRequest();
        }
    }
}

void Get::handle_personal_page(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
    vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2)
{
    string title;
    string key;
    iss2 >> title;
    iss2 >> key;
    if (currentUser == nullptr) {
        throw Inaccessibility();
    }

    if (line == EMPTY || all_is_space(line)) {
        throw BadRequest();
    }

    else {
        if (title == "id") {
            check_natural_number(key);
            if (!user_exists(key, users)) {
                throw Absence();
            }

            User* chosenUser = find_user_by_id(key, users);
            chosenUser->show_personal_page();
        }

        else {
            throw BadRequest();
        }
    }
}

void Get::handle_my_courses(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
    vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2)
{
    if (line != EMPTY and !all_is_space(line)) {
        throw BadRequest();
    }

    if (currentUser == nullptr) {
        throw Inaccessibility();
    }

    if (currentUser->no_active_lessons()) {
        throw EmptyException();
    }

    currentUser->display_all_lessons();
}

void Get::handle_post(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
    vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2)
{
    Argument user;
    Argument post;
    string title;
    string key;
    iss2 >> title;
    iss2 >> key;
    if (currentUser == nullptr) {
        throw Inaccessibility();
    }

    if (title == "id") {
        user.title = title;
        user.key = key;
        iss2 >> title;
        iss2 >> key;
        if (title == "post_id") {
            post.title = title;
            post.key = key;
        } else {
            throw BadRequest();
        }
    }

    else if (title == "post_id") {
        post.title = title;
        post.key = key;
        iss2 >> title;
        iss2 >> key;
        if (title == "id") {
            user.title = title;
            user.key = key;
        } else {
            throw BadRequest();
        }
    }

    if (!user_exists(user.key, users)) {
        throw Absence();
    }

    User* chosenUser = find_user_by_id(user.key, users);
    check_natural_number(post.key);
    check_natural_number(user.key);

    if (!chosenUser->have_this_post(stoi(post.key))) {
        throw Absence();
    }

    show_post(chosenUser, stoi(post.key), lessons);
}

void Get::handle_course_channel(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
    vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2)
{
    if (currentUser == nullptr) {
        throw Inaccessibility();
    }

    Manager* admin = dynamic_cast<Manager*>(currentUser);
    if (admin)
        throw Inaccessibility();

    if (line == EMPTY || all_is_space(line)) {
        throw BadRequest();
    }

    string title;
    string id;
    iss2 >> title;
    if (title == "id") {
        iss2 >> id;
        check_natural_number(id);
        check_lesson_existance(stoi(id), lessons);
        Lesson* chosenLesson = find_lesson_by_id(lessons, id);
        if (!chosenLesson->is_accessable(currentUser->get_id(), currentUser->have_this_lesson(stoi(id))))
            throw Inaccessibility();
        chosenLesson->show_channel();
    } else {
        throw BadRequest();
    }
}

void Get::handle_course_post(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
    vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2)
{
    if (currentUser == nullptr) {
        throw Inaccessibility();
    }

    Manager* admin = dynamic_cast<Manager*>(currentUser);
    if (admin)
        throw Inaccessibility();

    if (line == EMPTY || all_is_space(line)) {
        throw BadRequest();
    }
    string lessId;
    size_t pos = line.find(" id");
    if (pos == string::npos) {
        throw BadRequest();
    }
    string tempLine = line.substr(pos + 3);
    istringstream tempIss(tempLine);
    tempIss >> lessId;
    check_natural_number(lessId);
    check_lesson_existance(stoi(lessId), lessons);
    Lesson* chosenLesson = find_lesson_by_id(lessons, lessId);
    if (!chosenLesson->is_accessable(currentUser->get_id(), currentUser->have_this_lesson(stoi(lessId))))
        throw Inaccessibility();
    string firstPart = line.substr(0, pos);

    pos = line.find(lessId);
    string secondPart = line.substr(pos + lessId.length(), line.length());

    line = firstPart + secondPart;

    istringstream iss(line);
    Argument post;
    iss >> post.title;
    iss >> post.key;

    if (post.title == "post_id") {
        check_natural_number(post.key);
        if (!chosenLesson->course_post_exists(stoi(post.key))) {
            throw Absence();
        }
        chosenLesson->show_channel_post_detailed(stoi(post.key));
    } else
        throw BadRequest();
}
