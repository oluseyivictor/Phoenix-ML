#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <iostream>
#include "Vector.hpp"

using namespace phoenix;

class MyClass {
public:
    MyClass(const Matrix<double>& values, const Matrix<double>& val)
        : m_values(values), m_val(val) {}

    void print_values1() const {
        
        std::cout << m_values << std::endl;
    }
    void print_values2() const {
        
        std::cout << m_val << std::endl;
    }

private:
    Matrix<double> m_values;
    Matrix<double> m_val;
};

using namespace boost::python;
namespace np = boost::python::numpy;

void extract_matnum(const np::ndarray& m_values, const np::ndarray& m_malues, Matrix<double>& arr1, Matrix<double>& arr2)
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

    
    if (m_malues.get_nd() == 1)
        {
        arr2 = Matrix<double>(m_malues.shape(0), 1);
        for (int i = 0; i < m_malues.shape(0); i++) {
            arr2(i, 0) = boost::python::extract<double>(m_malues[i]);
            }
        }
        else if (m_malues.get_nd() == 2)
        {
          arr2 = Matrix<double>(m_malues.shape(0), m_malues.shape(1));  
          for (int i = 0; i < m_malues.shape(0); i++) {
                for (int j = 0; j < m_malues.shape(1); j++) {
                    arr2(i, j) = boost::python::extract<double>(m_malues[i][j]);
                }
            }
        }
        else {
            std::cout << "Unsupported matrix dimension: " << m_values.get_nd() << std::endl;
        }

}

class MyClassWrapper {
public:
    MyClassWrapper(const np::ndarray& values, const np::ndarray& malues) 
        : m_values(values), v_values(malues) {
        
        extract_matnum(values, malues, arr1, arr2);

       
        my_class = new MyClass(arr1, arr2);
    }

    ~MyClassWrapper() {
        // Delete the object of the first class in the destructor of the second class
        delete my_class;
    }

    void print_value1() {
        
        my_class->print_values1();
    }

    void print_value2() {
        
        my_class->print_values2();
    }

private:
    np::ndarray m_values;
    np::ndarray v_values;
    MyClass* my_class;
    Matrix<double> arr1;
    Matrix<double> arr2;
};

class SecClassWrapper {
public:
    SecClassWrapper(const np::ndarray& values, const np::ndarray& malues) 
        : m_values(values), v_values(malues) {
        
        extract_matnum(values, malues, arr1, arr2);

       
        my_class = new MyClass(arr1, arr2);
    }

    ~SecClassWrapper() {
        // Delete the object of the first class in the destructor of the second class
        delete my_class;
    }

    void print_value1() {
        
        my_class->print_values1();
    }

    void print_value2() {
        
        my_class->print_values2();
    }

private:
    np::ndarray m_values;
    np::ndarray v_values;
    MyClass* my_class;
    Matrix<double> arr1;
    Matrix<double> arr2;
};

BOOST_PYTHON_MODULE(calculator_module) {
    Py_Initialize();
    np::initialize();

    class_<MyClassWrapper>("MyClass", init<const np::ndarray&, const np::ndarray&>())
        .def("print_values", &MyClassWrapper::print_value1)
    ;

    class_<SecClassWrapper>("SecClass", init<const np::ndarray&, const np::ndarray&>())
        .def("print_value1", &SecClassWrapper::print_value1)
        .def("print_value2", &SecClassWrapper::print_value2)
    ;
}