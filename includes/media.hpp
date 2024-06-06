#pragma once

#include "../includes/consts.hpp"
#include "../includes/lesson.hpp"

class Media {
protected:
    string type;
    PostStruct mediaPost;
    int id;
public:
    Media(PostStruct post_);
    ~Media();
    string get_type();
    PostStruct get_mediaPost();
    int get_id();
};

class TaForm : public Media {
private:
    bool is_open;
    Lesson* lesson;
    vector<StudentData> requests;
    vector<StudentData> accepted;
    vector<StudentData> rejected; 
    
public:
    TaForm(PostStruct formPost_, Lesson* &chosenLesson);
    ~TaForm();
    void display_number_of_requests();
    void judge_requests();
    void display_student_data(StudentData stu);
    Lesson* get_lesson();
    vector<StudentData> get_rejected();
    vector<StudentData> get_accepted();
    void close();
    void reset_requests();
    void reset_rejected();
    void reset_accepted();
    void add_new_request(StudentData stu);
};
