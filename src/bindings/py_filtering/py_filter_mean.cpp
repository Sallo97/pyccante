// This file contains the binding of the Piccante's FilterMean filter class.


#include "py_filter_mean.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the FilterMean filter class to the passed module.
 */
void init_FilterMean(pybind11::module_& m)
{
    // Defines the Image class in the passed module.
    py::class_<pic::FilterMean, pic::Filter>(m, "FilterMean")

    // region Functions

    /**
     * @brief execute the FilterMean filter.
     * @param imgIn the source image.
     * @param size the size of the circular area where to apply the filter.
     * @return the filtered image.
     */
    .def_static
    (
        "execute",
        ([] (pic::Image* imgIn, int size)
        {
            return pic::FilterMean::execute(imgIn, NULL, size);
        }), 
        "execute FilterMean",
        py::return_value_policy::take_ownership,
        py::arg("imgIn"), py::arg("imgOut")
    );

    // endregion Functions
} 