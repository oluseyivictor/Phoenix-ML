#include <iostream>

#include "ADT/Matrix.hpp"
#include "ADT/tensor.hpp"
#include "nnet/simplenn.h"
#include "nnet/LinearRegression.h"
#include "utils.h"

#include "config.hpp"


int main()
{

    Matrix<double> value(3,5);
    Tensor<double> rain;

    rain.addMatrix(value);
    value.randfill();


Matrix<double>raw_X(4,3);
Matrix<double>raw_Y(4,2);

Matrix<double>m1(2,3);
        Matrix<double>m2(3, 2);


        m1(0, 0) = 1;
        m1(0, 1) = 2;
        m1(0, 2) = 3;
        m1(1, 0) = 4;
        m1(1, 1) = 5;
        m1(1, 2) = 6;

        m2 = {{7,8},{9,10},{11,12}};
        std::cout<<m1 <<std::endl;
        std::cout<< m2 <<std::endl;

        auto m3 = m1 * m2;
        std::cout<< m3 <<std::endl;

raw_X = {{2, 8, 5}, {2, 8, 5}, {2, 8, 5}, {2, 8, 5}};
raw_Y = {{1,6}, {1,6},{1,6},{1,6}}; 

auto ld = raw_Y.size();
//SimpleNeuralNetwork nn(raw_X, raw_Y, {raw_Y.size()}, 0.001);

LinearRegression nn(raw_X, raw_Y);
std::cout<< nn.num_hidden<<std::endl;

 nn.train(500);

auto input = convert_row(raw_X, 1);

std::cout<< nn.predict(input) <<std::endl;
std::cout<<project_name<<std::endl;

nn.network.print();

    return 1;
}