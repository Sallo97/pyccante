#ifndef PYCCANTE_MAIN_CPP
#define PYCCANTE_MAIN_CPP

#include "bindings/py_dynamics_range.h"
#include "bindings/py_point_samplers.h"
#include "bindings/py_bbox.h"
#include "bindings/py_image.h"
#include "bindings/py_histogram.h"
#include "bindings/py_matrix_3_x_3.h"
#include "bindings/py_filter.h"
#include "bindings/py_filter_luminance.h"
#include "bindings/py_filter_bilateral_2df.h"
#include "bindings/py_filter_gaussian_2d.h"
#include "bindings/py_filter_rotation.h"
#include "bindings/py_filter_mosaic.h"
#include "bindings/py_filter_conv_2d.h"
#include "bindings/py_filter_warp_2d.h"
#include "bindings/py_filter_bilateral_2ds.h"
#include "bindings/py_filter_max.h"
#include "bindings/py_filter_med.h"
#include "bindings/py_filter_mean.h"
#include "bindings/py_filter_med_vec.h"
#include "bindings/py_algo_hdr_merger.h"
#include "bindings/py_algo_grow_cut.h"
#include "bindings/py_algo_poisson_solver.h"

namespace py = pybind11;

// Creating the pyccante module
PYBIND11_MODULE(pyccante, m)
{
    init_LDR_type(m);           // LDR_type Enum
    init_SAMPLER_TYPE(m);       // SAMPLER_TYPE Enum
    init_BBox(m);               // BBox Class
    init_Image(m);              // Image Class 
    init_Histogram(m);          // Histogram Class
    init_Matrix_3_x_3(m);       // Matrix3x3 Class
    init_Filter(m);             // Filter Class
    init_FilterLuminance(m);    // FilterLuminance filter-Class
    init_FilterBilateral2DF(m); // FilterBilateral2DF filter-Class
    init_FilterGaussian2D(m);   // FilterGaussian2D filter_Class
    init_FilterRotation(m);     // FilterRotation filter_Class
    init_FilterMosaic(m);       // FilterMosaic filter_class
    init_FilterConv2D(m);       // FilterConv2D filter_class
    init_FilterWarp2D(m);       // FilterWarp2 filter_class
    init_FilterBilateral2DS(m); // FilterBilateral2DS filter_class
    init_FilterMax(m);          // FilterMax filter_class
    init_FilterMed(m);          // FilterMed filter_class
    init_FilterMean(m);         // FilterMean filter_class
    init_FilterMedVec(m);       // FilterMedVec filter_class
    init_HDRMerger(m);          // HDRMerger algorithm_class
    init_GrowCut(m);            // GrowCut algorithm_class
    init_PoissonSolver(m);      // PoissonSolver algorithm_class
}

#endif /* PYCCANTE_MAIN_CPP */