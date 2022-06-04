#ifndef BASE_CAMERA_H
#define BASE_CAMERA_H

#include "../object.h"
#include "../primitives/point.h"
#include "../../visitor/draw_visitor.h"


class BaseCamera : public InvisibleObject
{
public:
    BaseCamera() = default;
    virtual ~BaseCamera() = default;
};


class BaseCameraFactory
{
public:
    BaseCameraFactory() = default;
    virtual ~BaseCameraFactory() = default;

    virtual std::shared_ptr<BaseCamera> create() = 0;
};


#endif // BASE_CAMERA_H
