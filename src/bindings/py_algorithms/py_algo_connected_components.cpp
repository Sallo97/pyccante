#include "py_algo_connected_components.h"

static unsigned int find_areaMin(std::vector<pic::LabelOutput> ret, int areaMin)
{
    for(unsigned int i = 0; i < ret.size(); i++) {
        unsigned int areaTmp = ret[i].coords.size();
        if(areaMin > areaTmp) {
            areaMin = areaTmp;
        }
    }
    std::string out = "The size of the smallest circle is: " + pic::fromNumberToString(areaMin) + " pixels.\n";
    printf("%s", out.c_str());
    return areaMin;
}


void init_ConnectedComponents(pybind11::module_& m)
{

    // region img_x_ret

    py::class_<Img_x_ret>(m, "Image_x_ret")
        .def(py::init<>(),
            "Img_x_ret constructor")
        .def_readonly("imgOut", &Img_x_ret::imgOut)
        .def_readonly("ret", &Img_x_ret::ret);

    // endregion

    // region LabelInfo

    py::class_<pic::LabelInfo>(m, "LabelInfo");

    // endregion

    // region LabelOutput

    py::class_<pic::LabelOutput>(m, "LabelOutput")
        .def(py::init<>(),
            "LabelOutput constructor")
        .def_readonly("coords", &pic::LabelOutput::coords)
        .def_readonly("id", &pic::LabelOutput::id)
        .def_readonly("neighboars", &pic::LabelOutput::neighbors)
        .def_readonly("bValid", &pic::LabelOutput::bValid);

    // endregion


    // region ConnectedComponents

    py::class_<pic::ConnectedComponents>(m, "ConnectedComponents")
    
    // region Constructors

    .def(py::init<float>(),
        "ConnectedComponents constructor",
        py::arg("thr") = 0.05f)

    // endregion

    // region Functions

    .def
    (
        "execute",
        ([] (pic::ConnectedComponents* this_cc, py::buffer imgIn_buffer, int width,
            int height)
            
        {
            // Get the raw pointer for imgIn
            bool* imgIn = return_bool_ptr(imgIn_buffer);

            uint* imgOut;
            std::vector<pic::LabelOutput> ret;

            imgOut = this_cc->execute(imgIn, width, height, NULL, &ret);
        
            return img;
        })
    )


    .def_static("convertFromIntegerToImage", pic::ConnectedComponents::convertFromIntegerToImage,
        "convertfromIntegerToImage",
        py::arg("imgLaber"), py::arg("imgOut"), 
        py::arg("width"), py::arg("height"))

    .def_static
    (
        "convertFromIntegerToImage",
        ([] (uint* imgLabel, int width, int height)
        {
            return pic::ConnectedComponents::convertFromIntegerToImage(imgLabel, NULL, width, height);
        }),
        "convertFromIntegerToImage",
        py::arg("imgLabel"), py::arg("width"),
        py::arg("height")
    );

    // endregion

    // endregion

    m.def("find_areaMin", find_areaMin);

}