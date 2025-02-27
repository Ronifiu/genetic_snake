#include "genetic_snake.h"
#include "game.h"
#include "neural.h"
#include "agent.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    NeuralNetwork nn(22, 16, 4);
    Agent agent(nn);
    Fruit fruit;
    Game game;
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        
        game.update(agent, fruit);
        game.draw(agent, fruit);
        
        EndDrawing();
    }

    CloseWindow();
    

    return 0;
}
