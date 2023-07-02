// This file contains function that take use of the exif library.


#include "py_exif.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the custom functions to the passed module.
 */
void init_exif(pybind11::module_& m)
{

    /**
    * @brief read the exposure values associated to the image.
    * @param nameFile is the path to the .jpeg picture.
    * @return return the exposure value as a float.
    */
    m.def
    (
        "getJPGExposure",
        ([] (std::string nameFile)
        {
            // Create a EXIFInfo struct
            pic::EXIFInfo info;
                
            // Calling the function
            pic::readEXIF(nameFile, info);

            // Returing the exposure info
            return info.exposureTime;
            
        }),
        "Returns the exposureTime of the image",
        py::return_value_policy::take_ownership,
        py::arg("imgIn")
    );

}
