#include"py_filter_bilateral_2df.h"


void init_FilterBilateral2DF(pybind11::module_& m)
{
    // region FilterBilateral2DF

    py::class_<pic::FilterBilateral2DF, pic::Filter>(m, "FilterBilateral2DF")

    // region Constructor
    
    .def(py::init <>(),
        "FilterBilateral2DF constructor")

    .def(py::init < float, float > (),
        "FilterBilateral2DF",
        py::arg("sigma_s"), py::arg("sigma_r"))

    // endregion

    // region Functions
    
    .def_static("execute", &pic::FilterBilateral2DF::execute,
                "execute FilterBilateral2DF",
                py::arg("imgIn"), py::arg("imgOut"), 
                py::arg("sigma_s"), py::arg("sigma_r"))
    
    .def_static("execute", ([] (pic::Image* imgIn, float sigma_s, float sigma_r)
    {
        return pic::FilterBilateral2DF::execute(imgIn, NULL, sigma_s, sigma_r);
    }),
    "execute FilterBilateral2DF",
    py::arg("imgIn"), py::arg("sigma_s"),
    py::arg("sigma_r")
    );

    // endregions

    // endregion


}