#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "../objects/camera/camera.h"
#include "../objects/composite/composite.h"


class Scene
{
public:
    Scene(): objects(std::make_shared<Composite>()) {}
    ~Scene() = default;

    void add_object(const std::shared_ptr<Object> &object);
    void remove_object(size_t &id);

    Iterator begin();
    Iterator end();

    size_t get_model_num() const;
    size_t get_camera_num() const;

    Iterator get_object_iter(size_t &id);

protected:
    std::shared_ptr<Composite> objects;
    size_t model_num = 0;
    size_t camera_num = 0;
};


#endif // SCENE_H
