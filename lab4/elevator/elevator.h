#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>
#include <QTextEdit>

#include "cabin/cabin.h"
#include "controller/control_panel.h"


class Elevator : public QObject
{
    Q_OBJECT

public:
    Elevator();

    void button_click(const int button_number);

private:
    ControlPanel elevator_control;
    Cabin        elevator_cabin;
};


#endif // ELEVATOR_H
