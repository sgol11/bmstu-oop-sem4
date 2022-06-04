#include "model_director.h"
#include "../../exceptions/director_exceptions.h"


ModelDirector::ModelDirector(std::string name_arg)
{
    name = name_arg;
}


std::shared_ptr<Object> ModelDirector::create()
{
    time_t cur_time = time(NULL);

    if (loader == nullptr)
    {
        throw NoLoaderException(__FILE__, __func__, __LINE__,
                                ctime(&cur_time));
    }

    if (builder == nullptr)
    {
        throw NoBuilderException(__FILE__, __func__, __LINE__,
                                 ctime(&cur_time));
    }

    builder->build();

    return loader->load(builder);
}

void ModelDirector::set_loader(std::shared_ptr<BaseLoader> loader_arg)
{
    loader = loader_arg;
}

void ModelDirector::set_builder(std::shared_ptr<BaseBuilder> builder_arg)
{
    builder = builder_arg;
}


std::shared_ptr<ModelDirector> ModelDirectorCreator::get_director(std::string name_arg)
{
    if (director == nullptr)
    {
        create_instance(name_arg);
    }

    return director;
}

void ModelDirectorCreator::create_instance(std::string name_arg)
{
    auto config_solution = std::make_shared<ConfigSolution>();
    config_solution->registrate(ConfigCreator().create_config());
    config_solution->create_creator()->get_config_info();

    director = std::make_shared<ModelDirector>(name_arg);
    director->set_loader(LoaderSolution().create_creator("model")->create_loader(name_arg));
    director->set_builder(BuilderSolution().create_creator("model")->create_builder());
}
