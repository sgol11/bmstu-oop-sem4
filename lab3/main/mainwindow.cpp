#include <QFileDialog>
#include <QMessageBox>

#include <string>
#include <vector>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../objects/model/model_structure.h"
#include "../objects/model/frame_model.h"
#include "../commands/model/model_commands.h"
#include "../commands/scene/scene_commands.h"
#include "../commands/camera/camera_commands.h"
#include "../config/config_solution.h"
#include "../config/config.h"
#include "../exceptions/gui_exceptions.h"
#include "../managers/scene/scene_manager.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setup_scene();

    facade = std::make_unique<Facade>();
}

MainWindow::~MainWindow()
{
    delete ui;
}


size_t MainWindow::get_camera_count()
{
    std::shared_ptr<size_t> res = std::make_shared<size_t>();

    std::shared_ptr<BaseCommand<SceneManager>> cmd =
            std::make_shared<CountCameraCommand<SceneManager>>(&SceneManager::count_camera, res);

    facade->execute(cmd);

    return *res;
}

size_t MainWindow::get_models_count()
{
    std::shared_ptr<size_t> res = std::make_shared<size_t>();

    std::shared_ptr<BaseCommand<SceneManager>> cmd =
            std::make_shared<CountModelCommand<SceneManager>>(&SceneManager::count_model, res);

    facade->execute(cmd);

    return *res;
}


void MainWindow::setup_scene()
{
    scene = std::make_shared<QGraphicsScene>(this);
    ui->graphicsView->setScene(scene.get());
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    scene->setSceneRect(-(ui->graphicsView->width()) / 2, -(ui->graphicsView->height()) / 2,
                          ui->graphicsView->width() / 2, ui->graphicsView->height() / 2);

    std::unique_ptr<AbstractDrawerFactory> factory = std::make_unique<QtDrawerFactory>(scene);
    drawer = factory->create_graphics();
}


void MainWindow::update_scene()
{
    std::shared_ptr<BaseCommand<DrawManager>> cmd =
            std::make_shared<DrawSceneCommand<DrawManager>>(&DrawManager::draw, drawer);

    facade->execute(cmd);
}


void MainWindow::on_loadModelButton_clicked()
{
    if (get_camera_count() < 1)
    {
        QMessageBox::critical(nullptr, "Error", "No cameras added");
        return;
    }

    auto Qfile = QFileDialog::getOpenFileName();
    auto file = Qfile.toStdString();

    std::shared_ptr<BaseCommand<LoadManager>> cmd =
            std::make_shared<LoadModelCommand<LoadManager>>(&LoadManager::load_model, file);

    facade->execute(cmd);

    ui->modelsList->addItem(QFileInfo(Qfile.toUtf8().data()).fileName());
    ui->modelsList->setCurrentIndex(ui->modelsList->count() - 1);

    update_scene();
}

void MainWindow::on_deleteModelButton_clicked()
{
    if (get_camera_count() < 1)
    {
        QMessageBox::critical(nullptr, "Error", "No models to delete");
        return;
    }

    size_t id = ui->modelsList->currentIndex();

    std::shared_ptr<BaseCommand<SceneManager>> cmd =
            std::make_shared<RemoveModelCommand<SceneManager>>(&SceneManager::remove_object, id);

    facade->execute(cmd);

    ui->modelsList->removeItem(ui->modelsList->currentIndex());
    ui->modelsList->setCurrentIndex(ui->modelsList->count() - 1);

    update_scene();
}

void MainWindow::on_deleteAllModelsButton_clicked()
{
    if (get_camera_count() < 1)
    {
        QMessageBox::critical(nullptr, "Error", "No models to delete");
        return;
    }

    int max_ind = ui->modelsList->count() - 1;

    for (int i = 0; i <= max_ind; i++)
    {
        size_t id = 0;

        std::shared_ptr<BaseCommand<SceneManager>> cmd =
                std::make_shared<RemoveModelCommand<SceneManager>>(&SceneManager::remove_object, id);

        facade->execute(cmd);

        ui->modelsList->removeItem(ui->modelsList->currentIndex());
    }

    ui->modelsList->setCurrentIndex(ui->modelsList->count() - 1);

    update_scene();
}


