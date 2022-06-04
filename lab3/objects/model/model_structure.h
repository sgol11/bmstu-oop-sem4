#ifndef MODEL_STRUCTURE_H
#define MODEL_STRUCTURE_H

#include <memory>
#include <vector>

#include "../primitives/point.h"
#include "../primitives/edge.h"
#include "../../visitor/draw_visitor.h"


class FrameModelStructure
{
public:
    FrameModelStructure() = default;
    FrameModelStructure(const std::vector<Point> &src_points,
                        const std::vector<Edge> &src_edges,
                        const Point &src_center = {});
    ~FrameModelStructure() = default;

    const std::vector<Point> &get_points();
    const std::vector<Edge>  &get_edges();
    const Point              &get_center();

    void update_center();

    void set_center(const Point &src_center);
    void add_point(const Point &point);
    void add_edge (const Edge  &edge);

    virtual void transform(const Point &move_params, const Point &scale_params, const Point &rotate_params);

    friend void DrawVisitor::visit(const FrameModel &model);

private:
    Point center{};
    std::vector<Point> points;
    std::vector<Edge>  edges;

    void move  (const Point &move_params);
    void scale (const Point &scale_params);
    void rotate(const Point &rotate_params);
};


#endif // MODEL_STRUCTURE_H
