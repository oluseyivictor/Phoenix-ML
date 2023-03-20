#include <iostream>
#include "nnet/simplenn.h"
#include "io.h"
#include "utils.h"

using namespace phoenix;





int main()
{

    auto input_data = ReadFileToMatrix("/home/ml/Desktop/Phoenix-ML/examples/semeoin.data", ' ');

    std::cout << input_data.getCols() << " X " << input_data.getRows() << std::endl;

    ShuffleMatrixRows(input_data, 0.5);

    std::vector<int> feature_mark;
    std::vector<int> label_mark;

    for (int i = 0; i < input_data.getCols() - 10; i++)
    {
        feature_mark.push_back(i);
    }

    for (int i = 256; i < input_data.getCols(); i++)
    {
        label_mark.push_back(i);
    }

    auto feature_data = SetMatrix(input_data, feature_mark);

    auto label_data = SetMatrix(input_data, label_mark);

    std::cout<<feature_data.getCols()<< " X "<<feature_data.getRows()<<std::endl;

    auto [X_train, X_test, Y_train, Y_test] = train_test_split(feature_data, label_data, 0.75);

    auto feau = convert_row(X_test, 5);
    auto lab = convert_row(Y_test, 5);

    SimpleNeuralNetwork model(X_train, Y_train, {100}, 0.01);
    model.train(50);

    model.save("../../app/mymodel.nn");

    std::cout << model.predict(feau) << std::endl;
    std::cout << lab << std::endl;

    return 1;
}
