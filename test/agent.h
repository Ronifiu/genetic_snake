#ifndef AGENT_H
#define AGENT_H

#include "neural.h"
#include "game.h"
#include "fruit.h"
#include "snake.h"

#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <cstdlib>
#include <raylib.h>


class Agent : public Snake {
public:
    NeuralNetwork nn;
    double fitness;
    int steps = 0;

    Agent(NeuralNetwork &nn);

    void update(Fruit &fruit);
    void draw();
    double calculateFitness();
};

#endif