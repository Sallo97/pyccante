#include "py_algo_grow_cut.h"

void init_GrowCut(pybind11::module_& m)
{
    py::class_<pic::GrowCut>(m, "GrowCut")
    
    // region Constructors
    
    .def(py::init <>(),
        "GrowCut constructor")

    // endregion

    // region Functions

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