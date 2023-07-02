// This file contains the binding of the Piccante's base Filter class.


#include "py_filter.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the Filter class to the passed module.
 */
void init_Filter(pybind11::module_& m)
{
    // Defines the Image class in the passed module.
    py::class_<pic::Filter>(m, "Filter");

}