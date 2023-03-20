/**
 * @file nn.h
 * @brief lightweight neural network engine of phoenixs library .
 */

#ifndef NN_H
#define NN_H

#include "Vector.hpp"
#include "utils.h"
#include <functional>
#include "tensor.hpp"

using namespace phoenix;

/**
* @brief A class for implementing a neural network model.
*        \n This class contains the necessary data members and methods for creating, 
*        \n training, and using a neural network model.
*/
class NeuralModel {

private:
    Matrix<double> feature;
    Matrix<double> label; 
    std::initializer_list<int> hid_list; 
    std::vector<int> hiddn;

    /*number of hidden neuron in each layer*/
    std::vector<Vector<double>> target;
    int no_hid = 0;
    double learning_rate = 0.01;
    
   struct act{
    std::function<double(double)> activation;
    std::function<double(double)> derivative;
   }; 

   std::vector<act> A;    

  protected:

  Tensor<double> network; /**< Tensor network */
  std::vector<Vector<double>> B; /**< Bias of network */        
 

public:
    /**
     * @brief Constructs a neural network model object.
     */
    NeuralModel();

    /**
     * @brief Constructs a neural network model object with the specified parameters.
     *
     * @param in The input matrix.
     * @param out The output matrix.
     * @param hidden_neurons An initializer list specifying the number of hidden neurons in each layer.
     * @param rate The learning rate of the neural network model.
     */
    NeuralModel (Matrix<double> &in,
                 Matrix<double> &out,
                 std::initializer_list<int> hidden_neurons,
                 double rate );

    /**
     * @brief Destructs a neural network model.
     */
    ~NeuralModel()  {};

  protected:
    /**
     * @brief Configures the activation functions for the neural network model.
     *
     * @param act_function An initializer list specifying the activation functions for each layer.
     */
    void NNConnfigure(std::initializer_list<std::string> act_function);

    /**
     * @brief Builds the neural network model with the specified input size, output size, and hidden layer sizes.
     *
     * @param input_size The number of neurons in the input layer.
     * @param output_size The number of neurons in the output layer.
     * @param hids A vector specifying the number of neurons in each hidden layer.
     */
    void NNBuild(int input_size, int output_size, std::vector<int> &hids);

    /**
     * @brief Performs forward propagation for the given input.
     *
     * @param input The input vector for the neural network model.
     */
    void forward_propagation(const Vector<double> &input);

    /**
     * @brief Performs back propagation to update the weights and biases of the neural network model.
     *
     * @param expected_output The expected output vector for the neural network model.
     */
    void back_propagation(const Vector<double> &expected_output);

    /**
     * @brief Predicts the output for the given input using the trained neural network model.
     *
     * @return The predicted output vector for the given input.
     */
    Vector<double> NNPredicted();
};


#endif