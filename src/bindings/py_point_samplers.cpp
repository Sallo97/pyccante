// This file contains the binding of the Piccante's SAMPLER_TYPE enum class.


#include "py_point_samplers.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the SAMPLER_TYPE enum class to the passed module.
 */
void init_SAMPLER_TYPE(pybind11::module_& m)
{
    // Defines the LDR_type class in the passed module.
    py::enum_<pic::SAMPLER_TYPE>(m,"SAMPLER_TYPE")
        .value("ST_BRIDSON", pic::SAMPLER_TYPE::ST_BRIDSON)
        .value("ST_DARTTHROWING", pic::SAMPLER_TYPE::ST_DARTTHROWING)
        .value("ST_PATTERN", pic::SAMPLER_TYPE::ST_PATTERN)
        .value("ST_MONTECARLO", pic::SAMPLER_TYPE::ST_MONTECARLO)
        .value("ST_MONTECARLO_S", pic::SAMPLER_TYPE::ST_MONTECARLO_S);
}
