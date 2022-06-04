#include <iterator>
#include "scene.h"


void Scene::add_object(const std::shared_ptr<Object> &object)
{
    if (object->is_visible())
        model_num += 1;
    else
        camera_num += 1;

    objects->add(object);
}

void Scene::remove_object(size_t &id)
{
    auto iterator = get_object_iter(id);
    objects->remove(iterator);
}


Iterator Scene::begin()
{
    return objects->begin();
}

Iterator Scene::end()
{
    return objects->end();
}


size_t Scene::get_model_num() const
{
    return model_num;
}

size_t Scene::get_camera_num() const
{
    return camera_num;
}


Iterator Scene::get_object_iter(size_t &id)
{
    auto iterator = begin();

    for (size_t cur = 0; cur < id; cur++)
        iterator++;

    return iterator;
}
