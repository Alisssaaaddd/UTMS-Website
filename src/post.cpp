#include "../includes/post.hpp"

Post::Post()
    : Method()
{
}

Post::~Post()
{
}

void Post::login(Argument id, Argument password, vector<User*>& users, User*& currentUser)
{
    bool id_found = user_exists(id.key, users);
    if (!id_found) {
        throw Absence();
    }

    User* chosenUser = find_user_by_id(id.key, users);

    if (chosenUser->get_password() != password.key) {
        throw Inaccessibility();
    }

    if (chosenUser->signed_in()) {
        throw Inaccessibility();
    }

    chosenUser->login();
    currentUser = chosenUser;
    successful_request();
}

void Post::identify_command(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
    vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors)
{
    istringstream iss(line);
    string command;
    iss >> command;

    check_question_mark(line);

    istringstream iss2(line);
    if (command == "login") {
        handle_login(line, users, currentUser, lessonID_, lessons, courses, majors, iss2);
    }

    else if (command == "logout") {
        logout(currentUser, line);
    }

    else if (command == "post") {
        handle_post(line, users, currentUser, lessonID_, lessons, courses, majors, iss2);
    }

    else if (command == "connect") {
        handle_connect(line, users, currentUser, lessonID_, lessons, courses, majors, iss2);
    }

    else if (command == "course_offer") {
        handle_course_offer(line, users, currentUser, lessonID_, lessons, courses, majors);
    }

    else if (command == "profile_photo") {
        handle_profile_photo(line, users, currentUser, lessonID_, lessons, courses, majors, iss2);
    }

    else if (command == "course_post") {
        handle_course_post(line, users, currentUser, lessonID_, lessons, courses, majors, iss2);
    }

    else if (command == "ta_form") {
        handle_ta_form(line, users, currentUser, lessonID_, lessons, courses, majors, iss2);
    }

    else if (command == "close_ta_form") {
        handle_closing_ta_form(line, users, currentUser, lessonID_, lessons, courses, majors, iss2);
    }

    else if (command == "ta_request") {
        handle_ta_request(line, users, currentUser, lessonID_, lessons, courses, majors, iss2);
    }

    else {
        throw Absence();
    }
}

void Post::logout(User*& currentUser, string line)
{
    if (line != EMPTY and !all_is_space(line)) {
        throw BadRequest();
    }

    if (currentUser != nullptr) {
        currentUser->logout();
        currentUser = nullptr;
        successful_request();
    }

    else {
        throw Inaccessibility();
    }
}

void Post::course_offer(LessonStruct lesson, int& lessonID, User*& currentUser, vector<Lesson*>& lessons,
    vector<Course*>& courses, vector<Major*>& majors, vector<User*>& users)
{
    Manager* admin = dynamic_cast<Manager*>(currentUser);
    if (admin) {
        if (!can_convert_to_int(lesson.courseId) || !can_convert_to_int(lesson.profId) || !can_convert_to_int(lesson.capacity) || !can_convert_to_int(lesson.classNumber)) {
            throw BadRequest();
        }

        User* chosenUser = find_user_by_id(lesson.profId, users);
        Professor* professor = dynamic_cast<Professor*>(chosenUser);

        if (professor == nullptr) {
            throw Inaccessibility();
        }

        Course* chosenCourse = find_course_by_id(courses, lesson.courseId);

        if (!chosenCourse->valid_major(professor->get_majorID())) {
            throw Inaccessibility();
        }

        Lesson* newLesson = new Lesson(lesson, lessonID);
        if (professor->does_interfere(newLesson)) {
            throw Inaccessibility();
        }

        lessons.push_back(newLesson);
        lessonID++;
        professor->add_lesson(newLesson);
        Notification newNotif = construct_notif(professor, COURSE_OFFER_NOTIF);
        send_notif_to_all(newNotif, users);
        successful_request();
    }

    else {
        throw Inaccessibility();
    }
}

bool Post::course_exists(string courseId, vector<Course*> courses)
{
    for (Course* c : courses) {
        if (c->get_CID() == courseId) {
            return true;
        }
    }

    return false;
}

