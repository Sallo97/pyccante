#include "py_filter_max.h"

void init_FilterMax(pybind11::module_& m)
{
    py::class_<pic::FilterMax, pic::Filter>(m, "FilterMax")

    // region Constructors

    .def(py::init<int>(),
        "FilterMax constructor",
        py::arg("size"))

    // endregion

    // region Functions

    .def_static("execute", &pic::FilterMax::execute,
        "execute FilterMax",
        py::arg("imgIn"), py::arg("imgOut"),
        py::arg("size"))
    
    .def_static
    (
        "execute",
        ([] (pic::Image* imgIn, int size)
        {
            return pic::FilterMax::execute(imgIn, NULL, size);
        }), 
        "execute FilterMax",
        py::arg("imgIn"), py::arg("imgOut")
    );

    // endregion

}