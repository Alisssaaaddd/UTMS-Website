#include "../includes/put.hpp"

Put::Put() : Method()
{
}

Put::~Put()
{
}

void Put::identify_command(string line, vector<User *> &users, User *&currentUser, int &lessonID_,
                           vector<Lesson *> &lessons, vector<Course *> &courses, vector<Major *> &majors)
{
    istringstream iss(line);
    string command;
    iss >> command;
    
    check_question_mark(line);

    istringstream iss2(line);
    if (command == "my_courses")
    {
        handle_my_courses(line, users, currentUser, lessons, courses, majors, iss2);
    }

    else
    {
        throw Absence();
    }
}

void Put::handle_my_courses(string line, vector<User *> &users, User *&currentUser,
                            vector<Lesson *> &lessons, vector<Course *> &courses, vector<Major *> &majors, istringstream &iss2)
{
    string title;
    string lesID;
    iss2 >> title;
    iss2 >> lesID;

    if (currentUser == nullptr)
    {
        throw Inaccessibility();
    }

    if (title == "id")
    {
        if (!can_convert_to_int(lesID))
        {
            throw BadRequest();
        }

        if (!lesson_exists(stoi(lesID), lessons))
        {
            throw Absence();
        }

        Lesson *chosenLesson = find_lesson_by_id(lessons, lesID);
        Course *course = find_course_by_id(courses, chosenLesson->get_course_id());

        if (!course->valid_major(currentUser->get_majorID()))
        {
            throw Inaccessibility();
        }

        Student *currentStudent = dynamic_cast<Student *>(currentUser);

        if (currentStudent)
        {
            if (!currentStudent->can_take_lesson(chosenLesson))
            {
                throw Inaccessibility();
            }

            if (!chosenLesson->can_accept_this_major(currentStudent->get_majorID()))
            {
                throw Inaccessibility();
            }

            if (currentStudent->does_interfere(chosenLesson) ||
                currentStudent->exam_interfers(chosenLesson->get_date()))
            {
                throw Inaccessibility();
            }

            currentStudent->add_lesson(chosenLesson);
            Notification newNotif = construct_notif(currentStudent, GET_COURSE_NOTIF);
            currentStudent->send_notif(newNotif);
            successful_request();
        }

        else
        {
            throw Inaccessibility();
        }
    }

    else
    {
        throw BadRequest();
    }
}