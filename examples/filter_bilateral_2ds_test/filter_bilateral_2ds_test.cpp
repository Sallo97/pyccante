// compile with: clang++ -std=c++17 -I/usr/include/GL -Iusr/include/GLEW -I../../include/stb -I../../include/piccante/include filter_bilateral_2ds_test.cpp -lGL -lGLEW

#include <GL/glew.h>
#include <piccante.hpp>
#include <Eigen/Dense>

int main()
{
    pic::Image imgIn;
    imgIn.Read("tommaseo_statue.png", pic::LT_NOR_GAMMA);
    
    pic::Image imgOut = pic::FilterBilateral2DS::execute(&imgIn, NULL, 8.0f, 0.05f);
    
    imgOut.Write("filtered.png", pic::LDR_type::LT_NOR_GAMMA);
}
