#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QTextEdit>
#include <QTimer>


enum Direction
{
    DOWN = -1,
    STAY = 0,
    UP = 1
};

#define NUM_OF_FLOORS           10
#define START_FLOOR             1

#define ONE_FLOOR_PASS_TIME     1500
#define WAITING_DELAY           2000
#define OPENING_DELAY           1500
#define CLOSING_DELAY           1500

#define NO_TARGET               (-1)


#endif // CONSTANTS_H
