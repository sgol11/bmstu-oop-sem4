#include "drawing.h"


static err_t find_points(point_t &p1, point_t &p2, const points_t &points, const connection_t &connection)
{
    err_t error_code = OK;

    if (points.array == NULL)
    {
        error_code = ERR_NO_FIGURE;
    }

    if (error_code == OK)
    {
        p1 = points.array[connection.point_1];
        p2 = points.array[connection.point_2];
    }

   return error_code;
}

static err_t center_points(point_t &p1, point_t &p2, const int width, const int height)
{
    err_t error_code = OK;

    p1.x += width / 2;
    p1.y += height / 2;
    p2.x += width / 2;
    p2.y += height / 2;

   return error_code;
}

static err_t qt_draw_line(const point_t &point_1, const point_t &point_2, const canvas_t &canvas)
{
    err_t error_code = OK;

    if (canvas.scene == NULL)
    {
        error_code = ERR_NO_SCENE;
    }

    if (error_code == OK)
    {
        canvas.scene->addLine(
            point_1.x,
            point_1.y,
            point_2.x,
            point_2.y,
            QPen(Qt::black, 2)
       );
    }

   return error_code;
}

static err_t draw_line(point_t &point_1, point_t &point_2, const canvas_t &canvas)
{
    err_t error_code = OK;

    if (canvas.scene == NULL)
    {
        error_code = ERR_NO_SCENE;
    }

    if (error_code == OK)
    {
        error_code = center_points(point_1, point_2, canvas.width, canvas.height);
    }

    if (error_code == OK)
    {
        qt_draw_line(point_1, point_2, canvas);
    }

   return error_code;
}

err_t draw_lines(const points_t &points, const connections_t &connections, const canvas_t &canvas)
{
    err_t error_code = OK;

    if (points.array == NULL || connections.array == NULL)
    {
        error_code = ERR_NO_FIGURE;
    }
    if (error_code == OK && canvas.scene == NULL)
    {
        error_code = ERR_NO_SCENE;
    }

    point_t p1, p2;

    for (int i = 0; error_code == OK && i < connections.size; i++)
    {
        error_code = find_points(p1, p2, points, connections.array[i]);

        if (error_code == OK)
        {
            error_code = draw_line(p1, p2, canvas);
        }
    }

    return error_code;
}
