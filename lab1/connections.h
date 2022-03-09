#ifndef CONNECTIONS_H
#define CONNECTIONS_H


#include <stdio.h>
#include <stdlib.h>

#include "ui_mainwindow.h"
#include "errors.h"


struct connection
{
    int point_1;
    int point_2;
};
using connection_t = struct connection;

struct connections
{
    int size = 0;
    connection_t *array = NULL;
};
using connections_t = struct connections;


void init_connections(connections_t &connections);

err_t read_connections(connections_t &connections, FILE *f);

err_t write_connections(connections_t &connections, FILE *f);

void free_connections(connections_t &connections);


#endif // CONNECTIONS_H
