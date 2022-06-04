#ifndef BASE_EXCEPTION_H
#define BASE_EXCEPTION_H

#include <exception>
#include <string>
#include <ctime>
#include <chrono>


class BaseException : public std::exception
{
public:
    BaseException(std::string filename, std::string classname,
                  int cur_line, const char *time, std::string info)
    {
        error_info = "\n\nFile: " + filename +
                     "\nClass: " + classname +
                     "\nLine: " + std::to_string(cur_line) +
                     "\nTime: " + time +
                     "\nAbout error: " + info;
    }

    virtual const char *what() const noexcept override
    {
        return error_info.c_str();
    }

    virtual ~BaseException() {}

protected:
    std::string error_info;
};


#endif // BASE_EXCEPTION_H
