#ifndef PYCCANTE_PY_HISTOGRAM_H
#define PYCCANTE_PY_HISTOGRAM_H

#include <GL/glew.h>
#include <piccante.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>

namespace py = pybind11;
using namespace py::literals;



void init_Histogram(pybind11::module_& m)
{
    // region VALUE_SPACE

    py::enum_<pic::VALUE_SPACE>(m, "VALUE_SPACE")
        .value("VS_LDR", pic::VALUE_SPACE::VS_LDR)
        .value("VS_LIN", pic::VALUE_SPACE::VS_LIN)
        .value("VS_LOG_2", pic::VALUE_SPACE::VS_LOG_2)
        .value("VS_LOG_E", pic::VALUE_SPACE::VS_LOG_E)
        .value("VS_LOG_10", pic::VALUE_SPACE::VS_LOG_10);

    // endregion

    // region Constructors

    py::class_<pic::Histogram>(m, "Histogram")
        .def(py::init<>())

        .def(py::init( [](pic::Image *imgIn, pic::VALUE_SPACE type,
                                         int nBin, int channel = 0)
        {
            return new pic::Histogram(imgIn, type, nBin, channel);
        }
        ), py::arg("imgIn"), py::arg("type"), py::arg("nBin"), py::arg("channel")=0)


    // endregion

    // region Destructors

    // remember to add the Destructor
    
    // endregion

    // region Functions

        .def("release", &pic::Histogram::release);
    // endregion


}



#endif /* PYCCANTE_PY_HISTOGRAM_H */