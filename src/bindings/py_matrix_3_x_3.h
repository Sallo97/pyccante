#ifndef PYCCANTE_MATRIX_3_x_3_H
#define PYCCANTE_MATRIX_3_x_3_H

#include <stdlib.h>
#include <GL/glew.h>
#include <piccante.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>
#include <pybind11/functional.h>

void init_Matrix_3_x_3(pybind11::module_& m);

#endif