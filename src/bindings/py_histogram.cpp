// This file contains the binding of the Piccante's Histogram class


#include "py_histogram.h"
#include "support.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the Histogram class to the passed module.
 */
void init_Histogram(pybind11::module_& m)
{

    // Since the enum VALUE_SPACE is used as a value passed to 
    // the constructor of Histogram it must be bound.
    // Since only Histogram use it (for now) it's here.
    // region VALUE_SPACE

    py::enum_<pic::VALUE_SPACE>(m, "VALUE_SPACE")
        .value("VS_LDR", pic::VALUE_SPACE::VS_LDR)
        .value("VS_LIN", pic::VALUE_SPACE::VS_LIN)
        .value("VS_LOG_2", pic::VALUE_SPACE::VS_LOG_2)
        .value("VS_LOG_E", pic::VALUE_SPACE::VS_LOG_E)
        .value("VS_LOG_10", pic::VALUE_SPACE::VS_LOG_10);

    // endregion VALUE_SPACE

    // region Constructors

    /**
    * @brief The Histogram class is a class for creating,
    * managing, loading, and saving histogram for an Image.
    */
    py::class_<pic::Histogram>(m, "Histogram")
        
        /**
        * @brief Histogram is an extension of the basic constructor, where calculate
        * is called in order to populate the Histogram.
        * @param imgIn is an input image for which Histogram needs to be computed.
        * @param type is the space of computations (please see calculate()).
        * @param nBin is the number of bins of the Histogram.
        * @param channel is the color channel for which Histogram needs to be computed.
        */
        .def(py::init< pic::Image*, pic::VALUE_SPACE, int, int >(),
            "Histogram is an extension of the basic constructor, where calculate"
            "is called in order to populate the Histogram.",
            py::return_value_policy::take_ownership,
            py::arg("imgIn"), py::arg("type"),
            py::arg("nBin")=256, py::arg("channel")=0
            )
        
    // endregion Constructors

    // region Methods

    /**
     * @brief project converts an input value in the histogram domain.
     * @param x is an input value.
     * @return x is projected in the histogram domain.
     */
    .def("project", &pic::Histogram::project,
        "project converts an input value in the histogram domain.",
        py::return_value_policy::take_ownership,
        py::arg("x"))
        
    
    /**
     * @brief unproject converts a histogram value back to its original domain.
     * @param ind is a histogram value.
     * @return ind is converted back to its original domain.
     */
    .def("unproject", &pic::Histogram::unproject,
        "unproject converts a histogram value back to its original domain.",
        py::return_value_policy::take_ownership,
        py::arg("ind"))

    /**
     * @brief ceiling limits the maximum value of the histogram using Ward
     * algorithm.
     * @param k
     */
    .def("ceiling", &pic::Histogram::ceiling,
        "ceiling limits the maximum value of the histogram using Ward",
        "algorithm.",
        py::arg("k"))

    /**
     * @brief clip clips the histogram to value.
     * @param value the maximum allowed value in the histogram.
     */
    .def("clip", &pic::Histogram::clip,
        "clip clips the histogram to value.",
        py::arg("value"))

    /**
     * @brief cumulativef computes the cumulative Histogram.
     * @param bNormalized is a boolean value; if it is true values of
     * the Histogram will be normalized.
     * @return It returns the cumulative Histogram as a float pointer.
     */   
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

    /**
     * @brief getCumulativef this function returns the cumulative
     * Histogram. Note that cumulativef needs to be computed before otherwise
     * the function will return a NULL pointer.
     * @return It returns a float pointer to the cumulative Histogram.
     */
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

    /**
     * @brief getfMin
     * @return
     */  
    .def("getfMin", &pic::Histogram::getfMin,
        "getfMin",
        py::return_value_policy::take_ownership)

    /**
     * @brief getfMax
     * @return
     */
    .def("getfMax", &pic::Histogram::getfMax,
        "getfMax",
        py::return_value_policy::take_ownership)

    /**
     * @brief getNormalized normalizes the Histogram.
     * @return It returns the normalized Histogram as a float pointer.
     */
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

    /**
     * @brief getOtsu
     * @return
     */ 
    .def("getOtsu", &pic::Histogram::getOtsu,
        "getOtsu",
        py::return_value_policy::take_ownership)

    /**
     * @brief write saves the Histogram as an Image into a file.
     * @param name is the filename where to save the Histogram.
     * @param bNor is a boolean value for normalizing or not the Histogram.
     */
    .def("write", &pic::Histogram::write,
        "write saves the Histogram as an Image into a file.",
        py::arg("name"), py::arg("bNor"))

    /**
     * @brief exposureCovering computes the exposure values for fully covering
     * the dynamic range of the image. This function works only if the histogram
     * was compute usign VS_LOG_2.
     * @param nBits is the number of bit used for storing each output exposure image.
     * The default value is 8.
     * @param overlap is the value, in f-stops, of overlapping between two exposure images.
     * This value is set to 1 by default.
     * @return It returns an std::vector<float> which contains the exposure values
     * in f-stops for all required exposures for covering information.
     */    
    .def("exposureCovering", &pic::Histogram::exposureCovering,
        "exposureCovering computes the exposure values for fully covering"
        " the dynamic range of the image. This function works only if the histogram"
        " was compute usign VS_LOG_2.",
        py::return_value_policy::take_ownership,
        py::arg("nBits")=8, py::arg("overlap")=1.0f)
    
    // endregion Methods

    // region Arguments

    .def_readonly("bin", &pic::Histogram::bin)
    .def_readonly("bin_work", &pic::Histogram::bin_work);

    // endregion Arguments
}
