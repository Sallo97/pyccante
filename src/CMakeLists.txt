# Finding the required packages
find_package(Python 3.8 COMPONENTS Interpreter Development.Module REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set(PYCCANTE_MODULE_NAME = "pyccante")

# Setting general values
set(HEADERS
    bindings/support.h
    bindings/py_dynamics_range.h
    bindings/py_image.h
    bindings/py_histogram.h
    bindings/py_bbox.h
    bindings/py_filter.h
    bindings/py_filter_luminance.h
    bindings/py_filter_bilateral_2df.h
    bindings/py_filter_gaussian_2d.h
    bindings/py_filter_rotation.h
    # add here the binding header files
    )

set(SOURCES
    main.cpp
    bindings/support.cpp
    bindings/py_dynamics_range.cpp
    bindings/py_image.cpp
    bindings/py_histogram.cpp
    bindings/py_bbox.cpp
    bindings/py_filter.cpp
    bindings/py_filter_luminance.cpp
    bindings/py_filter_bilateral_2df.cpp
    bindings/py_filter_gaussian_2d.cpp
    bindings/py_filter_rotation.cpp
    # add here the binding source files
    )

# Detect the installed pybind package and import it into CMake
execute_process(
COMMAND "${Python_EXECUTABLE}" -m pybind11 --cmakedir
OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE PY11_DIR)
list(APPEND CMAKE_PREFIX_PATH "${PY11_DIR}")
find_package(pybind11 CONFIG REQUIRED)

# Setting the required library
include_directories(
    ../include/piccante/include
    ../include/stb
    ${GLEW_INCLUDE_DIRS} 
    ${OPENGL_INCLUDE_DIRS}
)

# Adding the binding modules
pybind11_add_module(pyccante ${HEADERS} ${SOURCES})

# Linking the OpenGL library
target_link_libraries(pyccante PRIVATE ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})





