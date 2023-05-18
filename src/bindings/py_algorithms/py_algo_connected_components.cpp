#include "py_algo_connected_components.h"

void init_ConnectedComponents(pybind11::module_& m)
{
    // region LabelInfo

    py::class_<pic::LabelInfo>(m, "LabelInfo");

    // endregion


    // region ConnectedComponents

    py::class_<pic::ConnectedComponents<pic::Image>>(m, "ConnectedComponents")
    
    // region Constructors

    .def(py::init<float>(),
        "ConnectedComponents constructor",
        py::arg("thr"))

    // endregion

    // region Functions

    .def
    (
        "execute",
        ([] (pic::ConnectedComponents<pic::Image> this_cc, pic::Image* imgIn,
            uint* imgOut, std::vector<pic::LabelOutput>& ret)
        {
            return this_cc.execute(imgIn, imgOut, ret);
        }),
        py::arg("imgIn"), py::arg("imgOut"), py::arg("ret")
    )

    .def
    (
        "execute",
        ([] (pic::ConnectedComponents<pic::Image> this_cc, pic::Image* imgIn,
            std::vector<pic::LabelOutput>& ret)
        {
            return this_cc.execute(imgIn, NULL, ret);
        }),
        "execute",
        py::arg("imgIn"), py::arg("ret")
    );
    
    // endregion

    // endregion
}