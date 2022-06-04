#include "camera_structure.h"


CameraStructure::CameraStructure(const Point &position_arg, const Point &direction_arg):
    position(position_arg), direction(direction_arg) {}


const Point CameraStructure::get_position()
{
    return position;
}

const Point CameraStructure::get_direction()
{
    return direction;
}


void CameraStructure::set_position(const Point &position_arg)
{
    position = position_arg;
}

void CameraStructure::set_direction(const Point &direction_arg)
{
    direction = direction_arg;
}


void CameraStructure::move(const Point &move_params)
{
    position.move(move_params.get_x(), move_params.get_y(), move_params.get_z());
}

void CameraStructure::scale(const Point &scale_params)
{
    position.scale(scale_params.get_x(), scale_params.get_y(), scale_params.get_z());
}

void CameraStructure::rotate(const Point &rotate_params)
{
    position.rotate(rotate_params.get_x(), rotate_params.get_y(), rotate_params.get_z());

    direction.set_x(direction.get_x() + rotate_params.get_x());
    direction.set_y(direction.get_y() + rotate_params.get_y());
    direction.set_z(direction.get_z() + rotate_params.get_z());
}


void CameraStructure::transform(const Point &move_params,
                                const Point &scale_params,
                                const Point &rotate_params)
{
    move(move_params);
    scale(scale_params);
    rotate(rotate_params);
}
