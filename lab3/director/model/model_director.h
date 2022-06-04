#ifndef MODEL_DIRECTOR_H
#define MODEL_DIRECTOR_H

#include "../base_load_director.h"
#include "../../loader/loader_solution.h"
#include "../../builder/builder_solution.h"
#include "../../loader/base_loader.h"
#include "../../builder/base_builder.h"
#include "../../config/config_solution.h"
#include "../../config/config.h"


class ModelDirector : public BaseLoadDirector
{
public:
    explicit ModelDirector(std::string name_arg);
    ~ModelDirector() override = default;

    std::shared_ptr<Object> create() override;
    void set_loader(std::shared_ptr<BaseLoader> loader_arg) override;
    void set_builder(std::shared_ptr<BaseBuilder> builder_arg) override;

private:
    std::string name{};

    std::shared_ptr<BaseLoader>  loader;
    std::shared_ptr<BaseBuilder> builder;
};


class ModelDirectorCreator
{
public:
    ModelDirectorCreator() = default;
    ~ModelDirectorCreator() = default;

    std::shared_ptr<ModelDirector> get_director(std::string name_arg);

private:
    void create_instance(std::string name_arg);
    std::shared_ptr<ModelDirector> director;
};


#endif // MODEL_DIRECTOR_H
