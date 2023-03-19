#include "io.h"


Matrix<double> ReadFileToMatrix(const std::string &filename, char delimeter)
{

    Matrix<double> matrix(1, 1);

    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return matrix;
    }

    // char delimeter = ' ';

    std::string token;

    std::string line;
    std::vector<double> values;
    int rows = 0, cols, col = 0;

    try
    {
        while (std::getline(file, line))
        {
            std::stringstream line_stream(line);
            double value;
            col = 0;
            while (std::getline(line_stream, token, delimeter))
            {
                double value = std::stod(token); 
                if (col == 0)
                {
                    cols++;
                }
                values.push_back(value);
                col++;
            }
            ++rows;
        }

        matrix = Matrix<double>(rows, col);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                matrix(i, j) = values[i * col + j];
            }
        }

        file.close();
    }

    catch (const std::invalid_argument &e)
    {
        std::cerr << "file conversion error check delimeter or file " << e.what() << std::endl;
        file.close();
        return matrix;
    }

    return matrix;
}
