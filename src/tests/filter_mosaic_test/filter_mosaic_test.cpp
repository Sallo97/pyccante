// compile with: clang++ -std=c++11 -I/usr/include/GL -Iusr/include/GLFW -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include filter_mosaic_test.cpp -lGL -lGLEW -lGLU -lglut -lz


#include <GL/glew.h>
#include <piccante.hpp>
#include <Eigen/Dense>

int main()
{
    pic::Image imgIn("rabbit.png", pic::LDR_type::LT_NOR);

    pic::Image imgOut = pic::FilterMosaic::execute(&imgIn, &imgOut);
    
    imgOut.Write("filtered.png");
}