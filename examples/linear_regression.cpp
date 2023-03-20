#include <random>
#include <iostream>

#include "nnet/LinearRegression.h"
using namespace phoenix;



int main(){
	
        /*Generate Random data*/
	std::size_t num_data_points = 100;
	std::size_t num_dims = 50;
	Matrix<double> X(num_data_points, num_dims);
	Vector<double> y(num_data_points);


	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> normal(0,2);
	for(std::size_t i = 0; i != num_data_points; ++i){
		for(std::size_t j = 0; j != num_dims; ++j){
			X(i,j) = normal(gen);
		}
	}

	std::normal_distribution<> normal_noise(0, 0.1);
	for (std::size_t i = 0; i != num_data_points; ++i)
	{
		y[i] = sum(convert_row(X, i)) + normal_noise(gen) + 1;
	}

	/* Linear Model*/
	LinearRegression model(X, y);
	model.train(5000);

	auto input = convert_row(X, 1);
	auto predicted = model.predict(input);
	double actual = y[1];

	std::cout << actual << std::endl;
	std::cout << predicted << std::endl;

	std::cout << "error = " << ((actual - predicted[0]) / actual) << std::endl;

	return 1;
}