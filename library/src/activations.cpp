#include "activations.h"

/**

    @brief Computes the sigmoid function of a given value.
    The sigmoid function maps any input value to a value between 0 and 1.
    The formula used is: f(x) = 1 / (1 + exp(-x))
    @param x The input value for which to compute the sigmoid function.
    @return The result of applying the sigmoid function to the input value.
*/
double sigmoid(double x){
        double result;
        result = 1/(1 + std::exp(-x));

        return result;
    }

 /**
    @brief Computes the derivative of the sigmoid function at a given point.
    The derivative of the sigmoid function at any point is given by f'(x) = f(x) * (1 - f(x)),
    where f(x) is the value of the sigmoid function at x.
    @param a The point at which to compute the derivative of the sigmoid function.
    @return The value of the derivative of the sigmoid function at the input point.
*/
double sigmoid_derivative(double a){
        double result;
        result = sigmoid(a) * (1.0 - sigmoid(a));

        return result;
    }  

/**

    @brief Computes the rectified linear unit (ReLU) function of a given value.
    The ReLU function maps any input value x to max(0, x).
    @param x The input value for which to compute the ReLU function.
    @return The result of applying the ReLU function to the input value.
*/
double relu(double x){
        
        return std::max(0.0, x);
    }

 
 /**

    @brief Computes the derivative of the ReLU function at a given point.
    The derivative of the ReLU function at any point is given by:
        1, if the input value is greater than 0
        0, otherwise
    @param a The point at which to compute the derivative of the ReLU function.
    @return The value of the derivative of the ReLU function at the input point.
*/
double relu_derivative(double a){

        return ( a > 0.0) ? 1.0 : 0.0;
    }  

/**

    @brief Computes the linear function of a given value.
    The linear function simply returns the input value.
    @param x The input value for which to compute the linear function.
    @return The result of applying the linear function to the input value.
*/
double linear(double x){
        
        return x;
    }

 
 /**

    @brief Computes the derivative of the linear function at a given point.
    The derivative of the linear function is a constant value of 1.
    @param a The point at which to compute the derivative of the linear function.
    @return The value of the derivative of the linear function at the input point.
    */
double linear_derivative(double a){

        return 1;
    }  


