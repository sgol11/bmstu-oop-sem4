#ifndef BASE_EXCEPTION_H
#define BASE_EXCEPTION_H


#include <exception>
#include <iostream>


class BaseVectorException: public std::exception
{
    protected:
        std::string error_info;

    public:
        BaseVectorException(std::string file_name, std::string class_name,
                            int cur_line, const char *time, std::string info)
        {
            error_info = "\n\nFile: " + file_name + "\nClass: " + class_name +
                         "\nLine: " + std::to_string(cur_line) +
                         "\nTime: " + time + "\nAbout error: " + info;
        }

        virtual const char *what() const noexcept override
        {
            return error_info.c_str();
        }

        virtual ~BaseVectorException() {}
};


#endif // BASE_EXCEPTION_H
