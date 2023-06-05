#include "py_filter_mean.h"

void init_FilterMean(pybind11::module_& m)
{
    py::class_<pic::FilterMean, pic::Filter>(m, "FilterMean")

    // region Constructors

    .def(py::init<int>(),
        "FilterMean constructor",
        py::return_value_policy::take_ownership,
        py::arg("size"))

    // endregion

    // region Functions

    .def_static("execute", &pic::FilterMean::execute,
        "execute FilterMean",
        py::return_value_policy::take_ownership,
        py::arg("imgIn"), py::arg("imgOut"),
        py::arg("size"))
    
    .def_static
    (
        "execute",
        ([] (pic::Image* imgIn, int size)
        {
            return pic::FilterMean::execute(imgIn, NULL, size);
        }), 
        "execute FilterMean",
        py::return_value_policy::take_ownership,
        py::arg("imgIn"), py::arg("imgOut")
    );

    // endregion
}