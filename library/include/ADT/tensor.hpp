/**
 * @file matrix.h
 * @brief This file contains the declaration of the Matrix class.
 */

#ifndef TENSOR_H
#define TENSOR_H


#include "Matrix.hpp"

namespace phoenix {
/**

    @brief A template class representing a Tensor, which is a collection of Matrix objects
    @tparam T the type of data stored in the tensor
**/

template <typename T>
class Tensor
{
public:
  /*
     @brief Constructs a new empty Tensor object
  */
  Tensor(){};

  /**
      @brief Adds a new Matrix to the Tensor
      @param m the Matrix to be added
  */
  void addMatrix(const Matrix<T> &m)
  {
    matrices_.push_back(m);
  }

  /**
      @brief Prints all the Matrix object in the Tensor
  */
  void print()
  {
    for (int i = 0; i < this->size(); i++)
      std::cout << matrices_[i] << std::endl;
  }

  /**
      @brief Returns the Matrix at the given index in the Tensor
      @param r the index of the Matrix to be returned
      @return Matrix<T>& a reference to the Matrix at the given index
  */
  Matrix<T> &operator[](int r) { return matrices_.at(r); }

  /**
      @brief Returns the number of Matrices in the Tensor
      @return int the number of Matrices in the Tensor
  */
  int size() { return matrices_.size(); }

private:
  std::vector<Matrix<T>> matrices_;
};
}

#endif