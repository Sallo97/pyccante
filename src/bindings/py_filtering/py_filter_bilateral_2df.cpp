// This file contains the binding of the Piccante's FilterBilateral2D filter class

#include"py_filter_bilateral_2df.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the PoissonSolver class{} to the passed module.
 */
void init_FilterBilateral2DF(pybind11::module_& m)
{
    /**
     * @brief the basic construct of an Image
     */
    py::class_<pic::FilterBilateral2DF, pic::Filter>(m, "FilterBilateral2DF")

    // region Functions
    
    /**
     * @brief execute
     * @param imgIn
     * @param imgOut
     * @param sigma_s
     * @param sigma_r
     * @return
     */
    .def_static("execute", ([] (pic::Image* imgIn, float sigma_s, float sigma_r)
    {
        return pic::FilterBilateral2DF::execute(imgIn, NULL, sigma_s, sigma_r);
    }),
    "execute FilterBilateral2DF",
    py::return_value_policy::take_ownership,
    py::arg("imgIn"), py::arg("sigma_s"),
    py::arg("sigma_r")
    );

    // endregions Functions



}