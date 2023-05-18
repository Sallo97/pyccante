#include "py_durand_tmo.h"

void init_DurandTMO(pybind11::module_& m)
{
    py::class_<pic::DurandTMO, pic::ToneMappingOperator>(m, "DurandTMO")

    // region Constructor

    .def(py::init<float>(),
        "DurandTMO constructor",
        py::arg("target_constrast") = 5.0f)

    // endregion

    // region Functions

    .def_static("execute", &pic::DurandTMO::execute,
        "execute the DurandTMO tone-mapping",
        py::arg("imgIn"), py::arg("imgOut"))

    .def_static
    (
        "execute", 
        ([] (pic::Image* imgIn)
        {
            return pic::DurandTMO::execute(imgIn, NULL);
        }),
        "execute the DurandTMO tone-mapping",
        py::arg("imgIn")
    );

    // endregion
}