// This file contains the binding of the Piccante's FilterMin filter class.


#include "py_filter_min.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the FilterMin filter class to the passed module.
 */
void init_FilterMin(pybind11::module_& m)
{

    // Defines the Image class in the passed module.
    py::class_<pic::FilterMin, pic::Filter>(m, "FilterMin")

    // region Functions

    /**
     * @brief execute the FilterMin filter.
     * @param imgIn the source image.
     * @param size the size of the circular area where to apply the filter.
     * @return the filtered image.
     */
    .def_static
    (
        "execute",
        ([] (pic::Image* imgIn, int size)
        {
            return pic::FilterMin::execute(imgIn, NULL, size);
        }), 
        "execute FilterMin",
        py::return_value_policy::take_ownership,
        py::arg("imgIn"), py::arg("imgOut")
    );

    // endregion

}