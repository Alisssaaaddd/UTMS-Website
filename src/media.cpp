#include "../includes/media.hpp"

Media::Media(PostStruct post_)
{
    mediaPost = post_;
    id = post_.id;
}

Media::~Media()
{
}

string Media::get_type(){return type;};
PostStruct Media::get_mediaPost(){return mediaPost;};
int Media::get_id(){return id;};

TaForm::TaForm(PostStruct formPost_, Lesson* &chosenLessson) : Media(formPost_)
{
    type = TA_FORM_TYPE;
    lesson = chosenLessson;
    is_open = true;
}

TaForm::~TaForm()
{
}

void TaForm::display_number_of_requests(){
    cout << SHOW_REQUESTS_PRE_TITLE << requests.size() << SHOW_REQUESTS_END_TITLE << endl;
}

void TaForm::judge_requests(){
    string reply;
    for(StudentData stu: requests){
        display_student_data(stu);
        getline(cin, reply);
        if(reply== ACCEPT_REPLY){
            accepted.push_back(stu);
        }
        else if(reply == REJECT_REPLY){
            rejected.push_back(stu);
        }
        else{
            display_student_data(stu);
            getline(cin, reply);
        }
    }
}

void TaForm::display_student_data(StudentData stu){
    cout << stu.SID << SPACE << stu.name << SPACE << stu.semester << COLON << SPACE;
}

Lesson* TaForm::get_lesson(){return lesson;};

void TaForm::close(){
    is_open = false;
}

vector<StudentData> TaForm::get_rejected(){return rejected;};
vector<StudentData> TaForm::get_accepted(){return accepted;};

void TaForm::reset_requests(){
    requests.clear();    
}

void TaForm::reset_accepted(){
    accepted.clear();
}

void TaForm::reset_rejected(){
    rejected.clear();
}

void TaForm::add_new_request(StudentData stu){
    requests.push_back(stu);
}