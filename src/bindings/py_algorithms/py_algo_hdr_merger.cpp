// This file contains the binding of the Piccante's HDRMerger algorithm class

#include "py_algo_hdr_merger.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the HDRMerger class to the passed module.
 */
void init_HDRMerger(pybind11::module_& m)
{
    // Defining the HDRMerger class in pyccante.
    py::class_<pic::HDRMerger>(m, "HDRMerger")
    
    // region Constructors

    /**
     * @brief HDRMerger basic constructor.
     */
    .def(py::init<>(),
        "HDRMerger constructor")

    // endregion Constructors

    // region Functions

    /**
     * @brief addFile adds an Image to the HDRMerger stack
     * @param file_name the path to the image.
     * @param exposure_time is luminance value (default is -1.0f).
     */
    .def("addFile", &pic::HDRMerger::addFile,
        "adds an Image to the algorithms.",
        py::arg("file_name"), py::arg("exposure_time") = -1.0f)

    /**
     * @brief executes generates a HDR iamge using the images inside the object stack.
     * @return an HDR image.
     */
    .def
    (
        "execute", 
        ([] (pic::HDRMerger* this_algo)
        {
            return this_algo->pic::HDRMerger::execute(NULL);
        }),
        "execute the algorithm HDRMerger",
        py::return_value_policy::take_ownership
    );

    // endregion Functions
}