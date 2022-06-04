#ifndef MODEL_COMMANDS_H
#define MODEL_COMMANDS_H

#include <cstddef>
#include <memory>
#include <string>

#include "../base_command.h"
#include "../../objects/object.h"
#include "../../objects/primitives/point.h"


template <typename Manager>
class BaseModelCommand : public BaseCommand<Manager> { };


template <typename Manager>
class LoadModelCommand : public BaseModelCommand<Manager>
{
    using Action = void(Manager::*)(std::string);

public:
    explicit LoadModelCommand(Action a, std::string fname_) : act(a)
    {
        fname = fname_;
    }

    void execute(std::shared_ptr<Manager> mng) override { ((*mng).*act)(fname); }

private:
    Action act;
    std::string fname;
};


template <typename Manager>
class RemoveModelCommand : public BaseModelCommand<Manager>
{
    using Action = void(Manager::*)(std::size_t&);

public:
    explicit RemoveModelCommand(Action a, std::size_t &id_) : act(a)
    {
        id = id_;
    }

    void execute(std::shared_ptr<Manager> mng) override { ((*mng).*act)(id); }

private:
    Action act;
    std::size_t id;
};


template <typename Manager>
class MoveModelCommand : public BaseModelCommand<Manager>
{
    using Action = void(Manager::*)(std::size_t, const Point&, const Point&, const Point&);

public:
    explicit MoveModelCommand(Action a, std::size_t id_,
                              double dx_, double dy_, double dz_) : act(a)
    {
        id = id_;
        dx = dx_; dy = dy_; dz = dz_;
    }

    void execute(std::shared_ptr<Manager> mng) override { ((*mng).*act)(id, Point{dx, dy, dz},
                                                                            Point{1, 1, 1},
                                                                            Point{0, 0, 0}); }

private:
    Action act;
    std::size_t id;
    double dx, dy, dz;
};


template <typename Manager>
class ScaleModelCommand : public BaseModelCommand<Manager>
{
    using Action = void(Manager::*)(std::size_t, const Point&, const Point&, const Point&);

public:
    explicit ScaleModelCommand(Action a, std::size_t id_,
                               double kx_, double ky_, double kz_) : act(a)
    {
        id = id_;
        kx = kx_; ky = ky_; kz = kz_;
    }

    void execute(std::shared_ptr<Manager> mng) override { ((*mng).*act)(id, Point{0, 0, 0},
                                                                            Point{kx, ky, kz},
                                                                            Point{0, 0, 0}); }

private:
    Action act;
    std::size_t id;
    double kx, ky, kz;
};


template <typename Manager>
class RotateModelCommand : public BaseModelCommand<Manager>
{
    using Action = void(Manager::*)(std::size_t, const Point&, const Point&, const Point&);

public:
    explicit RotateModelCommand(Action a, std::size_t id_,
                                double ox_, double oy_, double oz_) : act(a)
    {
        id = id_;
        ox = ox_; oy = oy_; oz = oz_;
    }

    void execute(std::shared_ptr<Manager> mng) override { ((*mng).*act)(id, Point{0, 0, 0},
                                                                            Point{1, 1, 1},
                                                                            Point{ox, oy, oz}); }

private:
    Action act;
    std::size_t id;
    double ox, oy, oz;
};


template <typename Manager>
class TransformModelCommand : public BaseModelCommand<Manager>
{
    using Action = void(Manager::*)(std::size_t, const Point&, const Point&, const Point&);

public:
    explicit TransformModelCommand(Action a, std::size_t id_,
                                   Point move_params_, Point scale_params_, Point rotate_params_) : act(a)
    {
        id = id_;
        move_params = move_params_;
        scale_params = scale_params_;
        rotate_params = rotate_params_;
    }

    void execute(std::shared_ptr<Manager> mng) override { ((*mng).*act)(id, move_params,
                                                                            scale_params,
                                                                            rotate_params); }

private:
    Action act;
    std::size_t id;
    Point& move_params, scale_params, rotate_params;
};


template <typename Manager>
class CountModelCommand : public BaseModelCommand<Manager>
{
    using Action = std::size_t(Manager::*)();

public:
    explicit CountModelCommand(Action a, std::shared_ptr<size_t> &count_) : act(a)
    {
        count = count_;
    }

    void execute(std::shared_ptr<Manager> mng) override { *count = ((*mng).*act)(); }

private:
    Action act;
    std::shared_ptr<size_t> count;
};


#endif //MODEL_COMMANDS_H
