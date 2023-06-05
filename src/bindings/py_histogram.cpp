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
        "Histogram is the basic constructor setting variables to defaults.",
        py::return_value_policy::take_ownership)

        .def(py::init< pic::Image*, pic::VALUE_SPACE, int, int >(),
            py::return_value_policy::reference,
            "Histogram is an extension of the basic constructor, where calculate"
            "is called in order to populate the Histogram.",
            py::return_value_policy::take_ownership,
            py::arg("imgIn"), py::arg("type"),
            py::arg("nBin")=256, py::arg("channel")=0
            )
        
    // endregion

    // region Functions

    .def("project", &pic::Histogram::project,
        "project converts an input value in the histogram domain.",
        py::return_value_policy::take_ownership,
        py::arg("x"))
        
    .def("unproject", &pic::Histogram::unproject,
        "unproject converts a histogram value back to its original domain.",
        py::return_value_policy::take_ownership,
        py::arg("ind"))

    .def("ceiling", &pic::Histogram::ceiling,
        "ceiling limits the maximum value of the histogram using Ward",
        "algorithm.",
        py::arg("k"))

    .def("clip", &pic::Histogram::clip,
        "clip clips the histogram to value.",
        py::arg("value"))
        
    .def
    (
        "cumulativef",
        ([](pic::Histogram* this_h, bool bNormalized)
        {
            float* ret = this_h->cumulativef(bNormalized);

            // Return the NumPy array to Python
            return py::array_t<float>( 1024, ret);
        }),
        "cumulativef computes the cumulative Histogram.",
        py::return_value_policy::take_ownership,
        py::arg("bNormalized")
    )

    .def
    (
        "getCumulativef", 
        ([](pic::Histogram* this_h)
        {
            float* ret = this_h->getCumulativef();

            // Return the NumPy array to Python
            return py::array_t<float>( 1024, ret);
        }),
        "getCumulativef this function returns the cumulative Histogram."
        "Histogram. Note that cumulativef needs to be computed before otherwise"
        "the function will return a NULL pointer.",
        py::return_value_policy::take_ownership
    )
        
    .def("getfMin", &pic::Histogram::getfMin,
        "getfMin",
        py::return_value_policy::take_ownership)

    .def("getfMax", &pic::Histogram::getfMax,
        "getfMax",
        py::return_value_policy::take_ownership)

    .def
        (
        "getNormalized",
        ([](pic::Histogram* this_h, bool bNor = true)
        {
            float* ret = this_h->getNormalized(bNor);

            // Return the NumPy array to Python
            return py::array_t<float>( 1024, ret);
        }),
        "getNormalized normalizes the Histogram.",
        py::return_value_policy::take_ownership,
        py::arg("bNor")=true
        )
        
    .def("getOtsu", &pic::Histogram::getOtsu,
        "getOtsu",
        py::return_value_policy::take_ownership)

    .def("write", &pic::Histogram::write,
        "write saves the Histogram as an Image into a file.",
        py::arg("name"), py::arg("bNor"))
        
    .def("exposureCovering", &pic::Histogram::exposureCovering,
        "exposureCovering computes the exposure values for fully covering"
        " the dynamic range of the image. This function works only if the histogram"
        " was compute usign VS_LOG_2.",
        py::return_value_policy::take_ownership,
        py::arg("nBits")=8, py::arg("overlap")=1.0f)
    // endregion

    // region Arguments
    // For now all the variables are readonly, change them as the project goes on.

    .def_readonly("bin", &pic::Histogram::bin)
    .def_readonly("bin_work", &pic::Histogram::bin_work);

    // endregion
}
