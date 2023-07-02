// This header contains the definitions of function used 

#ifndef PYCCANTE_SUPPORT_H
#define PYCCANTE_SUPPORT_H

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

py::array_t<float> return_float_NumPy(float* ptr,uint size);



#endif /* support.h*/