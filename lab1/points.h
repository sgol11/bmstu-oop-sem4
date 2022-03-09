#ifndef POINTS_H
#define POINTS_H


#define _USE_MATH_DEFINES
#include <cmath>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "errors.h"


struct point
{
    double x;
    double y;
    double z;
};
using point_t = struct point;

struct points
{
    int size = 0;
    point_t *array = NULL;
};
using points_t = struct points;

struct change
{
    double chg_x;
    double chg_y;
    double chg_z;
};
using change_t = struct change;


void init_points(points_t &points);
void init_center(point_t &center);

err_t read_points(points_t &points, FILE *f);

err_t write_points(points_t &points, FILE *f);

err_t move_point(point_t &point, const change_t &move);
err_t scale_point(point_t &point, const point_t &center, const change_t &scale);
err_t rotate_point(point_t &point, const point_t &center, const change_t &rotate);

void free_points(points_t &points);


#endif // POINTS_H
