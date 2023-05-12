#ifndef PYCCANTE_PY_GAUSSIAN_2D_H
#define PYCCANTE_PY_GAUSSIAN_2D__H

#include "py_filter.h"
#include "support.h"
#include <GL/glew.h>
#include <piccante.hpp>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace py::literals;

void init_FilterGaussian2D(pybind11::module_& m);

#endif /* PYCCANTE_PY_GAUSSIAN_2D_*/