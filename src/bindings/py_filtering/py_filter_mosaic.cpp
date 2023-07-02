// This file contains the binding of the Piccante's FilterMosaic filter class.


#include "py_filter_mosaic.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the FilterMosaic filter class to the passed module.
 */
void init_FilterMosaic(pybind11::module_& m)
{

    // Defines the FilterMosaic filter class in the passed module.
    py::class_<pic::FilterMosaic, pic::Filter>(m, "FilterMosaic")

    // region Functions

    /**
     * @brief execute FilterMosaic.
     * @param imgIn the source image
     * @return the filtered image.
     */
    .def_static("execute", ([](pic::Image* imgIn)
        {
            return pic::FilterMosaic::execute(imgIn, NULL);
        }),
        "execute FilterMosaic",
        py::return_value_policy::take_ownership,
        py::arg("imgIn")
        );

    // endregion Functions

}