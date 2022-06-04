#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <fstream>
#include <iostream>

#include "base_config.h"
#include "../loader/loader_solution.h"
#include "../loader/camera/file_camera_loader.h"
#include "../loader/model/file_model_loader.h"
#include "../builder/model/model_builder.h"
#include "../builder/builder_solution.h"

#define CFG_FILE "C:\\Users\\Sonya\\Desktop\\OOP\\lab3\\lab3\\data\\config.txt"


class Config : public BaseConfig
{
public:
    Config();
    ~Config() override;

    virtual void get_config_info() override;

private:
    std::shared_ptr<std::ifstream> file;
    std::string filename;

    std::string gui_lib;
    std::string source;
    std::string model_type;

    void read_config_file();
};


class ConfigCreator : public BaseConfigCreator
{
public:
    explicit ConfigCreator();
    ~ConfigCreator() override = default;

    std::shared_ptr<BaseConfig> create_config() override;

private:
    void create_instance();
    std::shared_ptr<Config> config;
    std::string filename;
};


#endif // CONFIG_H
