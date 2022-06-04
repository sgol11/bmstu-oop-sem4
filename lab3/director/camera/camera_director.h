#ifndef CAMERA_DIRECTOR_H
#define CAMERA_DIRECTOR_H

#include "../base_load_director.h"
#include "../../loader/loader_solution.h"
#include "../../builder/builder_solution.h"
#include "../../loader/base_loader.h"
#include "../../builder/base_builder.h"
#include "../../config/config_solution.h"
#include "../../config/config.h"


class CameraDirector : public BaseLoadDirector
{
public:
    explicit CameraDirector(std::string name_arg);
    ~CameraDirector() override = default;

    std::shared_ptr<Object> create() override;
    void set_loader(std::shared_ptr<BaseLoader> loader_arg) override;
    void set_builder(std::shared_ptr<BaseBuilder> builder_arg) override;

private:
    std::string name{};

    std::shared_ptr<BaseLoader>  loader;
    std::shared_ptr<BaseBuilder> builder;
};


class CameraDirectorCreator
{
public:
    CameraDirectorCreator() = default;
    ~CameraDirectorCreator() = default;

    std::shared_ptr<CameraDirector> get_director(std::string name_arg);

private:
    void create_instance(std::string name_arg);
    std::shared_ptr<CameraDirector> director;
};


#endif // CAMERA_DIRECTOR_H
