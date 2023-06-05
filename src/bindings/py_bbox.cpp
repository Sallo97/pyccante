#include "py_bbox.h"

void init_BBox(pybind11::module_& m)
{   
    py::class_<pic::BBox>(m, "BBox")
    // region Constructors
        .def(py::init<>(),
            "BBox constructor",
            py::return_value_policy::take_ownership)
        
        .def(py::init<int, int>(),
            "BBox constructor",
            py::return_value_policy::take_ownership,
            py::arg("width"), py::arg("height"))
        
        .def(py::init<int, int, int>(), 
            "BBox constructor",
            py::return_value_policy::take_ownership,
            py::arg("width"), py::arg("height"),
            py::arg("frames"))
        
        .def(py::init<int, int, int, int>(),
            "BBox constructor",
            py::return_value_policy::take_ownership,
            py::arg("x0"), py::arg("x1"),
            py::arg("y0"), py::arg("y1"))
        
        .def(py::init<int, int, int ,int ,int>(),
            "BBox constructor",
            py::return_value_policy::take_ownership,
            py::arg("x0"), py::arg("y0"),
            py::arg("size"), py::arg("width"),
            py::arg("height"))
    
    // endregion

    // region Functions
        .def("Size", &pic::BBox::Size,
            "Size computes the number of pixels in a bounding box.",
            py::return_value_policy::take_ownership)

        .def("setBox", &pic::BBox::setBox,
            "setBox sets a BBox up.",
            py::arg("x0"), py::arg("x1"), py::arg("y0"),
            py::arg("y1"), py::arg("z0"), py::arg("z1"),
            py::arg("width"), py::arg("height"), py::arg("frames"))
        
        .def("setCentered", &pic::BBox::setCentered,
            "setCentered centers the BBox (I think)",
            py::arg("x0"), py::arg("y0"), py::arg("size"),
            py::arg("width"), py::arg("height"))
        
        .def("getFourBlocks", &pic::BBox::getFourBlocks,
            "getFourBlocks sets the BBox as a quadrant of a given size.",
            py::arg("width"), py::arg("height"), py::arg("i"))

        .def("__repr__", &pic::BBox::toString,
            "returns a string representation of BBox")

    // endregion

    // region Args
    //⚠⚠⚠ For now all the variables are readonly, change them as the project goes on. ⚠⚠⚠

        .def_readonly("x0", &pic::BBox::x0)
        .def_readonly("y0", &pic::BBox::y0)
        .def_readonly("z0", &pic::BBox::z0)
        .def_readonly("x1", &pic::BBox::x1)
        .def_readonly("y1", &pic::BBox::y1)
        .def_readonly("z1", &pic::BBox::z1);
    // endregion

}