#ifndef PYCCANTE_PY_ALGO_CONNECTED_COMPONENTS_H
#define PYCCANTE_PY_ALGO_CONNECTED_COMPONENTS_H

#include "../py_filter.h"
#include "../support.h"
#include <piccante.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

namespace py = pybind11;
using namespace py::literals;

void init_ConnectedComponents(pybind11::module_& m);

#endif /* PYCCANTE_PY_ALGO_CONNECTED_COMPONENTS_H */