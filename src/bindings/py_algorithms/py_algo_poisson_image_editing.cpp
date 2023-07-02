// This file contains the binding of the Piccante's computePoissonImageEditing function

#include "py_algo_poisson_image_editing.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the computePoissonImageEditing function to the passed module.
 */

void init_computePoissonImageEditing(pybind11::module_& m)
{
    /**
     * @brief computePoissonImageEditing
     * @param source
     * @param target
     * @param mask
     * @param ret
     * @return
     */
    m.def   
    (
        "computePoissonImageEditing",
        ([] (pic::Image* source, pic::Image* target,
            py::buffer mask_buffer)
        {
            // Get the raw pointer to the data
            bool* mask = return_bool_ptr(mask_buffer);

            // Call the function
            pic::Image* img = pic::computePoissonImageEditing(source, target,
                                                              mask, NULL);
            // Return the resulting image
            return img;
            
        }),
        "execute the computePoissonImageEditing algorithm",
        py::return_value_policy::take_ownership,
        py::arg("source"), py::arg("target"),
        py::arg("mask")
    );

}
