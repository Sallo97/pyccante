// This file contains the implementations of some functions used
// across the whole project to convert from a pointer to a numpy buffer
// and vice versa.

#include "support.h"


/**
     * @brief return_float_ptr returns the raw pointer from the python
     *        buffer, casted as a float*
     * @param data_buffer the buffer to be casted as float*.
     */
float* return_float_ptr (py::buffer data_buffer)
{
    // Get the buffer information
    py::buffer_info info = data_buffer.request();

    // Check if the buffer is type float
    if ( info.format != py::format_descriptor<float>::format() )
        throw std::runtime_error("Incompatible buffer format," 
                                 "must be of float values.");
            
    // Return the raw pointer to the data
    return static_cast<float*>(info.ptr);

}

/**
     * @brief return_bool_ptr returns the raw pointer from the python
     *        buffer, casted as a bool*
     * @param data_buffer the buffer to be casted as bool*.
     */
bool* return_bool_ptr(py::buffer data_buffer)
{
    
    // Get the buffer information
    py::buffer_info info = data_buffer.request();

    // Check if the buffer is type float
    if ( info.format != py::format_descriptor<bool>::format() )
        throw std::runtime_error("Incompatible buffer format," 
                                 "must be of bool values.");
            
    // Return the raw pointer to the data
    return static_cast<bool*>(info.ptr);
}

/**
     * @brief return_uint_ptr returns the raw pointer from the python
     *        buffer, casted as a uint*
     * @param data_buffer the buffer to be casted as uint*.
     */
uint* return_uint_ptr(py::buffer data_buffer)
{
    
    // Get the buffer information
    py::buffer_info info = data_buffer.request();

    // Check if the buffer is type float
    if ( info.format != py::format_descriptor<uint>::format() )
        throw std::runtime_error("Incompatible buffer format," 
                                 "must be of uint values.");
            
    // Return the raw pointer to the data
    return static_cast<uint*>(info.ptr);
}



/**
     * @brief return_float_NumPy converts a float pointer to a 
     *        NumPy array of float values
     * @param ptr the float* to be casted as a NumPy array.
     * @param size the size of the array
     */
py::array_t<float> return_float_NumPy(float* ptr,uint size)
{
    return py::array_t<float>(size, ptr);
}

