#include "py_filter_simple_tmo.h"

void init_FilterSimpleTMO(pybind11::module_& m)
{
   // region FilterSimpleTMO
   py::class_<pic::FilterSimpleTMO, pic::Filter>(m, "FilterSimpleTMO")

   // region Constructors

    .def(py::init <float, float>(),
        "FilterSimpleTMO constructor",
        py::return_value_policy::take_ownership,
        py::arg("gamma"), py::arg("fstop"))

   // endregion

   // region Functions

    .def_static("execute", &pic::FilterSimpleTMO::execute,
                "executing FilterSimpleTMO",
                py::return_value_policy::take_ownership,
                py::arg("imgIn"), py::arg("imgOut"),
                py::arg("gamma"), py::arg("fstop"))
    
    .def_static("execute",
                ([] (pic::Image* imgIn, float gamma, float fstop)
                {
                    return pic::FilterSimpleTMO::execute(imgIn, NULL, gamma, fstop);

                }),
                "executing FilterSimpleTMO",
                py::return_value_policy::take_ownership,
                py::arg("imgIn"), py::arg("gamma"),
                py::arg("fstop"));

   // endregion
}