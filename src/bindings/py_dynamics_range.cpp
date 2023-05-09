#include "py_dynamics_range.h"

void init_LDR_type(pybind11::module_& m)
{
    // region LDR_type
    py::enum_<pic::LDR_type>(m, "LDR_type")
        .value("LT_NOR", pic::LDR_type::LT_NOR)
        .value("LT_NOR_GAMMA", pic::LDR_type::LT_NOR_GAMMA)
        .value("LT_LDR", pic::LDR_type::LT_LDR)
        .value("LT_NONE", pic::LDR_type::LT_NONE);

    // endregion
}