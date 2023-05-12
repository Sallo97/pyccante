#include "py_filter.h"



template <class FilterBase = pic::Filter> class PyFilter : public FilterBase 
{
    public:
    /* Inherit the constructors */
    using pic::Filter::Filter;

    /* Trampoline (need one for each virtual function) */

    void release() override 
    {
        PYBIND11_OVERRIDE_PURE
        (
            void,           // Return type
            pic::Filter,    // Parent class
            override        // Name of the function in C++ (must match Python name)
        );
    }

    void changePass(int pass, int tPass) override
    {
        PYBIND11_OVERRIDE_PURE
        (
            void,           // Return type
            pic::Filter,    // Parent class
            changePass,     // Name of the function in C++ (must match Python name)
            pass, tPass     // Argument(s)
        );
    }

    std::string signature() override
    {
        PYBIND11_OVERRIDE
        (
            std::string,    // Return type
            pic::Filter,    // Parent class
            signature,      // Name of the fuction in C++ (must match Python name)
        );
    }

    void OutputSize(pic::ImageVec imgIn, int &width, int &height,
                    int &channels, int &frames) override
    {
        PYBIND11_OVERRIDE
        (
            void,           // Return type
            pic::Filter,    // Parent class
            OutputSize,     // Name of the function in C++ (must match Python name)
            imgIn, width,   // Argument(s)
            height, channels, frames
        );
    }

    void ProcessAux(pic::ImageVec imgIn, pic::Image *imgOut, 
                    pic::TileList* tiles) override
    {
        PYBIND11_OVERRIDE
        (
            void,           // Return type
            pic::Filter,    // Parent class
            ProcessAux,     // Name of the function in C++ (must match Python name)
            imgIn, imgOut,  // Argument(s)
            tiles
        );
    }

    pic::Image *Process(pic::ImageVec imgIn, pic::Image* imgOut) override
    {
        PYBIND11_OVERRIDE
        (
            pic::Image*,    // Return type
            pic::Filter,    // Parent class
            Process,        // Name of the function in C++ (must match Python name)
            imgIn, imgOut   // Argument(s)
        );
    }

};


void init_Filter(pybind11::module_& m)
{
    py::class_<pic::Filter, PyFilter <> > (m, "Filter")

        // region Constructors
        .def(py::init<>())

        // endregion Constructors

        // region Functions

        .def("release", &pic::Filter::release,
            "release")
        
        .def("changePass", &pic::Filter::changePass,
            "changePass changes the pass direction.",
                py::arg("pass"), py::arg("tPass"))
        .def("signature", &pic::Filter::signature,
            "signature returns the signature for the filter.")
        
        .def("checkHalfSize", &pic::Filter::checkHalfSize,
            "checkHalfSize",
            py::arg("size"))
        
        .def("getOutputName", &pic::Filter::getOutPutName,
            "getOutPutName",
            py::arg("nameIn"))
        
        .def("cachedProcess", &pic::Filter::cachedProcess,
            "cachedProcess",
            py::arg("imgIn"), py::arg("imgOut"),
            py::arg("nameIn"))
        
        .def("OutputSize", &pic::Filter::OutputSize,
            "OutputSize",
            py::arg("imgIn"), py::arg("width"), py::arg("height"),
            py::arg("channels"), py::arg("frames"))
        
        .def("allocateOutputMemory", &pic::Filter::allocateOutputMemory,
            "allocateOutputMemory",
            py::arg("imgIn"), py::arg("imgOut"), py::arg("bDelete"))
        
        .def("insertFilter", &pic::Filter::insertFilter,
            "insertFilter",
            py::arg("flt"), py::arg("asSingle")=false)
        
        .def("setFloatParameters", &pic::Filter::setFloatParameters,
            "setFloatParameters sets float parameters.",
            py::arg("param_f"))
        
        .def("ProcessAux", &pic::Filter::ProcessAux,
            "ProcessAux",
            py::arg("imgIn"), py::arg("imgOut"), py::arg("tiles"))

        .def("Process", &pic::Filter::Process,
            "Process",
            py::arg("imgIn"), py::arg("imgOut"))
        
        // endregion

        // region Arguments
        
        .def_readonly("cachedOnly", &pic::Filter::cachedOnly)
        .def_readonly("bDelete", &pic::Filter::bDelete)
        .def_readonly("filters", &pic::Filter::filters);

        // endregion 


}