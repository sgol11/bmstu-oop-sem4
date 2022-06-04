#include "draw_visitor.h"
#include "../objects/model/frame_model.h"
#include "../objects/model/model.h"
#include "../objects/camera/camera.h"
#include "../objects/composite/composite.h"

#include "iostream"


DrawVisitor::DrawVisitor(const std::shared_ptr<BaseDrawer> &drawer_arg, const std::shared_ptr<Camera> &camera_arg):
    drawer(drawer_arg), camera(camera_arg) {};


void DrawVisitor::visit(const FrameModel &model)
{
    auto points = model.get_model_structure()->get_points();
    auto edges  = model.get_model_structure()->get_edges();

    for (const auto &edge : edges)
        drawer->draw_line(project_point(points[edge.get_start_index()]),
                          project_point(points[edge.get_end_index()]));
}

double to_radians(double degrees)
{
    return degrees * (M_PI / 180);
}

Point DrawVisitor::project_point(const Point &point)
{
    Point res_point(point);

    Point center = camera->get_camera_structure()->get_position();
    Point direction = camera->get_camera_structure()->get_direction();

    res_point.rotate(-direction.get_x(), -direction.get_y(), -direction.get_z());
    res_point.move(-center.get_x(), -center.get_y(), -center.get_z());

    return res_point;
}


DrawVisitorFactory::DrawVisitorFactory(std::shared_ptr<BaseDrawer> &drawer_arg,
                                       std::shared_ptr<Camera> &camera_arg)
{
    drawer = drawer_arg;
    camera = camera_arg;
}

std::unique_ptr<Visitor> DrawVisitorFactory::create()
{
    return std::make_unique<DrawVisitor>(drawer, camera);
}


void DrawVisitor::visit(const Camera &camera)       {};
void DrawVisitor::visit(const Composite &composite) {};
void DrawVisitor::visit(const Scene &scene)         {};
