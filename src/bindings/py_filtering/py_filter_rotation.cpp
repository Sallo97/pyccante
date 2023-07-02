// This file contains the binding of the Piccante's FilterRotation filter class.


#include "py_filter_rotation.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

/**
 * @brief binds the FilterRotationfilter class to the passed module.
 */
void init_FilterRotation(pybind11::module_& m)
{
    // Defines the FilterRotation filter class in the passed module.
    py::class_<pic::FilterRotation, pic::Filter>(m, "FilterRotation")

    // region Methods

    /**
     * @brief execute rotates the given image by the X,Y, and Z axis.
     * @param imgIn is the source image.
     * @param angleX is the radian value the X axis will be rotated.
     * @param angleY is the radian value the Y axis will be rotated.
     * @param angleZ is the radian value the Z axis will be rotated.
     * @return imgIn rotated by the given values.
     */

    .def_static
    (
        "execute",
        ([] (pic::Image* imgIn, float angleX, float angleY, float angleZ)
        
        {
            return pic::FilterRotation::execute(imgIn, NULL, angleX,
                                                angleY, angleZ);
        }),
        "execute FilterRotation",
        py::return_value_policy::take_ownership,
        py::arg("imgIn"), py::arg("angleX"),
        py::arg("angleY"), py::arg("angleZ")
    )

    /**
     * @brief execute rotates the given image by the X,Y, and Z axis.
     * @param imgIn is the source image.
     * @param mtx is a matrix 3by3.
     * @return imgIn rotated by the given values.
     */
    .def_static
    (
        "execute",
        ([] (pic::Image* imgIn, Eigen::Matrix3f& mtx)
        {
            return pic::FilterRotation::execute(imgIn, NULL, mtx);
        }),
        "execute FilterRotation",
        py::return_value_policy::take_ownership,
        py::arg("imgIn"), py::arg("mtx")
    );

    // endregion Methods
}