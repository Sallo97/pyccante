# Finding the required packages
find_package(Python 3.8 COMPONENTS Interpreter Development.Module REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Detect the installed pybind package and import it into CMake
execute_process(
COMMAND "${Python_EXECUTABLE}" -m pybind11 --cmakedir
OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE PY11_DIR)
list(APPEND CMAKE_PREFIX_PATH "${PY11_DIR}")
find_package(pybind11 CONFIG REQUIRED)

# Setting general values
set(HEADERS
    bindings/py_image.hpp
    # add here the binding headers
    )

set(SOURCES
    main.cpp 
    bindings/py_image.cpp
    # add here the binding .cpp
    )

# Setting the required headers
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
