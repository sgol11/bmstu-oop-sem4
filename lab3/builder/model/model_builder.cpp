#include "model_builder.h"
#include "../../exceptions/builder_exceptions.h"


bool ModelBuilder::is_built()
{
    return model_struct != nullptr;
}

void ModelBuilder::reset()
{
    model_struct.reset();
}

void ModelBuilder::build()
{
    model_struct = std::make_shared<FrameModelStructure>();
}


void ModelBuilder::build_center(const Point &center)
{
    if (model_struct == nullptr)
    {
        time_t cur_time = time(NULL);
        throw BuildNotStartedException(__FILE__, __func__, __LINE__,
                                       ctime(&cur_time));
    }

    model_struct->set_center(center);
}

void ModelBuilder::build_point(const Point &point)
{
    if (model_struct == nullptr)
    {
        time_t cur_time = time(NULL);
        throw BuildNotStartedException(__FILE__, __func__, __LINE__,
                                       ctime(&cur_time));
    }

    model_struct->add_point(point);
}

void ModelBuilder::build_edge(const Edge &edge)
{
    if (model_struct == nullptr)
    {
        time_t cur_time = time(NULL);
        throw BuildNotStartedException(__FILE__, __func__, __LINE__,
                                       ctime(&cur_time));
    }

    model_struct->add_edge(edge);
}


std::shared_ptr<Object> ModelBuilder::get()
{
    return std::make_shared<FrameModel>(model_struct);
}


std::shared_ptr<BaseBuilder> ModelBuilderCreator::create_builder()
{
    return std::make_shared<ModelBuilder>();
}
