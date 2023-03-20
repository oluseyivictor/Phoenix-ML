/**
 * @file matrix.h
 * @brief This file contains the declaration of the Matrix class.
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <memory>
#include <cstdlib>
#include <initializer_list>
#include <vector>
#include <cmath>

namespace phoenix {

/*forward declaration of vector class*/
template <typename T>
class Vector;

/**
 *  @brief The Matrix class represents a matrix of values with generic programming.
 *
 *  @tparam T Type of elements stored in the matrix
 *  @tparam rows Number of rows in the matrix
 *  @tparam cols Number of cols in the matrix
 *  @note Matrix<T>(row,col)
 */
template <typename T>
class Matrix
{

private:
    /**
     * @brief Unique pointer to the data stored in the matrix
     */

    int rows;
    int cols;

private:
    std::shared_ptr<T[]> data;

public:
    /**
     * @brief Constructs a Matrix object with the specified number of rows and columns.
     * @param r row index for matrix elements
     * @param c col index for matrix elements
     */
    Matrix(int r, int c = 1) : rows(r), cols(c), data(std::make_unique<T[]>(r * c))
    {
    }

    /**
     * @brief Default Matrix object constructor.
     *
     */
    Matrix() : rows(1), cols(1), data(std::make_unique<T[]>(1))
    {
    }

    /**
     *   @brief Transpose the current matrix and return a new matrix.
     *   @return Matrix<T> The transposed matrix.
     */
    Matrix<T> transpose() const
    {
        Matrix<T> result(cols, rows);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                result[j][i] = operator()(i, j);
            }
        }
        return result;
    }

    /**
     * @brief Get the number of rows in the matrix
     *
     * @return int Number of rows
     */
    int getRows() const { return rows; }

    /**
     *   @brief Assigns the values of a vector of initializer lists to the matrix.
     *       \n The method assigns the values of a vector of initializer lists to the matrix.
     *       \n The number of rows and columns in the matrix should be equal to the size of the input data.
     *       \n extra values in the input data are ignored.
     *   @param list A vector of initializer lists with the data to be assigned to the matrix.
     *   @return void.
     */
    void operator=(const std::vector<std::initializer_list<T>> list)
    {
        int i = 0;
        for (const auto &val : list)
        {
            for (const auto &value : val)
            {
                data[i++] = value;
                if (i == rows * cols)
                    break;
            }
        }
    }
    /**
     * @brief Get the number of cols in the matrix
     *
     * @return int Number of cols
     */
    int getCols() const { return cols; }

    /**
     * @brief Overloaded parenthesis operator to accesses matrix element (mutable)).
     *
     * @param i row Row index of the element.
     * @param j col Column index of the element.
     *
     * @return T& Reference to the element at the specified row and column.
     */
    T &operator()(int i, int j) { 
        int index = (i * cols + j);
         if (index > size())
        {
            throw std::invalid_argument("Accessing wrong index in matrix. ");
        }
        return data[index]; 
     }

    /**
     * @brief Overloaded parenthesis operator to accesses matrix element(read-only)).
     *
     * @param i row Row index of the element.
     * @param j col Column index of the element.
     *
     * @return T& Reference to the element at the specified row and column.
     */
    const T &operator()(int i, int j) const { 
        int index = (i * cols + j);
         if (index > size())
        {
            throw std::invalid_argument("Accessing wrong index in matrix. ");
        }
        return data[index]; 
     }

    /**
     * @brief Accesses matrix element at the specified row and column(read-only)).
     *
     * @param i row Row index of the element.
     * @return A pointer to the first element in the row.
     */
    T *operator[](size_t row) { return data.get() + row * cols; }

    /**
     * @brief Accesses matrix element at the specified row and column(mutable)).
     *
     * @param i row Row index of the element.
     * @return A pointer to the first element in the row.
     */
    const T *operator[](size_t row) const { return data.get() + row * cols; }

    /**
     * @brief Get a pointer to the raw data stored in the matrix.
     * @return A pointer to the raw data stored in the matrix.
     */
    T *getdata() { return data.get(); }

    /**
     * @brief Get the total number of element in a matrix
     * @return the total size of the matric given by row multiply by col
     */
    int size() const { return rows * cols; }

    /**
     * @brief Returns the maximum value in the matrix.
     * @return double Maximum value in the matrix.
     */
    double max()
    {
        double val = data[0];

        for (int i = 1; i < size(); i++)
        {
            if (data[i] > val)
                val = data[i];
        }

        return val;
    }

    /**
     * @brief Returns the index position of the maximum element in the matrix.
     * @return the index position of the maximum element in the matrix.
     */
    double maxposition()
    {
        int i = 0;
        int position = 0;
        double val = data[i];

        for (int i = 1; i < size(); i++)
        {
            if (data[i] > val)
            {
                position = i;
                val = data[i];
            }
        }

        return position;
    }
    
    /**
     * @brief Scales the matrix by dividing all elements by the maximum value.
     * @return A new scaled Matrix object.
     */
    Matrix<T> scale()
    {
        Matrix<T> result(rows, cols);
        T ran = this->max();
        for (int i = 0; i < this->size(); i++)
        {
            result.data[i] = this->data[i] / ran;
        }
        return result;
    }

    /**
    * @brief Fills the matrix with random values between 0 and 1 using the srand function with seed value 2.
    */
    void randfill()
    {
        double d_rand;
        srand(2);
        for (int i = 0; i < size(); i++)
        {
            d_rand = (rand() % 10);
            d_rand /= 10;
            data[i] = d_rand;
        }
    }

    /**
    * @brief Fills the matrix with zeros.
    */
    void zerofill()
    {
        double d_zero = 0;
        for (int i = 0; i < size(); i++)
        {

            data[i] = d_zero;
        }
    }
    /**
     * @brief find the sum of all element in a matrix.
     * @return double sum.
     */
    double Tsum()
    {
        double d_sum = 0;
        for (int i = 0; i < size(); i++)
        {

            d_sum += data[i];
        }
        return d_sum;
    };

    /**
    * @brief Fills the matrix with zeros except for the maximum element, which is set to 1.
    */
    void topfill()
    {
        int position = maxposition();
        zerofill();
        data[position] = 1;
    }

    /**
     * @brief Multiplies two matrices and returns the result.
     *
     * @param other The matrix to multiply with.
     * @return The result of the matrix multiplication.
     */
    Matrix<T> operator*(const Matrix &other) const
    {
        Matrix<T> result(getRows(), other.getCols());
        for (int i = 0; i < getRows(); i++)
        {
            for (int j = 0; j < other.getCols(); j++)
            {
                result[i][j] = 0;
                for (int k = 0; k < getCols(); k++)
                {
                    result[i][j] += (*this)[i][k] * other[k][j];
                }
            }
        }
        return result;
    }

    /**
     * @brief Overloaded stream operator to print the matrix
     *
     * @param os Output stream
     * @param mat Matrix to print
     * @return std::ostream& Output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &mat)
    {
        for (int i = 0; i < mat.getRows(); i++)
        {
            for (int j = 0; j < mat.getCols(); j++)
            {
                os << mat.data[i * mat.getCols() + j] << " ";
            }
            os << std::endl;
        }
        return os;
    }
};

}

#endif // MATRIX_H