#include "builder_solution.h"
#include "../exceptions/builder_exceptions.h"


BuilderSolution::BuilderSolution()
{
    static auto builder_map = std::make_shared<callback_map>();
    callback = builder_map;
}


std::shared_ptr<BuilderCreator> BuilderSolution::create_creator(const std::string &object_type)
{
    callback_map::const_iterator it = callback->find(object_type);

    if (it == callback->end())
    {
        time_t cur_time = time(NULL);

        throw BuilderNotRegisteredException(__FILE__, __func__, __LINE__,
                                            ctime(&cur_time));
    }

    return it->second;
}

bool BuilderSolution::registrate(const std::string object_type, std::shared_ptr<BuilderCreator> builder_creator)
{
    if (check(object_type))
    {
        callback->erase(object_type);
    }

    return callback->insert(callback_map::value_type(object_type, builder_creator)).second;
}

bool BuilderSolution::check(const std::string &object_type)
{
    return callback->count(object_type) > 0;
}
