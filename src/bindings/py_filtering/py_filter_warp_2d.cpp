// This file contains the binding of the Piccante's FilterWarp2D filter class.


#include "py_filter_warp_2d.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the Image class to the passed module.
 */
void init_FilterWarp2D(pybind11::module_& m)
{
    // Defines the Image class in the passed module.
    py::class_<pic::FilterWarp2D, pic::Filter>(m, "FilterWarp2D")
    
    // region Functions

    /**
     * @brief execute
     * @param img
     * @param imgOut
     * @param h
     * @param bSameSize
     * @param bCentroid
     * @return
     */
    .def_static("execute", ([] (pic::Image* img, pic::Matrix3x3 h, 
                                bool bSameSize, bool bCentroid)
        {
            pic::Image* imgOut;
            imgOut = pic::FilterWarp2D::execute(img, imgOut, h,
                                                bSameSize = false, bCentroid = false); 
            return imgOut;
        }),
        "execute the FilterWarp2D filter",
        py::return_value_policy::take_ownership,
        py::arg("img"), py::arg("h"),
        py::arg("bSameSize"), py::arg("bCentroid")
        );

    // endregion Functions

}