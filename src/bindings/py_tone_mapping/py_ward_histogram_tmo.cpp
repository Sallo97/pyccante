// This file contains the binding of the Piccante's WardHistogramTMO base class


#include "py_ward_histogram_tmo.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the WardHistogramTMO class to the passed module.
 */
void init_WardHistogramTMO(pybind11::module_& m)
{
    py::class_<pic::WardHistogramTMO, pic::ToneMappingOperator>(m, "WardHistogramTMO")
    
    // region Methods
    
    /**
     * @brief execute the Ward Tone Mapping
     * @param imgIn the HDR source image.
     * @return a compressed SDR image.
     */
    .def_static
    (
        "execute",
        ([] (pic::Image* imgIn)
        {
            return pic::WardHistogramTMO::execute(imgIn, NULL);
        }),
        "execute the WardHistogramTMO tone-mapping",
        py::return_value_policy::take_ownership,
        py::arg("imgIn")
    );
    
    // endregion Methods
}
