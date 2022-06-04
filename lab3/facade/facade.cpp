#include "facade.h"


Facade::Facade()
{
    draw_manager = DrawManagerCreator().get_manager();
    load_manager = LoadManagerCreator().get_manager();
    scene_manager = SceneManagerCreator().get_manager();
    transform_manager = TransformManagerCreator().get_manager();
}


void Facade::execute(std::shared_ptr<BaseCommand<DrawManager>> command)
{
    command->execute(draw_manager);
}

void Facade::execute(std::shared_ptr<BaseCommand<LoadManager>> command)
{
    command->execute(load_manager);
}

void Facade::execute(std::shared_ptr<BaseCommand<SceneManager>> command)
{
    command->execute(scene_manager);
}

void Facade::execute(std::shared_ptr<BaseCommand<TransformManager>> command)
{
    command->execute(transform_manager);
}
