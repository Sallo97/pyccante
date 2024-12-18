# Finding the required packages
find_package(Python 3.8 COMPONENTS Interpreter Development.Module REQUIRED)


set(PYCCANTE_MODULE_NAME = "pyccante")

# Setting general values
set(HEADERS
    bindings/support.h
    bindings/py_dynamics_range.h
    bindings/py_point_samplers.h
    bindings/py_image.h
    bindings/py_histogram.h
    bindings/py_bbox.h
    bindings/py_matrix_3_x_3.h
    bindings/py_exif.h
    bindings/py_point_samplers.h
    bindings/py_filter.h
    bindings/py_filtering/py_filter_luminance.h
    bindings/py_filtering/py_filter_bilateral_2df.h
    bindings/py_filtering/py_filter_gaussian_2d.h
    bindings/py_filtering/py_filter_rotation.h
    bindings/py_filtering/py_filter_mosaic.h
    bindings/py_filtering/py_filter_conv_2d.h
    bindings/py_filtering/py_filter_warp_2d.h
    bindings/py_filtering/py_filter_bilateral_2ds.h
    bindings/py_filtering/py_filter_max.h
    bindings/py_filtering/py_filter_min.h
    bindings/py_filtering/py_filter_med.h
    bindings/py_filtering/py_filter_mean.h
    bindings/py_filtering/py_filter_med_vec.h
    bindings/py_filtering/py_filter_simple_tmo.h
    bindings/py_algorithms/py_algo_hdr_merger.h
    bindings/py_algorithms/py_algo_grow_cut.h
    bindings/py_algorithms/py_algo_poisson_solver.h
    bindings/py_algorithms/py_algo_poisson_image_editing.h
    bindings/py_algorithms/py_algo_connected_components.h
    bindings/py_tone_mapping/py_tone_mapping_operator.h
    bindings/py_tone_mapping/py_ward_histogram_tmo.h
    bindings/py_tone_mapping/py_reinhard_tmo.h
    bindings/py_tone_mapping/py_exposure_fusion_tmo.h
    bindings/py_tone_mapping/py_durand_tmo.h
    bindings/py_tone_mapping/py_drago_tmo.h
    # add here the binding header files
    )

set(SOURCES
    main.cpp
    bindings/support.cpp
    bindings/py_dynamics_range.cpp
    bindings/py_point_samplers.cpp
    bindings/py_image.cpp
    bindings/py_histogram.cpp
    bindings/py_matrix_3_x_3.cpp
    bindings/py_exif.cpp
    bindings/py_point_samplers.cpp
    bindings/py_bbox.cpp
    bindings/py_filter.cpp
    bindings/py_filtering/py_filter_luminance.cpp
    bindings/py_filtering/py_filter_bilateral_2df.cpp
    bindings/py_filtering/py_filter_gaussian_2d.cpp
    bindings/py_filtering/py_filter_rotation.cpp
    bindings/py_filtering/py_filter_mosaic.cpp
    bindings/py_filtering/py_filter_conv_2d.cpp
    bindings/py_filtering/py_filter_warp_2d.cpp
    bindings/py_filtering/py_filter_bilateral_2ds.cpp
    bindings/py_filtering/py_filter_max.cpp
    bindings/py_filtering/py_filter_min.cpp
    bindings/py_filtering/py_filter_med.cpp
    bindings/py_filtering/py_filter_mean.cpp
    bindings/py_filtering/py_filter_med_vec.cpp
    bindings/py_filtering/py_filter_simple_tmo.cpp
    bindings/py_algorithms/py_algo_hdr_merger.cpp
    bindings/py_algorithms/py_algo_grow_cut.cpp
    bindings/py_algorithms/py_algo_poisson_solver.cpp
    bindings/py_algorithms/py_algo_poisson_image_editing.cpp
    bindings/py_algorithms/py_algo_connected_components.cpp
    bindings/py_tone_mapping/py_tone_mapping_operator.cpp
    bindings/py_tone_mapping/py_ward_histogram_tmo.cpp
    bindings/py_tone_mapping/py_reinhard_tmo.cpp
    bindings/py_tone_mapping/py_exposure_fusion_tmo.cpp
    bindings/py_tone_mapping/py_durand_tmo.cpp
    bindings/py_tone_mapping/py_drago_tmo.cpp
    # add here the binding source files
    )

# Detect the installed pybind package and import it into CMake
execute_process(
COMMAND "${Python_EXECUTABLE}" -m pybind11 --cmakedir
OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE PY11_DIR)
list(APPEND CMAKE_PREFIX_PATH "${PY11_DIR}")
find_package(pybind11 CONFIG REQUIRED)

SET( EIGEN3_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../include/piccante/include/externals" )
IF( NOT EIGEN3_INCLUDE_DIR )
    MESSAGE( FATAL_ERROR "Please point the environment variable EIGEN3_INCLUDE_DIR to the include directory of your Eigen3 installation.")
ENDIF()
INCLUDE_DIRECTORIES ( "${EIGEN3_INCLUDE_DIR}" )


# Setting the required library
include_directories(
    ../include/piccante/include
    ../include/stb
)

# Adding the binding modules
pybind11_add_module(pyccante ${HEADERS} ${SOURCES})





