#include "scene_manager.h"
#include "../../exceptions/manager_exceptions.h"


SceneManager::SceneManager() : scene(std::make_shared<Scene>()) {}


std::shared_ptr<Scene> SceneManager::get_scene()
{
    return scene;
}

std::shared_ptr<Camera> SceneManager::get_camera()
{
    if (camera.lock() == nullptr)
    {
        time_t cur_time = time(NULL);
        throw NoMainCameraException(__FILE__, __func__, __LINE__,
                                    ctime(&cur_time));
    }

    return camera.lock();
}

void SceneManager::set_scene(std::shared_ptr<Scene> &scene_arg)
{
    scene = scene_arg;
}

void SceneManager::set_camera(size_t &id)
{
    auto iterator = scene->get_object_iter(id);
    camera = std::dynamic_pointer_cast<Camera>(*iterator);
}


void SceneManager::add_camera(const Point &position, const Point &direction)
{
    auto camera = CameraFactory(position, direction).create();
    scene->add_object(camera);
}


std::shared_ptr<SceneManager> SceneManagerCreator::get_manager()
{
    if (manager == nullptr)
    {
        create_instance();
    }

    return manager;
}

void SceneManagerCreator::create_instance()
{
    static auto _manager = std::make_shared<SceneManager>();
    manager = _manager;
}
