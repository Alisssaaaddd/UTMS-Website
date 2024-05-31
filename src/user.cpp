#include "../includes/user.hpp"

User::User(MD major_)
{
    is_signed_in = false;
    postID = 1;
    major.MID = major_.MID;
    major.name = major_.name;
};

User::~User()
{
}

string User::get_id() { return ID; };
string User::get_name() { return name; };
string User::get_majorID() { return majorID; };
string User::get_password() { return password; };
bool User::signed_in() { return is_signed_in; };
int User::get_postID() { return postID; };
string User::get_profile_photo_path() {return profile_photo_path;};

void User::login()
{
    is_signed_in = true;
}

void User::logout()
{
    is_signed_in = false;
}

void User::show_personal_page()
{
}

bool User::does_interfere(Lesson *lesson_)
{
    bool day_interference = false;
    bool time_interference = false;
    for (Lesson *l : activeLessons)
    {
        day_interference = false;
        if (lesson_->get_week_day() == l->get_week_day())
        {
            day_interference = true;
            if (day_interference)
            {
                if (stoi(l->get_end_time()) > stoi(lesson_->get_start_time()))
                {
                    time_interference = true;
                    break;
                }
            }
        }
    }

    if (day_interference and time_interference)
    {
        return true;
    }

    return false;
}

void User::add_lesson(Lesson *&newLesson)
{
    activeLessons.push_back(newLesson);
}

void User::add_post(PostStruct &post)
{
    posts.push_back(post);
    postID++;
}

void User::delete_post(int postID_)
{
    bool valid_post = false;
    for (auto p = posts.begin(); p != posts.end(); ++p)
    {
        if (p->id == postID_)
        {
            valid_post = true;
            posts.erase(p);
            break;
        }
    }

    if (!valid_post)
    {
        throw Absence();
    }
}

string User::lessons_in_line()
{
    string ll = "";
    for (int i = 0; i < activeLessons.size(); i++)
    {
        ll += activeLessons[i]->get_course_name();
        if (i != activeLessons.size() - 1)
        {
            ll += COMMA;
        }
    }
    return ll;
}

void User::show_post_titles()
{
    for (PostStruct p : posts)
    {
        cout << p.id << SPACE << DOUBLE_QUOTATION << p.title << DOUBLE_QUOTATION << endl;
    }
}

void User::show_personal_info()
{
}

void User::show_post(int postID_)
{
    for (PostStruct p : posts)
    {
        if (p.id == postID_)
        {
            cout << p.id << SPACE << DOUBLE_QUOTATION << p.title << DOUBLE_QUOTATION << SPACE;
            cout << DOUBLE_QUOTATION << p.message << DOUBLE_QUOTATION << endl;
        }
    }
}

bool User::have_this_post(int postID_)
{
    for (PostStruct p : posts)
    {
        if (p.id == postID_)
        {
            return true;
        }
    }
    return false;
}

bool User::already_connected(string userID_)
{
    for (User *u : connections)
    {
        if (u->get_id() == userID_)
        {
            return true;
        }
    }
    return false;
}

void User::connect(User *chosenUser)
{
    connections.push_back(chosenUser);
}

void User::receive_notif(Notification newNotif)
{
    notifs.push_back(newNotif);
}

void User::display_all_notifs()
{
    if (notifs.size() == 0)
    {
        throw EmptyException();
    }

    for (int i = notifs.size() - 1; i >= 0; i--)
    {
        display_notif(notifs[i]);
    }

    notifs.clear();
}

void User::display_notif(Notification notif)
{
    cout << notif.id << SPACE << notif.name << COLON << SPACE << notif.message << endl;
}

void User::send_notif(Notification postNotif)
{
    for (User *u : connections)
    {
        u->receive_notif(postNotif);
    }
}

bool User::have_this_lesson(int lessId_)
{
    for (Lesson *l : activeLessons)
    {
        if (lessId_ == l->get_lessonID())
        {
            return true;
        }
    }
    return false;
}

void User::delete_lesson(int lessId_)
{
    bool valid_lesson = false;

    for (int i = 0; i < activeLessons.size(); i++)
    {
        if (activeLessons[i]->get_lessonID() == lessId_)
        {
            activeLessons.erase(activeLessons.begin() + i);
            valid_lesson = true;
        }
    }

    if (!valid_lesson)
    {
        throw Absence();
    }
}

bool User::no_active_lessons()
{
    if (activeLessons.size() == 0)
    {
        return true;
    }
    return false;
}

void User::display_all_lessons()
{
    for (Lesson *l : activeLessons)
    {
        l->display();
    }
}

void User::set_profile(string newPath){
    profile_photo_path = newPath;
}

Student::Student(SD student, MD major_) : User(major_)
{
    ID = student.SID;
    name = student.name;
    majorID = student.majorID;
    password = student.password;
    semester = student.semester;
}

Student::~Student()
{
}

void Student::show_personal_page()
{
    show_personal_info();
    show_post_titles();
}

void Student::show_personal_info()
{
    cout << name << SPACE << major.name << SPACE << semester
         << SPACE << lessons_in_line() << endl;
}

bool Student::can_take_lesson(Lesson *&lesson_)
{
    if (semester < lesson_->get_prereq())
    {
        return false;
    }
    return true;
}

bool Student::exam_interfers(string examDate_)
{
    for (Lesson *l : activeLessons)
    {
        if (l->get_date() == examDate_)
        {
            return true;
        }
    }
    return false;
}

Professor::Professor(PD professor, MD major_) : User(major_)
{
    ID = professor.PID;
    name = professor.name;
    majorID = professor.majorID;
    password = professor.password;
    position = professor.position;
}

Professor::~Professor()
{
}

void Professor::show_personal_page()
{
    show_personal_info();
    show_post_titles();
}

void Professor::show_personal_info()
{
    cout << name << SPACE << major.name << SPACE << position
         << SPACE << lessons_in_line() << endl;
}

Manager::Manager(MD major_) : User(major_)
{
    ID = MANAGER_ID;
    name = MANAGER_NAME;
    majorID = MANAGER_MAJOR_ID;
    password = MANAGER_PASSWORD;
}

Manager::~Manager()
{
}

void Manager::show_personal_page()
{
    show_personal_info();
    show_post_titles();
}

void Manager::show_personal_info()
{
    cout << MANAGER_PASSWORD << endl;
}
