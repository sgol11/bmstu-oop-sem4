#ifndef FIGURE_H
#define FIGURE_H


#include "ui_mainwindow.h"
#include "errors.h"

#include "points.h"
#include "connections.h"
#include "drawing.h"


struct figure
{
    points_t points;
    connections_t connections;
    point_t center;
};
using figure_t = struct figure;

using filename_t = const char *;


figure_t &init_figure(void);

err_t load_figure(figure_t &figure, filename_t filename);

err_t save_figure(figure_t &figure, filename_t filename);

err_t draw_figure(const figure_t &figure, const canvas_t &canvas);

err_t move_figure(figure_t &figure, const change_t &move_coeffs);
err_t scale_figure(figure_t &figure, const change_t &scale_coeffs);
err_t rotate_figure(figure_t &figure, const change_t &rotate_coeffs);

void free_figure(figure_t &figure);


#endif // FIGURE_H
