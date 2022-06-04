#ifndef BASE_DRAWER_H
#define BASE_DRAWER_H

#include "../objects/primitives/point.h"


class BaseDrawer
{
public:
    BaseDrawer() = default;
    virtual ~BaseDrawer() = default;

    virtual void draw_line(const Point &point1, const Point &point2) = 0;
    virtual void clear_scene() = 0;
};


#endif // BASE_DRAWER_H
