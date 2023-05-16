#include "py_filter_warp_2d.h"

void init_FilterWarp2D(pybind11::module_& m)
{
    py::class_<pic::FilterWarp2D, pic::Filter>(m, "FilterWarp2D")
    
    // region Constructor

    .def(py::init<>(),
        "FilterWarp2D Constructor")

    .def(py::init<pic::Matrix3x3, bool, bool>(),
        "FilterWarp2D Constructor",
        py::arg("h"), py::arg("bSameSize") = false,
        py::arg("bCentroid") = false)

    // endregion

    // region Functions

    .def_static("execute", &pic::FilterWarp2D::execute,
        "execute the FilterWarp2D filter",
        py::arg("img"), py::arg("imgOut"),
        py::arg("h"), py::arg("bSameSize") = false,
        py::arg("bCentroid") = false);

    // endregion

}