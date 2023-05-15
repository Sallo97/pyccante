#include "py_matrix_3_x_3.h"

void init_Matrix_3_x_3(pybind11::module_& m)
{
    py::class_<pic::Matrix3x3>(m, "Matrix3x3")

    // region Constructors

    .def(py::init<> (),
        "Matrix3x3")

    .def(py::init( [](py::buffer data_buffer)
    {

        // Get the raw pointer to the data
        float* data = return_float_ptr(data_buffer);

        // Return the matrix
        return pic::Matrix3x3(data);
    }),
    "Matrix3x3",
    py::arg("data")
    )

    // endregion

    // region Functions

    .def("clone", &pic::Matrix3x3::clone,
        "clone clones the matrix.")

    .def("set", ( [] (py::buffer data_buffer)
    {
        // Get the raw pointer to the data
        float* data = return_float_ptr(data_buffer);

        // Return the function
        return set(data);
    }),
    "set sets the matrix up.",
    
    py::arg("data")
    )

    .def("set", ( [] (pic::Matrix3x3* mtx)
    {
        // Return the function
        return set(mtx);
    }),
    "set sets the matrix up.",
    py::arg("mtx")
    )

    // endregion

    // region Arguments

    // endregion

}