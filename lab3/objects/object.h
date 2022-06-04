#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <vector>
#include "primitives/point.h"
#include "primitives/edge.h"
#include "../visitor/visitor.h"


class Object;
using Iterator = std::vector<std::shared_ptr<Object>>::iterator;

class Object
{
public:
    Object() = default;
    virtual ~Object() = default;

    virtual bool is_visible()   { return false; };
    virtual bool is_composite() { return false; };

    virtual bool add(const std::shared_ptr<Object> &) { return false; };
    virtual bool remove(const Iterator &)             { return false; };

    virtual void transform(const Point &move_params, const Point &scale_params, const Point &rotate_params) = 0;
    virtual void accept(std::shared_ptr<Visitor> visitor) = 0;

    virtual Iterator begin() { return Iterator(); };
    virtual Iterator end()   { return Iterator(); };

    virtual void update_center() = 0;
    virtual Point get_center() = 0;
};

class VisibleObject : public Object
{
public:
    VisibleObject() = default;
    virtual ~VisibleObject() override = default;

    bool is_visible() override { return true; }
};

class InvisibleObject : public Object
{
public:
    InvisibleObject() = default;
    virtual ~InvisibleObject() override = default;
};


#endif // OBJECT_H
