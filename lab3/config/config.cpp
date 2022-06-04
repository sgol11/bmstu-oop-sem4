#include "config.h"
#include "../exceptions/config_exceptions.h"


Config::Config()
{
    filename = CFG_FILE;
    file = std::make_shared<std::ifstream>();

    file->open(filename);

    if (!file)
    {
        time_t cur_time = time(NULL);
        throw NoFileException(__FILE__, __func__, __LINE__,
                              ctime(&cur_time));
    }
}

Config::~Config()
{
    file->close();
}


void Config::read_config_file()
{
    time_t cur_time = time(NULL);

    if (!std::getline(*file, gui_lib))
    {
        throw ReadException(__FILE__, __func__, __LINE__,
                            ctime(&cur_time));
    }

    if (!std::getline(*file, source))
    {
        throw ReadException(__FILE__, __func__, __LINE__,
                            ctime(&cur_time));
    }

    if (!std::getline(*file, model_type))
    {
        throw ReadException(__FILE__, __func__, __LINE__,
                            ctime(&cur_time));
    }
}

void Config::get_config_info()
{
    read_config_file();

    if (source == "textfile")
    {
        LoaderSolution().registrate("camera", std::make_shared<FileCameraLoaderCreator>());
        LoaderSolution().registrate("model", std::make_shared<FileModelLoaderCreator>());
    }

    if (model_type == "frame")
    {
        BuilderSolution().registrate("camera", std::make_shared<CameraBuilderCreator>());
        BuilderSolution().registrate("model", std::make_shared<ModelBuilderCreator>());
    }
}


ConfigCreator::ConfigCreator()
{
    filename = CFG_FILE;
}

std::shared_ptr<BaseConfig> ConfigCreator::create_config()
{
    config = std::make_shared<Config>();

    if (config == nullptr)
    {
        create_instance();
    }

    return config;
}

void ConfigCreator::create_instance()
{
    config = std::make_shared<Config>();
}
