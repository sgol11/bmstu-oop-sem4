#ifndef CAMERA_COMMANDS_H
#define CAMERA_COMMANDS_H

#include <memory>
#include <cstddef>
#include <string>
#include "../base_command.h"
#include "../../objects/camera/camera.h"
#include "../../objects/primitives/point.h"


template <typename Manager>
class BaseCameraCommand : public BaseCommand<Manager> { };


template <typename Manager>
class LoadCameraCommand : public BaseCameraCommand<Manager>
{
    using Action = void(Manager::*)(std::string);

public:
    explicit LoadCameraCommand(Action a, std::string fname_) : act(a)
    {
        fname = fname_;
    }

    void execute(std::shared_ptr<Manager> mng) override { ((*mng).*act)(fname); }

private:
    Action act;
    std::string fname;
};


template <typename Manager>
class AddCameraCommand : public BaseCameraCommand<Manager>
{
    using Action = void(Manager::*)(const Point&, const Point&);

public:
    explicit AddCameraCommand(Action a, Point &pos, Point &dir) : act(a)
    {
        position = pos;
        direction = dir;
    }

    void execute(std::shared_ptr<Manager> mng) override { ((*mng).*act)(position, direction); }

private:
    Action act;
    Point position, direction;
};


template <typename Manager>
class RemoveCameraCommand : public BaseCameraCommand<Manager>
{
    using Action = void(Manager::*)(std::size_t&);

public:
    explicit RemoveCameraCommand(Action a, std::size_t &id_) : act(a)
    {
        id = id_;
    }

    void execute(std::shared_ptr<Manager> mng) override { ((*mng).*act)(id); }

private:
    Action act;
    std::size_t id;
};


template <typename Manager>
class SetCameraCommand : public BaseCameraCommand<Manager>
{
    using Action = void(Manager::*)(std::size_t&);

public:
    explicit SetCameraCommand(Action a, std::size_t id_) : act(a)
    {
        id = id_;
    }

    void execute(std::shared_ptr<Manager> mng) override { ((*mng).*act)(id); }

private:
    Action act;
    std::size_t id;
};


template <typename Manager>
class MoveCameraCommand : public BaseCameraCommand<Manager>
{
    using Action = void(Manager::*)(std::size_t, const Point&, const Point&, const Point&);

public:
    explicit MoveCameraCommand(Action a, std::size_t id_,
                               Point &move_params_,
                               Point &scale_params_,
                               Point &rotate_params_) : act(a)
    {
        id = id_;
        move_params = move_params_;
        scale_params = scale_params_;
        rotate_params = rotate_params_;
    }

    void execute(std::shared_ptr<Manager> mng) override { ((*mng).*act)(id, move_params,
                                                                            Point{1, 1, 1},
                                                                            rotate_params); }

private:
    Action act;
    std::size_t id;
    Point move_params, scale_params, rotate_params;
};


template <typename Manager>
class CountCameraCommand : public BaseCameraCommand<Manager>
{
    using Action = std::size_t(Manager::*)();

public:
    explicit CountCameraCommand(Action a, std::shared_ptr<size_t> &count_) : act(a)
    {
        count = count_;
    }

    void execute(std::shared_ptr<Manager> mng) override { *count = ((*mng).*act)(); }

private:
    Action act;
    std::shared_ptr<size_t> count;
};


#endif // CAMERA_COMMANDS_H
