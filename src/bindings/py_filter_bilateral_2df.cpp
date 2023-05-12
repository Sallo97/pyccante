#include"py_filter_bilateral_2df.h"


void init_FilterBilateral2DF(pybind11::module_& m)
{
    // region FilterBilateral2DF

    py::class_<pic::FilterBilateral2DF, pic::Filter>(m, "FilterBilateral2DF")

    // region Constructor
    
    .def(py::init <>(),
        "FilterBilateral2DF")

    .def(py::init < float, float > (),
        "FilterBilateral2DF",
        py::arg("sigma_s"), py::arg("sigma_r"))

    // endregion

    // region Functions

    .def("signature", &pic::FilterBilateral2DF::signature,
        "signature")

    .def_static("execute", &pic::FilterBilateral2DF::execute,
        "execute");

    // endregions

    // endregion


}