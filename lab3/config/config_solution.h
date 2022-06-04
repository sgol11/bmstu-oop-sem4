#ifndef CONFIG_SOLUTION_H
#define CONFIG_SOLUTION_H

#include "base_config.h"


class ConfigSolution
{
public:
    ConfigSolution() = default;
    ~ConfigSolution() = default;

    std::shared_ptr<BaseConfig> create_creator();
    void registrate(std::shared_ptr<BaseConfig> config_arg);

private:
    std::shared_ptr<BaseConfig> config;
};


#endif // CONFIG_SOLUTION_H
