#include "doors.h"
#include "../colors.h"

#include <QDebug>


Doors::Doors(QObject *parent) : QObject(parent), state(CLOSED)
{
    // Time of opening is over => finish doors opening
    QObject::connect(&opening_timer, SIGNAL(timeout()), this, SLOT(finish_doors_opening()));
    // Time of closing is over => finish doors closing
    QObject::connect(&closing_timer, SIGNAL(timeout()), this, SLOT(finish_doors_closing()));

    // Doors are opened => waiting time => doors are closing
    waiting_timer.setInterval(WAITING_DELAY);
    QObject::connect(this, SIGNAL(doors_opened()), &waiting_timer, SLOT(start()));
    QObject::connect(&waiting_timer, SIGNAL(timeout()), this, SLOT(doors_closing()));
}


void Doors::doors_opening()
{
    if (state != CLOSING && state != CLOSED) return;

    if (state == CLOSED)
    {
        opening_timer.start(OPENING_DELAY);
    }
    else if (state == CLOSING)
    {
        int remaining_time = closing_timer.remainingTime();
        closing_timer.stop();
        opening_timer.start(OPENING_DELAY - remaining_time);
    }

    state = OPENING;

    qDebug() << SET_COLOR GREEN << "Doors are opening..." << SET_COLOR BASE_COLOR;
}

void Doors::doors_closing()
{
    if (state != OPENED) return;

    state = CLOSING;

    closing_timer.start(CLOSING_DELAY);

    qDebug() << SET_COLOR RED << "Doors are closing..." << SET_COLOR BASE_COLOR;
}

void Doors::finish_doors_opening()
{
    if (state != OPENING) return;

    state = OPENED;

    qDebug() << SET_COLOR GREEN << "Doors are opened. Elevator is waiting for incoming and outcoming passengers"
             << SET_COLOR BASE_COLOR;

    emit doors_opened();
}

void Doors::finish_doors_closing()
{
    if (state != CLOSING) return;

    state = CLOSED;

    qDebug() << SET_COLOR RED << "Doors are closed" << SET_COLOR BASE_COLOR;

    emit doors_closed();
}
