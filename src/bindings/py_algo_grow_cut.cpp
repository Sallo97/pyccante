#include "py_algo_grow_cut.h"

void init_GrowCut(pybind11::module_& m)
{
    py::class_<pic::GrowCut>(m, "GrowCut")
    
    // region Constructors
    
    .def(py::init <>(),
        "GrowCut constructor")

    // endregion

    // region Functions

    .def_static("fromStrokeImageToSeeds", &pic::GrowCut::fromStrokeImageToSeeds,
        "fromStrokeImageToSeeds",
        py::arg("strokes"), py::arg("out"))

    .def_static
    (
        "fromStrokeImageToSeeds",
        ([] (pic::Image* strokes)
        {
            return pic::GrowCut::fromStrokeImageToSeeds(strokes, NULL);
        }),
        "formStrokeImageToSeeds",
        py::arg("strokes")
    )

    .def_static("getMaskAsImage", &pic::GrowCut::getMaskAsImage,
        "getMaskAsImage",
        py::arg("state"), py::arg("out"))

    .def_static
    (
        "getMaskAsImage",
        ([] (pic::Image* state)
        {
            return pic::GrowCut::getMaskAsImage(state, NULL);
        }),
        "getMaskAsImage",
        py::arg("state")
    )

    .def_static("execute", &pic::GrowCut::execute,
        "execute the algorithm GrowCut",
        py::arg("img"), py::arg("seeds"), py::arg("imgOut"))

    .def_static
    (
        "execute",
        ([] (pic::Image* img, pic::Image* seeds)
        {
            return pic::GrowCut::execute(img, seeds, NULL);
        }),
        "execute the algorithm GrowCut",
        py::arg("img"), py::arg("seeds") 
    );

    // endregion
}