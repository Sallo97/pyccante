#ifndef PYCCANTE_PY_BBOX_H
#define PYCCANTE_PY_BBOX_H

#include <GL/glew.h>
#include <piccante.hpp>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace py::literals;

void init_BBox(pybind11::module_& m);

#endif /* PYCCANTE_PY_BBOX_H */