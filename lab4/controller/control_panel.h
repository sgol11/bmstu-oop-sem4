#ifndef CONTROL_PANEL_H
#define CONTROL_PANEL_H

#include <QObject>
#include <QVector>

#include "../constants.h"


class ControlPanel : public QObject
{
    Q_OBJECT

    enum ControlPanelState
    {
        FREE,
        BUSY
    };

public:
    explicit ControlPanel(QObject *parent = nullptr);

    void set_target_floor(int floor);

private:
    int cur_floor;
    int target_floor;

    QVector<bool>     floors_to_visit;
    ControlPanelState state;
    Direction         direction;

    int  find_new_target(int &new_target);

    void update_direction();
    void update_floor();

signals:
    void move_cabin();
    void stop_cabin();
    void floor_reached();

public slots:
    void reach_floor();                                 // -> FREE
    void update_target(bool got_new, int floor = 1);    // -> BUSY
};


#endif // CONTROL_PANEL_H
