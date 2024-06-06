
#include "../includes/lesson.hpp"

Lesson::Lesson(LessonStruct ls, int& lessonId_current)
{
    courseName = ls.courseName;
    profName = ls.profName;
    courseId = ls.courseId;
    profId = ls.profId;
    capacity = ls.capacity;
    time.weekDay = ls.weekDay;
    time.startTime = ls.startTime;
    time.endTime = ls.endTime;
    date = ls.date;
    classNumber = ls.classNumber;
    lessonID = ls.lessonID;
    majorsId = ls.majors_id;
    prereq = ls.prereq;
    postID = 1;
}

Lesson::~Lesson()
{
}

string Lesson::get_course_name() { return courseName; };
string Lesson::get_prof_name() { return profName; };
string Lesson::get_course_id() { return courseId; };
string Lesson::get_prof_id() { return profId; };
string Lesson::get_capacity() { return capacity; };
string Lesson::get_week_day() { return time.weekDay; };
string Lesson::get_prereq() { return prereq; };
string Lesson::get_start_time() { return time.startTime; };
string Lesson::get_end_time() { return time.endTime; };
int Lesson::get_class_num() { return stoi(classNumber); };
string Lesson::get_date() { return date; };
int Lesson::get_lessonID() { return lessonID; };

void Lesson::show()
{
    cout << lessonID << SPACE << courseName << SPACE << capacity << SPACE << profName << endl;
}

void Lesson::show_detailed()
{
    cout << lessonID << SPACE << courseName << SPACE << capacity << SPACE << profName << SPACE << time.weekDay << COLON << time.startTime << HYPHEN << time.endTime << SPACE << date << SPACE << classNumber << endl;
}

bool Lesson::can_accept_this_major(string majorID_)
{
    for (auto m : majorsId) {
        if (m == majorID_)
            return true;
    }
    return false;
}

void Lesson::display()
{
    cout << lessonID << SPACE << courseName << SPACE << capacity << SPACE << profName << SPACE << time.weekDay << COLON << time.startTime << HYPHEN << time.endTime << SPACE << date << SPACE << classNumber << endl;
}

bool Lesson::is_TA(string studentID)
{
    for (auto ta_id : TA_IDs) {
        if (ta_id == studentID)
            return true;
    }
    return false;
}

void Lesson::add_post_to_channel(PostStruct& newPost)
{
    newPost.id = postID;
    informing_channel.push_back(newPost);
    postID++;
}

void Lesson::show_channel()
{
    show_detailed();
    for (int i = informing_channel.size() - 1; i >= 0; i--) {
        show_channel_post(informing_channel[i]);
    }
}

void Lesson::show_channel_post(PostStruct cPost)
{
    cout << cPost.id << SPACE << cPost.sender << SPACE << DOUBLE_QUOTATION << cPost.title << DOUBLE_QUOTATION << endl;
}

void Lesson::show_channel_post_detailed(int postId_)
{
    show_detailed();
    PostStruct p = find_course_post_by_postId(postId_);
    cout << p.id << SPACE << p.sender << SPACE << DOUBLE_QUOTATION << p.title << DOUBLE_QUOTATION << SPACE << DOUBLE_QUOTATION << p.message << DOUBLE_QUOTATION << endl;
}

bool Lesson::is_accessable(string userId, bool userHaveLesson)
{
    if (is_TA(userId) || userHaveLesson) {
        return true;
    }
    return false;
}

bool Lesson::course_post_exists(int postId_)
{
    for (PostStruct post : informing_channel) {
        if (postId_ == post.id)
            return true;
    }
    return false;
}

PostStruct Lesson::find_course_post_by_postId(int postId_)
{
    for (PostStruct post : informing_channel) {
        if (post.id == postId_)
            return post;
    }
}

void Lesson::add_TA(string TA_id){
    TA_IDs.push_back(TA_id);
}

bool Lesson::can_accept_this_semester(string StuSemester){
    if(stoi(StuSemester)<=stoi(prereq)){
        return false;
    }
    return true;
}