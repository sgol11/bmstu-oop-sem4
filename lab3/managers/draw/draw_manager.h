#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

#include "../base_manager.h"
#include "../../drawer/base_drawer.h"
#include "../../objects/camera/camera.h"
#include "../../scene/scene.h"
#include "../../managers/scene/scene_manager.h"


class DrawManager : public BaseManager
{
public:
    DrawManager() = default;
    DrawManager(const DrawManager &manager) = delete;
    ~DrawManager() override = default;

    void draw(std::shared_ptr<BaseDrawer> &src_drawer);
    void set_drawer(const std::shared_ptr<BaseDrawer> src_drawer);
    void set_camera(const std::shared_ptr<Camera> src_camera);
private:
    std::shared_ptr<BaseDrawer> drawer;
    std::shared_ptr<Camera>     camera;
};


class DrawManagerCreator
{
public:
    std::shared_ptr<DrawManager> get_manager();

private:
    void create_instance();
    std::shared_ptr<DrawManager> manager;
};


#endif // DRAW_MANAGER_H
