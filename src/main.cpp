#ifndef PYCCANTE_MAIN_CPP
#define PYCCANTE_MAIN_CPP

#include "bindings/py_bbox.h"
#include "bindings/py_image.h"
#include "bindings/py_histogram.h"


namespace py = pybind11;

// Creating the pyccante module
PYBIND11_MODULE(pyccante, m)
{
    // binding all the the classes in the module
    init_BBox(m);
    init_Image(m);        //Image Class 
    init_Histogram(m);    //Histogram Class
}

#endif /* PYCCANTE_MAIN_CPP */