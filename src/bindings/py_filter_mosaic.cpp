#include "py_filter_mosaic.h"

void init_FilterMosaic(pybind11::module_& m)
{
    // region FilterMosaic

    py::class_<pic::FilterMosaic, pic::Filter>(m, "FilterMosaic")

    // region Constructors

    .def(py::init<> (),
        "FilterMosaic")

    // endregion

    // region Functions
    .def_static("execute", &pic::FilterMosaic::execute,
                "execute",
                py::arg("imgIn"), py::arg("imgOut"));

    // endregion

    // endregion

}