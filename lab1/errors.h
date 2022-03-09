#ifndef ERRORS_H
#define ERRORS_H


#include <QMessageBox>


enum errors
{
    OK,
    ERR_OPEN_FILE,
    ERR_READ_DATA,
    ERR_POINTS_NUM,
    ERR_CONNECTIONS_NUM,
    ERR_ALLOCATE,
    ERR_NO_FIGURE,
    ERR_NO_SCENE,
    ERR_UNKNOWN
};
using err_t = enum errors;


void show_error(err_t err_code);


#endif // ERRORS_H
