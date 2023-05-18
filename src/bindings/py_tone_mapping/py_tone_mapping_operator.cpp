#include "py_tone_mapping_operator.h"

void init_ToneMappingOperator(pybind11::module_& m)
{
    py::class_<pic::ToneMappingOperator>(m, "ToneMappingOperator");

}