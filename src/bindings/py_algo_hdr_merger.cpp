#include "py_algo_hdr_merger.h"

void init_HDRMerger(pybind11::module_& m)
{
    py::class_<pic::HDRMerger>(m, "HDRMerger")
    
    // region Constructors

    .def(py::init<>(),
        "HDRMerger constructor")

    // endregion

    // region Functions

    .def("addFile", &pic::HDRMerger::addFile,
        "adds an Image to the algorithms.",
        py::arg("file_name"), py::arg("exposure_time") = -1.0f)
    
    .def(
        "execute", 
        ([] ()
        {
            return pic::HDRMerger::execute(NULL);
        }),
        "execute the algorithm HDRMerger"
        );

    // endregion
}