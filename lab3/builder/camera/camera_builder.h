#ifndef CAMERA_BUILDER_H
#define CAMERA_BUILDER_H

#include "base_camera_builder.h"
#include "../../objects/camera/camera.h"


class CameraBuilder : public BaseCameraBuilder
{
public:
    CameraBuilder() = default;
    ~CameraBuilder() override = default;

    bool is_built() override;
    void reset() override;
    void build() override;

    virtual void build_position(const Point &position) override;
    virtual void build_direction(const Point &direction) override;

    std::shared_ptr<Object> get() override;

private:
    std::shared_ptr<Camera> camera;
};


class CameraBuilderCreator : public BuilderCreator
{
public:
    CameraBuilderCreator() = default;
    ~CameraBuilderCreator() override = default;

    std::shared_ptr<BaseBuilder> create_builder() override;
};


#endif // CAMERA_BUILDER_H
