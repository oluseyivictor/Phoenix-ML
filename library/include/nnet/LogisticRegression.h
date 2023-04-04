/**
 * @file matrix.h
 * @brief This file contains the declaration of the Matrix class.
 */

#ifndef LOGR_NN_H
#define LOGR_NN_H

#include "nn.h"
#include "nn_interface.h"
#include <fstream>

using namespace phoenix;

/**
 * @brief Logistic Regression Application Interface .
 */
class LogisticRegression : public NeuralModel, public INeuralNetwork {
    private:

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
         * @brief Constructs a Logistic Regression object.
         *
         * @param rin The input matrix for the model.
         * @param rout The output matrix for the model.
         */
        LogisticRegression(Matrix<double> &rin,
                         Matrix<double> &rout
                        );

         /**
         * @brief Constructs a LogisticRegression with default values.
         */
        LogisticRegression();

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