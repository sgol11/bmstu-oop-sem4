#include "file_camera_loader.h"
#include "../../exceptions/loader_exceptions.h"

#include <iostream>


FileCameraLoader::FileCameraLoader(std::string &name)
{
    file = std::make_shared<std::ifstream>();
    filename = name;
}


void FileCameraLoader::open()
{
    file->open(filename);
    if (!file)
    {
        time_t cur_time = time(NULL);
        throw NoFileException(__FILE__, __func__, __LINE__,
                              ctime(&cur_time));
    }
}

void FileCameraLoader::close()
{
    if (!file)
    {
        time_t cur_time = time(NULL);
        throw NoFileException(__FILE__, __func__, __LINE__,
                              ctime(&cur_time));
    }
    file->close();
}

std::shared_ptr<Object> FileCameraLoader::load(std::shared_ptr<BaseBuilder> src_builder)
{
    std::shared_ptr<BaseCameraBuilder> builder = std::dynamic_pointer_cast<BaseCameraBuilder>(src_builder);

    open();

    builder->build_position(read_position());
    builder->build_direction(read_direction());

    close();

    return builder->get();
}

Point FileCameraLoader::read_position()
{
    double x = 0, y = 0, z = 0;
    *file >> x >> y >> z;

    return Point{x, y, z};
}

Point FileCameraLoader::read_direction()
{
    double ox = 0, oy = 0, oz = 0;
    *file >> ox >> oy >> oz;

    return Point{ox, oy, oz};
}


std::shared_ptr<BaseLoader> FileCameraLoaderCreator::create_loader(std::string &name)
{
    return std::make_shared<FileCameraLoader>(name);
}
