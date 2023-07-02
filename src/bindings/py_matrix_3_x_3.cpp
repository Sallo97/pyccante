// This file contains the binding of the Piccante's Matrix3x3 class

#include "py_matrix_3_x_3.h"

//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


// region support Functions

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

// endregion support Functions


/**
 * @brief binds the Matrix3x3 class to the passed module.
 */
void init_Matrix_3_x_3(pybind11::module_& m)
{
    /**
    * @brief The Matrix3x3 class provides methods for managing a 3 by 3 matrix.
    */
    py::class_<pic::Matrix3x3>(m, "Matrix3x3")

    // region Constructors

    /**
     * @brief defines an empty Matrix3x3
     */
    .def(py::init<> (),
        "Matrix3x3 constructor",
        py::return_value_policy::take_ownership)

    /**
     * @brief defines a Matrix3x3 with the values set to data
     * @param data: array containing the values associated to the matrix.
     */
    .def(py::init( [](py::buffer data_buffer)
    {

        // Get the raw pointer to the data
        float* data = return_float_ptr(data_buffer);

        // Return the matrix
        return pic::Matrix3x3(data);
    }),
    "Matrix3x3 constructor",
    py::return_value_policy::take_ownership,
    py::arg("data")
    )

    // endregion Constructors

    // region Functions

        /**
     * @brief mul multiplies the matrix with mtx.
     * @param mtx: the matrix to multiply.
     * @return: returns a matrix with the result of the multiplication.
     */
    .def("mul", ( [] (pic::Matrix3x3* this_mtx, const pic::Matrix3x3 &mtx)
    {
        // Return the function
        return this_mtx->mul(mtx);
    }),
    "mul.",
    py::return_value_policy::take_ownership,
    py::arg("mtx")
    )

    /**
     * @brief MulH multiply the matrix with a vector.
     * @param vec: vec is the vector interpreted as an array.
     * @return the resulting matrix.
     */
    .def("mulH", ( [] (pic::Matrix3x3* this_mtx, py::buffer vec_buffer)
    {
        // Get the raw pointer to the data
        float* vec = return_float_ptr(vec_buffer);

        // Call the function
        float* ret = this_mtx->mulH(vec, NULL);

        // Return the NumPy array to Python
        return return_float_NumPy(ret, 3);
    }),
    "mulH.",
    py::return_value_policy::take_ownership,
    py::arg("vec")
    )

    /**
     * @brief projection does a projection of the matrix with a vector.
     * @param vec: vec is the vector 
     * @return the resulting matrix.
     */
    .def("projection", ( [] (pic::Matrix3x3* this_mtx,
                            py::buffer vec_buffer)
    {
        // Get the raw pointer to the data
        float* vec = return_float_ptr(vec_buffer);
        
        // Call the function
        float* ret = this_mtx->projection(vec, NULL);

        // Return the NumPy array to Python
        return return_float_NumPy(ret, 9);
    }),
    "projection",
    py::return_value_policy::take_ownership,
    py::arg("vec")
    )

    /**
     * @brief crossProduct computes the cross product matrix
     * @param t is a three value array.
     */
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

    /**
     * @brief Add adds a value to the diagonal.
     * @param value is the value to be added.
     */
    .def("add", &pic::Matrix3x3::add,
        "Add adds a value to the diagonal.",
        py::arg("value"))
    
    /**
     * @brief determinant computes the determinant of the matrix.
     * @return
     */
    .def("determinant", &pic::Matrix3x3::determinant,
        "determinant computes the determinant of the matrix.",
        py::return_value_policy::take_ownership)
    
    /**
     * @brief inverse computes the inverse of the matrix.
     * @param ret
     * @return
     */
    .def("inverse", &pic::Matrix3x3::inverse,
        "inverse computes the inverse of the matrix.",
        py::return_value_policy::take_ownership,
        py::arg("ret"))
    
    /**
     * @brief transpose computes the transposed matrix.
     */
    .def("transpose", &pic::Matrix3x3::transpose,
        "transpose computes the transposed matrix.",
        py::return_value_policy::take_ownership,
        py::arg("ret"))

    // endregion Functions

    // region base_func

    .def("__repr__", ( [] (pic::Matrix3x3* this_mtx)
        {
            return return_info(this_mtx);
        })
        );
    
    // endregion base_func

    // region Custom Functions

    /**
     * @brief getIdentityMatrix3x3 returns an identity matrix as a Matrix3x3.
     * @return Returns mtx, an identity matrix as a Matrix3x3.
    */
    m.def(
        "getIdentityMatrix3x3",
        ([]()
        {
            // Create a new Matrix3x3
            pic::Matrix3x3 mtx;

            // Set it as an identity matrix
            mtx.getIdentity();

            // Return it to Python
            return mtx;
        }),
        "get an identity matrix as a Matrix3x3",
        py::return_value_policy::take_ownership
    );

    /**
     * @brief getTranslationMatrix3x3 returns a translation matrix as a Matrix3x3.
     * @param tx 
     * @param ty
     * @return Returns mtx, a translation matrix as a Matrix3x3.
    */
    m.def(
        "getTranslationMatrix3x3",
        ([](float tx, float ty)
        {
            // Create a new Matrix3x3
            pic::Matrix3x3 mtx;

            // Set it as an identity matrix
            mtx.setTranslationMatrix(tx, ty);

            // Return it to Python
            return mtx;
        }),
        "get a traslation matrix as a Matrix3x3",
        py::return_value_policy::take_ownership,
        py::arg("tx"), py::arg("ty")
    );

    /**
     * @brief getRotationMatrix3x3 returns a rotation matrix as a Matrix3x3.
     * @param ang
     * @return Returns mtx, a rotation matrix as a Matrix3x3.
    */
    m.def(
        "getRotationMatrix3x3",
        ([](float ang)
        {
            // Create a new Matrix3x3
            pic::Matrix3x3 mtx;

            // Set it as an identity matrix
            mtx.setRotationMatrix(ang);

            // Return it to Python
            return mtx;
        }),
        "get a rotation matrix as a Matrix3x3",
        py::return_value_policy::take_ownership,
        py::arg("ang")
    );
    
    /**
     * @brief getShearMatrix3x3 returns a shear matrix as a Matrix3x3.
     * @param horizontal_shear
     * @param vertical_shear
     * @return Returns mtx, a shear matrix as a Matrix3x3.
    */
    m.def(
        "getShearMatrix3x3",
        ([](float horizontal_shear, float vertical_shear)
        {
            // Create a new Matrix3x3
            pic::Matrix3x3 mtx;

            // Set it as an identity matrix
            mtx.setShearMatrix(horizontal_shear, vertical_shear);

            // Return it to Python
            return mtx;
        }),
        "get a shear matrix as a Matrix3x3",
        py::return_value_policy::take_ownership,
        py::arg("horizontal_shear"), py::arg("vertical_shear")
    );


    /**
     * @brief getScaleMatrix3x3 returns a scaling matrix as a Matrix3x3.
     * @param x_scale
     * @param y_scale
     * @return Returns mtx, a scaling matrix as a Matrix3x3.
    */
    m.def(
        "getScaleMatrix3x3",
        ([](float x_scale, float y_scale)
        {
            // Create a new Matrix3x3
            pic::Matrix3x3 mtx;

            // Set it as an identity matrix
            mtx.setShearMatrix(x_scale, y_scale);

            // Return it to Python
            return mtx;
        }),
        "get a scaling matrix as a Matrix3x3",
        py::return_value_policy::take_ownership,
        py::arg("x_scale"), py::arg("y_scale")
    );
    // endregion Custom Functions

}