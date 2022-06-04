#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <iostream>

#include "../facade/facade.h"
#include "../drawer/base_drawer.h"
#include "../drawer/abstract_drawer_factory.h"
#include "../drawer/qt_drawer.h"
#include "../drawer/qt_drawer_factory.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void on_loadModelButton_clicked();
    void on_deleteModelButton_clicked();
    void on_deleteAllModelsButton_clicked();
    void on_loadCameraButton_clicked();
    void on_addCameraButton_clicked();
    void on_deleteCameraButton_clicked();
    void on_moveModelButton_clicked();
    void on_scaleModelButton_clicked();
    void on_rotateModelButton_clicked();
    void on_moveCameraButton_clicked();
    void on_rotateCameraButton_clicked();
    void on_camerasList_currentIndexChanged(int index);
    void on_clearSceneButton_clicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void setup_scene();
    void update_scene();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<Facade>         facade;
    std::shared_ptr<QGraphicsScene> scene;
    std::shared_ptr<BaseDrawer>     drawer;

    size_t get_camera_count();
    size_t get_models_count();
};


#endif // MAINWINDOW_H
