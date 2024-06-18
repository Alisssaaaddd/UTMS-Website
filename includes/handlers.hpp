#pragma once
#include "../includes/website.hpp"
#include "../server/server.hpp"

class LoginHandler : public RequestHandler {
public:
    LoginHandler(Website* );
    Response* callback(Request* req);

private:
    Website* utms;
};

class UploadHandler : public RequestHandler {
public:
    Response* callback(Request*) override;
};