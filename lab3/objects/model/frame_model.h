#ifndef FRAME_MODEL_H
#define FRAME_MODEL_H

#include <memory>

#include "model.h"
#include "model_structure.h"
#include "../../visitor/draw_visitor.h"


class FrameModel : public Model
{
    friend void DrawVisitor::visit(const FrameModel &model);

public:
    FrameModel() = default;
    explicit FrameModel(std::shared_ptr<FrameModelStructure> src_model_structure):
                       model_structure(src_model_structure) {}
    ~FrameModel() override = default;

    virtual void update_center() override;
    virtual Point get_center() override;

    void transform(const Point &move_params, const Point &scale_params, const Point &rotate_params) override;
    void accept(std::shared_ptr<Visitor> visitor) override;

protected:
    std::shared_ptr<FrameModelStructure> get_model_structure() const;

private:
    std::shared_ptr<FrameModelStructure> model_structure;
};


#endif // FRAME_MODEL_H
