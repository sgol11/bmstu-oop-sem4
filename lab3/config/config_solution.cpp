#include "config_solution.h"
#include "../exceptions/config_exceptions.h"


std::shared_ptr<BaseConfig> ConfigSolution::create_creator()
{
    if (config == nullptr)
    {
        time_t cur_time = time(NULL);
        throw NoConfigException(__FILE__, __func__, __LINE__,
                                ctime(&cur_time));
    }

    return config;
}

void ConfigSolution::registrate(std::shared_ptr<BaseConfig> config_arg)
{
    config = config_arg;
}
