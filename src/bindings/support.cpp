#include "support.h"

/**
     * @brief return_float_ptr return the raw pointer from the python
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

py::buffer return_numpy_array (float* float_array)
{
    // Create a NumPy array that owns the data of the float* array
    py::array_t<float, py::array::c_style> np_arr ({sizeof(float_array) / sizeof(float)},
                                                  float_array);

    // Return the NumPy array to Python
    return np_arr; 
}
