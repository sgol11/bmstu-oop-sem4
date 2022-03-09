#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "requests.h"

#define SCENE_X 779
#define SCENE_Y 628

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_load_button_clicked();
    void on_save_button_clicked();
    void on_move_button_clicked();
    void on_scale_button_clicked();
    void on_rotate_button_clicked();

    err_t drawing_settings(void);

private:
    Ui::MainWindow *ui;
};

#endif
