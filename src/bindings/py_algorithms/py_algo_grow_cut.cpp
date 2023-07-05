// This file contains the binding of the Piccante's GrowCut algorithm class. 

#include "py_algo_grow_cut.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the GrowCut class to the passed module
 */
void init_GrowCut(pybind11::module_& m)
{
    /**
     * @brief GrowCut algorithm
     */
    py::class_<pic::GrowCut>(m, "GrowCut")
    
    // region Functions

    /**
     * @brief fromStrokeImageToSeeds
     * @param strokes
     * @param out
     * @return
     */
    .def_static
    (
        "fromStrokeImageToSeeds",
        ([] (pic::Image* strokes)
        {
            return pic::GrowCut::fromStrokeImageToSeeds(strokes, NULL);
        }),
        "formStrokeImageToSeeds",
        py::return_value_policy::take_ownership,
        py::arg("strokes")
    )

    /**
     * @brief getMaskAsImage
     * @param state
     * @return
     */
    .def_static
    (
        "getMaskAsImage",
        ([] (pic::Image* state)
        {
            return pic::GrowCut::getMaskAsImage(state, NULL);
        }),
        "getMaskAsImage",
        py::return_value_policy::take_ownership,
        py::arg("state")
    )

    /**
     * @brief execute the GrowCut algorithm
     * @param img
     * @param seeds
     * @return
     */
    .def_static
    (
        "execute",
        ([] (pic::Image* this_img, pic::Image* seeds)
        {
            return pic::GrowCut::execute(this_img, seeds, NULL);
        }),
        "execute the algorithm GrowCut",
        py::return_value_policy::take_ownership,
        py::arg("img"), py::arg("seeds") 
    );

    // endregion
}