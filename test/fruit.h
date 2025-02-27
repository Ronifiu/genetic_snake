#ifndef FRUIT_H
#define FRUIT_H

#include <raylib.h>
#include "snake.h"

class Fruit {
protected:
    void randomPosition(Snake &snake);
public:
    int col, row;
    bool eaten = false;

    void init(Snake &snake);
    void draw();
    void update(Snake &snake);
};

#endif