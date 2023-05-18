#include "py_ward_histogram_tmo.h"

void init_WardHistogramTMO(pybind11::module_& m)
{
    py::class_<pic::WardHistogramTMO, pic::ToneMappingOperator>(m, "WardHistogramTMO")
    
    // region Constructor

    .def(py::init<int, float, float, bool>(),
        "WardHistogramTMO constructor",
        py::arg("nBin")=256, py::arg("LdMin")=1.0f,
        py::arg("LdMax")=100.0f, py::arg("bCeiling")=true)
    
    .def_static("execute", &pic::WardHistogramTMO::execute,
        "execute the WardHistogramTMO tone-mapping",
        py::arg("imgIn"), py::arg("imgOut"))
    
    .def_static
    (
        "execute",
        ([] (pic::Image* imgIn)
        {
            return pic::WardHistogramTMO::execute(imgIn, NULL);
        }),
        "execute the WardHistogramTMO tone-mapping",
        py::arg("imgIn")
    );
    
    // endregion
}
