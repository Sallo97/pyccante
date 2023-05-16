// compile with: clang++ -std=c++11 -I/usr/include/GL -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include filter_bilateral_2ds_test.cpp -lGL -lGLEW 

#include <GL/glew.h>
#include <piccante.hpp>
#include <Eigen/Dense>

int main()
{
    pic::Image imgIn("crash.bmp", pic::LDR_type::LT_NONE);
    
    pic::Image imgOut = pic::FilterBilateral2DS::execute(&imgIn, NULL, 2.5, 2.5);
    
    imgOut.Write("filtered.png");
}