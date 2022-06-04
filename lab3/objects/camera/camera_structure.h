#ifndef CAMERA_STRUCTURE_H
#define CAMERA_STRUCTURE_H

#include <memory>
#include <vector>

#include "../primitives/point.h"
#include "../primitives/edge.h"
#include "../../visitor/draw_visitor.h"


class CameraStructure
{
public:
    CameraStructure() = default;
    CameraStructure(const Point &position_arg, const Point &direction_arg);
    ~CameraStructure() = default;

    const Point get_position();
    const Point get_direction();

    void set_position(const Point &position_arg);
    void set_direction(const Point &direction_arg);

    virtual void transform(const Point &move_params, const Point &scale_params, const Point &rotate_params);

private:
    Point position{};
    Point direction{0, 0, 0};

    void move  (const Point &move_params);
    void scale (const Point &scale_params);
    void rotate(const Point &rotate_params);
};


#endif // CAMERA_STRUCTURE_H
