#ifndef DRAW_VISITOR_H
#define DRAW_VISITOR_H

#include <cmath>
#include "visitor.h"
#include "../drawer/base_drawer.h"


class DrawVisitor : public Visitor
{
public:
    DrawVisitor(const std::shared_ptr<BaseDrawer> &drawer_arg, const std::shared_ptr<Camera> &camera_arg);
    ~DrawVisitor() override = default;

    void visit(const FrameModel &model)     override;
    void visit(const Camera &camera)        override;
    void visit(const Composite &composite)  override;
    void visit(const Scene &scene)          override;

private:
    std::shared_ptr<BaseDrawer> drawer;
    std::shared_ptr<Camera>     camera;

    Point project_point(const Point &point);
};


class DrawVisitorFactory : public VisitorFactory
{
public:
    DrawVisitorFactory(std::shared_ptr<BaseDrawer> &drawer_arg, std::shared_ptr<Camera> &camera_arg);
    ~DrawVisitorFactory() override = default;

    std::unique_ptr<Visitor> create() override;

private:
    std::shared_ptr<BaseDrawer> drawer;
    std::shared_ptr<Camera>     camera;
};


#endif // DRAW_VISITOR_H
