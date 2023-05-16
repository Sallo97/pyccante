#ifndef PYCCANTE_PY_FILTER_BILATERAL_2DS_H
#define PYCCANTE_PY_FILTER_BILATERAL_2DS_H

#include "py_filter.h"
#include <piccante.hpp>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace py::literals;

void init_FilterBilateral2DS(pybind11::module_& m);

#endif /* PYCCANTE_PY_FILTER_BILATERAL_2DS_H */