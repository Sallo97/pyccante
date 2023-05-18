#include "py_filter_rotation.h"

void init_FilterRotation(pybind11::module_& m)
{
    // region FilterRotation
    py::class_<pic::FilterRotation, pic::Filter>(m, "FilterRotation")

    // region Constructor

    .def(py::init<>(),
        "FilterRotation")

    .def(py::init<float, float, float>(),
        "FilterRotation",
        py::arg("angleX"), py::arg("angleY"), 
        py::arg("angleZ"))
    
    .def(py::init<Eigen::Matrix3f>(),
        "FilterRotation")

    // endregion

    // region Functions
    .def_static
    (
        "execute",
        ([] (pic::Image* imgIn, pic::Image* imgOut,
            float angleX, float angleY, float angleZ)
        {
            return pic::FilterRotation::execute(imgIn, imgOut,
                                                angleX, angleY, angleZ);
        }),
        "execute FilterRotation",
        py::arg("imgIn"), py::arg("imgOut"),
        py::arg("angleX"), py::arg("angleY"),
        py::arg("angleZ")
    )

    .def_static
    (
        "execute",
        ([] (pic::Image* imgIn, float angleX, float angleY, float angleZ)
        
        {
            return pic::FilterRotation::execute(imgIn, NULL, angleX,
                                                angleY, angleZ);
        }),
        "execute FilterRotation",
        py::arg("imgIn"), py::arg("angleX"),
        py::arg("angleY"), py::arg("angleZ")
    )

    .def_static
    (
        "execute", 
        ([] (pic::Image* imgIn, pic::Image* imgOut, Eigen::Matrix3f& mtx)
        {
            return pic::FilterRotation::execute(imgIn, imgOut, mtx);
        }),
        "execute FilterRotation",
        py::arg("imgIn"), py::arg("imgOut"), py::arg("mtx")
    )

    .def_static
    (
        "execute",
        ([] (pic::Image* imgIn, Eigen::Matrix3f& mtx)
        {
            return pic::FilterRotation::execute(imgIn, NULL, mtx);
        }),
        "execute FilterRotation",
        py::arg("imgIn"), py::arg("mtx")
    );

    // endregion

    // endregion
}