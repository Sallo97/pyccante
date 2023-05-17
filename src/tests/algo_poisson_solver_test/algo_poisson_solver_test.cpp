// compile with: clang++ -std=c++11 -I/usr/include/GL -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include algo_poisson_solver_test.cpp -lGL -lGLEW 


#include <GL/glew.h>
#include <piccante.hpp>

int main()
{
    // Load Image
    pic::Image img("result.hdr", pic::LDR_type::LT_NONE);

    // Execute the algorithm
    pic::Image ret = pic::computePoissonSolver(&img, NULL);
    ret.Write("return.hdr");

}