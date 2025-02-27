#include <iostream>
#include <raylib.h>
#include "neural.cpp"
#include "genetic.cpp"
#include "game.cpp"

using namespace std;


Game game;
Fruit fruit;
Snake snake;
NeuralNetwork nn(24, 16, 4);


int main(void) {


    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game"); // create window
    SetTargetFPS(10); // setting fps 



    game.init(snake, fruit);

    /*---game loop---*/
    while(!WindowShouldClose()) {
        BeginDrawing();

        game.update(snake, fruit);
        game.draw(snake, fruit);

        EndDrawing();
    }

    CloseWindow(); // close game

    return 0;
}