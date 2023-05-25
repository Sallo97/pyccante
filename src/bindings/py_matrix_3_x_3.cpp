#include "py_matrix_3_x_3.h"

namespace py = pybind11;
using namespace py::literals;

std::string return_info(pic::Matrix3x3* this_mtx)
{
    std::string str;
    str.append( std::to_string(this_mtx->data[0] ) );
    str.append(" ");
    str.append( std::to_string(this_mtx->data[1]) );
    str.append(" ");
    str.append( std::to_string(this_mtx->data[2]) );
    str.append("\n");
            
    str.append( std::to_string(this_mtx->data[3]) );
    str.append(" ");
    str.append( std::to_string(this_mtx->data[4]) );
    str.append(" ");
    str.append( std::to_string(this_mtx->data[5]) );
    str.append("\n");

    str.append( std::to_string(this_mtx->data[6]) );
    str.append(" ");
    str.append( std::to_string(this_mtx->data[7]) );
    str.append(" ");
    str.append( std::to_string(this_mtx->data[8]) );
    str.append("\n");
            
    return str;
}

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

    .def("set", ( [] (pic::Matrix3x3* this_mtx,
                     py::buffer data_buffer)
    {
        // Get the raw pointer to the data
        float* data = return_float_ptr(data_buffer);

        // Return the function
        return this_mtx->set(data);
    }),
    "set sets the matrix up.",
    py::arg("data")
    )

    .def("set", ( [] (pic::Matrix3x3* this_mtx, 
                     pic::Matrix3x3* mtx)
    {
        // Return the function
        return this_mtx->set(mtx);
    }),
    "set sets the matrix up.",
    py::arg("mtx")
    )

    .def("getIdentity", &pic::Matrix3x3::getIdentity,
        "getIdentity sets the matrix as an identity matrix; diag(1, 1, 1).")

    .def("mul", ( [] (pic::Matrix3x3* this_mtx, const pic::Matrix3x3 &mtx)
    {
        // Return the function
        return this_mtx->mul(mtx);
    }),
    "mul.",
    py::arg("mtx")
    )

    .def("mul", ( [] (pic::Matrix3x3* this_mtx, 
                py::buffer vec_buffer, py::buffer ret_buffer)
    {
        // Get the raw pointer to the data
        float* vec = return_float_ptr(vec_buffer);
        
        // Get the raw pointer to the data
        float* ret = return_float_ptr(ret_buffer);

        // Call the function
        ret = this_mtx->mul(vec, ret);

        // Return the NumPy array to Python
        return py::array_t<float>( 9, ret);
    }),
    "mul.",
    py::arg("vec"), py::arg("ret")
    )

    .def("mulH", ( [] (pic::Matrix3x3* this_mtx, 
                py::buffer vec_buffer, py::buffer ret_buffer)
    {
        // Get the raw pointer to the data
        float* vec = return_float_ptr(vec_buffer);
        
        // Get the raw pointer to the data
        float* ret = return_float_ptr(ret_buffer);

        // Call the function
        ret = this_mtx->mulH(vec, ret);

        // Return the NumPy array to Python
        return py::array_t<float>( 3, ret);
    }),
    "mulH.",
    py::arg("vec"), py::arg("ret")
    )

    .def("projection", ( [] (pic::Matrix3x3* this_mtx,
                            py::buffer vec_buffer,
                            py::buffer ret_buffer)
    {
        // Get the raw pointer to the data
        float* vec = return_float_ptr(vec_buffer);
        
        // Get the raw pointer to the data
        float* ret = return_float_ptr(ret_buffer);

        // Call the function
        ret = this_mtx->projection(vec, ret);

        // Return the NumPy array to Python
        return py::array_t<float>( 9, ret);
    }),
    "projection",
    py::arg("vec"), py::arg("ret")
    )

    .def("crossProduct", ( [] (pic::Matrix3x3* this_mtx,
                              py::buffer t_buffer)
    {
        // Get the raw pointer to the data
        float* t = return_float_ptr(t_buffer);
        
        // Return the function
        return this_mtx->crossProduct(t);
    }),
    "crossProduct computes the cross product matrix",
    py::arg("t")
    )

    .def("add", &pic::Matrix3x3::add,
        "Add adds a value to the diagonal.",
        py::arg("value"))
    
    .def("determinant", &pic::Matrix3x3::determinant,
        "determinant computes the determinant of the matrix.")
    
    .def("inverse", &pic::Matrix3x3::inverse,
        "inverse computes the inverse of the matrix.",
        py::arg("ret"))
    
    .def("transpose", &pic::Matrix3x3::transpose,
        "transpose computes the transposed matrix.",
        py::arg("ret"))

    .def("setTranslationMatrix", &pic::Matrix3x3::setTranslationMatrix,
        "setTranslationMatrix sets the matrix as a translation matrix.",
        py::arg("tx"), py::arg("ty"))
    
    .def("setRotationMatrix", &pic::Matrix3x3::setRotationMatrix,
        "setRotationMatrix sets the matrix as a rotation matrix",
        py::arg("ang"))

    .def("setShearMatrix", &pic::Matrix3x3::setShearMatrix,
        py::arg("horizontal_shear"), py::arg("vertical_shear"))

    .def("setScaleMatrix", &pic::Matrix3x3::setScaleMatrix,
        py::arg("x_scale"), py::arg("y_scale"))

    .def("print", &pic::Matrix3x3::print)

    // endregion

    // region base_func

    .def("__repr__", ( [] (pic::Matrix3x3* this_mtx)
        {
            return return_info(this_mtx);
        })
        );
    
    // endregion

    // region Arguments

    // endregion

}