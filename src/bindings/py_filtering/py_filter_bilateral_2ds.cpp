#include "py_filter_bilateral_2ds.h"

void init_FilterBilateral2DS(pybind11::module_& m)
{
    py::class_<pic::FilterBilateral2DS, pic::Filter>(m, "FilterBilateral2DS")

    // region Constructor

    .def(py::init<>(),
        "FilterBilateral2DS constructor",
        py::return_value_policy::take_ownership)
    
    .def(py::init<std::string, float>(),
        "FilterBilateral2DS constructor",
        py::return_value_policy::take_ownership,
        py::arg("nameFile"), py::arg("sigma_r"))
    
    .def(py::init<float, float, int, pic::SAMPLER_TYPE>(),
        "FilterBilateral2DS constructor",
        py::return_value_policy::take_ownership,
        py::arg("sigma_s"), py::arg("sigma_r"),
        py::arg("mult"), py::arg("type"))

    // endregion

    // region Functions

    .def_static(
        "execute",
        ([] (pic::Image* imgIn, float sigma_s,
            float sigma_r)
        {
            return pic::FilterBilateral2DS::execute(imgIn, sigma_s, sigma_r);
        }),
        "execute FilterBilateral2DS",
        py::return_value_policy::take_ownership,
        py::arg("imgIn"), py::arg("sigma_s"),
        py::arg("sigma_r")
    )

    .def_static(
        "execute",
        ([] (pic::Image* imgIn, pic::Image* imgEdge,
            float sigma_s, float sigma_r)
        {
            return pic::FilterBilateral2DS::execute(imgIn, imgEdge, sigma_s,
                                                     sigma_r);
        }),
        "execute FilterBilateral2DS",
        py::return_value_policy::take_ownership,
        py::arg("imgIn"), py::arg("imgEdge"),
        py::arg("sigma_s"), py::arg("sigma_r")
    );

    // endregion
}