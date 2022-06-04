#ifndef LOAD_MANAGER_H
#define LOAD_MANAGER_H

#include <memory>

#include "../base_manager.h"
#include "../../director/base_load_director.h"
#include "../../objects/object.h"
#include "../../scene/scene.h"
#include "../../director/model/model_director.h"
#include "../../director/camera/camera_director.h"
#include "../scene/scene_manager.h"


class LoadManager : public BaseManager
{
public:
    LoadManager() = default;
    LoadManager(const LoadManager &manager) = delete;
    ~LoadManager() override = default;

    void load_camera(std::string fname);
    void load_model(std::string fname);
    void set_director(std::shared_ptr<BaseLoadDirector> src_director);

private:
    std::shared_ptr<BaseLoadDirector> director = nullptr;
};


class LoadManagerCreator
{
public:
    std::shared_ptr<LoadManager> get_manager();

private:
    void create_instance();
    std::shared_ptr<LoadManager> manager;
};


#endif // LOAD_MANAGER_H
