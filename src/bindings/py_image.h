#ifndef PYCCANTE_PY_IMAGE_H
#define PYCCANTE_PY_IMAGE_H

#include <GL/glew.h>
#include <piccante.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>
#include <pybind11/functional.h>

void init_Image(pybind11::module_& m);

#endif