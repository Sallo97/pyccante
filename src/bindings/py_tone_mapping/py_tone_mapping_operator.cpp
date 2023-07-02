// This file contains the binding of the piccante's ToneMappingOperator base class


#include "py_tone_mapping_operator.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the ToneMappingOperator class to the passed module.
 */
void init_ToneMappingOperator(pybind11::module_& m)
{
    // Defines the ToneMappingOperator class in the passed module.
    py::class_<pic::ToneMappingOperator>(m, "ToneMappingOperator");

}