#ifndef FACADE_H
#define FACADE_H

#include <memory>
#include "../commands/base_command.h"


class Facade
{
public:
    Facade();
    ~Facade() = default;

    void execute(std::shared_ptr<BaseCommand<DrawManager>> command);
    void execute(std::shared_ptr<BaseCommand<LoadManager>> command);
    void execute(std::shared_ptr<BaseCommand<SceneManager>> command);
    void execute(std::shared_ptr<BaseCommand<TransformManager>> command);

private:
    std::shared_ptr<DrawManager>      draw_manager;
    std::shared_ptr<LoadManager>      load_manager;
    std::shared_ptr<SceneManager>     scene_manager;
    std::shared_ptr<TransformManager> transform_manager;
};


#endif // FACADE_H
