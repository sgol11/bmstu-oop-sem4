#include "requests.h"


err_t process_request(const actions action, const request_t request)
{
    static figure_t figure = init_figure();

    err_t error_code = OK;

    switch (action)
    {
        case LOAD:
            error_code = load_figure(figure, request.file_name);
            break;
        case SAVE:
            error_code = save_figure(figure, request.file_name);
            break;
        case DRAW:
            error_code = draw_figure(figure, request.canvas);
            break;
        case MOVE:
            error_code = move_figure(figure, request.change);
            break;
        case SCALE:
            error_code = scale_figure(figure, request.change);
            break;
        case ROTATE:
            error_code = rotate_figure(figure, request.change);
            break;
        case QUIT:
            free_figure(figure);
            break;
        default:
            error_code = ERR_UNKNOWN;
    }

    return error_code;
}
