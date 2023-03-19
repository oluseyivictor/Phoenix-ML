#include "nn.h"

NeuralModel::NeuralModel()
{}

NeuralModel::NeuralModel(Matrix<double> &in,
                         Matrix<double> &out,
                         std::initializer_list<int> hidden_neurons,
                         double rate) : feature(in), label(out), hid_list(hidden_neurons), learning_rate(rate)
{
  for (int n : hid_list)
    hiddn.push_back(n);
  NNBuild(feature.getCols(), label.getCols(), hiddn);
}


void NeuralModel::NNConnfigure(std::initializer_list<std::string> act_function)
{

  if (!A.empty())
  {
    A.clear();
  }

  for (auto fn : act_function)
  {
    act activationType;

    if (fn == "sigmoid")
    {
      activationType.activation = sigmoid;
      activationType.derivative = sigmoid_derivative;
    }
    else if (fn == "relu")
    {
      activationType.activation = relu;
      activationType.derivative = relu_derivative;
    }
    else if (fn == "linear")
    {
      activationType.activation = linear;
      activationType.derivative = linear_derivative;
    }
    else
    {
      std::cout << "invalid actvation function" << std::endl;
    }
    A.push_back(activationType);
  }
}


void NeuralModel::NNBuild(int input_size, int output_size, std::vector<int> &hids)
{

  int bk_n = input_size; 
  no_hid = hids.size();
  Vector<double> input(bk_n);

  network.addMatrix(input);

  /*Add hidden layer neurons to network*/
  for (auto n : hids)
  {
    Vector<double> neurons(n);
    Vector<double> hidden_bias(n);

    /*construct weight matrices*/
    Matrix<double> weight(n, bk_n); 

    weight.randfill();
    hidden_bias.zerofill();

    network.addMatrix(weight);
    network.addMatrix(neurons);
    B.push_back(hidden_bias);

    bk_n = neurons.size();
  }

  int last_n = output_size; 

  Vector<double> output(last_n);
  Vector<double> output_bias(last_n); 
  output_bias.zerofill();
  B.push_back(output_bias);

  Matrix<double> weight(last_n, bk_n);
  weight.randfill();
  network.addMatrix(weight);
  network.addMatrix(output);

  act default_fn = {sigmoid, sigmoid_derivative};
  act output_fn = {linear, linear_derivative};

  for (int i = 0; i < hids.size(); i++)
  {
    A.push_back(default_fn);
  }
  A.push_back(output_fn);
}

void NeuralModel::forward_propagation(const Vector<double> &input)
{

  int layer = 0;
  int i = 0;
  network[layer] = input;

  /* Calculate output of hidden layer */
  for (i = 0; i < no_hid; i++)
  {
    auto hidden_layer = convert_col(network[layer++], 0);
    auto p = (network[layer++] * hidden_layer) + B[i];

    network[layer] = vector_act(p, A[i].activation);
  }

  /*Calculate final output  no sigmoid*/ 
  auto hidden_layer = convert_col(network[layer++], 0);
  auto p = (network[layer++] * hidden_layer); 

  network[layer] = vector_act(p, A[no_hid].activation);
}


Vector<double> NeuralModel::NNPredicted()
{
  int count = network.size() - 1;
  Vector<double> output = convert_col(network[count], 0);

  return (output);
}

void NeuralModel::back_propagation(const Vector<double> &expected_output)
{

  std::vector<Vector<double>> error;
  int count = network.size() - 1;

  /*Extract Value of output from tensor network*/ 
  Vector<double> output = convert_col(network[count], 0);

  /* calculate error for the output layer*/
  Vector<double> output_error(output.size());
  for (int i = 0; i < output.size(); i++)
  {
    double derr = expected_output[i] - output[i];
    output_error[i] = derr * A[no_hid].derivative(output[i]);
  }
  error.push_back(output_error);

  /*calculate error for the hidden layer*/
  for (int hid = 0; hid < no_hid; hid++)
  {
    Matrix<double> h_weight = network[--count].transpose();
    Vector<double> hidden_n = convert_col(network[--count], 0);
    Vector<double> h_error(hidden_n.size());

    h_error = h_weight * error[hid];

    for (int i = 0; i < h_error.size(); i++)
      h_error[i] = h_error[i] * A[hid].derivative(hidden_n[i]);

    error.push_back(h_error);
  }

  count = network.size() - 1;
  int iter = no_hid + 1;

  /* Update weights for layers*/
  for (int layer = 0; layer < iter; layer++)
  {
    Matrix<double> &h_weight = network[--count];
    Vector<double> hidden_n = convert_col(network[--count], 0);

    for (int i = 0; i < h_weight.getRows(); i++)
    {
      for (int j = 0; j < h_weight.getCols(); j++)
      {
        double delta_weight = learning_rate * error[layer][i] * hidden_n[j];
        h_weight[i][j] += delta_weight;
      }

      /*Update Bias*/ 
      B[no_hid - layer][i] += learning_rate * error[layer][i];
    }
  }

}