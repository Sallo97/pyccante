#ifndef PYCCANTE_PY_ALGO_HDR_MERGER_H
#define PYCCANTE_PY_ALGO_HDR_MERGER_H

#include "../py_filter.h"
#include "../support.h"
#include <piccante.hpp>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace py::literals;

void init_HDRMerger(pybind11::module_& m);

#endif /* PYCCANTE_PY_ALGO_HDR_MERGER_H */