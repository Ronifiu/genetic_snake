#include <raylib.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int GRID_ROWS = 15;
const int GRID_COLS = 20;

class Snake {
protected:
    void setDirection() {
        if (IsKeyPressed(KEY_RIGHT) && orientation != 2) orientation = 0;
        if (IsKeyPressed(KEY_DOWN) && orientation != 3) orientation = 1;
        if (IsKeyPressed(KEY_LEFT) && orientation != 0) orientation = 2;
        if (IsKeyPressed(KEY_UP) && orientation != 1) orientation = 3;
    }

public:
    int col, row;
    int colSpeed, rowSpeed;
    int colNext, rowNext;
    int colPrev, rowPrev;
    int colTail, rowTail;
    int tailLength;
    int tailX[100], tailY[100];
    int orientation;

    void init() {
        col = 0;
        row = 0;
        colSpeed = 0;
        rowSpeed = 0;
        orientation = 0;
        tailLength = 0;
    }

    void update() {
        setDirection();
        switch (orientation) {
            case 0: // right
                colSpeed = 1;
                rowSpeed = 0;
                break;
            case 1: // down
                colSpeed = 0;
                rowSpeed = 1;
                break;
            case 2: // left
                colSpeed = -1;
                rowSpeed = 0;
                break;
            case 3: // up
                colSpeed = 0;
                rowSpeed = -1;
                break;
        }
        colPrev = col;
        rowPrev = row;
        col += colSpeed;
        row += rowSpeed;
        colNext = col;
        rowNext = row;
    }
    void updateTail() {
        if (tailLength > 0) {
            colTail = tailX[tailLength - 1];
            rowTail = tailY[tailLength - 1];
            for (int i = tailLength - 1; i > 0; i--) {
                tailX[i] = tailX[i - 1];
                tailY[i] = tailY[i - 1];
            }
            tailX[0] = colPrev;
            tailY[0] = rowPrev;
        } else {
            colTail = colPrev;
            rowTail = rowPrev;
        }
    }
    bool isPositionOccupied(int x, int y) {
        if (col == x && row == y) return true;
        for (int i = 0; i < tailLength; i++) {
            if (tailX[i] == x && tailY[i] == y) return true;
        }
        return false;
    }

    void draw() {
        DrawRectangle(col*40, row*40, 40, 40, GREEN);
        for (int i = 0; i < tailLength; i++) {
            DrawRectangle(tailX[i]*40, tailY[i]*40, 40, 40, GREEN);
        }
    }
};

class Fruit {    
protected:
    void randomPosition(Snake &snake) {
        do {
            col = GetRandomValue(0, GRID_COLS - 1);
            row = GetRandomValue(0, GRID_ROWS - 1);
        } while (snake.isPositionOccupied(col, row));
    }

public:
    int col, row;
    bool eaten = false;

    void init(Snake &snake) {
        randomPosition(snake);
    }
    void draw() {
        DrawCircle(col*40+20, row*40+20, 10, RED);
    }
    void update(Snake &snake) {
        if (eaten) {
            randomPosition(snake);
            eaten = false;
        }
    }
};


class Game {
protected:
    void drawScore() {
        DrawText(TextFormat("%i", score), 10, 10, 20, WHITE);
    }
    void checkCollision(Snake &snake, Fruit &fruit) {
        if (snake.col == fruit.col && snake.row == fruit.row) {
            fruit.eaten = true;
            snake.tailLength++;
            score++;
        }
        for (int i = 0; i < snake.tailLength; i++) {
            if (snake.col == snake.tailX[i] && snake.row == snake.tailY[i]) {
                gameOver = true;
            }
        }
        if (snake.col >= GRID_COLS || snake.col < 0 || snake.row >= GRID_ROWS || snake.row < 0) {
            gameOver = true;
        }
    }
    
public:
    bool gameOver;
    int score;
    int cellWidth = SCREEN_WIDTH / GRID_COLS;
    int cellHeight = SCREEN_HEIGHT / GRID_ROWS;

    /*---Initialization---*/
    void init(Snake &snake, Fruit &fruit) {
        gameOver = false;
        score = 0;
        snake.init();
        fruit.init(snake);
    }

    /*---Updating---*/
    void update(Snake &snake, Fruit &fruit) {
        if (gameOver) {
            if (IsKeyPressed(KEY_ENTER)) {
                init(snake, fruit);
            }
            return;
        }
        snake.update();
        checkCollision(snake, fruit);
        snake.updateTail();
        fruit.update(snake);
        
    }
    /*---Drawing---*/
    void draw(Snake &snake, Fruit &fruit) {
        // Clear screen
        ClearBackground(BLACK);
        // Draw grid
        for (int i = 0; i <= GRID_ROWS; i++) {
            DrawLine(0, i * cellHeight, SCREEN_WIDTH, i * cellHeight, GRAY);
        }
        for (int i = 0; i <= GRID_COLS; i++) {
            DrawLine(i * cellWidth, 0, i * cellWidth, SCREEN_HEIGHT, GRAY);
        }
        fruit.draw();
        snake.draw();
        drawScore();

        if (gameOver) {
            DrawText("Game Over", 300, 200, 40, RED);
            DrawText("Press Enter to Restart", 250, 250, 20, RED);
        }
    }

};