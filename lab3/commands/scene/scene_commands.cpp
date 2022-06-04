#include "scene_commands.h"


DrawSceneCommand::DrawSceneCommand(std::shared_ptr<BaseDrawer> &src_drawer) : drawer(src_drawer)
{
    manager = DrawManagerCreator().get_manager();
    act = &DrawManager::draw;
}

void DrawSceneCommand::execute()
{
    ((*manager).*act)(drawer);
}
