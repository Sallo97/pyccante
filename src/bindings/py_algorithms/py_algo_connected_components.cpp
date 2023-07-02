// This file contains the binding of the Piccante's Connected_Components algorithm class

#include "py_algo_connected_components.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


// region Support Functions

/**
 * @brief find_areaMin finds the shape of minimal area inside an array of shapes.
 * @param shapes is an array of LabelOutput containing the area of the shapes.
 * @param areaMin is the threshold of the minimum.
 * @return a int value containing the minimum area present in the array.
 */
static unsigned int find_areaMin(std::vector<pic::LabelOutput> shapes, int areaMin)
{
    for(unsigned int i = 0; i < shapes.size(); i++) {
        unsigned int areaTmp = shapes[i].coords.size();
        if(areaMin > areaTmp) {
            areaMin = areaTmp;
        }
    }
    std::string out = "The size of the smallest circle is: " + pic::fromNumberToString(areaMin) + " pixels.\n";
    printf("%s", out.c_str());
    return areaMin;
}

// endregion Support Functions

void init_ConnectedComponents(pybind11::module_& m)
{
    // region LabelInfo

    /**
     * @brief LabelInfo
     */
    py::class_<pic::LabelInfo>(m, "LabelInfo");

    // endregion

    // region LabelOutput

    /**
     * @brief LabelOutput
     */
    py::class_<pic::LabelOutput>(m, "LabelOutput")
        
        /**
         * @brief LabelOutput creates a LabelOutput with default values.
         */
        .def(py::init<>(),
            "LabelOutput constructor",
            py::return_value_policy::take_ownership)

        .def_readonly("coords", &pic::LabelOutput::coords)
        .def_readonly("id", &pic::LabelOutput::id)
        .def_readonly("neighboars", &pic::LabelOutput::neighbors)
        .def_readonly("bValid", &pic::LabelOutput::bValid);

    // endregion


    // region ConnectedComponents
    
    /**
     * @brief ConnectedComponents implements the aforementioned algorithm.
     */
    py::class_<pic::ConnectedComponents>(m, "ConnectedComponents")
    
    // region Constructors

    /**
     * @brief ConnectedComponents create a connected components with a threshold value.
     * @param thr is the threshold value specified by the user.
     */
    .def(py::init<float>(),
        "ConnectedComponents constructor",
        py::return_value_policy::take_ownership,
        py::arg("thr") = 0.05f)

    // endregion

    // region Functions

    /**
     * @brief execute execute the algorithm ConnectedComponents
     * @param imgIn_buffer is the NumPy algorithms that represent the input image mask
     * @param width is the width of the image
     * @param height is the height of the image
     * @return a tuple containing the uint buffer of the resulting image of the algorith and his ret buffer.
     */ 
    .def
    (
        "execute",
        ([] (pic::ConnectedComponents* this_cc, py::buffer imgIn_buffer, int width,
            int height)
            
        {
            // Get the raw pointer for imgIn
            bool* imgIn = return_bool_ptr(imgIn_buffer);

            // Creating the returning objs
            std::vector<pic::LabelOutput> ret;

            // Calling the function
            uint* imgOut = this_cc->execute(imgIn, width, height, NULL, ret);

            // Creating the buffer
            py::buffer imgOut_buffer = py::array_t<uint>( (width * height) , imgOut);

            // Creating and returning the tuple
            py::tuple tup = py::make_tuple(imgOut_buffer, ret);

            return tup;

        }),
        "executing the Connected Components algorithm",
        py::return_value_policy::take_ownership
    )

    /**
     * @brief convertFromIntegerToImage convert the passed buffer to an Image object.
     * @param imgLabel is the uint buffer.
     * @param width defines the image width.
     * @param height defines the image height.
     * @return the image object based upon the passed imgLabel
     */
    .def_static
    (
        "convertFromIntegerToImage",
        ([] (py::buffer imgLabel_buffer, int width, int height)
        {
            // Get the raw pointer for imgLabel
            uint* imgLabel = return_uint_ptr(imgLabel_buffer);
            return pic::ConnectedComponents::convertFromIntegerToImage(imgLabel, NULL, width, height);
        }),
        "convertFromIntegerToImage",
        py::return_value_policy::take_ownership,
        py::arg("imgLabel"), py::arg("width"),
        py::arg("height")
    );

    // endregion Functions

    // region Custom Functions
    /**
     * @brief find_areaMin finds the shape of minimal area inside an array of shapes.
     * @return a int value containing the minimum area present in the array.
     */
    m.def("find_areaMin", find_areaMin);

    // endregion Custom Functions

}