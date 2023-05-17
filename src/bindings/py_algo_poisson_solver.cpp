#include "py_algo_poisson_solver.h"

void init_PoissonSolver(pybind11::module_& m)
{

    m.def("computePoissonSolver", &pic::computePoissonSolver,
        "execute the computePoissonSolver algorithm",
        py::arg("f"), py::arg("ret"));

    m.def
    (
        "computePoissonSolver", 
        ([] (pic::Image* f)
        {
            return pic::computePoissonSolver(f, NULL);
        }),
        "execute the computePoissonSolver algorithm",
        py::arg("f")
    );

    m.def("computePoissonSolverIterative", &pic::computePoissonSolverIterative,
        "execute the computePoissonSolverIterative algorithm",
        py::arg("img"), py::arg("laplacian"),
        py::arg("coords"), py::arg("maxSteps") = 100);
}