    #include "LogisticRegression.h"

    LogisticRegression::LogisticRegression(Matrix<double> &rin,
                                    Matrix<double> &rout) : NeuralModel(rin, rout, {rout.getCols()}, 0.001), input(rin) , output(rout)
    {
        num_inputs = rin.getCols();
        num_hidden = 1;
        num_outputs = rout.getCols();
        learning_rate = 0.001;
        H.push_back(num_outputs);
        NeuralModel::NNConnfigure({"linear", "sigmoid"});
    }

    LogisticRegression::LogisticRegression(): NeuralModel()
    {

    }
                 

    
    void LogisticRegression::train(int epochs){
         double error;

         for (int count = 0; count < epochs; count++)
         {
           error = 0;
           for(int i = 0; i < input.getRows(); i++)
            {
              auto in = convert_row(input, i);
              auto target = convert_row(output, i);

              NeuralModel::forward_propagation(in);
              NeuralModel::back_propagation(target);

            error += total_error(target,  NeuralModel::NNPredicted());
          }
          error = error/input.getRows();
           std::cout<<"Epoch----- "<< count << " Error: "<<error<<std::endl;
         }
 }


    void LogisticRegression::save(std::string filename) {

        std::ofstream file(filename, std::ios::out | std::ios::binary);
        if (!file) {
            std::cerr << "Error: Could not open file " << filename << " for writing\n";
            return;
        }
        
        file.write(reinterpret_cast<char*>(&num_inputs), sizeof(num_inputs));
        file.write(reinterpret_cast<char*>(&num_hidden), sizeof(num_hidden));
        file.write(reinterpret_cast<char*>(&num_outputs), sizeof(num_outputs));
        file.write(reinterpret_cast<char*>(&learning_rate), sizeof(learning_rate));

        
        for (auto vals: H){
            file.write(reinterpret_cast<char*>(&vals), sizeof(vals));
        }
        
        int network_size = NeuralModel::network.size() - 1;
        for (int i = 1; i < network_size; i = i+2 )
        {
            Matrix<double> weight = NeuralModel::network[i];
            file.write(reinterpret_cast<char*>(weight.getdata()), weight.size() * sizeof(double)) ;       

        }

                
        
        int bias_size = NeuralModel::B.size();
        for (int i = 0; i < bias_size; i++ )
        {
            Vector<double> bias = NeuralModel::B[i];
            file.write(reinterpret_cast<char*>(bias.getdata()), bias.size() * sizeof(double)) ;       

        }
        file.close();
    }


    void LogisticRegression::load(std::string filename) {
        std::ifstream file(filename, std::ios::in | std::ios::binary);
        if (!file) {
            std::cerr << "Error: Could not open file " << filename << " for reading\n";
            return;
        }
        file.read(reinterpret_cast<char*>(&num_inputs), sizeof(num_inputs));
        file.read(reinterpret_cast<char*>(&num_hidden), sizeof(num_hidden));
        file.read(reinterpret_cast<char*>(&num_outputs), sizeof(num_outputs));
        file.read(reinterpret_cast<char*>(&learning_rate), sizeof(learning_rate));


        std::vector<int> nl;

        for (int i = 0; i < num_hidden; i++ )
        {
            file.read(reinterpret_cast<char*>(&value), sizeof(value));
            nl.push_back(value);   

        }

        NNBuild(num_inputs, num_outputs, nl);

        int network_size = NeuralModel::network.size() - 1;
        for (int i = 1; i < network_size; i = i+2 )
        {
            Matrix<double> &weight =  NeuralModel::network[i];
           file.read(reinterpret_cast<char*>(weight.getdata()), weight.size() * sizeof(double));   

        }

        B.clear();
        for (int i = 0; i < num_hidden; i++ )
        {
            Vector<double> bias(nl[i]);
            file.read(reinterpret_cast<char*>(bias.getdata()), bias.size() * sizeof(double));  
            B.push_back(bias);

        }
        file.close();
    }


    void LogisticRegression::configure(std::initializer_list<std::string>& act_value)
   {
        NeuralModel::NNConnfigure(act_value);
   }

    Vector<double> LogisticRegression::predict(const Vector<double> &predict){
        int count = NeuralModel::network.size() - 1;

        NeuralModel::forward_propagation(predict);

        Vector<double> output =  convert_col(NeuralModel::network[count], 0);

    return (output);

  }