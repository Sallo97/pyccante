#include "py_filter_luminance.h"


void init_FilterLuminance(pybind11::module_& m)
{
    // region LUMINANCE_TYPE
    py::enum_<pic::LUMINANCE_TYPE>(m, "LUMINANCE_TYPE")
        .value("LT_CIE_LUMINANCE", pic::LUMINANCE_TYPE::LT_CIE_LUMINANCE)
        .value("LT_LUMA", pic::LUMINANCE_TYPE::LT_LUMA)
        .value("LT_WARD_LUMINANCE", pic::LUMINANCE_TYPE::LT_WARD_LUMINANCE)
        .value("LT_MEAN", pic::LUMINANCE_TYPE::LT_MEAN);

    // endregion 

    // region FilterLuminance
    py::class_<pic::FilterLuminance, pic::Filter>(m, "FilterLuminance")
    
    // region Constructors

    .def(py::init< pic::LUMINANCE_TYPE >(),
        "FilterLuminance",
        py::arg("type") = pic::LUMINANCE_TYPE::LT_CIE_LUMINANCE)

    // endregion

    // region Functions

    .def("computeWeights", ([](pic::FilterLuminance this_filter, pic::LUMINANCE_TYPE type, 
                            int channels, py::buffer weights_buffer)
    {
        // Get the raw pointer to the data
        float* weights = return_float_ptr(weights_buffer);

        // Call the function
        float* ret_val = this_filter.computeWeights(type, channels, weights);

        // Return the Numpy array to Python
        return return_numpy_array(ret_val);
        
    }),
    "computeWeights",
    py::arg("type"), py::arg("channels"), py::arg("weights")
    )

    .def("update", &pic::FilterLuminance::update,
        "update",
        py::arg("update")=pic::LUMINANCE_TYPE::LT_CIE_LUMINANCE)

    .def("OutputSize", &pic::FilterLuminance::OutputSize,
        "OutputSize",
        py::arg("imgIn"), py::arg("width"),
        py::arg("height"), py::arg("channels"),
        py::arg("frames"))

    .def_static("execute", &pic::FilterLuminance::execute,
        "execute",
        py::arg("imgIn"), py::arg("imgOut"), 
        py::arg("type")= pic::LUMINANCE_TYPE::LT_CIE_LUMINANCE);
    
    // endregion

    // endregion


}