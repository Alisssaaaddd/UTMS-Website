#include "../includes/handlers.hpp"
#include "../includes/website.hpp"
#include "../server/server.hpp"

int main(int argc, char* argv[])
{
    try {
        Website* utms = new Website(argv[1], argv[2], argv[3], argv[4]);
        int port = PORT_NUM;
        Server server(port);
        server.setNotFoundErrPage("static/404.html");
        server.get("/", new ShowPage("static/home.html"));
        server.get("/home.png", new ShowImage("static/home.png"));
        server.get("/login", new ShowPage("static/login.html"));
        server.post("/login", new LoginHandler(utms));
        server.get("/up", new ShowPage("static/upload_form.html"));
        server.post("/up", new UploadHandler());
        server.get("/stu_homePage", new ShowPage("static/stu_homePage.html"));
        server.get("/prof_homePage", new ShowPage("static/prof_homePage.html"));
        server.get("/admin_homePage", new ShowPage("static/admin_homePage.html"));
        cout << SERVER_ON_PORT << port << endl;
        server.run();
    } catch (BadRequest& br) {
        Response* res = Response::redirect("/bad_req");
    }

    catch (Absence& a) {
        Response* res = Response::redirect("/not_found");
    }

    catch (EmptyException& ee) {
        Response* res = Response::redirect("/error");
    }

    catch (Inaccessibility& ie) {
        Response* res = Response::redirect("/permission_error");
    }
    return 0;
}