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

py::buffer return_numpy_array (float* float_array)
{
    // Create a NumPy array that owns the data of the float* array
    py::array_t<float, py::array::c_style> np_arr ({sizeof(float_array) / sizeof(float)},
                                                  float_array);

    // Return the NumPy array to Python
    return np_arr; 
}


py::buffer return_bool_array (bool* bool_array)
{
    // Create a NumPy array that owns the data of the bool* array
    py::array_t<bool, py::array::c_style> np_arr ({sizeof(bool_array) / sizeof(bool)},
                                                  bool_array);

    // Return the NumPy array to Python
    return np_arr; 
}

py::buffer return_uint_array (uint* uint_array)
{
    // Create a NumPy array that owns the data of the uint* array
    py::array_t<uint, py::array::c_style> np_arr ({sizeof(uint_array) / sizeof(uint)},
                                                  uint_array);

    // Return the NumPy array to Python
    return np_arr; 
}


