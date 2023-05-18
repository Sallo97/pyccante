#ifndef PYCCANTE_PY_FILTER_MEAN_H
#define PYCCANTE_PY_FILTER_MEAN_H

#include "../py_filter.h"
#include <piccante.hpp>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace py::literals;

void init_FilterMean(pybind11::module_& m);

#endif /* PYCCANTE_PY_FILTER_MEAN_H */