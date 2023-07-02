// This file contains the binding of the Piccante's FilterConv2D filter class

#include "py_filter_conv_2d.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the FilterConv2D class to the passed module.
 */
void init_FilterConv2D(pybind11::module_& m)
{
    // Defining the FilterConv2D class in pyccante.
    py::class_<pic::FilterConv2D, pic::Filter>(m, "FilterConv2D")

    // region Constructors

    /**
     * @brief execute
     * @param img
     * @param conv
     * @param imgOut
     * @return
     */
    .def_static("execute", ([](pic::Image* img, pic::Image* conv)
        {
            return pic::FilterConv2D::execute(img, conv, NULL);
        }),
        "execute FilterConv2D",
        py::return_value_policy::take_ownership,
        py::arg("img"), py::arg("conv")
    );

    // endregion Functions

}