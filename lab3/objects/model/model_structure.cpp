#include "model_structure.h"


FrameModelStructure::FrameModelStructure(const std::vector<Point> &src_points,
                                         const std::vector<Edge> &src_edges,
                                         const Point &src_center):
    points(src_points), edges(src_edges), center(src_center) {}


const std::vector<Point> &FrameModelStructure::get_points()
{
    return points;
}

const std::vector<Edge> &FrameModelStructure::get_edges()
{
    return edges;
}

const Point &FrameModelStructure::get_center()
{
    return center;
}

void FrameModelStructure::update_center()
{
    center = Point{0, 0, 0};
    size_t count = 0;

    for (const auto &point : points)
    {
        center = center + point;
        count++;
    }

    center = Point(center.get_x() / count,
                   center.get_y() / count,
                   center.get_z() / count);
}


void FrameModelStructure::add_point(const Point &point)
{
    points.push_back(point);
}

void FrameModelStructure::add_edge(const Edge &edge)
{
    edges.push_back(edge);
}

void FrameModelStructure::set_center(const Point &src_center)
{
    center = src_center;
}


void FrameModelStructure::move(const Point &move_params)
{
    for (Point &point: points)
    {
        point.move(move_params.get_x(), move_params.get_y(), move_params.get_z());
    }
}

void FrameModelStructure::scale(const Point &scale_params)
{
    for (Point &point: points)
    {
        point.scale(scale_params.get_x(), scale_params.get_y(), scale_params.get_z());
    }
}

void FrameModelStructure::rotate(const Point &rotate_params)
{
    for (Point &point: points)
    {
        point.rotate(rotate_params.get_x(), rotate_params.get_y(), rotate_params.get_z());
    }
}

void FrameModelStructure::transform(const Point &move_params, const Point &scale_params, const Point &rotate_params)
{
    move(move_params);
    update_center();

    move(-center);

    scale(scale_params);
    rotate(rotate_params);

    move(center);
}
