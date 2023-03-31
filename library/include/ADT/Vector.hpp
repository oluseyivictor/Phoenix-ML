/**
 * @file vector.h
 * @brief This file contains the declaration of the Vector (m, 1)class .
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <boost/thread.hpp>
#include "Matrix.hpp"

namespace phoenix {

    template <typename T>
void matrix_vector_multiply_thread(const Matrix<T>& m2, const Vector<T>& v1,
                                   Vector<T>& result, std::size_t row_start, std::size_t row_end);

template <typename T>
void matrix_vector_multiply(const Matrix<T>& m2, const Vector<T>& v1, Vector<T>& result, std::size_t num_threads);

template <typename T>
void matrix_vector_multiply(const Matrix<T>& m2, const Vector<T>& v1, Vector<T>& result);

template <typename T>
void vector_vector_add(const Vector<T>& v1, const Vector<T>& v2, Vector<T>& result);


template <typename T>
void vector_vector_add(const Vector<T>& m2, const Vector<T>& v1, Vector<T>& result, int num_threads);

template <typename T>
void vector_addition_thread (const Vector<T>& v1, const Vector<T>& v2, Vector<T>& result, int start, int end);
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
    T& operator()(std::size_t i) { return Matrix<T>::operator()(i, 0); }
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

    vector_vector_add(v, other, result, boost::thread::hardware_concurrency());

    
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

        matrix_vector_multiply(m2, v1, result, boost::thread::hardware_concurrency());

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




template <typename T>
void matrix_vector_multiply_thread(const Matrix<T>& m2, const Vector<T>& v1,
                                   Vector<T>& result, std::size_t row_start, std::size_t row_end)
{
    for (std::size_t k = row_start; k < row_end; ++k) {
        T sum = 0;
        for (std::size_t i = 0; i < v1.getRows(); ++i) {
            sum += v1[i] * m2(k,i);
        }
        result[k] = sum;
    }
}

// Define a function to launch multiple threads for matrix-vector multiplication
template <typename T>
void matrix_vector_multiply(const Matrix<T>& m2, const Vector<T>& v1, Vector<T>& result, std::size_t num_threads)
{

    std::vector<boost::thread> threads(num_threads);

    std::size_t rows_per_thread = m2.getRows() / num_threads;

    for (std::size_t i = 0; i < num_threads; ++i) {
        std::size_t row_start = i * rows_per_thread;
        std::size_t row_end = (i == num_threads - 1) ? m2.getRows() : (i + 1) * rows_per_thread;
        threads[i] = boost::thread(matrix_vector_multiply_thread<T>, std::cref(m2), std::cref(v1),
                                        std::ref(result), row_start, row_end);
}

for (auto& thread : threads) {
    thread.join();
}
}

template <typename T>
void matrix_vector_multiply(const Matrix<T>& m2, const Vector<T>& v1, Vector<T>& result)
{
    for (int k = 0; k < m2.getRows(); k++)
    {
        result[k] = 0;
        for (int i = 0; i < v1.getRows(); i++)
        {

            result[k] += v1[i] * m2[k][i];
        }
    }
}

template <typename T>
void vector_addition_thread (const Vector<T>& v1, const Vector<T>& v2, Vector<T>& result, int start, int end) {
        for (int i = start; i < end; i++) {
            result[i] = v1[i] + v2[i];
        }
}

template <typename T>
void vector_vector_add(const Vector<T> &v, const Vector<T> &other, Vector<T>& result, int num_threads)
{

    // Define the thread function for vector addition
    auto vector_addition_thread = [](const Vector<T>& v1, const Vector<T>& v2, Vector<T>& result, int start, int end) {
        for (int i = start; i < end; i++) {
            result[i] = v1[i] + v2[i];
        }
    };

    // Launch threads to perform vector addition in parallel
    std::vector<boost::thread> threads;
    int chunk_size = v.size() / num_threads;
    int remainder = v.size() % num_threads;
    int start = 0;
    int end = 0;

    for (int i = 0; i < num_threads; i++) {
        start = end;
        end += chunk_size;
        if (i == num_threads - 1) {
            end += remainder;
        }
        threads.emplace_back(vector_addition_thread, std::cref(v), std::cref(other),
                              std::ref(result), start, end);
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

}

template <typename T>
void vector_vector_add(const Vector<T>& v1, const Vector<T>& v2, Vector<T>& result)
{ 
    for (int i = 0; i < v1.size(); i++)
        {
            result[i] = v1[i] + v2[i];
        }
}


}
#endif