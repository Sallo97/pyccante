// compile with: clang++ -std=c++11 -I/usr/include/GL -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include algo_poisson_solver_test.cpp -lGL -lGLEW 


#include <GL/glew.h>
#include <piccante.hpp>
#include <vector>


int main()
{
    // Load Image
    pic::Image img;
    img.Read("target.png");
    pic::Image laplacian;
    img.Read("mask.png");
    std::vector<int> coords;
    coords.push_back(100);
    coords.push_back(100);
        
    // Execute the algorithm
    pic::Image ret = pic::computePoissonSolverIterative(&img, &laplacian, coords);
    ret.Write("return.jpg");

}