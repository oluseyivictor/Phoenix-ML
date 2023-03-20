#include <random>
#include <iostream>

#include "nnet/LinearRegression.h"
using namespace phoenix;



int main(){
	//Step 0: Theory
	// The goal of linear regression is to find a linear function f(x) = w^Tx + b
	// that fits best a given set of point-label pairs (x1,y1),(x2,y2),...,(xN,yN).
	// This is measured by the squared error:
	// E(w) = 1/(2N) sum_i (f(x_i)-y_i)^2
	// It turns out that the optimal solution can be written in simple matrix algebra,
	// when X is the data matrix where points are stored row-wise and y is the vector
	// of labels:
	// w=((X|1)^T (X|1))^{-1} (X|1)^Ty
	
	//Step 1: Generate some random data
	//###begin<data_declaration>

	std::size_t num_data_points = 100;
	std::size_t num_dims = 50;
	Matrix<double> X(num_data_points, num_dims);
	Vector<double> y(num_data_points);
	//###end<data_declaration>
	//###begin<generate_X>
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> normal(0,2);
	for(std::size_t i = 0; i != num_data_points; ++i){
		for(std::size_t j = 0; j != num_dims; ++j){
			X(i,j) = normal(gen); //set element (i,j) of X to a rnadomly generated number
		}
	}
	//###end<generate_X>
	//###begin<generate_Y>
	std::normal_distribution<> normal_noise(0,0.1);
	for(std::size_t i = 0; i != num_data_points; ++i){
		//label is chosen to be just the sum of entries plus some noise
		y[i] = sum(convert_row(X,i)) + normal_noise(gen) + 1;
	}

    LinearRegression model(X, y);
    model.train(5000);

    auto input = convert_row(X, 1);
    auto w = model.predict(input);

    std::cout<<y[1]<<std::endl;
	std::cout<<w<<std::endl;

    return 1;
}