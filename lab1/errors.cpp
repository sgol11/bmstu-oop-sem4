#include "errors.h"


void show_error(const err_t err_code)
{
    switch (err_code)
    {
        case ERR_OPEN_FILE:
            QMessageBox::critical(NULL, "Ошибка", "Ошибка при открытии файла");
            break;
        case ERR_READ_DATA:
            QMessageBox::critical(NULL, "Ошибка", "Ошибка при чтении данных из файла");
            break;
        case ERR_POINTS_NUM:
            QMessageBox::critical(NULL, "Ошибка", "Некорректный размер количества точек");
            break;
        case ERR_CONNECTIONS_NUM:
            QMessageBox::critical(NULL, "Ошибка", "Некорректный размер количества соединений");
            break;
        case ERR_ALLOCATE:
            QMessageBox::critical(NULL, "Ошибка", "Ошибка при выделении памяти");
            break;
        case ERR_NO_FIGURE:
            QMessageBox::critical(NULL, "Ошибка", "Фигура не задана");
            break;
        case ERR_NO_SCENE:
            QMessageBox::critical(NULL, "Ошибка", "Поле для отрисовки фигуры не задано");
            break;
        default:
            QMessageBox::critical(NULL, "Ошибка", "Некорректная команда");
    }
}
