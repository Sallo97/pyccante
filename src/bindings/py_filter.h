#ifndef PYCCANTE_PY_FILTER_H
#define PYCCANTE_PY_FILTER_H

#include <piccante.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/functional.h>


namespace py = pybind11;
using namespace py::literals;

void init_Filter(pybind11::module_& m);

#endif /* PYCCANTE_PY_FILTER*/