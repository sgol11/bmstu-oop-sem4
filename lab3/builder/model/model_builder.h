#ifndef MODEL_BUILDER_H
#define MODEL_BUILDER_H

#include "base_model_builder.h"
#include "../../objects/model/frame_model.h"
#include "../../objects/model/model_structure.h"
#include "../../objects/primitives/point.h"
#include "../../objects/primitives/edge.h"


class ModelBuilder : public BaseModelBuilder
{
public:
    ModelBuilder() = default;
    ~ModelBuilder() override = default;

    bool is_built() override;
    void reset() override;
    void build() override;

    void build_center(const Point &center) override;
    void build_point(const Point &point) override;
    void build_edge(const Edge &edge) override;

    std::shared_ptr<Object> get() override;

private:
    std::shared_ptr<FrameModelStructure> model_struct;
};


class ModelBuilderCreator : public BuilderCreator
{
public:
    ModelBuilderCreator() = default;
    ~ModelBuilderCreator() override = default;

    std::shared_ptr<BaseBuilder> create_builder() override;
};


#endif // MODEL_BUILDER_H
