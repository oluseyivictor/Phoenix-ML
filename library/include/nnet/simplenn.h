/**
 * @file matrix.h
 * @brief This file contains the declaration of the Matrix class.
 */

#ifndef SIMPLE_NN_H
#define SIMPLE_NN_H

#include "nn.h"
#include "nn_interface.h"
#include <fstream>


class SimpleNeuralNetwork : public NeuralModel, public INeuralNetwork {
    public:

        Matrix<double> input;
        Matrix<double> output;
        std::vector<int> H;

        int num_inputs;
        int num_hidden;
        int num_outputs;
        double learning_rate;
        int value;
    
    public:
        /**
         * @brief Constructs a simple neural network object with the given input, output, hidden neurons, and learning rate.
         *
         * @param rin The input matrix for the model.
         * @param rout The output matrix for the model.
         * @param rhidden_neurons The number of hidden neurons in each layer.
         * @param rrate The learning rate of the model.
         */
        SimpleNeuralNetwork(Matrix<double> &rin,
                            Matrix<double> &rout,
                            std::initializer_list<int> rhidden_neurons,
                            double rrate);

         /**
         * @brief Constructs a simple neural network object with default values.
         */
        SimpleNeuralNetwork();

        /**
         * @brief Trains the model for the given number of epochs.
         *
         * @param epochs The number of epochs to train the model.
         */
        void train(const int epochs = 100);

        /**
         * @brief Predicts the output for the given input vector.
         *
         * @param predict The input vector for prediction.
         * @return The predicted output vector.
         */
        Vector<double> predict(const Vector<double> &predict);

        /**
         * @brief Configures the activation functions for the model.
         *
         * @param act_value The list of activation function names.
         */
        void configure(std::initializer_list<std::string> &act_value);

        /**
         * @brief Saves the model to a file with the given filename.
         *
         * @param filename The name of the file to save the model.
         */
        void save(std::string filename);

        /**
         * @brief Loads the model from a file with the given filename.
         *
         * @param filename The name of the file to load the model.
         */
        void load(std::string filename);
};

#endif