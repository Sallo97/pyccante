// This file contains the binding of the piccante's DragoTMO tone_mapper class


#include "py_drago_tmo.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the DragoTMO class to the passed module.
 */
void init_DragoTMO(pybind11::module_& m)
{
    // Defines the Image class in the passed module.
    py::class_<pic::DragoTMO, pic::ToneMappingOperator>(m, "DragoTMO")

    // region Methods

    /**
     * @brief execute the Drago Tone Mapping
     * @param imgIn the HDR source image.
     * @return a compressed SDR image.
     */
    .def_static
    (
        "execute",
        ([] (pic::Image* imgIn)
        {
            return pic::DragoTMO::execute(imgIn, NULL);
        }),
        "execute the DragonTMO tone-mapper",
        py::return_value_policy::take_ownership,
        py::arg("imgIn")    
    );

    // endregion Methods
}
