#include "camera_commands.h"


// LOAD CAMERA

LoadCameraCommand::LoadCameraCommand(std::string name_arg) : name(name_arg)
{
    manager = LoadManagerCreator().get_manager();
    act = &LoadManager::load_camera;
}

void LoadCameraCommand::execute()
{
    ((*manager).*act)(name);
};


// ADD CAMERA

AddCameraCommand::AddCameraCommand(const Point &position_arg, const Point &direction_arg) :
    position(position_arg), direction(direction_arg)
{
    manager = SceneManagerCreator().get_manager();
    act = &SceneManager::add_camera;
}

void AddCameraCommand::execute()
{
    ((*manager).*act)(position, direction);
};


// REMOVE CAMERA

RemoveCameraCommand::RemoveCameraCommand(std::size_t src_id) : id(src_id)
{
    manager = SceneManagerCreator().get_manager();
    act = &SceneManager::remove_object;
}

void RemoveCameraCommand::execute()
{
    ((*manager).*act)(id);
}


// SET MAIN CAMERA

SetCameraCommand::SetCameraCommand(std::size_t src_id) : id(src_id)
{
    manager = SceneManagerCreator().get_manager();
    act = &SceneManager::set_camera;
}

void SetCameraCommand::execute()
{
    ((*manager).*act)(id);
}


// MOVE CAMERA

MoveCameraCommand::MoveCameraCommand(std::size_t src_id, const Point &src_move_params,
                                                         const Point &src_scale_params,
                                                         const Point &src_rotate_params) :
    id(src_id), move_params(src_move_params), scale_params(src_scale_params), rotate_params(src_rotate_params)
{
    manager = TransformManagerCreator().get_manager();
    act = &TransformManager::transform;
}

void MoveCameraCommand::execute()
{
    ((*manager).*act)(id, move_params, Point{1, 1, 1}, rotate_params);
}


// COUNT CAMERA

CountCameraCommand::CountCameraCommand(std::shared_ptr<size_t> &src_count) : count(src_count)
{
    manager = SceneManagerCreator().get_manager();
    act = &SceneManager::count_camera;
}

void CountCameraCommand::execute()
{
    *count = ((*manager).*act)();
}
