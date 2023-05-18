#include "py_reinhard_tmo.h"

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

    // region Constructor

    .def(py::init<float, float, float, pic::SIGMOID_MODE>(),
        "ReinhardTMO constructor",
        py::arg("alpha") = 0.18f, py::arg("whitePoint") = -1.0f,
        py::arg("phi") = 8.0f, py::arg("sig_mode") = pic::SIGMOID_MODE::SIG_TMO)

    // endregion

    // region Functions

    .def_static("executeGlobal1", &pic::ReinhardTMO::executeGlobal1,
        "execute the Reinhard executeGlobal1 tone mapping",
        py::arg("imgIn"), py::arg("imgOut"))
    
    .def_static
    (
        "executeGlobal1", 
        ([] (pic::Image* imgIn)
        {
            return pic::ReinhardTMO::executeGlobal1(imgIn, NULL);    
        }),
        "execute the Reinhard executeGlobal2 tone mapping",
        py::arg("imgIn")
    )

    .def_static("executeGlobal2", &pic::ReinhardTMO::executeGlobal2,
        "execute the Reinhard executeGlobal2 tone mapping",
        py::arg("imgIn"), py::arg("imgOut"))
    
    .def_static
    (
        "executeGlobal2", 
        ([] (pic::Image* imgIn)
        {
            return pic::ReinhardTMO::executeGlobal2(imgIn, NULL);    
        }),
        "execute the Reinhard executeGlobal2 tone mapping",
        py::arg("imgIn")
    )

    .def_static("executeLocal1", &pic::ReinhardTMO::executeLocal1,
        "execute the Reinhard executeLocal1 tone mapping",
        py::arg("imgIn"), py::arg("imgOut"))
    
    .def_static
    (
        "executeLocal1", 
        ([] (pic::Image* imgIn)
        {
            return pic::ReinhardTMO::executeLocal1(imgIn, NULL);    
        }),
        "execute the Reinhard executeLocal1 tone mapping",
        py::arg("imgIn")
    )

    .def_static("executeLocal2", &pic::ReinhardTMO::executeLocal2,
        "execute the Reinhard executeLocal2 tone mapping",
        py::arg("imgIn"), py::arg("imgOut"))
    
    .def_static
    (
        "executeLocal2", 
        ([] (pic::Image* imgIn)
        {
            return pic::ReinhardTMO::executeLocal1(imgIn, NULL);    
        }),
        "execute the Reinhard executeLocal tone mapping",
        py::arg("imgIn")
    );
    // endregion

    // endregion
}