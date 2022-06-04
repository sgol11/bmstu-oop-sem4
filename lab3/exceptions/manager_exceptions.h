#ifndef MANAGER_EXCEPTIONS_H
#define MANAGER_EXCEPTIONS_H

#include "base_exception.h"


class ManagerException : public BaseException
{
public:
    ManagerException(std::string filename, std::string classname,
                     int cur_line, const char *time,
                     std::string info = "Manager error"):
    BaseException(filename, classname, cur_line, time, info) {}
};


class NoMainCameraException : public ManagerException
{
public:
    NoMainCameraException(std::string filename, std::string classname,
                          int cur_line, const char *time,
                          std::string info = "No main camera"):
    ManagerException(filename, classname, cur_line, time, info) {};
};


#endif // MANAGER_EXCEPTIONS_H
