// This file contains the binding of the piccante's ReinhardTMO tone_mapper class


#include "py_reinhard_tmo.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

/**
 * @brief binds the ReinhardTMO class to the passed module.
 */
void init_ReinhardTMO(pybind11::module_& m)
{
    // region SIGMOID_MODE
    py::enum_<pic::SIGMOID_MODE>(m, "SIGMOID_MODE")
        .value("SIG_TMO", pic::SIGMOID_MODE::SIG_TMO)
        .value("SIG_TMO_WP", pic::SIGMOID_MODE::SIG_TMO_WP)
        .value("SIG_SDM", pic::SIGMOID_MODE::SIG_SDM);

    // endregion


    // region ReinhardTMO

    py::class_<pic::ReinhardTMO, pic::ToneMappingOperator>(m, "ReinhardTMO")


    // region Methods
    
    /**
     * @brief execute the Reinhard TMO taking into account 
     *        the global environment.
     * @param imgIn the HDR source image.
     * @return a compressed SDR image.
     */
    .def_static
    (
        "executeGlobal1", 
        ([] (pic::Image* imgIn)
        {
            return pic::ReinhardTMO::executeGlobal1(imgIn, NULL);    
        }),
        "execute the Reinhard executeGlobal2 tone mapping",
        py::return_value_policy::take_ownership,
        py::arg("imgIn")
    )

    /**
     * @brief execute the Reinhard TMO taking into account 
     *        the global environment.
     * @param imgIn the HDR source image.
     * @return a compressed SDR image.
     */
    
    .def_static
    (
        "executeGlobal2", 
        ([] (pic::Image* imgIn)
        {
            return pic::ReinhardTMO::executeGlobal2(imgIn, NULL);    
        }),
        "execute the Reinhard executeGlobal2 tone mapping",
        py::return_value_policy::take_ownership,
        py::arg("imgIn")
    )

    /**
     * @brief execute the Reinhard TMO taking into account 
     *        the local environment.
     * @param imgIn the HDR source image.
     * @return a compressed SDR image.
     */
    
    .def_static
    (
        "executeLocal1", 
        ([] (pic::Image* imgIn)
        {
            return pic::ReinhardTMO::executeLocal1(imgIn, NULL);    
        }),
        "execute the Reinhard executeLocal1 tone mapping",
        py::return_value_policy::take_ownership,
        py::arg("imgIn")
    )

    /**
     * @brief execute the Reinhard TMO taking into account 
     *        the local environment.
     * @param imgIn the HDR source image.
     * @return a compressed SDR image.
     */
    
    .def_static
    (
        "executeLocal2", 
        ([] (pic::Image* imgIn)
        {
            return pic::ReinhardTMO::executeLocal2(imgIn, NULL);    
        }),
        "execute the Reinhard executeLocal tone mapping",
        py::return_value_policy::take_ownership,
        py::arg("imgIn")
    );
    // endregion Methods

    // endregion ReinhardTMO
}
