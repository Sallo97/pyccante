// This file contains the binding of the piccante's DurandTMO tone_mapper class


#include "py_durand_tmo.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


void init_DurandTMO(pybind11::module_& m)
{
    // Defines the Image class in the passed module.
    py::class_<pic::DurandTMO, pic::ToneMappingOperator>(m, "DurandTMO")

    // region Methods

    /**
     * @brief execute the Durand Tone Mapping
     * @param imgIn the HDR source image.
     * @return a compressed SDR image.
     */
    .def_static
    (
        "execute", 
        ([] (pic::Image* imgIn)
        {
            return pic::DurandTMO::execute(imgIn, NULL);
        }),
        "execute the DurandTMO tone-mapping",
        py::return_value_policy::take_ownership,
        py::arg("imgIn")
    );

    // endregion Methods
}