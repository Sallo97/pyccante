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
        .def(py::init<>(),
            "Filter constructor",
            py::return_value_policy::take_ownership)

        // endregion Constructors

        // region Functions

        .def("ProcessAux", &pic::Filter::ProcessAux,
            "ProcessAux",
            py::arg("imgIn"), py::arg("imgOut"), py::arg("tiles"))

        .def("Process", &pic::Filter::Process,
            "Process",
            py::return_value_policy::take_ownership,
            py::arg("imgIn"), py::arg("imgOut"))
        
        // endregion

        // region Arguments
        
        .def_readonly("cachedOnly", &pic::Filter::cachedOnly)
        .def_readonly("bDelete", &pic::Filter::bDelete)
        .def_readonly("filters", &pic::Filter::filters);

        // endregion 


}