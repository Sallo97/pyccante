#include "py_image_vec.h"

void init_ImageVec(pybind11::module_& m)
{
    m.def("Single", &pic::Single,
        "Single creates an std::vector which contains img; this is for filters input.",
        py::arg("img"));

    m.def("Double", &pic::Double,
        "Double creates an std::vector which contains img1 and img2; this is for filters input.",
        py::arg("img1"), py::arg("img2"));

    m.def("Triple", &pic::Triple,
        "Triple creates an std::vector which contains img1, img2, and img3; this is for filters input.",
        py::arg("img1"), py::arg("img2"),
        py::arg("img3"));
        
    m.def("Quad", &pic::Quad,
        "Quad creates an std::vector which contains img1, img2, img3, and img4; this is for filters input.",
        py::arg("img1"), py::arg("img2"),
        py::arg("img3"), py::arg("img4"));
}
