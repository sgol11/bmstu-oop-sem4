#include "connections.h"


void init_connections(connections_t &connections)
{
    connections.array = NULL;
    connections.size = 0;
}


static err_t read_connections_amount(int &amount, FILE *f)
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
    else if (error_code == OK && tmp_amount < 0)
    {
        error_code = ERR_CONNECTIONS_NUM;
    }
    else if (error_code == OK)
    {
        amount = tmp_amount;
    }

    return error_code;
}


static err_t read_one_connection(connection_t &connection, FILE *f)
{
    err_t error_code = OK;

    if (f == NULL)
    {
        error_code = ERR_OPEN_FILE;
    }

    int tmp_p1 = 0, tmp_p2 = 0;
    int args_num = 0;

    if (error_code == OK)
    {
        args_num = fscanf(f, "%d %d", &tmp_p1, &tmp_p2);
    }

    if (error_code == OK && args_num != 2)
    {
        error_code = ERR_READ_DATA;
    }
    else if (error_code == OK)
    {
        connection.point_1 = tmp_p1;
        connection.point_2 = tmp_p2;
    }

    return error_code;
}

static err_t read_all_connections(connections_t &connections, FILE *f)
{
    err_t error_code = OK;

    if (f == NULL)
    {
        error_code = ERR_OPEN_FILE;
    }

    for (int i = 0; error_code == OK && i < connections.size; i++)
    {
        error_code = read_one_connection(connections.array[i], f);
    }

    return error_code;
}


static err_t allocate_connections_arr(connections_t &connections)
{
    err_t error_code = OK;

    connection_t *tmp_array = (connection_t *)malloc(connections.size * sizeof(connection_t));

    if (tmp_array == NULL)
    {
        error_code = ERR_ALLOCATE;
    }

    if (error_code == OK)
    {
        connections.array = tmp_array;
    }

    return error_code;
}

void free_connections(connections_t &connections)
{
    if (connections.array != NULL)
    {
        free(connections.array);
        connections.size = 0;
    }
}


err_t read_connections(connections_t &connections, FILE *f)
{
    err_t error_code = OK;

    if (f == NULL)
    {
        error_code = ERR_OPEN_FILE;
    }

    if (error_code == OK)
    {
        error_code = read_connections_amount(connections.size, f);
    }
    if (error_code == OK)
    {
        error_code = allocate_connections_arr(connections);
    }
    if (error_code == OK)
    {
        error_code = read_all_connections(connections, f);

        if (error_code != OK)
        {
            free_connections(connections);
        }
    }

    return error_code;
}


err_t write_connections(connections_t &connections, FILE *f)
{
    err_t error_code = OK;

    if (f == NULL)
    {
        error_code = ERR_OPEN_FILE;
    }

    if (error_code == OK && connections.array == NULL)
    {
        error_code = ERR_NO_FIGURE;
    }

    if (error_code == OK)
    {
        fprintf(f, "%d\n", connections.size);
    }

    for (int i = 0; error_code == OK && i < connections.size; i++)
    {
        fprintf(f, "%d %d\n", connections.array[i].point_1, connections.array[i].point_2);
    }

    return error_code;
}
