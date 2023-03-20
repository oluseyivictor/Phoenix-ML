/**
 * @file nn.h
 * @brief lightweight neural network engine of phoenixs library .
 */

#ifndef UTILX_H
#define UTILX_H

#include "Vector.hpp"
#include <algorithm>
#include <memory>
#include <random>
#include <initializer_list>
#include <functional>
#include "activations.h"

double rms_error(double y_pred, double y_true);
double pd_error(const double a, const double b);
double scalar_multiply(double input, double weight);

using namespace phoenix;

template <typename T>
double sum(Matrix<T> X) {   return X.Tsum(); }

/**

    @brief Computes the total error between a target vector and an output vector.
    The total error is computed as the sum of the root mean squared error (RMSE) between each
    corresponding element in the target and output vectors.
    @tparam T The data type of the input vectors (e.g. float, double, int).
    @param target The target vector with the desired values.
    @param output The output vector with the predicted values.
    @return The total error between the target and output vectors.
    @throw std::invalid_argument If the number of rows in the target and output vectors is not equal.
    */
template <typename T>
T total_error(const Vector<T> target, const Vector<T> output)
{
    if (output.getRows() != target.getRows())
    {
        throw std::invalid_argument("The number of vector rows must be equal in vector total error compute. ");
    }

    T sum = 0.0;

    for (int i = 0; i < target.getRows(); i++)
    {
        sum += rms_error(target[i], output[i]);
    }
    return sum;
}

/**

    @brief Converts a row of a matrix into a vector.
    Given a matrix and an index i for a row, this function extracts that row from the matrix
    and returns it as a vector.
    @tparam T The data type of the matrix elements (e.g. float, double, int).
    @param other The matrix from which to extract the row.
    @param i The index of the row to extract.
    @return A vector containing the elements of the specified row.
*/
template <typename T>
Vector<T> convert_row(Matrix<T> &other, int i)
{
    Vector<T> result(other.getCols());
    for (int j = 0; j < other.getCols(); j++)
    {
        result[j] = other(i, j);
    }

    return result;
}

/**

    @brief Converts a column of a matrix into a vector.
    Given a matrix and an index j for a column, this function extracts that column from the matrix
    and returns it as a vector.
    @tparam T The data type of the matrix elements (e.g. float, double, int).
    @param other The matrix from which to extract the column.
    @param j The index of the column to extract.
    @return A vector containing the elements of the specified column.
 */
template <typename T>
Vector<T> convert_col(Matrix<T> &other, int j)
{
    Vector<T> result(other.getRows());
    for (int i = 0; i < other.getRows(); i++)
    {
        result[i] = other(i, j);
    }

    return result;
}

/**

    @brief Multiplies two vectors element-wise and returns their sum.
    Given two vectors, this function multiplies their elements element-wise and returns the sum of
    the resulting products.
    @tparam T The data type of the input vectors (e.g. float, double, int).
    @param input The first input vector.
    @param weight The second input vector.
    @return The sum of the element-wise products of the input vectors.
    */
template <typename T>
T vecTovec_multiply(const Vector<T> &input, const Vector<T> &weight)
{
    T output = 0;

    for (int i = 0; i < input.getRows(); i++)
    {

        output += input[i] * weight[i];
    }
    return output;
}

/**

    @brief Multiplies a vector by a matrix and returns the resulting vector.
    Given a vector and a matrix, this function multiplies the vector by the matrix and returns the resulting vector.
    @tparam T The data type of the input vector and matrix elements (e.g. float, double, int).
    @param v1 The input vector.
    @param m2 The input matrix.
    @return A vector containing the result of the matrix-vector multiplication.
    @throw std::invalid_argument If the number of rows in the vector and columns in the matrix is not equal.
    */
template <typename T>
Vector<T> vecTomat_multiply(Vector<T> &v1, Matrix<T> &m2)
{
    if (v1.getRows() != m2.getCols())
    {
        throw std::invalid_argument("The number of vector rows must be equal to Matrix column. ");
    }
    Vector<double> result(m2.getRows());
    for (int k = 0; k < m2.getRows(); k++)
    {
        result[k] = 0;

        for (int i = 0; i < v1.getRows(); i++)
        {
            result[k] += v1[i] * m2[k][i];
        }
    }

    return result;
}

/**

    @brief Applies the sigmoid function element-wise to a vector and returns the resulting vector.
    Given a vector, this function applies the sigmoid function element-wise to the vector and returns
    the resulting vector.
    @tparam T The data type of the input vector elements (e.g. float, double, int).
    @param v The input vector.
    @return A vector containing the result of applying the sigmoid function to the input vector.
    */
template <typename T>
Vector<T> vector_sigmoid(Vector<T> &v)
{
    Vector<T> result(v.size());

    for (int i = 0; i < v.size(); i++)
    {
        result[i] = sigmoid(v[i]);
    }

    return result;
}

/**
    @brief Applies a given activation function element-wise to a vector and returns the resulting vector.
    Given a vector and an activation function (in the form of a std::function object), this function applies
    the activation function element-wise to the vector and returns the resulting vector.
    @tparam T The data type of the input vector elements (e.g. float, double, int).
    @param v The input vector.
    @param act The activation function to apply to the input vector.
    @return A vector containing the result of applying the activation function to the input vector.
    */
template <typename T>
Vector<T> vector_act(Vector<T> &v, std::function<double(double)> &act)
{
    Vector<T> result(v.size());

    for (int i = 0; i < v.size(); i++)
    {
        result[i] = act(v[i]);
    }

    return result;
}

