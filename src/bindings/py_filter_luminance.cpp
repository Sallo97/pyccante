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

    .def_static("execute", &pic::FilterLuminance::execute,
        "execute",
        py::arg("imgIn"), py::arg("imgOut"), 
        py::arg("type")= pic::LUMINANCE_TYPE::LT_CIE_LUMINANCE);
    
    // endregion

    // endregion


}