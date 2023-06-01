#include "py_exif.h"

void init_exif(pybind11::module_& m)
{

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
        py::arg("imgIn")
    );

}