void MainWindow::on_loadCameraButton_clicked()
{
    auto Qfile = QFileDialog::getOpenFileName();
    auto file = Qfile.toStdString();

    std::shared_ptr<BaseCommand<LoadManager>> load_cmd =
            std::make_shared<LoadCameraCommand<LoadManager>>(&LoadManager::load_camera, file);

    facade->execute(load_cmd);

    ui->camerasList->addItem(QFileInfo(Qfile.toUtf8().data()).fileName());
    ui->camerasList->setCurrentIndex(ui->camerasList->count() - 1);

    size_t id = ui->modelsList->count() + ui->camerasList->currentIndex();

    std::shared_ptr<BaseCommand<SceneManager>> set_cmd =
            std::make_shared<SetCameraCommand<SceneManager>>(&SceneManager::set_camera, id);

    facade->execute(set_cmd);

    update_scene();
}

void MainWindow::on_addCameraButton_clicked()
{
    double x = ui->xCameraInput->value();
    double y = ui->yCameraInput->value();

    double ox = ui->oxCameraInput_2->value();
    double oy = ui->oyCameraInput_2->value();
    double oz = ui->ozCameraInput_2->value();

    Point position{x, y, 0};
    Point direction{ox, oy, oz};

    std::shared_ptr<BaseCommand<SceneManager>> add_cmd =
            std::make_shared<AddCameraCommand<SceneManager>>(&SceneManager::add_camera,
                                                             position, direction);

    facade->execute(add_cmd);

    size_t id = 0;

    std::shared_ptr<BaseCommand<SceneManager>> set_cmd =
            std::make_shared<SetCameraCommand<SceneManager>>(&SceneManager::set_camera, id);

    facade->execute(set_cmd);

    update_scene();

    ui->camerasList->addItem("Camera");
    ui->camerasList->setCurrentIndex(ui->camerasList->count() - 1);
}

void MainWindow::on_deleteCameraButton_clicked()
{
    if (get_camera_count() < 1)
    {
        QMessageBox::critical(nullptr, "Error", "No cameras to delete");
        return;
    }

    if (get_models_count() > 1 && this->get_camera_count() == 1)
    {
        QMessageBox::critical(nullptr, "Error!", "Cannot delete the last camera before all models are deleted");
        return;
    }

    size_t id = ui->modelsList->count() + ui->modelsList->currentIndex();

    std::shared_ptr<BaseCommand<SceneManager>> cmd =
            std::make_shared<RemoveCameraCommand<SceneManager>>(&SceneManager::remove_object, id);

    facade->execute(cmd);

    ui->camerasList->removeItem(ui->modelsList->count() + ui->camerasList->currentIndex());
    ui->camerasList->setCurrentIndex(ui->camerasList->count() - 1);

    update_scene();
}


void MainWindow::on_moveModelButton_clicked()
{
    if (get_camera_count() < 1)
    {
        QMessageBox::critical(nullptr, "Error", "No cameras");
        return;
    }

    if (get_models_count() < 1)
    {
        QMessageBox::critical(nullptr, "Error", "No models");
        return;
    }

    double dx = ui->dxModelInput->value();
    double dy = ui->dyModelInput->value();
    double dz = ui->dzModelInput->value();

    size_t id = ui->modelsList->currentIndex();

    std::shared_ptr<BaseCommand<TransformManager>> cmd =
            std::make_shared<MoveModelCommand<TransformManager>>(&TransformManager::transform, id, dx, dy, dz);

    facade->execute(cmd);

    update_scene();
}

void MainWindow::on_scaleModelButton_clicked()
{
    if (get_camera_count() < 1)
    {
        QMessageBox::critical(nullptr, "Error", "No cameras");
        return;
    }

    if (get_models_count() < 1)
    {
        QMessageBox::critical(nullptr, "Error", "No models");
        return;
    }

    double kx = ui->kxModelInput->value();
    double ky = ui->kyModelInput->value();
    double kz = ui->kzModelInput->value();

    size_t id = ui->modelsList->currentIndex();

    std::shared_ptr<BaseCommand<TransformManager>> cmd =
            std::make_shared<ScaleModelCommand<TransformManager>>(&TransformManager::transform, id, kx, ky, kz);

    facade->execute(cmd);

    update_scene();
}