bool Post::is_prof(string userId, vector<User*> users)
{
    for (User* u : users) {
        if (u->get_id() == userId) {
            Professor* prof = dynamic_cast<Professor*>(u);
            if (prof) {
                return true;
            }
        }
    }

    return false;
}

void Post::connect_users(User* currentUser, User* chosenUser)
{
    currentUser->connect(chosenUser);
    chosenUser->connect(currentUser);
    successful_request();
}

void Post::handle_course_offer(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
    vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors)
{
    vector<string> parts = split(line, SPACE);
    LessonStruct lesson;
    lesson.lessonID = lessonID_;
    int i = 0;
    if (parts.size() != 13) {
        throw BadRequest();
    }

    for (int i = 1; i < 13; i += 2) {
        if (parts[i] == "course_id") {
            read_course_id_for_course_offer(courses, lesson, parts[i + 1]);
        }

        else if (parts[i] == "professor_id") {
            read_professor_id_for_course_offer(parts[i + 1], lesson, users);
        }

        else if (parts[i] == "capacity") {
            lesson.capacity = parts[i + 1];
        }

        else if (parts[i] == "time") {
            read_time_for_course_offer(lesson, parts[i + 1]);
        }

        else if (parts[i] == "exam_date") {
            lesson.date = parts[i + 1];
        }

        else if (parts[i] == "class_number") {
            lesson.classNumber = parts[i + 1];
        }
    }
    course_offer(lesson, lessonID_, currentUser, lessons, courses, majors, users);
}

void Post::read_course_id_for_course_offer(vector<Course*>& courses, LessonStruct& lesson, string& nextPart)
{
    if (course_exists(nextPart, courses)) {
        lesson.courseId = nextPart;
        Course* relatedCourse = find_course_by_id(courses, lesson.courseId);
        lesson.courseName = relatedCourse->get_name();
        lesson.prereq = relatedCourse->get_prereq();
        lesson.majors_id = relatedCourse->get_majors_id();
    } else {
        throw Absence();
    }
}

void Post::read_professor_id_for_course_offer(string& nextPart, LessonStruct& lesson, vector<User*>& users)
{
    if (user_exists(nextPart, users)) {
        lesson.profId = nextPart;
        User* prof = find_user_by_id(lesson.profId, users);
        lesson.profName = prof->get_name();
    } else {
        throw Absence();
    }
}

void Post::read_time_for_course_offer(LessonStruct& lesson, string& nextPart)
{
    lesson.weekDay = nextPart;
    vector<string> timeParts = split(lesson.weekDay, COLON);
    lesson.weekDay = timeParts[0];
    vector<string> hourParts = split(timeParts[1], HYPHEN);
    lesson.startTime = hourParts[0];
    lesson.endTime = hourParts[1];
}

void Post::handle_post(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
    vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2)
{

    PostStruct post;
    string first_argument;
    iss2 >> first_argument;

    check_user_loged_in(currentUser);

    if (first_argument == "title") {
        handle_title_first(line, post);
    }

    else if (first_argument == "message") {
        handle_message_first(line, post);
    }

    else if (first_argument == "image") {
        handle_image_first(line, post);
    }

    else {
        throw BadRequest();
    }
    send_post_notification(currentUser, post, users);
    successful_request();
}

void Post::handle_login(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
    vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2)
{
    Argument id;
    Argument password;
    string title;
    string key;
    string end;
    iss2 >> title;

    if (currentUser != nullptr) {
        throw Inaccessibility();
    }

    if (title == "id") {
        iss2 >> key;
        id.title = title;
        id.key = key;

        iss2 >> title;
        if (title == "password") {
            password.title = title;
            iss2 >> key;
            password.key = key;
        }

        else {
            throw BadRequest();
        }

        iss2 >> end;
        if (end != EMPTY)
            throw BadRequest();
    }

    else if (title == "password") {
        iss2 >> key;
        password.title = title;
        password.key = key;

        iss2 >> title;
        if (title == "id") {
            id.title = title;
            iss2 >> key;
            id.key = key;
        }

        else {
            throw BadRequest();
        }

        iss2 >> end;
        check_next_is_nothing(iss2, end);
    }

    else {
        throw BadRequest();
    }

    login(id, password, users, currentUser);
}

