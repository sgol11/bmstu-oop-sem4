#include "qt_drawer.h"


QtDrawer::QtDrawer(std::shared_ptr<QGraphicsScene> &src_scene)
{
    scene = src_scene;
}

QtDrawer::QtDrawer(const QtDrawer &src_drawer)
{
    scene = src_drawer.scene;
}


void QtDrawer::draw_line(const Point &point1, const Point &point2)
{
    scene->addLine(point1.get_x(), -point1.get_y(),
                   point2.get_x(), -point2.get_y());
}

void QtDrawer::clear_scene()
{
    scene->clear();
}
