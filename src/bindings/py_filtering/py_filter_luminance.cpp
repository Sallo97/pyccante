// This file contains the binding of the Piccante's FilterLuminance filter class.

#include "py_filter_luminance.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the LUMINANCE_TYPE enum class and the FilterLuminance filter class to the passed module.
 */
void init_FilterLuminance(pybind11::module_& m)
{
    // region LUMINANCE_TYPE
     /**
     * @brief defines the LUMINANCE_TYPE enum class to the module
     *        specifying it's possibile values.
     */
    py::enum_<pic::LUMINANCE_TYPE>(m, "LUMINANCE_TYPE")
        .value("LT_CIE_LUMINANCE", pic::LUMINANCE_TYPE::LT_CIE_LUMINANCE)
        .value("LT_LUMA", pic::LUMINANCE_TYPE::LT_LUMA)
        .value("LT_WARD_LUMINANCE", pic::LUMINANCE_TYPE::LT_WARD_LUMINANCE)
        .value("LT_MEAN", pic::LUMINANCE_TYPE::LT_MEAN);

    // endregion LUMINANCE_TYPE

    // region FilterLuminance

    // Defines the Image class in the passed module.
    py::class_<pic::FilterLuminance, pic::Filter>(m, "FilterLuminance")

    // region Functions
    
    /**
     * @brief execute the FilterLuminance filter to the passed image.
     * @param imgIn the source image.
     * @param type the LUMINANCE_TYPE used for applying the filter.
     * @return the filtered image.
     */
    .def_static("execute", ([](pic::Image* imgIn, 
                              pic::LUMINANCE_TYPE type = pic::LUMINANCE_TYPE::LT_CIE_LUMINANCE)
        {
            pic::Image* imgOut;
            pic::Image imgIn_copy(imgIn->nameFile, pic::LDR_type::LT_NOR_GAMMA);
            return pic::FilterLuminance::execute(&imgIn_copy, imgOut, type);
        }),
        "execute FilterLuminance",
        py::return_value_policy::take_ownership,
        py::arg("imgIn"), 
        py::arg("type") = pic::LUMINANCE_TYPE::LT_CIE_LUMINANCE
        );
    
    // endregion Functions
    
    // endregion FilterLuminance

}