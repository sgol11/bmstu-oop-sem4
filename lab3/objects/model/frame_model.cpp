#include "frame_model.h"


void FrameModel::transform(const Point &move_params, const Point &scale_params, const Point &rotate_params)
{
    model_structure->transform(move_params, scale_params, rotate_params);
}


void FrameModel::accept(std::shared_ptr<Visitor> visitor)
{
    visitor->visit(*this);
}


std::shared_ptr<FrameModelStructure> FrameModel::get_model_structure() const
{
    return model_structure;
}

Point FrameModel::get_center()
{
    return model_structure->get_center();
}

void FrameModel::update_center()
{
    model_structure->update_center();
}
