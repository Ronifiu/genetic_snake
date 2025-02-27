#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include "snake.h"
#include "fruit.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int GRID_ROWS = 15;
const int GRID_COLS = 20;

class Game {
protected:
    void drawScore();
    void checkCollision(Snake &snake, Fruit &fruit);
    void updateState(Snake &snake, Fruit &fruit);
public:
    bool gameOver;
    int score;
    int cellWidth = SCREEN_WIDTH / GRID_COLS;
    int cellHeight = SCREEN_HEIGHT / GRID_ROWS;
    int state[GRID_ROWS][GRID_COLS];

    void init(Snake &snake, Fruit &fruit);
    void update(Snake &snake, Fruit &fruit);
    void draw(Snake &snake, Fruit &fruit);
};

#endif