#ifndef BUILDER_SOLUTION_H
#define BUILDER_SOLUTION_H

#include <map>
#include <memory>
#include <string>

#include "base_builder.h"


class BuilderSolution
{
public:
    BuilderSolution();
    ~BuilderSolution() = default;

    std::shared_ptr<BuilderCreator> create_creator(const std::string &object_type);
    bool registrate(const std::string object_type, std::shared_ptr<BuilderCreator> builder_creator);
    bool check(const std::string &object_type);

private:
    using callback_map = std::map<const std::string, std::shared_ptr<BuilderCreator>>;
    std::shared_ptr<callback_map> callback;
};


#endif // BUILDER_SOLUTION_H
