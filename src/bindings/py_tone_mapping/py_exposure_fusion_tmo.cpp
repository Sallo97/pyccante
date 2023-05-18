#include "py_exposure_fusion_tmo.h"

void init_ExposureFusion(pybind11::module_& m)
{
    py::class_<pic::ExposureFusion, pic::ToneMappingOperator>(m, "ExposureFusion")

    // region Constructor

    .def(py::init<float, float, float>(),
        "ExposureFusion constructor",
        py::arg("wC") = 1.0f, py::arg("wE") = 1.0f,
        py::arg("wS") = 1.0f)
    
    .def_static("execute", &pic::ExposureFusion::execute,
        "execute ExposureFusion TMO",
        py::arg("imgIn"), py::arg("imgOut"))
    
    .def_static
    (
        "execute", 
        ([] (pic::Image* imgIn)
        {
            return pic::ExposureFusion::execute(imgIn, NULL);
        }),
        "execute ExposureFusion TMO",
        py::arg("imgIn")
    );

    // endregion
}