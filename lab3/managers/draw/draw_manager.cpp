#include "draw_manager.h"


void DrawManager::draw(std::shared_ptr<BaseDrawer> &src_drawer)
{
    set_drawer(src_drawer);

    auto scene_manager = SceneManagerCreator().get_manager();
    auto scene = scene_manager->get_scene();

    set_camera(scene_manager->get_camera());

    drawer->clear_scene();

    std::shared_ptr<Visitor> visitor = DrawVisitorFactory(drawer, camera).create();

    for (auto iterator = scene->begin(); iterator < scene->end(); iterator++)
    {
        auto object = *iterator;
        object->accept(visitor);
    }
}

void DrawManager::set_drawer(const std::shared_ptr<BaseDrawer> src_drawer)
{
    drawer = std::move(src_drawer);
}

void DrawManager::set_camera(const std::shared_ptr<Camera> src_camera)
{
    camera = std::move(src_camera);
}


std::shared_ptr<DrawManager> DrawManagerCreator::get_manager()
{
    if (manager == nullptr)
    {
        create_instance();
    }

    return manager;
}

void DrawManagerCreator::create_instance()
{
    manager = std::make_shared<DrawManager>();
}
