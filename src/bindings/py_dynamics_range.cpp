// This file contains the binding of the Piccante's LDR_type enum class.


#include "py_dynamics_range.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

/**
 * @brief binds the LDR_type enum class to the passed module.
 */
void init_LDR_type(pybind11::module_& m)
{
    // Defines the LDR_type class in the passed module.
    py::enum_<pic::LDR_type>(m, "LDR_type")
        .value("LT_NOR", pic::LDR_type::LT_NOR)
        .value("LT_NOR_GAMMA", pic::LDR_type::LT_NOR_GAMMA)
        .value("LT_LDR", pic::LDR_type::LT_LDR)
        .value("LT_NONE", pic::LDR_type::LT_NONE);

}