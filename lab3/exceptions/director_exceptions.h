#ifndef DIRECTOR_EXCEPTIONS_H
#define DIRECTOR_EXCEPTIONS_H


#include "base_exception.h"


class DirectorException : public BaseException
{
public:
    DirectorException(std::string filename, std::string classname,
                      int cur_line, const char *time,
                      std::string info = "Director error"):
    BaseException(filename, classname, cur_line, time, info) {}
};


class NoLoaderException : public DirectorException
{
public:
    NoLoaderException(std::string filename, std::string classname,
                      int cur_line, const char *time,
                      std::string info = "No loader"):
    DirectorException(filename, classname, cur_line, time, info) {};
};

class NoBuilderException : public DirectorException
{
public:
    NoBuilderException(std::string filename, std::string classname,
                       int cur_line, const char *time,
                       std::string info = "No builder"):
    DirectorException(filename, classname, cur_line, time, info) {};
};


#endif // DIRECTOR_EXCEPTIONS_H
