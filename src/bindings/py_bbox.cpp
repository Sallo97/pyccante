// This file contains the binding of the Piccante's Image class 


#include "py_bbox.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the BBox class to the passed module.
 */
void init_BBox(pybind11::module_& m)
{   
    // Defining the BBox class in pyccante.
    py::class_<pic::BBox>(m, "BBox")

    // region Constructors
    
        /**
         * @brief BBox is a constructor setting the BBox up.
         * @param width is the maxium horizontal coordinate in pixels.
         * The minimum is set to 0.
         * @param height is the maxium vertical coordinate in pixels.
         * The minimum is set to 0.
         */
        .def(py::init<int, int>(),
            "BBox constructor",
            py::return_value_policy::take_ownership,
            py::arg("width"), py::arg("height"))
        
        /**
         * @brief BBox is a constructor setting the BBox up.
         * @param width is the maxium horizontal coordinate in pixels.
         * The minimum is set to 0.
         * @param height is the maxium vertical coordinate in pixels.
         * The minimum is set to 0.
         * @param frames is the maxium temporal coordinate in pixels.
         * The minimum is set to 0.
         */
        .def(py::init<int, int, int>(), 
            "BBox constructor",
            py::return_value_policy::take_ownership,
            py::arg("width"), py::arg("height"),
            py::arg("frames"))
        
        /**
         * @brief BBox is a constructor setting the BBox up.
         * @param x0 is the minimum horizontal coordinate in pixels.
         * @param x1 is the maximum horizontal coordinate in pixels.
         * @param y0 is the minimum vertical coordinate in pixels.
         * @param y1 is the maximum vertical coordinate in pixels.
         */
        .def(py::init<int, int, int, int>(),
            "BBox constructor",
            py::return_value_policy::take_ownership,
            py::arg("x0"), py::arg("x1"),
            py::arg("y0"), py::arg("y1"))
        
        /**
         * @brief BBox
         * @param x0 is the horizontal coordinate in pixels.
         * @param y0 is the vertical coordinate in pixels.
         * @param size is the patch size
         * @param width is the original width of the image.
         * @param height is the original height of the image.
         */
        .def(py::init<int, int, int ,int ,int>(),
            "BBox constructor",
            py::return_value_policy::take_ownership,
            py::arg("x0"), py::arg("y0"),
            py::arg("size"), py::arg("width"),
            py::arg("height"))
    
    // endregion Constructors

    // region Functions
        
        /**
         * @brief Size computes the number of pixels in a bounding box.
         * @return It returns the number of pixels in a bounding box.
         */
        .def("Size", &pic::BBox::Size,
            "Size computes the number of pixels in a bounding box.",
            py::return_value_policy::take_ownership)

        /**
         * @brief getFourBlocks sets the BBox as a quadrant of a given size.
         * @param width is horizontal size in pixels.
         * @param height is the vertical size in pixels.
         * @param i is the i-th quadrant.
         */
        .def("getFourBlocks", &pic::BBox::getFourBlocks,
            "getFourBlocks sets the BBox as a quadrant of a given size.",
            py::arg("width"), py::arg("height"), py::arg("i"))

        /**
         * @brief print a string representation of BBox
         */

        .def("__repr__", &pic::BBox::toString,
            "returns a string representation of BBox")

    // endregion Functions

    // region Args

        .def_readonly("x0", &pic::BBox::x0)
        .def_readonly("y0", &pic::BBox::y0)
        .def_readonly("z0", &pic::BBox::z0)
        .def_readonly("x1", &pic::BBox::x1)
        .def_readonly("y1", &pic::BBox::y1)
        .def_readonly("z1", &pic::BBox::z1);
        
    // endregion Args

}