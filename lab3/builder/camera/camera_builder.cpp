#include "camera_builder.h"


bool CameraBuilder::is_built()
{
    return camera != nullptr;
}

void CameraBuilder::reset()
{
    camera.reset();
}

void CameraBuilder::build()
{
    camera = std::make_shared<Camera>();
}


void CameraBuilder::build_position(const Point &position)
{
    if (camera != nullptr)
    {
        auto camera_structure = std::make_shared<CameraStructure>();
        camera_structure->set_position(position);
        camera = std::make_shared<Camera>(camera_structure);
    }
    else
    {
        auto camera_structure = std::make_shared<CameraStructure>(position, Point{0, 0, 0});
        camera = std::make_shared<Camera>(camera_structure);
    }
}

void CameraBuilder::build_direction(const Point &direction)
{
    if (camera != nullptr)
    {
        auto camera_structure = std::make_shared<CameraStructure>();
        camera_structure->set_direction(direction);
        camera = std::make_shared<Camera>(camera_structure);
    }
    else
    {
        auto camera_structure = std::make_shared<CameraStructure>(Point{0, 0, 0}, direction);
        camera = std::make_shared<Camera>(camera_structure);
    }
}


std::shared_ptr<Object> CameraBuilder::get()
{
    return camera;
}


std::shared_ptr<BaseBuilder> CameraBuilderCreator::create_builder()
{
    return std::make_shared<CameraBuilder>();
}
