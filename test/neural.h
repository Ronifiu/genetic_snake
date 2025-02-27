#ifndef NEURAL_H
#define NEURAL_H

#include <vector>
#include <cmath>

using namespace std;

class NeuralNetwork {
public:
    vector<vector<double>> input_to_hidden;
    vector<vector<double>> hidden_to_output;
    vector<double> hidden_bias;
    vector<double> output_bias;
    
    NeuralNetwork(int input_size, int hidden_size, int output_size);

    vector<double> forward(vector<double> inputs);

private:
    vector<vector<double>> randomMatrix(int rows, int cols);
    vector<double> randomVector(int size);
    vector<double> activate(const vector<double>& vec);
    vector<double> softmax(const vector<double>& vec);
    vector<double> matrixMultiply(const vector<double>& vec, const vector<vector<double>>& mat, const vector<double>& bias);
};

#endif