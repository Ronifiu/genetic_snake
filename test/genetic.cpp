#include "genetic_snake.h"

using namespace std;

GeneticAlgorithm::GeneticAlgorithm(int pop_size, int input_size, int hidden_size, int output_size) : population_size(pop_size) {
    for (int i = 0; i < pop_size; i++) {
        population.push_back(NeuralNetwork(input_size, hidden_size, output_size));
    }
    for (int i = 0; i < pop_size; i++) {
        agents.push_back(Agent(population[i]));
    }
    for (int i = 0; i < pop_size; i++) {
        fitness_scores.push_back(0.0);
    }
}

void GeneticAlgorithm::mutate(NeuralNetwork& nn, double mutation_rate) {
    for (auto& layer : { &nn.input_to_hidden, &nn.hidden_to_output }) {
        for (auto& row : *layer) {
            for (auto& weight : row) {
                if ((rand() % 1000) / 1000.0 < mutation_rate) {
                    weight += ((rand() % 2000) / 1000.0 - 1.0) * 0.1;
                }
            }
        }
    }
}

NeuralNetwork GeneticAlgorithm::crossover(const NeuralNetwork& parent1, const NeuralNetwork& parent2) {
    NeuralNetwork child(parent1.input_to_hidden.size(), parent1.hidden_to_output.size(), parent2.hidden_to_output[0].size());
    for (size_t i = 0; i < parent1.input_to_hidden.size(); i++) {
        for (size_t j = 0; j < parent1.input_to_hidden[0].size(); j++) {
            child.input_to_hidden[i][j] = (rand() % 2 == 0) ? parent1.input_to_hidden[i][j] : parent2.input_to_hidden[i][j];
        }
    }
    return child;
}

void GeneticAlgorithm::calculateFitness(vector<Agent>& agents) {
    int i = 0;
    for (auto& agent : agents) {
        agent.calculateFitness();
        fitness_scores[i] = agent.fitness;
        i++;
    }
}

void GeneticAlgorithm::evolve(vector<double> fitness_scores) {
    vector<NeuralNetwork> new_population;
    
    vector<int> indices(fitness_scores.size());
    iota(indices.begin(), indices.end(), 0);
    sort(indices.begin(), indices.end(), [&](int a, int b) { return fitness_scores[a] > fitness_scores[b]; });

    for (size_t i = 0; i < population_size / 2; i++) {
        new_population.push_back(population[indices[i]]);
        new_population.push_back(crossover(population[indices[i]], population[indices[i + 1]]));
    }

    for (auto& nn : new_population) {
        mutate(nn, 0.05);
    }

    population = new_population;
}
