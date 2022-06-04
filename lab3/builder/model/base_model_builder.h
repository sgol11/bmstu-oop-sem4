#ifndef BASE_MODEL_BUILDER_H
#define BASE_MODEL_BUILDER_H

#include "../base_builder.h"


class BaseModelBuilder : public BaseBuilder
{
public:
    BaseModelBuilder() = default;
    ~BaseModelBuilder() override = default;

    virtual void build_center(const Point &center) = 0;
    virtual void build_point(const Point &point) = 0;
    virtual void build_edge(const Edge &edge) = 0;

    virtual std::shared_ptr<Object> get() = 0;
};


#endif // BASE_MODEL_BUILDER_H
