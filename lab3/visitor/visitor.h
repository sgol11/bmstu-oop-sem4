#ifndef VISITOR_H
#define VISITOR_H

#include <memory>


class FrameModel;
class Camera;
class Composite;
class Scene;

class Visitor
{
public:
    Visitor() = default;
    virtual ~Visitor() = default;

    virtual void visit(const Camera &camera) = 0;
    virtual void visit(const FrameModel &model) = 0;
    virtual void visit(const Composite &composite) = 0;
    virtual void visit(const Scene &scene) = 0;
};


class VisitorFactory
{
public:
    VisitorFactory() = default;
    virtual ~VisitorFactory() = default;

    virtual std::unique_ptr<Visitor> create() = 0;
};


#endif // VISITOR_H