/**

    @brief Computes the derivative of the sigmoid function element-wise for each element in a vector.
    Given a vector, this function computes the derivative of the sigmoid function element-wise for each
    element in the vector and returns the resulting vector.
    @tparam T The data type of the input vector elements (e.g. float, double, int).
    @param v The input vector.
    @return A vector containing the derivative of the sigmoid function for each element in the input vector.
    */
template <typename T>
Vector<T> v_sigmoid_derivative(Vector<T> &v)
{
    Vector<T> result(v.size());

    for (int i = 0; i < v.size(); i++)
    {
        result[i] = sigmoid_derivative(v[i]);
    }

    return result;
}

/**

    @brief Shuffle the rows of a matrix randomly with a given probability.
    @tparam T the type of elements in the matrix.
    @param matrix the matrix to shuffle.
    @param randomness the probability of shuffling each row.
    */
template <typename T>
void ShuffleMatrixRows(Matrix<T> &matrix, double randomness)
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> dist(0, 1);

    for (int i = 0; i < matrix.getRows(); ++i)
    {
        if (dist(rng) <= randomness)
        {
            int j = i + std::uniform_int_distribution<int>(0, matrix.getRows() - i - 1)(rng);
            std::swap_ranges(matrix.data.get() + i * matrix.getCols(),
                             matrix.data.get() + (i + 1) * matrix.getCols(),
                             matrix.data.get() + j * matrix.getCols());
        }
    }
}

/**
    @brief Set the columns of a new matrix using specified column labels from an existing matrix.
    @tparam T Data type of the matrix.
    @param matrix The existing matrix from which the columns will be taken.
    @param labels An initializer list containing the labels of the columns to be taken from the matrix.
    @return Matrix<T> A new matrix containing the columns specified by the labels in the order they were given in the labels parameter.
    @throws std::invalid_argument If one or more of the specified column labels are out of range for the input matrix.
    */
template <typename T>
Matrix<T> SetMatrix(Matrix<T> &matrix, std::initializer_list<std::string> labels)
{
    int rows = matrix.getRows();
    int cols = labels.size();

    Matrix<T> result(rows, cols);

    int j = 0;
    for (std::string n : labels)
    {
        auto recept = convert_col(matrix, stoi(n));

        for (int i = 0; i < rows; i++)
        {
            result(i, j) = recept[i];
        }
        ++j;
    }

    return result;
}

/**
    @brief Set the columns of a new matrix using specified column labels from an existing matrix.
    @tparam T Data type of the matrix.
    @param matrix The existing matrix from which the columns will be taken.
    @param labels A std vector containing the labels of the columns to be taken from the matrix.
    @return Matrix<T> A new matrix containing the columns specified by the labels in the order they were given in the labels parameter.
    @throws std::invalid_argument If one or more of the specified column labels are out of range for the input matrix.
    */
template <typename T>
Matrix<T> SetMatrix(Matrix<T> &matrix, std::vector<int> labels)
{
    int rows = matrix.getRows();
    int cols = labels.size();

    Matrix<T> result(rows, cols);

    int j = 0;
    for (int n : labels)
    {
        auto recept = convert_col(matrix, n);

        for (int i = 0; i < rows; i++)
        {
            result(i, j) = recept[i];
        }
        ++j;
    }

    return result;
}

/**
   @brief Extracts a row matrix from a given matrix, where the row indices are specified by the nrows parameter.
    @tparam T The data type of the matrix elements.
    @param matrix The input matrix.
    @param nrows The number of rows to extract. If positive, it extracts the first nrows rows. If negative, it extracts the last abs(nrows) rows.
    @return Matrix<T> A row matrix that contains the extracted rows.
    @throw std::invalid_argument if nrows is greater than the number of rows in the input matrix.
    */
template <typename T>
Matrix<T> RowMatrix(Matrix<T> &matrix, int nrows)
{
    int start = nrows > 0 ? 0 : abs(nrows);         // 0 (start) or 75(start)
    int end = nrows > 0 ? nrows : matrix.getRows(); // 35(end) or rows(end)

    std::cout << start << "    " << end << std::endl;

    int rows = end - start;
    int cols = matrix.getCols();

    Matrix<T> result(rows, cols);

    int j = 0;
    for (int il = start; il < end; il++)
    {
        auto recept = convert_row(matrix, il);

        for (int i = 0; i < cols; i++)
        {
            result(j, i) = recept[i];
        }
        ++j;
    }

    return result;
}

/**
 * Splits the input matrices X and Y into train and test sets based on the specified test size.
 *
 * @param X         The input matrix X.
 * @param Y         The input matrix Y.
 * @param test_size The ratio of the test set size to the total size of the input matrices.
 *
 * @return A struct containing the train and test sets of X and Y.
 *         The struct contains four matrices: auto [X_train, X_test, Y_train, Y_test]
 */
template <typename T>
auto train_test_split(Matrix<T> &X, Matrix<T> &Y, float test_size)
{

    double train_no = test_size;
    double test_no = (0 - test_size);

    test_no *= X.getRows();
    train_no *= Y.getRows();

    std::cout << test_no << "------" << train_no << std::endl;

    struct results
    {
        Matrix<T> X_train;
        Matrix<T> X_test;
        Matrix<T> Y_train;
        Matrix<T> Y_test;
    };

    return results{RowMatrix(X, train_no),
                   RowMatrix(X, test_no),
                   RowMatrix(Y, train_no),
                   RowMatrix(Y, test_no)};
}



#endif