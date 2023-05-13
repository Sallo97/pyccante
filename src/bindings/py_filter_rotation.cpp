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
        })
        // Add descriptions and name arguments
    )

    .def_static
    (
        "execute", 
        ([] (pic::Image* imgIn, pic::Image* imgOut,
            Eigen::Matrix3f& mtx)
        {
            return pic::FilterRotation::execute(imgIn, imgOut,
                                                mtx);
        })
        // Add descriptions and name arguments     
    );

    // endregion

    // endregion
}