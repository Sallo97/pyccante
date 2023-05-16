#include "py_point_samplers.h"

void init_SAMPLER_TYPE(pybind11::module_& m)
{
    py::enum_<pic::SAMPLER_TYPE>(m,"SAMPLER_TYPE")
        .value("ST_BRIDSON", pic::SAMPLER_TYPE::ST_BRIDSON)
        .value("ST_DARTTHROWING", pic::SAMPLER_TYPE::ST_DARTTHROWING)
        .value("ST_PATTERN", pic::SAMPLER_TYPE::ST_PATTERN)
        .value("ST_MONTECARLO", pic::SAMPLER_TYPE::ST_MONTECARLO)
        .value("ST_MONTECARLO_S", pic::SAMPLER_TYPE::ST_MONTECARLO_S);
}
