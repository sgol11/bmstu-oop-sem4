#include "composite.h"

#include <iostream>


Composite::Composite(std::shared_ptr<Object> &object)
{
    objects.push_back(object);
}

Composite::Composite(const std::vector<std::shared_ptr<Object>> &vector)
{
    objects = vector;
}


bool Composite::add(const std::shared_ptr<Object> &object)
{
    if (object->is_visible())
    {
        auto iter = objects.begin();
        while ((*iter)->is_visible())
            iter++;
        objects.insert(iter, object);
    }
    else
        objects.push_back(object);

    return true;
}

bool Composite::remove(const Iterator &iter)
{
    objects.erase(iter);

    return true;
}


void Composite::update_center()
{
    center = Point{0, 0, 0};
    size_t count = 0;

    for (const auto &object : objects)
    {
        center = center + object->get_center();
        count++;
    }

    center = Point(center.get_x() / count,
                   center.get_y() / count,
                   center.get_z() / count);
}

Point Composite::get_center()
{
    return center;
}

void Composite::move_objects_to_center()
{
    for (const auto &object : objects)
    {
        Point diff = object->get_center() - center;
        object->transform(diff, Point{1, 1, 1}, Point{0, 0, 0});
    }
}

void Composite::move_objects_to_origin()
{
    for (const auto &object : objects)
    {
        Point diff = object->get_center() + center;
        object->transform(diff, Point{1, 1, 1}, Point{0, 0, 0});
    }
}

void Composite::transform_objects(const Point &move_params, const Point &scale_params, const Point &rotate_params)
{
    for (const auto &object : objects)
    {
        object->transform(move_params, scale_params, rotate_params);
    }
}

void Composite::transform(const Point &move_params, const Point &scale_params, const Point &rotate_params)
{
    update_center();

    move_objects_to_center();
    transform_objects(move_params, scale_params, rotate_params);
    move_objects_to_origin();
}


void Composite::accept(std::shared_ptr<Visitor> visitor)
{
    for (const auto &object : objects)
    {
        object->accept(visitor);
    }
}


Iterator Composite::begin()
{
    return objects.begin();
}

Iterator Composite::end()
{
    return objects.end();
}
