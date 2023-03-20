#include <iostream>
#include "nnet/simplenn.h"
#include "io.h"
#include "utils.h"

using namespace phoenix;

int main()
{
    /*Extract Data*/
    auto input_data = ReadFileToMatrix("/home/ml/Desktop/Phoenix-ML/examples/semeoin.data", ' ');

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

    /*Split into Training and Testing Data*/
    auto [X_train, X_test, Y_train, Y_test] = train_test_split(feature_data, label_data, 0.75);
    auto actual_feature = convert_row(X_test, 1);
    auto actual_label = convert_row(Y_test, 1);

    /*Load NN Model*/
    SimpleNeuralNetwork nn;
    nn.load("mymodel.nn");

    auto predicted_label = nn.predict(actual_feature);

    predicted_label.topfill();
    std::cout << predicted_label << std::endl;
    std::cout << actual_label << std::endl;

    return 1;
}