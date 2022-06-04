#include "loader_solution.h"
#include "../exceptions/director_exceptions.h"

LoaderSolution::LoaderSolution()
{
    static auto loader_map = std::make_shared<callback_map>();
    callback = loader_map;
}


std::shared_ptr<LoaderCreator> LoaderSolution::create_creator(const std::string &object_type)
{
    callback_map::const_iterator it = callback->find(object_type);

    if (it == callback->end())
    {
        time_t cur_time = time(NULL);
        throw NoLoaderException(__FILE__, __func__, __LINE__,
                                ctime(&cur_time));
    }

    return it->second;
}

bool LoaderSolution::registrate(const std::string object_type, std::shared_ptr<LoaderCreator> loader_creator)
{
    if (check(object_type))
    {
        callback->erase(object_type);
    }

    return callback->insert(callback_map::value_type(object_type, loader_creator)).second;
}

bool LoaderSolution::check(const std::string &object_type)
{
    return callback->count(object_type) > 0;
}
