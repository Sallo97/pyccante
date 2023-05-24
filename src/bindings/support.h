// This header contains function used across all the binding files.

#ifndef PYCCANTE_SUPPORT_H
#define PYCCANTE_SUPPORT_H

#include <GL/glew.h>
#include <piccante.hpp>
#include "support.h"
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>
#include <pybind11/functional.h>

namespace py = pybind11;

bool* return_bool_ptr (py::buffer data_buffer);


float* return_float_ptr (py::buffer data_buffer);

uint* return_uint_ptr(py::buffer data_buffer);

py::buffer return_numpy_array (float* float_array);

py::buffer return_bool_array (bool* bool_buffer);

py::buffer return_uint_array (uint* uint_array);

#endif /* support.h*/