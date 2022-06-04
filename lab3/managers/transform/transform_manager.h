#ifndef TRANSFORM_MANAGER_H
#define TRANSFORM_MANAGER_H

#include "../base_manager.h"
#include "../../objects/object.h"
#include "../../managers/scene/scene_manager.h"


class TransformManager : public BaseManager
{
public:
    TransformManager() = default;
    TransformManager(const TransformManager &manager) = delete;
    TransformManager &operator = (const TransformManager &manager) = delete;
    ~TransformManager() override = default;

    void transform(size_t, const Point &, const Point &, const Point &);
};


class TransformManagerCreator
{
public:
    std::shared_ptr<TransformManager> get_manager();

private:
    void create_instance();
    std::shared_ptr<TransformManager> manager;
};


#endif // TRANSFORM_MANAGER_H
