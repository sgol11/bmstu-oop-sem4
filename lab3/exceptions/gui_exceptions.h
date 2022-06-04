#ifndef GUI_EXCEPTIONS_H
#define GUI_EXCEPTIONS_H

#include "base_exception.h"


class GuiException : public BaseException
{
public:
    GuiException(std::string filename, std::string classname,
                 int cur_line, const char *time,
                 std::string info = "GUI error"):
    BaseException(filename, classname, cur_line, time, info) {}
};


class NoModelException : public GuiException
{
public:
    NoModelException(std::string filename, std::string classname,
                     int cur_line, const char *time,
                     std::string info = "No models"):
    GuiException(filename, classname, cur_line, time, info) {};
};

class NoCameraException : public GuiException
{
public:
    NoCameraException(std::string filename, std::string classname,
                      int cur_line, const char *time,
                      std::string info = "No cameras"):
    GuiException(filename, classname, cur_line, time, info) {};
};

class ModelNotFoundException : public GuiException
{
public:
    ModelNotFoundException(std::string filename, std::string classname,
                           int cur_line, const char *time,
                           std::string info = "Model not found"):
    GuiException(filename, classname, cur_line, time, info) {};
};

class CameraNotFoundException : public GuiException
{
public:
    CameraNotFoundException(std::string filename, std::string classname,
                            int cur_line, const char *time,
                            std::string info = "Camera not found"):
    GuiException(filename, classname, cur_line, time, info) {};
};


#endif // GUI_EXCEPTIONS_H
