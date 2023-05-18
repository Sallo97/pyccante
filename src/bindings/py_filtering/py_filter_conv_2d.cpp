#include "py_filter_conv_2d.h"

void init_FilterConv2D(pybind11::module_& m)
{
    // region FilterConv2D

    py::class_<pic::FilterConv2D, pic::Filter>(m, "FilterConv2D")

    // region Constructors

    .def(py::init<> (),
        "FilterConv2D constructor")

    // endregion

    // region Functions

    .def_static("execute", &pic::FilterConv2D::execute,
                "execute FilterConv2D",
                py::arg("img"), py::arg("conv"), 
                py::arg("imgOut"))
    
    .def_static("execute", ([](pic::Image* img, pic::Image* conv)
        {
            return pic::FilterConv2D::execute(img, conv, NULL);
        }),
        "execute FilterConv2D",
        py::arg("img"), py::arg("conv")
    );

    // endregion

    // endregion



}