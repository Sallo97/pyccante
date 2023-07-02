// This file contains the binding of the Piccante's Image class.


#include "py_filter_simple_tmo.h"

//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the FilterSimpleTMO filter class to the passed module.
 */
void init_FilterSimpleTMO(pybind11::module_& m)
{
   // Defines the FilterSimpleTMO filter class in the passed module.
   py::class_<pic::FilterSimpleTMO, pic::Filter>(m, "FilterSimpleTMO")

   // region Functions
    
    /**
     * @brief execute the FilterSimpleTMO filter.
     * @param imgIn the source image.
     * @param gamma the gamma value to apply to the image.
     * @param fstop the exposure value to apply to the image.
     * @return the filtered image.
     */
    .def_static("execute",
                ([] (pic::Image* imgIn, float gamma, float fstop)
                {
                    return pic::FilterSimpleTMO::execute(imgIn, NULL, gamma, fstop);

                }),
                "executing FilterSimpleTMO",
                py::return_value_policy::take_ownership,
                py::arg("imgIn"), py::arg("gamma"),
                py::arg("fstop"));

   // endregion
}