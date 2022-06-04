#ifndef DOORS_H
#define DOORS_H

#include <QObject>
#include "../constants.h"


class Doors : public QObject
{
    Q_OBJECT

    enum DoorsState
    {
        OPENING,
        OPENED,
        CLOSING,
        CLOSED
    };

public:
    explicit Doors(QObject *parent = nullptr);

private:
    DoorsState state;

    QTimer     opening_timer;
    QTimer     closing_timer;
    QTimer     waiting_timer;

signals:
    void doors_opened();
    void doors_closed();

public slots:
    void doors_opening();           // -> OPENING
    void doors_closing();           // -> CLOSING
    void finish_doors_opening();    // -> OPENED
    void finish_doors_closing();    // -> CLOSED
};


#endif // DOORS_H
