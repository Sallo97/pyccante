#include "py_filter_gaussian_2d.h"

void init_FilterGaussian2D(pybind11::module_& m)
{
    // region FilterGaussian2D
    py::class_<pic::FilterGaussian2D, pic::Filter>(m, "FilterGaussian2D")

    // region Constructors
    
    .def(py::init <> (),
        "FilterGaussian2D constructor")

    .def(py::init <float> (),
        "FilterGaussian2D constructor",
        py::arg("sigma"))

    // endregion

    // region Functions
    
    .def_static("execute", ([] (pic::Image* imgIn, float sigma)
        {
            return pic::FilterGaussian2D::execute(imgIn, NULL, sigma);
        }),
        "execute FilterGaussian2D",
        py::arg("imgIn"), py::arg("sigma"));

    // endregion

    // endregion

}