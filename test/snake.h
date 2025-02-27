#ifndef SNAKE_H
#define SNAKE_H

#include <raylib.h>

class Snake {
protected:
    void setDirection();
public:
    int col, row;
    int colSpeed, rowSpeed;
    int colNext, rowNext;
    int colPrev, rowPrev;
    int colTail, rowTail;
    int tailLength;
    int tailX[100], tailY[100];
    int orientation;

    void init();
    void update();
    void updateTail();
    bool isPositionOccupied(int x, int y);
    void draw();
};

#endif