void MainWindow::on_rotateModelButton_clicked()
{
    if (get_camera_count() < 1)
    {
        QMessageBox::critical(nullptr, "Error", "No cameras");
        return;
    }

    if (get_models_count() < 1)
    {
        QMessageBox::critical(nullptr, "Error", "No models");
        return;
    }

    double ox = ui->oxModelInput->value();
    double oy = ui->oyModelInput->value();
    double oz = ui->ozModelInput->value();

    int id = ui->modelsList->currentIndex();

    std::shared_ptr<BaseCommand<TransformManager>> cmd =
            std::make_shared<RotateModelCommand<TransformManager>>(&TransformManager::transform, id, ox, oy, oz);

    facade->execute(cmd);

    update_scene();
}


void MainWindow::on_moveCameraButton_clicked()
{
    if (get_camera_count() < 1)
    {
        QMessageBox::critical(nullptr, "Error", "No cameras");
        return;
    }

    if (get_models_count() < 1)
    {
        QMessageBox::critical(nullptr, "Error", "No models");
        return;
    }

    double dx = ui->dxCameraInput->value();
    double dy = ui->dyCameraInput->value();

    Point move_params{dx, dy, 0};
    Point scale_params{1, 1, 1};
    Point rotate_params{0, 0, 0};

    size_t id = ui->modelsList->count() + ui->camerasList->currentIndex();

    std::shared_ptr<BaseCommand<SceneManager>> set_cmd =
            std::make_shared<SetCameraCommand<SceneManager>>(&SceneManager::set_camera, id);

    facade->execute(set_cmd);

    std::shared_ptr<BaseCommand<TransformManager>> cmd =
            std::make_shared<MoveCameraCommand<TransformManager>>(&TransformManager::transform, id,
                                                                  move_params, scale_params, rotate_params);

    facade->execute(cmd);

    update_scene();
}

void MainWindow::on_rotateCameraButton_clicked()
{
    if (get_camera_count() < 1)
    {
        QMessageBox::critical(nullptr, "Error", "No cameras");
        return;
    }

    if (get_models_count() < 1)
    {
        QMessageBox::critical(nullptr, "Error", "No models");
        return;
    }

    double ox = ui->oxCameraInput->value();
    double oy = ui->oyCameraInput->value();
    double oz = ui->ozCameraInput->value();

    Point move_params{0, 0, 0};
    Point scale_params{1, 1, 1};
    Point rotate_params{ox, oy, oz};

    size_t id = ui->modelsList->count() + ui->camerasList->currentIndex();

    std::shared_ptr<BaseCommand<SceneManager>> set_cmd =
            std::make_shared<SetCameraCommand<SceneManager>>(&SceneManager::set_camera, id);

    facade->execute(set_cmd);

    std::shared_ptr<BaseCommand<TransformManager>> cmd =
            std::make_shared<MoveCameraCommand<TransformManager>>(&TransformManager::transform, id,
                                                                  move_params, scale_params, rotate_params);

    facade->execute(cmd);

    update_scene();
}


void MainWindow::on_camerasList_currentIndexChanged(int index)
{
    size_t id =  ui->modelsList->count() + index;

    std::shared_ptr<BaseCommand<SceneManager>> set_cmd =
            std::make_shared<SetCameraCommand<SceneManager>>(&SceneManager::set_camera, id);

    facade->execute(set_cmd);

    update_scene();
}


void MainWindow::on_clearSceneButton_clicked() {
    int max_ind = ui->modelsList->count() - 1;

    for (int i = 0; i <= max_ind; i++)
    {
        size_t id = 0;

        std::shared_ptr<BaseCommand<SceneManager>> cmd =
                std::make_shared<RemoveModelCommand<SceneManager>>(&SceneManager::remove_object, id);

        facade->execute(cmd);

        ui->modelsList->removeItem(ui->modelsList->currentIndex());
    }

    ui->modelsList->setCurrentIndex(ui->modelsList->count() - 1);

    update_scene();
}
