// compile with: clang++ -std=c++11 -I/usr/include/GL -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include filter_max_test.cpp -lGL -lGLEW 


#include <GL/glew.h>
#include <piccante.hpp>
#include <Eigen/Dense>

int main()
{
    pic::Image imgIn("thief.ppm", pic::LDR_type::LT_NONE);

    pic::Image imgOut = pic::FilterMax::execute(&imgIn, NULL, 1);
    
    imgOut.Write("filtered.png");
}