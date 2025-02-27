#include "agent.h"


using namespace std;

Agent::Agent(NeuralNetwork &nn) : nn(nn) {
    col = rand() % GRID_COLS;
    row = rand() % GRID_ROWS;
    colSpeed = 0;
    rowSpeed = 0;
    orientation = rand() % 4;
    tailLength = 0;
    fitness = 0.0;
}

void Agent::update(Fruit &fruit) {
    vector<double> inputs = {
    (col - fruit.col) / (double)GRID_COLS,
    (row - fruit.row) / (double)GRID_ROWS,
    (col - colPrev) / (double)GRID_COLS,
    (row - rowPrev) / (double)GRID_ROWS,
    (col - colNext) / (double)GRID_COLS,
    (row - rowNext) / (double)GRID_ROWS,
    (col - fruit.col) > 0 ? 1.0 : 0.0,
    (row - fruit.row) > 0 ? 1.0 : 0.0,
    (col - colPrev) > 0 ? 1.0 : 0.0,
    (row - rowPrev) > 0 ? 1.0 : 0.0,
    (col - colNext) > 0 ? 1.0 : 0.0,
    (row - rowNext) > 0 ? 1.0 : 0.0,
    (col - fruit.col) < 0 ? 1.0 : 0.0,
    (row - fruit.row) < 0 ? 1.0 : 0.0,
    (col - colPrev) < 0 ? 1.0 : 0.0,
    (row - rowPrev) < 0 ? 1.0 : 0.0,
    (col - colNext) < 0 ? 1.0 : 0.0,
    (row - rowNext) < 0 ? 1.0 : 0.0,
    orientation == 0 ? 1.0 : 0.0,
    orientation == 1 ? 1.0 : 0.0,
    orientation == 2 ? 1.0 : 0.0,
    orientation == 3 ? 1.0 : 0.0
};


    vector<double> outputs = nn.forward(inputs);
    if (outputs.empty()) return;  // Prevents undefined behavior

    int max_index = distance(outputs.begin(), max_element(outputs.begin(), outputs.end()));

    // Update orientation based on max_index
    switch (max_index) {
        case 0: if (orientation != 2) orientation = 0; break; // Right
        case 1: if (orientation != 3) orientation = 1; break; // Down
        case 2: if (orientation != 0) orientation = 2; break; // Left
        case 3: if (orientation != 1) orientation = 3; break; // Up
    }

    // Update movement speed based on new orientation
    switch (orientation) {
        case 0: colSpeed = 1; rowSpeed = 0; break;  // Right
        case 1: colSpeed = 0; rowSpeed = 1; break;  // Down
        case 2: colSpeed = -1; rowSpeed = 0; break; // Left
        case 3: colSpeed = 0; rowSpeed = -1; break; // Up
    }

    // Update previous position
    colPrev = col;
    rowPrev = row;

    // Move the agent
    col += colSpeed;
    row += rowSpeed;

    // Update next position
    colNext = col + colSpeed;
    rowNext = row + rowSpeed;

    steps++;
}

void Agent::draw() {
    DrawRectangle(col*40, row*40, 40, 40, BLUE);
    for (int i = 0; i < tailLength; i++) {
        DrawRectangle(tailX[i]*40, tailY[i]*40, 40, 40, BLUE);
    }
}

double Agent::calculateFitness() {
    return fitness = tailLength*10 + steps*0.1;
}




