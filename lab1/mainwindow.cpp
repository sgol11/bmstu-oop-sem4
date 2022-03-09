#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    scene->setSceneRect(0, 0, SCENE_X, SCENE_Y);
}

MainWindow::~MainWindow()
{
    request_t request;
    err_t error_code = process_request(QUIT, request);

    if (error_code != OK)
    {
        show_error(error_code);
        return;
    }

    delete ui;
}

err_t MainWindow::drawing_settings(void)
{
    canvas_t canvas;

    canvas.scene = ui->graphicsView->scene();
    canvas.width = canvas.scene->width();
    canvas.height = canvas.scene->height();

    request_t request;

    request.canvas = canvas;

    err_t error_code = process_request(DRAW, request);

    return error_code;
}

void MainWindow::on_load_button_clicked(void)
{
    filename_t file = "C:/Users/Sonya/Desktop/OOP/lab1/test.txt";

    request_t request;

    request.file_name = file;

    err_t error_code = process_request(LOAD, request);

    if (error_code != OK)
    {
        show_error(error_code);
    }
    else
    {
        error_code = drawing_settings();

        if (error_code != OK)
        {
            show_error(error_code);
        }
    }
}

void MainWindow::on_save_button_clicked(void)
{
    filename_t file = "C:/Users/Sonya/Desktop/OOP/lab1/LastSavedState.txt";

    request_t request;

    request.file_name = file;

    err_t error_code = process_request(SAVE, request);

    if (error_code != OK)
    {
        show_error(error_code);
    }
    else
    {
        QMessageBox::information(NULL, "Информация",
                     "Текущее состояние модели сохранено в файл LastSavedState.txt");
    }
}

void MainWindow::on_move_button_clicked(void)
{
    change_t move_coeffs;

    move_coeffs.chg_x = ui->move_x->value();
    move_coeffs.chg_y = ui->move_y->value();
    move_coeffs.chg_z = ui->move_z->value();

    request_t request;

    request.change = move_coeffs;

    err_t error_code = process_request(MOVE, request);

    if (error_code != OK)
    {
        show_error(error_code);
    }
    else
    {
        error_code = drawing_settings();

        if (error_code != OK)
        {
            show_error(error_code);
        }
    }
}

void MainWindow::on_scale_button_clicked(void)
{
    change_t move_coeffs;

    move_coeffs.chg_x = ui->scale_x->value();
    move_coeffs.chg_y = ui->scale_y->value();
    move_coeffs.chg_z = ui->scale_z->value();

    request_t request;

    request.change = move_coeffs;

    err_t error_code = process_request(SCALE, request);

    if (error_code != OK)
    {
        show_error(error_code);
    }
    else
    {
        error_code = drawing_settings();

        if (error_code != OK)
        {
            show_error(error_code);
        }
    }
}

void MainWindow::on_rotate_button_clicked(void)
{
    change_t move_coeffs;

    move_coeffs.chg_x = ui->rotate_x->value();
    move_coeffs.chg_y = ui->rotate_y->value();
    move_coeffs.chg_z = ui->rotate_z->value();

    request_t request;

    request.change = move_coeffs;

    err_t error_code = process_request(ROTATE, request);

    if (error_code != OK)
    {
        show_error(error_code);
    }
    else
    {
        error_code = drawing_settings();

        if (error_code != OK)
        {
            show_error(error_code);
        }
    }
}
