#ifndef PYCCANTE_PY_DYNAMICS_RANGE_H
#define PYCCANTE_PY_DYNAMICS_RANGE_H

#include <GL/glew.h>
#include <piccante.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>

namespace py = pybind11;
using namespace py::literals;

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

#endif  /* PYCCANTE_PY_DYNAMICS_RANGE_H */