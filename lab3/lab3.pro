QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    builder/builder_solution.cpp \
    builder/camera/camera_builder.cpp \
    builder/model/model_builder.cpp \
    config/config.cpp \
    config/config_solution.cpp \
    director/camera/camera_director.cpp \
    director/model/model_director.cpp \
    drawer/qt_drawer.cpp \
    drawer/qt_drawer_factory.cpp \
    facade/facade.cpp \
    loader/camera/file_camera_loader.cpp \
    loader/loader_solution.cpp \
    loader/model/file_model_loader.cpp \
    main/main.cpp \
    main/mainwindow.cpp \
    managers/base_manager.cpp \
    managers/draw/draw_manager.cpp \
    managers/load/load_manager.cpp \
    managers/scene/scene_manager.cpp \
    managers/transform/transform_manager.cpp \
    objects/camera/camera.cpp \
    objects/camera/camera_structure.cpp \
    objects/composite/composite.cpp \
    objects/model/frame_model.cpp \
    objects/model/model_structure.cpp \
    objects/primitives/edge.cpp \
    objects/primitives/point.cpp \
    scene/scene.cpp \
    visitor/draw_visitor.cpp

HEADERS += \
    builder/base_builder.h \
    builder/builder_solution.h \
    builder/camera/base_camera_builder.h \
    builder/camera/camera_builder.h \
    builder/model/base_model_builder.h \
    builder/model/model_builder.h \
    commands/base_command.h \
    commands/camera/camera_commands.h \
    commands/model/model_commands.h \
    commands/scene/scene_commands.h \
    config/base_config.h \
    config/config.h \
    config/config_solution.h \
    director/base_load_director.h \
    director/camera/camera_director.h \
    director/model/model_director.h \
    drawer/abstract_drawer_factory.h \
    drawer/base_drawer.h \
    drawer/qt_drawer.h \
    drawer/qt_drawer_factory.h \
    exceptions/base_exception.h \
    exceptions/builder_exceptions.h \
    exceptions/config_exceptions.h \
    exceptions/director_exceptions.h \
    exceptions/gui_exceptions.h \
    exceptions/loader_exceptions.h \
    exceptions/manager_exceptions.h \
    facade/facade.h \
    loader/base_loader.h \
    loader/camera/camera_loader.h \
    loader/camera/file_camera_loader.h \
    loader/camera/file_camera_loader.h \
    loader/camera/model_loader.h \
    loader/loader_solution.h \
    loader/model/file_model_loader.h \
    loader/model/file_model_loader.h \
    loader/model/model_loader.h \
    loader/model/model_loader.h \
    main/mainwindow.h \
    managers/base_manager.h \
    managers/draw/draw_manager.h \
    managers/load/load_manager.h \
    managers/scene/scene_manager.h \
    managers/transform/transform_manager.h \
    objects/camera/base_camera.h \
    objects/camera/camera.h \
    objects/camera/camera_structure.h \
    objects/composite/composite.h \
    objects/model/frame_model.h \
    objects/model/model.h \
    objects/model/model_structure.h \
    objects/object.h \
    objects/primitives/edge.h \
    objects/primitives/point.h \
    scene/scene.h \
    visitor/draw_visitor.h \
    visitor/visitor.h

FORMS += \
    main/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
