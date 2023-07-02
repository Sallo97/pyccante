// This file contains the binding of the piccante's Exposure Fusion tone_mapper class


#include "py_exposure_fusion_tmo.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


void init_ExposureFusion(pybind11::module_& m)
{
    // Defines the Image class in the passed module.
    py::class_<pic::ExposureFusion, pic::ToneMappingOperator>(m, "ExposureFusion")

    // region Methods
    
    /**
     * @brief execute the Exposure Fusion Tone Mapping
     * @param imgIn the HDR source image.
     * @return a compressed SDR image.
     */
    .def_static
    (
        "execute", 
        ([] (pic::Image* imgIn)
        {
            return pic::ExposureFusion::execute(imgIn, NULL);
        }),
        "execute ExposureFusion TMO",
        py::return_value_policy::take_ownership,
        py::arg("imgIn")
    );

    // endregion Methods
}