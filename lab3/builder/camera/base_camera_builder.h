#ifndef BASE_CAMERA_BUILDER_H
#define BASE_CAMERA_BUILDER_H

#include "../base_builder.h"


class BaseCameraBuilder : public BaseBuilder
{
public:
    BaseCameraBuilder() = default;
    ~BaseCameraBuilder() override = default;

    virtual void build_position(const Point &position) = 0;
    virtual void build_direction(const Point &direction) = 0;

    virtual std::shared_ptr<Object> get() = 0;

protected:
    Point position, direction;
};


#endif // BASE_CAMERA_BUILDER_H
