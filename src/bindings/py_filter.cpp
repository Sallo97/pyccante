#include "py_filter.h"
#include "support.h"

class PyFilter : public pic::Filter {

};

void init_Filter(pybind11::module_& m)
{
    py::class_<pic::Filter>(m, "Filter")
        .def(py::init<> ())


}