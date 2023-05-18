#ifndef PYCCANTE_PY_CONV_2D_H
#define PYCCANTE_PY_CONV_2D_H

#include "../py_filter.h"
#include "../support.h"
#include <piccante.hpp>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace py::literals;

void init_FilterConv2D(pybind11::module_& m);

#endif /* PYCCANTE_PY_CONV_2D */