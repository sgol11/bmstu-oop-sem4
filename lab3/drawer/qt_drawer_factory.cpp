#include "qt_drawer_factory.h"


QtDrawerFactory::QtDrawerFactory(std::shared_ptr<QGraphicsScene> &src_scene) : scene(src_scene) {}


std::unique_ptr<BaseDrawer> QtDrawerFactory::create_graphics()
{
    return std::make_unique<QtDrawer>(scene);
}
