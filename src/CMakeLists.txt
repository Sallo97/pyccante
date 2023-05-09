# Finding the required packages
find_package(Python 3.8 COMPONENTS Interpreter Development.Module REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set(PYCCANTE_MODULE_NAME = "pyccante")

# Setting general values
set(HEADERS
    bindings/py_dynamics_range.h
    bindings/py_image.h
    #bindings/py_histogram.h
    #bindings/py_bbox.h
    # add here the binding headers
    )

set(SOURCES
    main.cpp
    bindings/py_image.cpp
    #bindings/py_histogram.cpp 
    # add here the binding .cpp
    )

# Detect the installed pybind package and import it into CMake
execute_process(
COMMAND "${Python_EXECUTABLE}" -m pybind11 --cmakedir
OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE PY11_DIR)
list(APPEND CMAKE_PREFIX_PATH "${PY11_DIR}")
find_package(pybind11 CONFIG REQUIRED)

# Setting the required library
include_directories(
    ../include/piccante
    ../include/stb
    ${GLEW_INCLUDE_DIRS} 
    ${OPENGL_INCLUDE_DIRS}
)

# Adding the binding modules
pybind11_add_module(pyccante ${HEADERS} ${SOURCES})

# Linking the OpenGL library
target_link_libraries(pyccante PRIVATE ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})





