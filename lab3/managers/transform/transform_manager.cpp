#include "transform_manager.h"


void TransformManager::transform(size_t id, const Point &move_params,
                                            const Point &scale_params,
                                            const Point &rotate_params)
{
    auto object_iter = SceneManagerCreator().get_manager()->get_scene()->get_object_iter(id);
    (*object_iter)->transform(move_params, scale_params, rotate_params);
}


std::shared_ptr<TransformManager> TransformManagerCreator::get_manager()
{
    if (manager == nullptr)
    {
        create_instance();
    }

    return manager;
}

void TransformManagerCreator::create_instance()
{
    static auto _manager = std::make_shared<TransformManager>();
    manager = _manager;
}
