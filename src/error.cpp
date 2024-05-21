#include "../includes/error.hpp"


Absence::Absence() : runtime_error("Not Found") {}
Absence::~Absence() {}

const char* Absence::what() {
    return "Not Found";
}

EmptyException::EmptyException() : runtime_error("Empty") {}
EmptyException::~EmptyException() {}

const char* EmptyException::what() {
    return "Empty";
}

BadRequest::BadRequest() : runtime_error("Bad request") {}
BadRequest::~BadRequest() {}

const char* BadRequest::what() {
    return "Bad request";
}

Inaccessibility::Inaccessibility() : runtime_error("Permission Denied") {}
Inaccessibility::~Inaccessibility() {}

const char* Inaccessibility::what() {
    return "Permission Denied";
}


