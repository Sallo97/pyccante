// This file contains the binding of the Piccante's FilterMax filter class.


#include "py_filter_max.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the Image class to the passed module.
 */
void init_FilterMax(pybind11::module_& m)
{
    // Defines the Image class in the passed module.
    py::class_<pic::FilterMax, pic::Filter>(m, "FilterMax")

    // region Functions

    /**
     * @brief execute the FilterMax filter.
     * @param imgIn the source image.
     * @param size the size of the circular area where to apply the filter.
     * @return the filtered image.
     */
    .def_static
    (
        "execute",
        ([] (pic::Image* imgIn, int size)
        {
            return pic::FilterMax::execute(imgIn, NULL, size);
        }), 
        "execute FilterMax",
        py::return_value_policy::take_ownership,
        py::arg("imgIn"), py::arg("imgOut")
    );

    // endregion Functions

}