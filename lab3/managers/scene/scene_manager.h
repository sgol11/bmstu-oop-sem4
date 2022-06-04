#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <memory>
#include "../base_manager.h"
#include "../../scene/scene.h"
#include "../../objects/camera/camera.h"


class SceneManager : public BaseManager
{
public:
    SceneManager();
    SceneManager(const SceneManager&) = delete;
    SceneManager &operator = (const SceneManager&) = delete;
    ~SceneManager() override = default;

    void set_scene(std::shared_ptr<Scene> &scene_arg);
    void set_camera(size_t &id);

    void add_camera(const Point &position, const Point &direction);
    void remove_object(size_t &id) {scene->remove_object(id);}

    size_t count_camera() {return scene->get_camera_num();}
    size_t count_model() {return scene->get_model_num();}

    std::shared_ptr<Scene>  get_scene();
    std::shared_ptr<Camera> get_camera();

private:
    std::shared_ptr<Scene>  scene;
    std::weak_ptr<Camera>  camera;
};


class SceneManagerCreator
{
public:
    std::shared_ptr<SceneManager> get_manager();

private:
    void create_instance();
    std::shared_ptr<SceneManager> manager;
};


#endif // SCENE_MANAGER_H
