#ifndef PYCCANTE_PY_FILTER_MED_H
#define PYCCANTE_PY_FILTER_MED_H

#include "py_filter.h"
#include <piccante.hpp>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace py::literals;

void init_FilterMed(pybind11::module_& m);

#endif /* PYCCANTE_PY_FILTER_MED_H */