void Post::handle_connect(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
    vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2)
{
    string title;
    string userID_;
    iss2 >> title;
    iss2 >> userID_;

    check_user_loged_in(currentUser);

    if (title == "id") {
        check_natural_number(userID_);
        if (currentUser->already_connected(userID_)) {
            throw BadRequest();
        }
        check_user_existance(userID_, users);

        User* chosenUser = find_user_by_id(userID_, users);
        connect_users(currentUser, chosenUser);
    }

    else {
        throw BadRequest();
    }
}

void Post::send_notif_to_all(Notification notif, vector<User*>& users)
{
    for (User* u : users) {
        u->receive_notif(notif);
    }
}

void Post::read_post_title(string& line, PostStruct& post)
{
    size_t i = line.find(DOUBLE_QUOTATION);
    if (i == string::npos) {
        throw BadRequest();
    }
    line = line.substr(i + 1);
    istringstream iss3(line);
    string temp;
    getline(iss3, temp, DOUBLE_QUOTATION);
    post.title = temp;

    i = line.find(DOUBLE_QUOTATION);
    if (i == string::npos) {
        throw BadRequest();
    }
    line = line.substr(i + 1);
}

void Post::read_post_message(string& line, PostStruct& post)
{
    size_t i = line.find(DOUBLE_QUOTATION);
    if (i == string::npos) {
        throw BadRequest();
    }
    line = line.substr(i + 1);
    istringstream iss5(line);
    string temp;
    getline(iss5, temp, DOUBLE_QUOTATION);
    post.message = temp;

    i = line.find(DOUBLE_QUOTATION);
    if (i == string::npos) {
        throw BadRequest();
    }
    line = line.substr(i + 1);
}

void Post::read_post_image(string& line, PostStruct& post)
{
    size_t i = line.find("image");
    line = line.substr(i + 6);
    string format = image_format(line);
    i = line.find(format);
    string path = line.substr(0, i + format.size());
    post.image = path;
    line = line.substr(i + format.size());
}

void Post::handle_title_first(string& line, PostStruct& post)
{
    read_post_title(line, post);
    istringstream iss4(line);
    string second_argument;
    iss4 >> second_argument;

    if (second_argument == "message") {
        read_post_message(line, post);

        if (line != EMPTY and !all_is_space(line)) {
            istringstream iss5(line);
            string third_argument;
            iss5 >> third_argument;

            if (third_argument == "image") {
                read_post_image(line, post);
            }

            else {
                throw BadRequest();
            }
        }
    }

    else if (second_argument == "image") {
        read_post_image(line, post);
        istringstream iss5(line);
        string third_argument;
        iss5 >> third_argument;
        if (third_argument == "message") {
            read_post_message(line, post);
        }

        else {
            throw BadRequest();
        }
    }

    else {
        throw BadRequest();
    }
}

void Post::handle_message_first(string& line, PostStruct& post)
{
    read_post_message(line, post);
    istringstream iss4(line);
    string second_argument;
    iss4 >> second_argument;

    if (second_argument == "title") {
        read_post_title(line, post);

        if (line != EMPTY and !all_is_space(line)) {

            istringstream iss5(line);
            string third_argument;
            iss5 >> third_argument;
            if (third_argument == "image") {
                read_post_image(line, post);
            } else {
                throw BadRequest();
            }
        }
    }

    else if (second_argument == "image") {
        read_post_image(line, post);
        istringstream iss5(line);
        string third_argument;
        iss5 >> third_argument;

        if (third_argument == "title") {
            read_post_title(line, post);
        }

        else {
            throw BadRequest();
        }
    }

    else {
        throw BadRequest();
    }
}

