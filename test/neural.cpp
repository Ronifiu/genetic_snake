#include "neural.h"

using namespace std;

NeuralNetwork::NeuralNetwork(int input_size, int hidden_size, int output_size) {
    input_to_hidden = randomMatrix(input_size, hidden_size);
    hidden_to_output = randomMatrix(hidden_size, output_size);
    hidden_bias = randomVector(hidden_size);
    output_bias = randomVector(output_size);
}

vector<double> NeuralNetwork::forward(vector<double> inputs) {
    vector<double> hidden = activate(matrixMultiply(inputs, input_to_hidden, hidden_bias));
    return softmax(matrixMultiply(hidden, hidden_to_output, output_bias));
}

vector<vector<double>> NeuralNetwork::randomMatrix(int rows, int cols) {
    vector<vector<double>> matrix(rows, vector<double>(cols));
    for (auto& row : matrix)
        for (auto& val : row)
            val = ((rand() % 2000) / 1000.0) - 1.0; // Random values in [-1,1]
    return matrix;
}

vector<double> NeuralNetwork::randomVector(int size) {
    vector<double> vec(size);
    for (auto& val : vec)
        val = ((rand() % 2000) / 1000.0) - 1.0;
    return vec;
}

vector<double> NeuralNetwork::activate(const vector<double>& values) {
    vector<double> activated(values.size());
    for (size_t i = 0; i < values.size(); i++) {
        activated[i] = max(0.0, values[i]);
    }
    return activated;
}

vector<double> NeuralNetwork::softmax(const vector<double>& values) {
    double sum = 0.0;
    for (double v : values) sum += exp(v);
    vector<double> probabilities(values.size());
    for (size_t i = 0; i < values.size(); i++) {
        probabilities[i] = exp(values[i]) / sum;
    }
    return probabilities;
}

vector<double> NeuralNetwork::matrixMultiply(const vector<double>& input, const vector<vector<double>>& weights, const vector<double>& bias) {
    vector<double> output(weights[0].size(), 0.0);
    for (size_t j = 0; j < weights[0].size(); j++) {
        for (size_t i = 0; i < input.size(); i++) {
            output[j] += input[i] * weights[i][j];
        }
        output[j] += bias[j]; // Add bias
    }
    return output;
}

