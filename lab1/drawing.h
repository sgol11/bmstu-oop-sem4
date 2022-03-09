#ifndef DRAWING_H
#define DRAWING_H


#include "ui_mainwindow.h"
#include "points.h"
#include "connections.h"


struct canvas
{
    QGraphicsScene *scene;
    double width;
    double height;
};
using canvas_t = struct canvas;


err_t draw_lines(const points_t &points, const connections_t &connections, const canvas_t &canvas);


#endif // DRAWING_H
