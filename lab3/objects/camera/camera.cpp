#include "camera.h"
#include "camera_structure.h"


void Camera::transform(const Point &move_params, const Point &scale_params, const Point &rotate_params)
{
    camera_structure->transform(move_params, scale_params, rotate_params);
}

std::shared_ptr<CameraStructure> Camera::get_camera_structure() const
{
    return camera_structure;
}


Point Camera::get_center()
{
    return camera_structure->get_position();
}

void Camera::update_center() {}


void Camera::accept(std::shared_ptr<Visitor> visitor)
{
    visitor->visit(*this);
}


CameraFactory::CameraFactory(const Point &position_arg, const Point &direction_arg)
{
    position = position_arg;
    direction = direction_arg;
}

std::shared_ptr<BaseCamera> CameraFactory::create()
{
    return std::make_shared<Camera>(std::make_shared<CameraStructure>(position, direction));
}
