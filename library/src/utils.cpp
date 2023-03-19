#include "utils.h"



double rms_error(double y_pred, double y_true) {return 0.5 * std::pow((y_pred - y_true), 2);}
double pd_error(const double a, const double b) { return a - b; }

/**
 * @brief Single input single output neural network.
 *
 * @param input The value of the input element.
 * @param weight The weight attached with the input.
 *
 * @return A predicted value which is input multiplied by weight.
 */
double scalar_multiply(double input, double weight) { return(input*weight); }

