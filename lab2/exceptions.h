#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H


#include "base_exception.h"


class ExpiredIteratorException: public BaseVectorException
{
    public:
        ExpiredIteratorException(std::string file_name, std::string class_name,
                                 int cur_line, const char *time,
                                 std::string info = "Expired iterator"):
        BaseVectorException(file_name, class_name, cur_line, time, info) {};
};

class InvalidIteratorException: public BaseVectorException
{
    public:
        InvalidIteratorException(std::string file_name, std::string class_name,
                                 int cur_line, const char *time,
                                 std::string info = "Invalid iterator"):
        BaseVectorException(file_name, class_name, cur_line, time, info) {};
};

class MemoryException: public BaseVectorException
{
    public:
        MemoryException(std::string file_name, std::string class_name,
                        int cur_line, const char *time,
                        std::string info = "Memory allocation error"):
        BaseVectorException(file_name, class_name, cur_line, time, info) {};
};

class InvalidPointerException: public BaseVectorException
{
    public:
        InvalidPointerException(std::string file_name, std::string class_name,
                                int cur_line, const char *time,
                                std::string info = "Invalid pointer to source array"):
        BaseVectorException(file_name, class_name, cur_line, time, info) {};
};

class EmptyVectorException: public BaseVectorException
{
    public:
        EmptyVectorException(std::string file_name, std::string class_name,
                             int cur_line, const char *time,
                             std::string info = "Vector is empty"):
        BaseVectorException(file_name, class_name, cur_line, time, info) {};
};

class OutOfRangeException: public BaseVectorException
{
    public:
        OutOfRangeException(std::string file_name, std::string class_name,
                            int cur_line, const char *time,
                            std::string info = "Index is out of range"):
        BaseVectorException(file_name, class_name, cur_line, time, info) {};
};

class ZeroDivisionException: public BaseVectorException
{
    public:
        ZeroDivisionException(std::string file_name, std::string class_name,
                              int cur_line, const char *time,
                              std::string info = "Division by zero"):
        BaseVectorException(file_name, class_name, cur_line, time, info) {};
};

class InvalidSizesException: public BaseVectorException
{
    public:
        InvalidSizesException(std::string file_name, std::string class_name,
                              int cur_line, const char *time,
                              std::string info = "Invalid sizes of vectors"):
        BaseVectorException(file_name, class_name, cur_line, time, info) {};
};


#endif // EXCEPTIONS_H
