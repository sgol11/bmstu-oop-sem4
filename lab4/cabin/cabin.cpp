#include "cabin.h"
#include "../colors.h"

#include <QString>
#include <QDebug>


Cabin::Cabin(QObject *parent) : QObject(parent), state(CabinState::READY)
{
    // Signal "Open doors" from cabin => doors are opening
    QObject::connect(this, SIGNAL(open_doors()), &doors, SLOT(doors_opening()));

    // Time of moving is over OR doors are closed => cabin is preparing (for next actions)
    QObject::connect(&move_timer, SIGNAL(timeout()), this, SLOT(cabin_prepare()));
    QObject::connect(&doors, SIGNAL(doors_closed()), this, SLOT(cabin_prepare()));
}


void Cabin::cabin_move()
{
    if (state != READY) return;

    state = MOVING;

    move_timer.start(ONE_FLOOR_PASS_TIME);
}

void Cabin::cabin_stop()
{
    state = STAYING;

    move_timer.stop();

    emit open_doors();
}

void Cabin::cabin_prepare()
{
    if (state == READY) return;

    state = READY;

    emit cabin_reached_target(false);
}
