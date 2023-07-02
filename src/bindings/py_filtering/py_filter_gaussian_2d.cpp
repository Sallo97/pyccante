// This file contains the binding of the Piccante's FilterGaussian2D filter class


#include "py_filter_gaussian_2d.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the FilterGaussian2D filter class to the passed module.
 */
void init_FilterGaussian2D(pybind11::module_& m)
{
    // Defines the FilterGaussian2D filter class in the passed module.
    py::class_<pic::FilterGaussian2D, pic::Filter>(m, "FilterGaussian2D")

    // region Functions
    
    /**
     * @brief execute the FilterGaussian2D filter to the image.
     * @param imgIn the source image.
     * @param sigma is the value for applying the gaussian function to the image.
     * @return the resulting image.
     */
    .def_static("execute", ([] (pic::Image* imgIn, float sigma)
        {
            return pic::FilterGaussian2D::execute(imgIn, NULL, sigma);
        }),
        "execute FilterGaussian2D",
        py::return_value_policy::take_ownership,
        py::arg("imgIn"), py::arg("sigma"));

    // endregion Functions

}