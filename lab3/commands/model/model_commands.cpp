#include "model_commands.h"


// LOAD MODEL

LoadModelCommand::LoadModelCommand(std::string name_arg): name(name_arg)
{
    manager = LoadManagerCreator().get_manager();
    act = &LoadManager::load_model;
}

void LoadModelCommand::execute()
{
    ((*manager).*act)(name);
}


// REMOVE MODEL

RemoveModelCommand::RemoveModelCommand(const std::size_t src_id) : id(src_id)
{
    manager = SceneManagerCreator().get_manager();
    act = &SceneManager::remove_object;
}

void RemoveModelCommand::execute()
{
    ((*manager).*act)(id);
}


// MOVE MODEL

MoveModelCommand::MoveModelCommand(std::size_t src_id, double src_dx, double src_dy, double src_dz):
    id(src_id), dx(src_dx), dy(src_dy), dz(src_dz)
{
    manager = TransformManagerCreator().get_manager();
    act = &TransformManager::transform;
}

void MoveModelCommand::execute()
{
    ((*manager).*act)(id, Point{dx, dy, dz}, Point{1, 1, 1}, Point{0, 0, 0});
}


// SCALE MODEL

ScaleModelCommand::ScaleModelCommand(std::size_t src_id, double src_kx, double src_ky, double src_kz):
    id(src_id), kx(src_kx), ky(src_ky), kz(src_kz)
{
    manager = TransformManagerCreator().get_manager();
    act = &TransformManager::transform;
}

void ScaleModelCommand::execute()
{
    ((*manager).*act)(id, Point{0, 0, 0}, Point{kx, ky, kz}, Point{0, 0, 0});
}


// ROTATE MODEL

RotateModelCommand::RotateModelCommand(std::size_t src_id, double src_ox, double src_oy, double src_oz):
        id(src_id), ox(src_ox), oy(src_oy), oz(src_oz)
{
    manager = TransformManagerCreator().get_manager();
    act = &TransformManager::transform;
}

void RotateModelCommand::execute()
{
    ((*manager).*act)(id, Point{0, 0, 0}, Point{1, 1, 1}, Point{ox, oy, oz});
}


// TRANSFORM MODEL

TransformModelCommand::TransformModelCommand(std::size_t src_id,
                                             const Point &src_move_params,
                                             const Point &src_scale_params,
                                             const Point &src_rotate_params):
    id(src_id), move_params(src_move_params), scale_params(src_scale_params), rotate_params(src_rotate_params)
{
    manager = TransformManagerCreator().get_manager();
    act = &TransformManager::transform;
}

void TransformModelCommand::execute()
{
    ((*manager).*act)(id, move_params, scale_params, rotate_params);
}


// COUNT MODEL

CountModelCommand::CountModelCommand(std::shared_ptr<size_t> &src_count) : count(src_count)
{
    manager = SceneManagerCreator().get_manager();
    act = &SceneManager::count_model;
}

void CountModelCommand::execute()
{
    *count = ((*manager).*act)();
}
