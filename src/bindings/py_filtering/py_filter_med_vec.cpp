// This file contains the binding of the Piccante's Image class.


#include "py_filter_med_vec.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the FilterMedVec filter class to the passed module.
 */
void init_FilterMedVec(pybind11::module_& m)
{
    // Defines the FilterMedVec class in the passed module.
    py::class_<pic::FilterMedVec, pic::Filter>(m, "FilterMedVec")

    // region Functions

    /**
     * @brief execute the FilterMedVec filter.
     * @param imgIn the source image.
     * @param size the size of the circular area where to apply the filter.
     * @return the filtered image.
     */
    .def_static
    (
        "execute",
        ([] (pic::Image* imgIn, int size)
        {
            return pic::FilterMedVec::execute(imgIn, NULL, size);
        }), 
        "execute FilterMedVec",
        py::return_value_policy::take_ownership,
        py::arg("imgIn"), py::arg("imgOut")
    );

    // endregion
}