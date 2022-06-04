#ifndef CAMERA_H
#define CAMERA_H

#include "base_camera.h"
#include "camera_structure.h"


class Camera : public BaseCamera
{
    friend DrawVisitor;
public:
    Camera() = default;
    explicit Camera(std::shared_ptr<CameraStructure> src_camera_structure):
                    camera_structure(src_camera_structure) {}
    Camera(const Point &position_arg, const Point &direction_arg);
    ~Camera() override = default;

    virtual void update_center() override;
    virtual Point get_center() override;

    void transform(const Point &move_params, const Point &scale_params, const Point &rotate_params) override;
    void accept(std::shared_ptr<Visitor> visitor) override;

protected:
    std::shared_ptr<CameraStructure> get_camera_structure() const;

private:
    std::shared_ptr<CameraStructure> camera_structure;
};


class CameraFactory : public BaseCameraFactory
{
public:
    CameraFactory(const Point &position_arg, const Point &direction_arg);
    ~CameraFactory() override = default;

    std::shared_ptr<BaseCamera> create() override;

private:
    Point position{};
    Point direction{0, 0, 0};
};


#endif // CAMERA_H
