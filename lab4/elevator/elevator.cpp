#include "elevator.h"


Elevator::Elevator()
{
    // Connect elevator moving and updating target
    QObject::connect(&elevator_cabin,   SIGNAL(cabin_reached_target(bool)),
                     &elevator_control, SLOT(update_target(bool)));

    // Signal "Move cabin" from controller => cabin starts moving
    QObject::connect(&elevator_control, SIGNAL(move_cabin()), &elevator_cabin, SLOT(cabin_move()));
    // Signal "Stop cabin" from controller => cabin stops
    QObject::connect(&elevator_control, SIGNAL(stop_cabin()), &elevator_cabin, SLOT(cabin_stop()));
}

void Elevator::button_click(const int button_number)
{
    elevator_control.set_target_floor(button_number);
}
