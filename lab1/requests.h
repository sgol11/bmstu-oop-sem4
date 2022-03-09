#ifndef REQUESTS_H
#define REQUESTS_H

#include "figure.h"


enum actions
{
    LOAD,
    SAVE,
    DRAW,
    MOVE,
    SCALE,
    ROTATE,
    QUIT
};

struct request
{
    filename_t file_name;
    canvas_t canvas;
    change_t change;
};
using request_t = struct request;


err_t process_request(actions action, request_t request);


#endif // REQUESTS_H
