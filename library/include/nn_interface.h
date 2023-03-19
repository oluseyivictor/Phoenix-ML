#pragma once

#include <iostream>
#include "Vector.hpp"

using namespace phoenix;


class INeuralNetwork {
public:
    virtual void train(const int epochs) = 0;
    virtual Vector<double> predict(const Vector<double> &predict) = 0;
    virtual void save(std::string filename) = 0;
    virtual void configure(std::initializer_list<std::string> &act_value) = 0;
    virtual void load(std::string filename) = 0;
};