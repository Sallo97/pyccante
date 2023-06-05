#include "py_drago_tmo.h"

void init_DragoTMO(pybind11::module_& m)
{
    py::class_<pic::DragoTMO, pic::ToneMappingOperator>(m, "DragoTMO")

    // region Constructor

    .def(py::init<float,float>(),
        "DragoTMO constructor",
        py::return_value_policy::take_ownership,
        py::arg("Ld_Max") = 100.0f, py::arg("b") = 0.95f)

    // endregion

    // region Functions

    .def_static("execute", &pic::DragoTMO::execute,
        "execute the DragoTMO tone-mapper",
        py::return_value_policy::take_ownership,
        py::arg("imgIn"), py::arg("imgOut"))

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

    // endregion
}