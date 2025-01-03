#ifndef PYCCANTE_PY_HISTOGRAM_H
#define PYCCANTE_PY_HISTOGRAM_H

#include <piccante.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>
#include <pybind11/complex.h>
#include <pybind11/stl.h>
//#include <pybind11/complex.h>

namespace py = pybind11;
using namespace py::literals;

void init_Histogram(pybind11::module_& m);

#endif