void Post::handle_image_first(string& line, PostStruct& post)
{
    read_post_image(line, post);
    istringstream iss4(line);
    string second_argument;
    iss4 >> second_argument;

    if (second_argument == "title") {
        read_post_title(line, post);
        istringstream iss5(line);
        string third_argument;
        iss5 >> third_argument;

        if (third_argument == "message") {
            read_post_message(line, post);
        }

        else {
            throw BadRequest();
        }
    }

    else if (second_argument == "message") {
        read_post_message(line, post);
        istringstream iss5(line);
        string third_argument;
        iss5 >> third_argument;

        if (third_argument == "title") {
            read_post_title(line, post);
        }

        else {
            throw BadRequest();
        }
    }

    else {
        throw BadRequest();
    }
}

void Post::send_post_notification(User*& currentUser, PostStruct& post, vector<User*>& users)
{
    Notification postNotif = construct_notif(currentUser, NEW_POST_NOTIF);
    post.id = currentUser->get_postID();
    currentUser->add_post(post);
    Manager* admin = dynamic_cast<Manager*>(currentUser);
    if (admin) {
        send_notif_to_all(postNotif, users);
    } else {
        currentUser->send_notif(postNotif);
    }
}

void Post::handle_profile_photo(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
    vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2)
{
    string title;
    string photoPath;
    iss2 >> title;

    check_user_loged_in(currentUser);

    if (title == "photo") {
        photoPath = read_profile_path(line);
        currentUser->set_profile(photoPath);
        successful_request();
    }

    else {
        throw BadRequest();
    }
}

string Post::read_profile_path(string& line)
{
    size_t i = line.find("photo ");
    line = line.substr(i + 5);

    string format = image_format(line);
    if (format == INVALID_FORMAT) {
        throw BadRequest();
    }
    i = line.find(format);
    string path = line.substr(0, i + format.size());
    line = line.substr(i + format.size());
    return path;
}

void Post::handle_course_post(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
    vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2)
{
    check_user_loged_in(currentUser);

    restrict_admin(currentUser);

    PostStruct post;
    handle_channel_post(line, users, currentUser, lessonID_, lessons, courses, majors, iss2, post);
}

void Post::handle_channel_post(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
    vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2, PostStruct& post)
{
    string lessId;
    size_t pos = line.find(" id");
    if (pos == string::npos) {
        throw BadRequest();
    }

    string tempLine = line.substr(pos + 3);
    istringstream tempIss(tempLine);
    tempIss >> lessId;
    string firstPart = line.substr(0, pos);

    pos = line.find(lessId);
    string secondPart = line.substr(pos + lessId.length(), line.length());

    line = firstPart + secondPart;
    check_natural_number(lessId);
    check_lesson_existance(stoi(lessId), lessons);
    Lesson* chosenLesson = find_lesson_by_id(lessons, lessId);

    Professor* professor = dynamic_cast<Professor*>(currentUser);
    if (professor) {
        professor_post(professor, chosenLesson, line, post, users, currentUser);
    } else {
        ta_post(currentUser, chosenLesson, line, post, users);
    }
}

void Post::professor_post(Professor*& professor, Lesson*& chosenLesson, string& line, PostStruct& post, vector<User*>& users, User*& currentUser)
{
    if (professor->get_id() != chosenLesson->get_prof_id()) {
        throw Inaccessibility();
    }
    post.sender = professor->get_name();
    istringstream iss(line);

    string first_argument;
    iss >> first_argument;
    if (first_argument == "title") {
        handle_title_first(line, post);
    }

    else if (first_argument == "message") {
        handle_message_first(line, post);
    }

    else if (first_argument == "image") {
        handle_image_first(line, post);
    }

    else {
        throw BadRequest();
    }

    chosenLesson->add_post_to_channel(post);
    Notification courseNotif = construct_course_notif(chosenLesson);
    send_course_notif(users, chosenLesson, currentUser, courseNotif);
    successful_request();
}

