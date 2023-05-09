#ifndef PYCCANTE_PY_DYNAMICS_RANGE_H
#define PYCCANTE_PY_DYNAMICS_RANGE_H

#include <GL/glew.h>
#include <piccante.hpp>
#include <pybind11/pybind11.h>


namespace py = pybind11;
using namespace py::literals;

void init_LDR_type(pybind11::module_& m);

#endif  /* PYCCANTE_PY_DYNAMICS_RANGE_H */