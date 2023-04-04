#pragma once

#include <boost/thread.hpp>
#include "Matrix.hpp"

using namespace phoenix;

template <typename T>
void matrix_vector_multiply_thread(const Matrix<T> &m2, const Vector<T> &v1,
                                   Vector<T> &result, std::size_t row_start, std::size_t row_end);
template <typename T>
void matrix_vector_multiply(const Matrix<T> &m2, const Vector<T> &v1, Vector<T> &result, std::size_t num_threads);
template <typename T>
void matrix_vector_multiply(const Matrix<T> &m2, const Vector<T> &v1, Vector<T> &result);
template <typename T>
void vector_vector_add(const Vector<T> &v1, const Vector<T> &v2, Vector<T> &result);
template <typename T>
void vector_vector_add(const Vector<T> &v1, const Vector<T> &v2, Vector<T> &result, int num_threads);
template <typename T>
void vector_addition_thread(const Vector<T> &v1, const Vector<T> &v2, Vector<T> &result, int start, int end);

/**
 * Multiplies a matrix and a vector in a specified range of rows using multiple threads.
 *
 * @param m2 The matrix to multiply.
 * @param v1 The vector to multiply.
 * @param result The resulting vector.
 * @param row_start The index of the first row to multiply.
 * @param row_end The index of the last row to multiply.
 * @tparam T The type of the elements in the matrix and vector.
 */
template <typename T>
void matrix_vector_multiply_thread(const Matrix<T> &m2, const Vector<T> &v1,
                                   Vector<T> &result, std::size_t row_start, std::size_t row_end)
{
    for (std::size_t k = row_start; k < row_end; ++k)
    {
        T sum = 0;
        for (std::size_t i = 0; i < v1.getRows(); ++i)
        {
            sum += v1[i] * m2(k, i);
        }
        result[k] = sum;
    }
}

/**
 * Multiplies a matrix and a vector using a specified number of threads.
 *
 * @param m2 The matrix to multiply.
 * @param v1 The vector to multiply.
 * @param result The resulting vector.
 * @param num_threads The number of threads to use.
 * @tparam T The type of the elements in the matrix and vector.
 */
template <typename T>
void matrix_vector_multiply(const Matrix<T> &m2, const Vector<T> &v1, Vector<T> &result, std::size_t num_threads)
{

    std::vector<boost::thread> threads(num_threads);

    std::size_t rows_per_thread = m2.getRows() / num_threads;

    for (std::size_t i = 0; i < num_threads; ++i)
    {
        std::size_t row_start = i * rows_per_thread;
        std::size_t row_end = (i == num_threads - 1) ? m2.getRows() : (i + 1) * rows_per_thread;
        threads[i] = boost::thread(matrix_vector_multiply_thread<T>, std::cref(m2), std::cref(v1),
                                   std::ref(result), row_start, row_end);
    }

    for (auto &thread : threads)
    {
        thread.join();
    }
}

/**
 * Multiplies a matrix and a vector using a single thread.
 *
 * @param m2 The matrix to multiply.
 * @param v1 The vector to multiply.
 * @param result The resulting vector.
 * @tparam T The type of the elements in the matrix and vector.
 */
template <typename T>
void matrix_vector_multiply(const Matrix<T> &m2, const Vector<T> &v1, Vector<T> &result)
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

/**
 * Adds two vectors together in a specified range of indices using a single thread.
 *
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @param result The resulting vector.
 * @param start The index of the first element to add.
 * @param end The index of the last element to add.
 * @tparam T The type of the elements in the vectors.
 */
template <typename T>
void vector_addition_thread(const Vector<T> &v1, const Vector<T> &v2, Vector<T> &result, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        result[i] = v1[i] + v2[i];
    }
}

/**
 * Adds two vectors together using a specified number of threads.
 *
 * @param v1 The first vector.
 * @param other The second vector.
 * @param result The resulting vector.
 * @param num_threads The number of threads to use.
 * @tparam T The type of the elements in the vectors.
 */
template <typename T>
void vector_vector_add(const Vector<T> &v, const Vector<T> &other, Vector<T> &result, int num_threads)
{

    // Define the thread function for vector addition
    auto vector_addition_thread = [](const Vector<T> &v1, const Vector<T> &v2, Vector<T> &result, int start, int end)
    {
        for (int i = start; i < end; i++)
        {
            result[i] = v1[i] + v2[i];
        }
    };

    // Launch threads to perform vector addition in parallel
    std::vector<boost::thread> threads;
    int chunk_size = v.size() / num_threads;
    int remainder = v.size() % num_threads;
    int start = 0;
    int end = 0;

    for (int i = 0; i < num_threads; i++)
    {
        start = end;
        end += chunk_size;
        if (i == num_threads - 1)
        {
            end += remainder;
        }
        threads.emplace_back(vector_addition_thread, std::cref(v), std::cref(other),
                             std::ref(result), start, end);
    }

    // Wait for all threads to finish
    for (auto &thread : threads)
    {
        thread.join();
    }
}

/**
 * Adds two vectors together.
 *
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @param result The resulting vector.
 * @tparam T The type of the elements in the vectors.
 */
template <typename T>
void vector_vector_add(const Vector<T> &v1, const Vector<T> &v2, Vector<T> &result)
{
    for (int i = 0; i < v1.size(); i++)
    {
        result[i] = v1[i] + v2[i];
    }
}
