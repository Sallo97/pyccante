// This file contains the binding of the Piccante's PoissonSolver algorithm class

#include "py_algo_poisson_solver.h"


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL


/**
 * @brief binds the PoissonSolver class{} to the passed module.
 */
void init_PoissonSolver(pybind11::module_& m)
{

    /**
     * @brief computePoissonSolver
     * @param f
     * @param ret
     * @return
     */
    m.def
    (
        "computePoissonSolver", 
        ([] (pic::Image* f)
        {
            return pic::computePoissonSolver(f, NULL);
        }),
        "execute the computePoissonSolver algorithm",
        py::return_value_policy::take_ownership,
        py::arg("f")
    );


    /**
     * @brief computePoissonSolverIterative
     * @param img
     * @param laplacian
     * @param coords
     * @param maxSteps
     * @return
     */
    m.def("computePoissonSolverIterative", &pic::computePoissonSolverIterative,
        "execute the computePoissonSolverIterative algorithm",
        py::return_value_policy::take_ownership,
        py::arg("img"), py::arg("laplacian"),
        py::arg("coords"), py::arg("maxSteps") = 100);
}