void Post::ta_post(User*& currentUser, Lesson*& chosenLesson, string& line, PostStruct& post, vector<User*>& users)
{
    if (!chosenLesson->is_TA(currentUser->get_id())) {
        throw Inaccessibility();
    }
    post.sender = currentUser->get_name();
    istringstream iss(line);

    string first_argument;
    iss >> first_argument;
    if (first_argument == "title") {
        handle_title_first(line, post);
    }

    else if (first_argument == "message") {
        handle_message_first(line, post);
    }

    else if (first_argument == "image") {
        handle_image_first(line, post);
    }

    else {
        throw BadRequest();
    }

    chosenLesson->add_post_to_channel(post);
    Notification courseNotif = construct_course_notif(chosenLesson);
    send_course_notif(users, chosenLesson, currentUser, courseNotif);
    successful_request();
}

void Post::send_course_notif(vector<User*>& users, Lesson*& chosenLesson, User*& currentUser, Notification courseNotif)
{
    for (User* u : users) {
        if (u->have_this_lesson(chosenLesson->get_lessonID()) || chosenLesson->is_TA(u->get_id())) {
            if (u == currentUser) {
                continue;
            }
            u->receive_notif(courseNotif);
        }
    }
}

Notification Post::construct_course_notif(Lesson*& chosenLesson)
{
    Notification courseNotif;
    courseNotif.id = to_string(chosenLesson->get_lessonID());
    courseNotif.name = chosenLesson->get_course_name();
    courseNotif.message = NEW_COURSE_POST_NOTIF;
    return courseNotif;
}

void Post::handle_ta_form(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
    vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2)
{
    check_user_loged_in(currentUser);
    restrict_admin(currentUser);
    restrict_students(currentUser);

    PostStruct formPost;
    formPost.type = TA_FORM_TYPE;
    Argument first;
    Argument second;
    iss2 >> first.title;
    iss2 >> first.key;
    if (first.title == "course_id") {
        first_handle_course_id_for_ta_form(first, second, lessons, currentUser, formPost, iss2, line);
    }

    else if (first.title == "message") {
        first_handle_message_for_ta_form(first, second, lessons, currentUser, formPost, iss2, line);
    }

    else {
        throw BadRequest();
    }
}

Lesson* Post::read_course_id(string& id_, vector<Lesson*>& lessons, User*& currentUser)
{
    check_natural_number(id_);
    check_lesson_existance(stoi(id_), lessons);
    if (!currentUser->have_this_lesson(stoi(id_))) {
        throw Inaccessibility();
    }
    Lesson* chosenLesson = find_lesson_by_id(lessons, id_);
    return chosenLesson;
}

void Post::handle_closing_ta_form(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
    vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2)
{
    check_user_loged_in(currentUser);
    restrict_admin(currentUser);
    restrict_students(currentUser);

    Professor* prof = dynamic_cast<Professor*>(currentUser);

    string title;
    string id;
    iss2 >> title;
    iss2 >> id;
    if (title == "id") {
        check_natural_number(id);
        check_form_existance(prof, id);
        close_ta_form(prof, users, id);
    } else {
        throw BadRequest();
    }
}

void Post::close_ta_form(Professor*& prof, vector<User*>& users, string id)
{
    prof->show_number_of_requests(stoi(id));
    prof->handle_requests_of_form(stoi(id));
    prof->send_reject_notifs(users, id);
    prof->send_accept_notifs(users, id);
    prof->delete_post(stoi(id));
    prof->delete_ta_form(stoi(id));
}

void Post::handle_ta_request(string line, vector<User*>& users, User*& currentUser, int& lessonID_,
    vector<Lesson*>& lessons, vector<Course*>& courses, vector<Major*>& majors, istringstream& iss2)
{
    pre_check_for_ta_request(currentUser);
    Student* student = dynamic_cast<Student*>(currentUser);

    string profId;
    size_t pos = line.find(" professor_id");
    if (pos == string::npos) {
        throw BadRequest();
    }
    string tempLine = line.substr(pos + 14);
    istringstream tempIss(tempLine);
    tempIss >> profId;
    check_natural_number(profId);
    string firstPart = line.substr(0, pos);
    string secondPart = line.substr(pos + profId.length() + 14, line.length());
    line = firstPart + secondPart;
    istringstream iss(line);
    add_new_ta_request(iss,profId, users, student);
}

