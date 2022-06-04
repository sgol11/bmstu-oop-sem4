#ifndef CONFIG_EXCEPTIONS_H
#define CONFIG_EXCEPTIONS_H

#include "base_exception.h"


class ConfigException : public BaseException
{
public:
    ConfigException(std::string filename, std::string classname,
                     int cur_line, const char *time,
                     std::string info = "Configuration error"):
    BaseException(filename, classname, cur_line, time, info) {}
};


class NoFileException : public ConfigException
{
public:
    NoFileException(std::string filename, std::string classname,
                    int cur_line, const char *time,
                    std::string info = "No file"):
    ConfigException(filename, classname, cur_line, time, info) {};
};

class ReadException : public ConfigException
{
public:
    ReadException(std::string filename, std::string classname,
                  int cur_line, const char *time,
                  std::string info = "Reading error"):
    ConfigException(filename, classname, cur_line, time, info) {};
};

class NoConfigException : public ConfigException
{
public:
    NoConfigException(std::string filename, std::string classname,
                      int cur_line, const char *time,
                      std::string info = "No configuration"):
    ConfigException(filename, classname, cur_line, time, info) {};
};


#endif // CONFIG_EXCEPTIONS_H
