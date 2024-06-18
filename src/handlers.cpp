#include "../includes/handlers.hpp"

LoginHandler::LoginHandler(Website* utms_)
{
    utms = utms_;
}

Response* LoginHandler::callback(Request* req)
{
    try {
        Response* res;
        string id = req->getBodyParam("id");
        string password = req->getBodyParam("password");
        Post* post = utms->call_post_method();
        vector<User*> users = utms->get_users();
        User* currentUser = utms->get_currentUser();
        post->login(id, password, users, currentUser);
        Student* stu = dynamic_cast<Student*>(currentUser);
        Professor* prof = dynamic_cast<Professor*>(currentUser);
        Manager* admin = dynamic_cast<Manager*>(currentUser);
        if(stu) res = Response::redirect("/stu_homePage");
        if(prof) res = Response::redirect("/prof_homePage");
        if(admin) res = Response::redirect("/admin_homePage");
        return res;
    } catch (BadRequest& br) {
        Response* res = Response::redirect("/bad_req");
        return res;
    }

    catch (Absence& a) {
        Response* res = Response::redirect("/not_found");
        return res;
    }

    catch (EmptyException& ee) {
        Response* res = Response::redirect("/error");
        return res;
    }

    catch (Inaccessibility& ie) {
        Response* res = Response::redirect("/permission_error");
        return res;
    }
}

Response* UploadHandler::callback(Request* req)
{
    std::string name = req->getBodyParam("file_name");
    std::string file = req->getBodyParam("file");
    utils::writeToFile(file, name);
    Response* res = Response::redirect("/");
    return res;
}