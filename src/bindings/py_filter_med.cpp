#include "py_filter_med.h"

void init_FilterMed(pybind11::module_& m)
{
    py::class_<pic::FilterMed, pic::Filter>(m, "FilterMed")

    // region Constructors

    .def(py::init<int>(),
        "FilterMed constructor",
        py::arg("size"))

    // endregion

    // region Functions

    .def_static("execute", &pic::FilterMax::execute,
        "execute FilterMed",
        py::arg("imgIn"), py::arg("imgOut"),
        py::arg("size"))
    
    .def_static
    (
        "execute",
        ([] (pic::Image* imgIn, int size)
        {
            return pic::FilterMax::execute(imgIn, NULL, size);
        }), 
        "execute FilterMed",
        py::arg("imgIn"), py::arg("imgOut")
    );

    // endregion

}