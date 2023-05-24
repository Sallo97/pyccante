#include "py_histogram.h"
#include "support.h"

namespace py = pybind11;
using namespace py::literals;



void init_Histogram(pybind11::module_& m)
{
    // region VALUE_SPACE

    py::enum_<pic::VALUE_SPACE>(m, "VALUE_SPACE")
        .value("VS_LDR", pic::VALUE_SPACE::VS_LDR)
        .value("VS_LIN", pic::VALUE_SPACE::VS_LIN)
        .value("VS_LOG_2", pic::VALUE_SPACE::VS_LOG_2)
        .value("VS_LOG_E", pic::VALUE_SPACE::VS_LOG_E)
        .value("VS_LOG_10", pic::VALUE_SPACE::VS_LOG_10);

    // endregion

    // region Constructors

    py::class_<pic::Histogram>(m, "Histogram")
        .def(py::init<>(),
            "Histogram is the basic constructor setting variables to defaults.")

        .def(py::init< pic::Image*, pic::VALUE_SPACE, int, int >(),
            py::return_value_policy::reference,
            "Histogram is an extension of the basic constructor, where calculate"
            "is called in order to populate the Histogram.",
            py::arg("imgIn"), py::arg("type"),
            py::arg("nBin")=256, py::arg("channel")=0
            )
        
    // endregion

    // region Functions

        .def("release", &pic::Histogram::release)

        .def("calculate", &pic::Histogram::calculate,
            "calculate computes the histogram of an input image. In the case"
            "of LDR images, they are assumed to be normalized; i.e. with values in [0, 1]."
            "This function computes the histogram for a single color channel.",
            py::arg("imgIn"), py::arg("type") = pic::VALUE_SPACE::VS_LIN,
            py::arg("nBin")=256, py::arg("box")=NULL, py::arg("channel")=0)

        .def("uniform", &pic::Histogram::uniform,
            "uniform",
            py::arg("fMin"), py::arg("fMax"), py::arg("value"),
            py::arg("type"), py::arg("nBin"))
                
        .def("project", &pic::Histogram::project,
            "project converts an input value in the histogram domain.",
            py::arg("x"))
        
        .def("unproject", &pic::Histogram::unproject,
            "unproject converts a histogram value back to its original domain.",
            py::arg("ind"))

        .def("ceiling", &pic::Histogram::ceiling,
            "ceiling limits the maximum value of the histogram using Ward",
            "algorithm.",
            py::arg("k"))

        .def("clip", &pic::Histogram::clip,
            "clip clips the histogram to value.",
            py::arg("value"))
        
        .def("cumulativef",([](pic::Histogram* this_h, bool bNormalized)
            {
                float* ret = this_h->cumulativef(bNormalized);

                // Return the NumPy array to Python
                return return_numpy_array(ret);
            }),
            "cumulativef computes the cumulative Histogram.",
            py::arg("bNormalized"))

        .def("getCumulativef", ([](pic::Histogram* this_h)
            {
                float* ret = this_h->getCumulativef();

                // Return the NumPy array to Python
                return return_numpy_array(ret);
            }),
            "getCumulativef this function returns the cumulative Histogram."
            "Histogram. Note that cumulativef needs to be computed before otherwise"
            "the function will return a NULL pointer.")
        
        .def("getfMin", &pic::Histogram::getfMin)

        .def("getfMax", &pic::Histogram::getfMax)

        .def("getNormalized",([](pic::Histogram* this_h, bool bNor = true)
            {
                float* ret = this_h->getNormalized(bNor);

                // Return the NumPy array to Python
                return return_numpy_array(ret);
            }),
            "getNormalized normalizes the Histogram.",
            py::arg("bNor")=true
            )
        
        .def("getOtsu", &pic::Histogram::getOtsu,
            "getOtsu")

        .def("write", &pic::Histogram::write,
            "write saves the Histogram as an Image into a file.",
            py::arg("name"), py::arg("bNor"))
        
        .def("exposureCovering", &pic::Histogram::exposureCovering,
            "exposureCovering computes the exposure values for fully covering"
            " the dynamic range of the image. This function works only if the histogram"
            " was compute usign VS_LOG_2.",
            py::arg("nBits")=8, py::arg("overlap")=1.0f)
    // endregion

    // region Arguments
    // For now all the variables are readonly, change them as the project goes on.

    .def_readonly("bin", &pic::Histogram::bin)
    .def_readonly("bin_work", &pic::Histogram::bin_work);

    // endregion
}
