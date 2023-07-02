// This file contains the binding of the Piccante's FilterMed filter class.


#include "py_filter_med.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the FilterMed filter class to the passed module.
 */
void init_FilterMed(pybind11::module_& m)
{

    // Defines the Image class in the passed module.
    py::class_<pic::FilterMed, pic::Filter>(m, "FilterMed")

    // region Functions

    /**
     * @brief execute the FilterMed filter.
     * @param imgIn the source image.
     * @param size the size of the circular area where to apply the filter.
     * @return the filtered image.
     */
    .def_static
    (
        "execute",
        ([] (pic::Image* imgIn, int size)
        {
            return pic::FilterMed::execute(imgIn, NULL, size);
        }), 
        "execute FilterMed",
        py::return_value_policy::take_ownership,
        py::arg("imgIn"), py::arg("imgOut")
    );

    // endregion

}