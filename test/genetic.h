#ifndef GENETIC_H
#define GENETIC_H

#include <vector>
#include "neural.h"
#include "agent.h"

using namespace std;

class GeneticAlgorithm {
public:
    vector<NeuralNetwork> population;
    vector<Agent> agents;
    vector<double> fitness_scores;
    int population_size;

    
    GeneticAlgorithm(int pop_size, int input_size, int hidden_size, int output_size);

    void mutate(NeuralNetwork& nn, double mutation_rate);
    NeuralNetwork crossover(const NeuralNetwork& parent1, const NeuralNetwork& parent2);
    void evolve(vector<double> fitness_scores);
    void calculateFitness(vector<Agent>& agents);
};

#endif