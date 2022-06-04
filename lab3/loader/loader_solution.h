#ifndef LOADER_SOLUTION_H
#define LOADER_SOLUTION_H

#include <map>
#include <memory>
#include <string>

#include "base_loader.h"


class LoaderSolution
{
public:
    LoaderSolution();
    ~LoaderSolution() = default;

    std::shared_ptr<LoaderCreator> create_creator(const std::string &object_type);
    bool registrate(const std::string object_type, std::shared_ptr<LoaderCreator> loader_creator);
    bool check(const std::string &object_type);

private:
    using callback_map = std::map<const std::string, std::shared_ptr<LoaderCreator>>;
    std::shared_ptr<callback_map> callback;
};


#endif // LOADER_SOLUTION_H
