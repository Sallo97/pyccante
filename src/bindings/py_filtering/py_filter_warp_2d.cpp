#include "py_filter_warp_2d.h"

void init_FilterWarp2D(pybind11::module_& m)
{
    py::class_<pic::FilterWarp2D, pic::Filter>(m, "FilterWarp2D")
    
    // region Constructor

    .def(py::init<>(),
        "FilterWarp2D Constructor",
        py::return_value_policy::take_ownership)

    .def(py::init<pic::Matrix3x3, bool, bool>(),
        "FilterWarp2D Constructor",
        py::return_value_policy::take_ownership,
        py::arg("h"), py::arg("bSameSize") = false,
        py::arg("bCentroid") = false)

    // endregion

    // region Functions

    .def_static("execute", &pic::FilterWarp2D::execute,
        "execute the FilterWarp2D filter",
        py::return_value_policy::take_ownership,
        py::arg("img"), py::arg("imgOut"),
        py::arg("h"), py::arg("bSameSize") = false,
        py::arg("bCentroid") = false)
    
    .def_static("execute", ([] (pic::Image* img, pic::Matrix3x3 h, 
                                bool bSameSize, bool bCentroid)
        {
            pic::Image imgOut = pic::FilterWarp2D::execute(img, &imgOut, h,
                                                bSameSize = false, bCentroid = false); 
            return imgOut;
        }),
        "execute the FilterWarp2D filter",
        py::return_value_policy::take_ownership,
        py::arg("img"), py::arg("h"),
        py::arg("bSameSize"), py::arg("bCentroid")
        );

    // endregion

}