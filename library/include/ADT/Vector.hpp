/**
 * @file vector.h
 * @brief This file contains the declaration of the Vector (m, 1)class .
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <config.hpp>
#include "Matrix.hpp"
#include "parallel.h"


namespace phoenix {
/**
 *  @brief The Vector class represents a 1D matrix with generic programming.
 *
 *  @tparam T Type of elements stored in the vector
 *  @tparam size Number of element in the vector
 */
template <typename T>
class Vector : public Matrix<T>
{
private:
    int v_size;

public:
    /**
     * @brief Constructs a vector object using matrix class constructor.
     *
     * @param list Initializer list for vector elements
     */
    Vector(int size)
        : Matrix<T>(size, 1)
    {
        v_size = size;
    }

    /**
     * @brief Overloaded bracket operator to accesses vector element at index i.
     *
     * @param i row Row index of the element.
     *
     * @return T& Reference to the element at the specified index.
     * @throws std::invalid_argument if wrong index is accessed
     */
    T &operator[](int i)
    {
        if (i > v_size)
        {
            throw std::invalid_argument("Accessing wrong parameter in vector. ");
        }
        return Matrix<T>::operator()(i, 0);
    }

    /**
     * @brief Overloaded bracket operator to accesses vector element at index i.
     *
     * @param i row Row index of the element.
     *
     * @return const T& Reference to the element at the specified index.
     * @throws std::invalid_argument if wrong index is accessed
     */
    const T &operator[](int i) const
    {
        if (i > v_size)
        {
            throw std::invalid_argument("Accessing wrong parameter in vector. ");
        }
        return Matrix<T>::operator()(i, 0);
    }

    /**
     * @brief Overloaded opening braces operator to accesses vector element at index i.
     *
     * @param i row Row index of the element.
     *
     * @return T& Reference to the element at the specified index.
     * @throws std::invalid_argument if wrong index is accessed
     */
    T& operator()(std::size_t i) { return Matrix<T>::operator()(i, 0); }

    /**
     * @brief Overloaded opening braces operator to accesses vector element at index i.
     *
     * @param i row Row index of the element.
     *
     * @return const T& Reference to the element at the specified index.
     * @throws std::invalid_argument if wrong index is accessed
     */
    const T& operator()(std::size_t i) const { return Matrix<T>::operator()(i, 0); }

    /**
     * @brief Multiplies the vector by a scalar value.
     *
     * @param scalar The scalar value to multiply the vector by.
     *
     * @return A reference to the current Vector object.
     */
    Vector<T> operator*(double scaler)
    {
        Vector<T> result(v_size);
        for (int i = 0; i < v_size; i++)
        {
            result[i] = (*this)[i] * scaler;
        }
        return result;
    }

    /**
     * @brief Overloaded addition operator for Vector class.
     * @param v The first vector to be added.
     * @param other The second vector to be added.
     * @return Vector<T> The resulting vector after adding the two input vectors.
     * @throws std::invalid_argument if the number of rows of the two vectors are not equal.
     */
   friend Vector<T> operator+(const Vector<T> &v, const Vector<T> &other)
{
    if (v.getRows() != other.getRows())
    {
        throw std::invalid_argument("The number of vector rows must be equal in vector + error. ");
    }

    Vector<T> result(other.size());

    if (enable_parallel)
        vector_vector_add(v, other, result, boost::thread::hardware_concurrency());
    else
        vector_vector_add(v, other, result);

    
    return result;
}

    /**
     * @brief Multiplies the vector by a scalar value.
     *
     * @param scalar The scalar value to multiply the vector by.
     *
     * @return A reference to the current Vector object.
     */
    friend Vector<T> operator*(double scaler, const Vector<T> &other)
    {
        Vector<T> result(other.size());
        for (int i = 0; i < other.size(); i++)
        {
            result[i] = other[i] * scaler;
        }
        return result;
    }

    /**
     * @brief Multiplies the vector by a scalar value.
     *
     * @param scalar The scalar value to multiply the vector by.
     *
     * @return A reference to the current Vector object.
     */
    friend Vector<T> operator*(const Vector<T> &other, double scaler)
    {
        Vector<T> result(other.size());
        result = (scaler * other);
        return result;
    }

    /**
     * @brief Performs vector-matrix multiplication and returns the result as a new vector.
     *
     * @param v The vector to multiply.
     * @param m The matrix to multiply.
     *
     * @return A new Vector object representing the result of the multiplication.
     * @throws std::invalid_argument if the number vector rows and the matrix column vectors are not equal.
     */

   friend Vector<T> operator*(Matrix<T> &m2, const Vector<T> &v1)
    {
        if (v1.getRows() != m2.getCols())
        {
            throw std::invalid_argument("The number of vector rows must be equal to Matrix column. ");
        }

        Vector<double> result(m2.getRows());

        if (enable_parallel)
            matrix_vector_multiply(m2, v1, result, boost::thread::hardware_concurrency());
        else
            matrix_vector_multiply(m2, v1, result);

        return result;
    }

    
    /**
     * @brief Assigns a vector of elements to the current vector using an initializer list.
     * @param list The initializer list containing the elements to be assigned to the vector.
     * @tparam T The data type of the elements in the vector.
     * @throw std::out_of_range if the size of the initializer list is greater than the size of the vector.
     */
    void operator=(const std::initializer_list<T> list)
    {
        int i = 0;
        for (const auto &value : list)
        {
            this->operator[](i++) = value;
            if (i == v_size)
                break;
        }
    }
};

}
#endif