#ifndef PYCCANTE_MAIN_CPP
#define PYCCANTE_MAIN_CPP

#include "bindings/py_dynamics_range.h"
#include "bindings/py_bbox.h"
#include "bindings/py_image.h"
#include "bindings/py_histogram.h"


namespace py = pybind11;

// Creating the pyccante module
PYBIND11_MODULE(pyccante, m)
{
    init_LDR_type(m);     // LDR_type Enum
    init_BBox(m);         // BBox Class
    init_Image(m);        // Image Class 
    init_Histogram(m);    // Histogram Class
}

#endif /* PYCCANTE_MAIN_CPP */