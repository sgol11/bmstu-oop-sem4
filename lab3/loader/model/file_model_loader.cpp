#include "file_model_loader.h"
#include "../../exceptions/loader_exceptions.h"

#include <iostream>


FileModelLoader::FileModelLoader(std::string &name)
{
    file = std::make_shared<std::ifstream>();
    filename = name;
}


void FileModelLoader::open()
{
    file->open(filename);
    if (!file)
    {
        time_t cur_time = time(NULL);
        throw NoFileException(__FILE__, __func__, __LINE__,
                              ctime(&cur_time));
    }
}

void FileModelLoader::close()
{
    if (!file)
    {
        time_t cur_time = time(NULL);
        throw NoFileException(__FILE__, __func__, __LINE__,
                              ctime(&cur_time));
    }
    file->close();
}

std::shared_ptr<Object> FileModelLoader::load(std::shared_ptr<BaseBuilder> src_builder)
{
    std::shared_ptr<BaseModelBuilder> builder = std::dynamic_pointer_cast<BaseModelBuilder>(src_builder);

    open();

    int points_count = read_count();

    for (int i = 0; i < points_count; i++)
        builder->build_point(read_point());

    int edges_count = read_count();

    for (int i = 0; i < edges_count; i++)
        builder->build_edge(read_edge());

    close();

    return builder->get();
}

int FileModelLoader::read_count()
{
    int count = 0;
    *file >> count;

    return count;
}

Point FileModelLoader::read_point()
{
    double x = 0, y = 0, z = 0;
    *file >> x >> y >> z;

    return Point{x, y, z};
}

Edge FileModelLoader::read_edge()
{
    size_t start_index = 0, end_index = 0;
    *file >> start_index >> end_index;

    return Edge{start_index, end_index};
}


std::shared_ptr<BaseLoader> FileModelLoaderCreator::create_loader(std::string &name)
{
    return std::make_shared<FileModelLoader>(name);
}
