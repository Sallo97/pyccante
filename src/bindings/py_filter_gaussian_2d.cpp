#include "py_filter_gaussian_2d.h"

void init_FilterGaussian2D(pybind11::module_& m)
{
    // region FilterGaussian2D
    py::class_<pic::FilterGaussian2D, pic::Filter>(m, "FilterGaussian2D")

    // region Constructors
    
    .def(py::init <> (),
        "FilterGaussian2D")

    .def(py::init <float> (),
        "FilterGaussian2D")

    // endregion

    // region Functions

    .def("update", &pic::FilterGaussian2D::update,
        "update",
        py::arg("sigma"))

    .def_static("execute", &pic::FilterGaussian2D::execute,
        "execute",
        py::arg("imgIn"), py::arg("imgOut"), py::arg("sigma"));

    // endregion

    // endregion

}