#include "bindings/py_image.hpp"
#include "bindings/py_histogram.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>

namespace py = pybind11;

// Creating the pyccante module
PYBIND11_MODULE(pyccante, m)
{
    // binding all the the classes in the module
    pyccante::bind_Image(m);        //Image Class 
    pyccante::bind_Histogram(m);    //Histogram Class
}