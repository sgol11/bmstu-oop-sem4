#ifndef BASE_CONFIG_H
#define BASE_CONFIG_H

#include <memory>
#include <string>


class BaseConfig
{
public:
    BaseConfig() = default;
    virtual ~BaseConfig() = default;

    virtual void get_config_info() = 0;
};


class BaseConfigCreator
{
public:
    BaseConfigCreator() = default;
    virtual ~BaseConfigCreator() = default;

    virtual std::shared_ptr<BaseConfig> create_config() = 0;
};


#endif // BASE_CONFIG_H
