#include "load_manager.h"


void LoadManager::set_director(std::shared_ptr<BaseLoadDirector> src_director)
{
    director = src_director;
}


void LoadManager::load_camera(std::string fname)
{
    auto new_director = CameraDirectorCreator().get_director(fname);
    set_director(new_director);
    auto object = director->create();
    SceneManagerCreator().get_manager()->get_scene()->add_object(object);
}

void LoadManager::load_model(std::string fname)
{
    auto new_director = ModelDirectorCreator().get_director(fname);
    set_director(new_director);
    auto object = director->create();
    SceneManagerCreator().get_manager()->get_scene()->add_object(object);
}


std::shared_ptr<LoadManager> LoadManagerCreator::get_manager()
{
    if (manager == nullptr)
    {
        create_instance();
    }

    return manager;
}

void LoadManagerCreator::create_instance()
{
    manager = std::make_shared<LoadManager>();
}
