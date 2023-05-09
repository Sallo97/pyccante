// This header contains function used across all the binding files.

#ifndef PYCCANTE_SUPPORT_H
#define PYCCANTE_SUPPORT_H

#include <GL/glew.h>
#include <piccante.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>
#include <pybind11/functional.h>

namespace py = pybind11;

float* return_float_ptr(py::buffer data_buffer);

py::buffer return_numpy_array (float* float_array);

#endif /* support.h*/