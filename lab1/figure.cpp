#include "figure.h"


figure_t &init_figure(void)
{
    static figure_t figure;

    init_points(figure.points);
    init_center(figure.center);
    init_connections(figure.connections);

    return figure;
}

void free_figure(figure_t &figure)
{
    free_points(figure.points);
    free_connections(figure.connections);
}


static err_t figure_exists(const points_t &points, const connections_t &connections)
{
    err_t error_code = OK;

    if (points.array == NULL || connections.array == NULL)
    {
        error_code = ERR_NO_FIGURE;
    }

    return error_code;
}


static err_t read_figure(figure_t &tmp_figure, FILE *f)
{
    err_t error_code = OK;

    if (f == NULL)
    {
        error_code = ERR_OPEN_FILE;
    }

    if (error_code == OK)
    {
        error_code = read_points(tmp_figure.points, f);
    }
    if (error_code == OK)
    {
        error_code = read_connections(tmp_figure.connections, f);

        if (error_code != OK)
        {
            free_points(tmp_figure.points);
        }
    }

    return error_code;
}

err_t load_figure(figure_t &figure, filename_t filename)
{
    err_t error_code = OK;

    figure_t tmp_figure;

    FILE *f = fopen(filename, "r");

    if (f == NULL)
    {
        error_code = ERR_OPEN_FILE;
    }

    if (error_code == OK)
    {
        error_code = read_figure(tmp_figure, f);
        fclose(f);
    }

    if (error_code == OK)
    {
        free_figure(figure);
        figure = tmp_figure;
    }

    return error_code;
}


static err_t write_figure(figure_t &figure, FILE *f)
{
    err_t error_code = OK;

    if (f == NULL)
    {
        error_code = ERR_OPEN_FILE;
    }

    if (error_code == OK)
    {
        error_code = write_points(figure.points, f);
    }
    if (error_code == OK)
    {
        error_code = write_connections(figure.connections, f);
    }

    return error_code;
}

err_t save_figure(figure_t &figure, filename_t filename)
{
    err_t error_code = OK;

    FILE *f = fopen(filename, "w");

    if (f == NULL)
    {
        error_code = ERR_OPEN_FILE;
    }

    if (error_code == OK)
    {
        error_code = write_figure(figure, f);
        fclose(f);
    }

    return error_code;
}


err_t draw_figure(const figure_t &figure, const canvas_t &canvas)
{
    err_t error_code = OK;

    error_code = figure_exists(figure.points, figure.connections);

    if (error_code == OK && canvas.scene == NULL)
    {
        error_code = ERR_NO_SCENE;
    }

    if (error_code == OK)
    {
        canvas.scene->clear();
        error_code = draw_lines(figure.points, figure.connections, canvas);
    }

    return error_code;
}


static err_t move_figure_points(points_t &points, point_t &center, const change_t &move_coeffs)
{
    err_t error_code = OK;

    if (points.array == NULL)
    {
        error_code = ERR_NO_FIGURE;
    }

    for (int i = 0; error_code == OK && i < points.size && error_code == OK; i++)
    {
        error_code = move_point(points.array[i], move_coeffs);
    }

    if (error_code == OK)
    {
        error_code = move_point(center, move_coeffs);
    }

    return error_code;
}

err_t move_figure(figure_t &figure, const change_t &move_coeffs)
{
    err_t error_code = OK;

    error_code = figure_exists(figure.points, figure.connections);

    if (error_code == OK)
    {
        error_code = move_figure_points(figure.points, figure.center, move_coeffs);
    }

    return error_code;
}


static err_t scale_figure_points(points_t &points, const point_t center, const change_t &scale_coeffs)
{
    err_t error_code = OK;

    if (points.array == NULL)
    {
        error_code = ERR_NO_FIGURE;
    }

    for (int i = 0; error_code == OK && i < points.size; i++)
    {
        error_code = scale_point(points.array[i], center, scale_coeffs);
    }

    return error_code;
}

err_t scale_figure(figure_t &figure, const change_t &scale_coeffs)
{
    err_t error_code = OK;

    error_code = figure_exists(figure.points, figure.connections);

    if (error_code == OK)
    {
        error_code = scale_figure_points(figure.points, figure.center, scale_coeffs);
    }

    return error_code;
}


static err_t rotate_figure_points(points_t &points, const point_t center, const change_t &rotate_coeffs)
{
    err_t error_code = OK;

    if (points.array == NULL)
    {
        error_code = ERR_NO_FIGURE;
    }

    for (int i = 0; error_code == OK && i < points.size; i++)
    {
        error_code = rotate_point(points.array[i], center, rotate_coeffs);
    }

    return error_code;
}

err_t rotate_figure(figure_t &figure, const change_t &rotate_coeffs)
{
    err_t error_code = OK;

    error_code = figure_exists(figure.points, figure.connections);

    if (error_code == OK)
    {
        error_code = rotate_figure_points(figure.points, figure.center, rotate_coeffs);
    }

    return error_code;
}
