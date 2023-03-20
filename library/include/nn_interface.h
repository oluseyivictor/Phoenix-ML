#pragma once

#include <iostream>
#include "Vector.hpp"

using namespace phoenix;

/**
 * @brief An interface for a neural network implementation.
 **/
class INeuralNetwork
{
public:
    /**
     * @brief Trains the neural network for a specified number of epochs.
     * @param epochs The number of epochs to train the neural network for.
     */
    virtual void train(const int epochs) = 0;

    /**
     * @brief Predicts an output based on a given input.
     * @param predict The vector input to the neural network to be predicted.
     * @return Vector The output predicted by the neural network.
     */
    virtual Vector<double> predict(const Vector<double> &predict) = 0;

    /**
     * @brief Saves the current state of the neural network to a file.
     * @param filename The name of the file to save the neural network to.
     */
    virtual void save(std::string filename) = 0;

    /**
     * @brief Configures the activation function for each layer of the neural network.
     * @param act_value An initializer list of strings representing the activation function for each layer of the neural network.
     */
    virtual void configure(std::initializer_list<std::string> &act_value) = 0;

    /**
     * @brief Loads a previously saved neural network from a file.
     * @param filename The name of the file to load the neural network from.
     */
    virtual void load(std::string filename) = 0;
};