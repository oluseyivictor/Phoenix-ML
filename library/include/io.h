#include <iostream>
#include <fstream>
#include <sstream>
#include "Vector.hpp"
#include <string>

using namespace phoenix;
/**

    @brief Reads a file and converts its contents to a Matrix object.
    @param filename The name of the file to read.
    @param delimeter The character used to separate values in the file.
    @return Matrix<double> The matrix object containing the values read from the file.
    @note If the file cannot be opened or there is an error in the file conversion, 
            \n an empty matrix object is returned.
**/
Matrix<double> ReadFileToMatrix(const std::string& filename, char delimeter);