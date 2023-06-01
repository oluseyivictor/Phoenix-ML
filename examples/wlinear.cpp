#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <iostream>
#include "nn_interface.h"
#include "nnet/LinearRegression.h"
#include "Vector.hpp"

using namespace phoenix;
using namespace boost::python;
namespace np = boost::python::numpy;


void extract_matnum(const np::ndarray& m_values, Matrix<double>& arr1)
{
    if (m_values.get_nd() == 1)
        {
        arr1 = Matrix<double>(m_values.shape(0), 1);
        for (int i = 0; i < m_values.shape(0); i++) {
            arr1(i, 0) = boost::python::extract<double>(m_values[i]);
            }
        }
        else if (m_values.get_nd() == 2)
        {
          arr1 = Matrix<double>(m_values.shape(0), m_values.shape(1));  
          for (int i = 0; i < m_values.shape(0); i++) {
                for (int j = 0; j < m_values.shape(1); j++) {
                    arr1(i, j) = boost::python::extract<double>(m_values[i][j]);
                }
            }
        }
        else {
            std::cout << "Unsupported matrix dimension: " << m_values.get_nd() << std::endl;
        }
}



np::ndarray convert_matrix_to_numpy(const Matrix<double>& mat) {
    np::dtype dtype = np::dtype::get_builtin<double>();
    boost::python::tuple shape = boost::python::make_tuple(mat.getRows(), mat.getCols());
    np::ndarray np_array = np::empty(shape, dtype);

    double* np_data = reinterpret_cast<double*>(np_array.get_data());
    auto size = mat.getRows();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < mat.getCols(); j++) {
            np_data[i * mat.getCols() + j] = mat(i, j);
        }
    }

    return np_array;
}

class Wlinear
{
    public:
        Wlinear(const np::ndarray& values, const np::ndarray& malues) 
        : m_values(values), v_values(malues) {
                /*Generate Random data*/
    extract_matnum(values, X);
    extract_matnum(malues, y);

    std::cout<<X<<std::endl;
    std::cout<<y<<std::endl;

	/* Linear Model*/
	my_model = new LinearRegression(X, y);
     }

     ~Wlinear()
     {
        delete my_model;
     }

        void train(int epochs)
        {
            
            my_model->train(epochs);
        }

        np::ndarray predict(const np::ndarray& talues)
        {
           Matrix<double> arr1;
           extract_matnum(talues, arr1);
           auto y = convert_col(arr1, 0);
           predicted = my_model->predict(y);
           return convert_matrix_to_numpy(predicted);
        }

        void pprint(void)
        {
            std::cout<<predicted<<std::endl;
        }

    public:
        np::ndarray m_values;
        np::ndarray v_values;
        INeuralNetwork* my_model;
        Matrix<double> X;
        Matrix<double> y;
        Matrix<double> predicted;

};

BOOST_PYTHON_MODULE(calculator_module) {
    Py_Initialize();
    np::initialize();

    class_<Wlinear>("Wlinear", init<const np::ndarray&, const np::ndarray&>())
        .def("train", &Wlinear::train)
        .def("predict", &Wlinear::predict)
        .def("pprint", &Wlinear::pprint)
    ;
}