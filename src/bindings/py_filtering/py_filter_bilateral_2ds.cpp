// This file contains the binding of the Piccante's FilterBilateral2DS classW

#include "py_filter_bilateral_2ds.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


void init_FilterBilateral2DS(pybind11::module_& m)
{
    // Defining the FilterBilateral2DS class to the passed module
    py::class_<pic::FilterBilateral2DS, pic::Filter>(m, "FilterBilateral2DS")

    // region Constructor

    // region Functions

    /**
     * @brief execute the FilterBilateral2DS
     * @param imgIn
     * @param sigma_s
     * @param sigma_r
     * @return the filtered image
     */
    .def_static(
        "execute",
        ([] (pic::Image* imgIn, float sigma_s,
            float sigma_r)
        {
            return pic::FilterBilateral2DS::execute(imgIn, sigma_s, sigma_r);
        }),
        "execute FilterBilateral2DS",
        py::return_value_policy::take_ownership,
        py::arg("imgIn"), py::arg("sigma_s"),
        py::arg("sigma_r")
    )


    /**
     * @brief execute the FilterBilateral2DS
     * @param imgIn
     * @param imgEdge
     * @param sigma_s
     * @param sigma_r
     * @return the filtered image
     */
    .def_static(
        "execute",
        ([] (pic::Image* imgIn, pic::Image* imgEdge,
            float sigma_s, float sigma_r)
        {
            return pic::FilterBilateral2DS::execute(imgIn, imgEdge, sigma_s,
                                                     sigma_r);
        }),
        "execute FilterBilateral2DS",
        py::return_value_policy::take_ownership,
        py::arg("imgIn"), py::arg("imgEdge"),
        py::arg("sigma_s"), py::arg("sigma_r")
    );

    // endregion Functions
}