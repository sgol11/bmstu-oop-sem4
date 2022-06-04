#ifndef FILE_MODEL_LOADER_H
#define FILE_MODEL_LOADER_H

#include <fstream>
#include "model_loader.h"
#include "../../builder/model/model_builder.h"


class FileModelLoader : public ModelLoader
{
public:
    FileModelLoader(std::string &name);
    ~FileModelLoader() override = default;

    void open() override;
    void close() override;

    std::shared_ptr<Object> load(std::shared_ptr<BaseBuilder> src_builder) override;

private:
    std::shared_ptr<std::ifstream> file;
    std::string filename;

    int read_count();
    Point read_point();
    Edge read_edge();
};


class FileModelLoaderCreator : public LoaderCreator
{
public:
    FileModelLoaderCreator() = default;
    ~FileModelLoaderCreator() override = default;

    std::shared_ptr<BaseLoader> create_loader(std::string &name) override;
};


#endif // FILE_MODEL_LOADER_H
