#ifndef BASE_COMMAND_H
#define BASE_COMMAND_H

#include <memory>

#include "../managers/draw/draw_manager.h"
#include "../managers/load/load_manager.h"
#include "../managers/scene/scene_manager.h"
#include "../managers/transform/transform_manager.h"


template <typename Manager>
class BaseCommand
{
public:
    virtual ~BaseCommand() = default;
    virtual void execute(std::shared_ptr<Manager>) = 0;
};


#endif //BASE_COMMAND_H
