#include "control_panel.h"
#include "../colors.h"


ControlPanel::ControlPanel(QObject *parent) : QObject(parent),
                                              cur_floor(START_FLOOR),
                                              target_floor(NO_TARGET),
                                              floors_to_visit(NUM_OF_FLOORS, false),
                                              state(FREE),
                                              direction(STAY)
{
    // Floor has been reached => performing all needed actions at the reached floor
    QObject::connect(this, SIGNAL(floor_reached()), this, SLOT(reach_floor()));
}


void ControlPanel::set_target_floor(int floor)
{
    if (floors_to_visit[floor - 1]) return;

    update_target(true, floor);
}

void ControlPanel::update_target(bool got_new, int floor)
{
    state = BUSY;

    if (got_new)
    {
        floors_to_visit[floor - 1] = true;

        find_new_target(floor);
        target_floor = floor;

        update_direction();

        if (direction == STAY)
            emit floor_reached();
        else
            emit move_cabin();
    }
    else if (find_new_target(floor))
    {
        // Pass the floors on the way to existing target
        // (other targets on this way will be visited)

        target_floor = floor;
        update_direction();

        if (direction == STAY)
            emit floor_reached();
        else
        {
            update_floor();
            if (direction == STAY)
                emit floor_reached();
            else
                emit move_cabin();
        }
    }
}

void ControlPanel::update_floor()
{
    cur_floor += direction;
    update_direction();

    if (direction != STAY)
        qDebug() << SET_COLOR YELLOW << "Elevator is coming (floor #" << cur_floor << ")"
                 << SET_COLOR BASE_COLOR;
}

void ControlPanel::update_direction()
{
    if (target_floor < cur_floor)
        direction = DOWN;
    else if (target_floor > cur_floor)
        direction = UP;
    else
        direction = STAY;
}

void ControlPanel::reach_floor()
{
    if (state != BUSY) return;

    state = FREE;

    qDebug() << SET_COLOR PURPURE << "Elevator has come! (floor #" << cur_floor << ")";

    floors_to_visit[target_floor - 1] = false;
    find_new_target(target_floor);

    emit stop_cabin();
}

int ControlPanel::find_new_target(int &new_target)
{
    bool rc = false;

    Direction dir = (direction != STAY) ? direction : DOWN;

    for (int i = cur_floor; !rc && i <= NUM_OF_FLOORS && i > 0; i += dir)
    {
        if (floors_to_visit[i - 1])
        {
            new_target = i;
            rc = true;
        }
    }

    if (!rc)
    {
        dir = (dir == UP) ? DOWN : UP;

        for (int i = cur_floor; !rc && i <= NUM_OF_FLOORS && i > 0; i += dir)
        {
            if (floors_to_visit[i - 1])
            {
                new_target = i;
                rc = true;
            }
        }
    }

    return rc;
}
