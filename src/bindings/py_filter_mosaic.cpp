#include "py_filter_mosaic.h"

void init_FilterMosaic(pybind11::module_& m)
{
    // region FilterMosaic

    py::class_<pic::FilterMosaic, pic::Filter>(m, "FilterMosaic")

    // region Constructors

    .def(py::init<> (),
        "FilterMosaic constructor")

    // endregion

    // region Functions
    .def_static("execute", &pic::FilterMosaic::execute,
                "execute FilterMosaic",
                py::arg("imgIn"), py::arg("imgOut"))
    
    .def_static("execute", ([](pic::Image* imgIn)
        {
            return pic::FilterMosaic::execute(imgIn, NULL);
        }),
        "execute FilterMosaic",
        py::arg("imgIn")
        );

    // endregion

    // endregion

}