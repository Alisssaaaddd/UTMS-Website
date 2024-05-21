#pragma once

#include "../includes/consts.hpp"

class Absence : public runtime_error
{
private:
public:
    Absence();
    ~Absence();
    const char *what();
};

class EmptyException : public runtime_error
{
private:
public:
    EmptyException();
    ~EmptyException();
    const char *what();
};

class BadRequest : public runtime_error
{
private:
public:
    BadRequest();
    ~BadRequest();
    const char *what();
};

class Inaccessibility : public runtime_error
{
private:
public:
    Inaccessibility();
    ~Inaccessibility();
    const char *what();
};