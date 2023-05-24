# Setting CMake project
cmake_minimum_required(VERSION 3.18)
project(pyccante)

# Setting C++17 
set(CMAKE_CXX_STANDARD 17)

option(USE_CLANG "build application with clang" OFF) # OFF is the default

if(USE_CLANG)
    SET (CMAKE_CXX_COMPILER clang)
endif(USE_CLANG)

# Adding src directory
add_subdirectory(src)