void Post::check_is_professor(string profID, vector<User*>& users)
{
    if (!is_prof(profID, users)) {
        throw Absence();
    }
}

void Post::check_form_existance(Professor*& prof, string formID)
{
    if (!prof->have_this_post(stoi(formID))) {
        throw Absence();
    }

    if (!prof->have_this_form(stoi(formID))) {
        throw Absence();
    }
}

void Post::add_new_ta_request(istringstream& iss,string &profID, vector<User*>& users, Student*& student)
{
    check_natural_number(profID);
    check_is_professor(profID, users);
    User* u = find_user_by_id(profID, users);
    Professor* prof = dynamic_cast<Professor*>(u);

    string second_argument;
    iss >> second_argument;
    if (second_argument == "form_id") {
        string formID;
        iss >> formID;
        check_natural_number(formID);
        check_form_existance(prof, formID);
        TaForm* taForm = prof->find_ta_form_by_id(stoi(formID));
        Lesson* chosenLesson = taForm->get_lesson();
        if (!chosenLesson->can_accept_this_semester(student->get_semester())) {
            throw Inaccessibility();
        }
        StudentData studentStruct = student->get_studentData();
        taForm->add_new_request(studentStruct);
        successful_request();

    } else {
        throw BadRequest();
    }
}

void Post::pre_check_for_ta_request(User*& currentUser)
{
    check_user_loged_in(currentUser);
    restrict_admin(currentUser);
    Professor* prof = dynamic_cast<Professor*>(currentUser);
    if (prof) {
        throw Inaccessibility();
    }
}

void Post::first_handle_course_id_for_ta_form(Argument& first, Argument& second, vector<Lesson*>& lessons, User*& currentUser, PostStruct& formPost,
    istringstream& iss2, string& line)
{
    check_natural_number(first.key);
    check_lesson_existance(stoi(first.key), lessons);
    Lesson* chosenLesson = read_course_id(first.key, lessons, currentUser);
    formPost.lessonId = to_string(chosenLesson->get_lessonID());
    iss2 >> second.title;
    if (second.title == "message") {
        read_post_message(line, formPost);
        Professor* prof = dynamic_cast<Professor*>(currentUser);
        formPost.title = FORM_POST_PRE_TITLE + chosenLesson->get_course_name() + FORM_POST_END_TITLE;
        formPost.id = prof->get_postID();
        prof->add_post(formPost);
        prof->add_ta_form(new TaForm(formPost, chosenLesson));
        Notification TaFormNotif = construct_notif(prof, NEW_FORM_NOTIF);
        prof->send_notif(TaFormNotif);
        successful_request();
    } else {
        throw BadRequest();
    }
}

void Post::first_handle_message_for_ta_form(Argument& first, Argument& second, vector<Lesson*>& lessons, User*& currentUser, PostStruct& formPost,
    istringstream& iss2, string& line)
{
    line = line.substr(line.find("message"));
    read_post_message(line, formPost);
    iss2 >> second.title;
    if (second.title == "course_id") {
        size_t pos = line.find("course_id");
        line = line.substr(pos + 9);
        istringstream iss3(line);
        iss3 >> second.key;
        check_natural_number(second.key);
        check_lesson_existance(stoi(second.key), lessons);
        Lesson* chosenLesson = read_course_id(second.key, lessons, currentUser);
        Professor* prof = dynamic_cast<Professor*>(currentUser);
        formPost.title = FORM_POST_PRE_TITLE + chosenLesson->get_course_name() + FORM_POST_END_TITLE;
        formPost.id = prof->get_postID();
        prof->add_post(formPost);
        prof->add_ta_form(new TaForm(formPost, chosenLesson));
        Notification TaFormNotif = construct_notif(prof, NEW_FORM_NOTIF);
        prof->send_notif(TaFormNotif);
        successful_request();
    } else {
        throw BadRequest();
    }
}