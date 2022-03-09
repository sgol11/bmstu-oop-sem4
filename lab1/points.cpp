#include "points.h"


void init_points(points_t &points)
{
    points.array = NULL;
    points.size = 0;
}

void init_center(point_t &center)
{
    center.x = 0;
    center.y = 0;
    center.z = 0;
}


static err_t read_points_amount(int &amount, FILE *f)
{
    err_t error_code = OK;

    if (f == NULL)
    {
        error_code = ERR_OPEN_FILE;
    }

    int tmp_amount = 0;
    int args_num = 0;

    if (error_code == OK)
    {
        args_num = fscanf(f, "%d", &tmp_amount);
    }

    if (error_code == OK && args_num != 1)
    {
        error_code = ERR_READ_DATA;
    }
    if (error_code == OK && tmp_amount < 1)
    {
        error_code = ERR_POINTS_NUM;
    }
    else if (error_code == OK)
    {
        amount = tmp_amount;
    }

    return error_code;
}


static err_t read_one_point(point_t &point, FILE *f)
{
    err_t error_code = OK;

    if (f == NULL)
    {
        error_code = ERR_OPEN_FILE;
    }

    double tmp_x = 0, tmp_y = 0, tmp_z = 0;
    int args_num = 0;

    if (error_code == OK)
    {
        args_num = fscanf(f, "%lf %lf %lf", &tmp_x, &tmp_y, &tmp_z);
    }

    if (error_code == OK && args_num != 3)
    {
        error_code = ERR_READ_DATA;
    }
    else if (error_code == OK)
    {
        point.x = tmp_x;
        point.y = tmp_y;
        point.z = tmp_z;
    }

    return error_code;
}

static err_t read_all_points(points_t &points, FILE *f)
{
    err_t error_code = OK;

    if (f == NULL)
    {
        error_code = ERR_OPEN_FILE;
    }

    for (int i = 0; error_code == OK && i < points.size; i++)
    {
        error_code = read_one_point(points.array[i], f);
    }

    return error_code;
}


static err_t allocate_points_arr(points_t &points)
{
    err_t error_code = OK;

    point_t *tmp_array = (point_t *)malloc(points.size * sizeof(point_t));

    if (tmp_array == NULL)
    {
        error_code = ERR_ALLOCATE;
    }

    if (error_code == OK)
    {
        points.array = tmp_array;
    }

    return error_code;
}

void free_points(points_t &points)
{
    if (points.array != NULL)
    {
        free(points.array);
        points.size = 0;
    }
}


err_t read_points(points_t &points, FILE *f)
{
    err_t error_code = OK;

    if (f == NULL)
    {
        error_code = ERR_OPEN_FILE;
    }

    if (error_code == OK)
    {
        error_code = read_points_amount(points.size, f);
    }
    if (error_code == OK)
    {
        error_code = allocate_points_arr(points);
    }
    if (error_code == OK)
    {
        error_code = read_all_points(points, f);

        if (error_code != OK)
        {
            free_points(points);
        }
    }

    return error_code;
}


err_t write_points(points_t &points, FILE *f)
{
    err_t error_code = OK;

    if (f == NULL)
    {
        error_code = ERR_OPEN_FILE;
    }

    if (error_code == OK && points.array == NULL)
    {
        error_code = ERR_NO_FIGURE;
    }

    if (error_code == OK)
    {
        fprintf(f, "%d\n", points.size);
    }

    for (int i = 0; error_code == OK && i < points.size; i++)
    {
        fprintf(f, "%lf %lf %lf\n", points.array[i].x, points.array[i].y, points.array[i].z);
    }

    return error_code;
}


err_t move_point(point_t &point, const change_t &move)
{
    err_t error_code = OK;

    point.x += move.chg_x;
    point.y += move.chg_y;
    point.z += move.chg_z;

    return error_code;
}


err_t scale_point(point_t &point, const point_t &center, const change_t &scale)
{
    err_t error_code = OK;

    point.x = point.x * scale.chg_x + (1 - scale.chg_x) * center.x;
    point.y = point.y * scale.chg_y + (1 - scale.chg_y) * center.y;
    point.z = point.z * scale.chg_z + (1 - scale.chg_z) * center.z;

    return error_code;
}


double trigonometric_func(double (*func)(double), const double angle_deg)
{
    double angle_rad = angle_deg * M_PI / 180;

    return (*func)(angle_rad);
}

static err_t rotate_x(point_t &point, const point_t &center, const double &angle)
{
    err_t error_code = OK;

    double buf_y = point.y;
    double cos_rad = trigonometric_func(cos, angle);
    double sin_rad = trigonometric_func(sin, angle);

    point.y = center.y + (point.y - center.y) * cos_rad +
              (point.z - center.z) * sin_rad;
    point.z = center.z + (point.z - center.z) * cos_rad -
              (buf_y - center.y) * sin_rad;

    return error_code;
}

static err_t rotate_y(point_t &point, const point_t &center, const double &angle)
{
    err_t error_code = OK;

    double buf_x = point.x;
    double cos_rad = trigonometric_func(cos, angle);
    double sin_rad = trigonometric_func(sin, angle);

    point.x = center.x + (point.x - center.x) * cos_rad +
              (point.z - center.z) * sin_rad;
    point.z = center.z + (point.z - center.z) * cos_rad -
              (buf_x - center.x) * sin_rad;

    return error_code;
}

static err_t rotate_z(point_t &point, const point_t &center, const double &angle)
{
    err_t error_code = OK;

    double buf_x = point.x;
    double cos_rad = trigonometric_func(cos, angle);
    double sin_rad = trigonometric_func(sin, angle);

    point.x = center.x + (point.x - center.x) * cos_rad +
              (point.y - center.y) * sin_rad;
    point.y = center.y + (point.y - center.y) * cos_rad -
              (buf_x - center.x) * sin_rad;

    return error_code;
}

err_t rotate_point(point_t &point, const point_t &center, const change_t &rotate)
{
    err_t error_code = OK;

    error_code = rotate_x(point, center, rotate.chg_x);

    if (error_code == OK)
    {
        error_code = rotate_y(point, center, rotate.chg_y);
    }

    if (error_code == OK)
    {
        error_code = rotate_z(point, center, rotate.chg_z);
    }

    return error_code;
}
