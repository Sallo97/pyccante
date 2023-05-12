#ifndef PYCCANTE_MAIN_CPP
#define PYCCANTE_MAIN_CPP

#include "bindings/py_dynamics_range.h"
#include "bindings/py_bbox.h"
#include "bindings/py_image.h"
#include "bindings/py_histogram.h"
#include "bindings/py_filter.h"
#include "bindings/py_filter_luminance.h"
#include "bindings/py_filter_bilateral_2df.h"
#include "bindings/py_filter_gaussian_2d.h"
#include "bindings/py_filter_rotation.h"

namespace py = pybind11;

// Creating the pyccante module
PYBIND11_MODULE(pyccante, m)
{
    init_LDR_type(m);           // LDR_type Enum
    init_BBox(m);               // BBox Class
    init_Image(m);              // Image Class 
    init_Histogram(m);          // Histogram Class
    init_Filter(m);             // Filter Class
    init_FilterLuminance(m);    // FilterLuminance sub-Class
    init_FilterBilateral2DF(m); // FilterBilateral2DF sub-Class
    init_FilterGaussian2D(m);   // FilterGaussian2D sub_Class
    init_FilterRotation(m);     // FilterRotation sub_Class

}

#endif /* PYCCANTE_MAIN_CPP */