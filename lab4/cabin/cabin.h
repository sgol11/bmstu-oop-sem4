#ifndef CABIN_H
#define CABIN_H

#include <QObject>

#include "../constants.h"
#include "../controller/control_panel.h"
#include "../door/doors.h"


class Cabin : public QObject
{
    Q_OBJECT

    enum CabinState
    {
        MOVING,
        STAYING,
        READY
    };

public:
    explicit Cabin(QObject *parent = nullptr);

private:
    CabinState state;
    Doors      doors;

    QTimer     move_timer;

signals:
    void open_doors();
    void cabin_reached_target(bool, int=1);

public slots:
    void cabin_move();                  // -> MOVING
    void cabin_stop();                  // -> STAYING
    void cabin_prepare();               // -> READY
};


#endif // CABIN_H
