#ifndef PYCCANTE_PY_TONE_MAPPING_OPERATOR_H
#define PYCCANTE_PY_TONE_MAPPING_OPERATOR_H

#include "../py_filter.h"
#include "../support.h"
#include <GL/glew.h>
#include <piccante.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
namespace py = pybind11;
using namespace py::literals;

void init_ToneMappingOperator(pybind11::module_& m);

#endif /* PYCCANTE_PY_TONE_MAPPING_OPERATOR_H */
