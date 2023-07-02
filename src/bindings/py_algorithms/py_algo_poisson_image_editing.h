#ifndef PYCCANTE_PY_ALGO_POISSON_IMAGE_EDITING_H
#define PYCCANTE_PY_ALGO_POISSON_IMAGE_EDITING_H

#include "../py_filter.h"
#include "../support.h"
#include <piccante.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

namespace py = pybind11;
using namespace py::literals;

void init_computePoissonImageEditing(pybind11::module_& m);

#endif /* PYCCANTE_PY_ALGO_POISSON_IMAGE_EDITING_H */