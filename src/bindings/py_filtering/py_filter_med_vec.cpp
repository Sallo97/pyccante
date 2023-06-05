#include "py_filter_med_vec.h"

void init_FilterMedVec(pybind11::module_& m)
{
    py::class_<pic::FilterMedVec, pic::Filter>(m, "FilterMedVec")

    // region Constructors

    .def(py::init<int>(),
        "FilterMedVec constructor",
        py::return_value_policy::take_ownership,
        py::arg("size"))

    // endregion

    // region Functions

    .def_static("execute", &pic::FilterMedVec::execute,
        "execute FilterMedVec",
        py::return_value_policy::take_ownership,
        py::arg("imgIn"), py::arg("imgOut"),
        py::arg("size"))
    
    .def_static
    (
        "execute",
        ([] (pic::Image* imgIn, int size)
        {
            return pic::FilterMedVec::execute(imgIn, NULL, size);
        }), 
        "execute FilterMedVec",
        py::return_value_policy::take_ownership,
        py::arg("imgIn"), py::arg("imgOut")
    );

    // endregion
}