#ifndef PYCCANTE_PY_FILTER_WARP_2D_H
#define PYCCANTE_PY_FILTER_WARP_2D_H

#include "../py_filter.h"
#include <piccante.hpp>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace py::literals;

void init_FilterWarp2D(pybind11::module_& m);

#endif /* PYCCANTE_PY_FILTER_WARP_2D_H */