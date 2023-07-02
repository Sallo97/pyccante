// compile with: clang++ -std=c++11 -I/usr/include/GL -Iusr/include/GLFW -Iusr/include/GLEW -I../../include/stb -I../../include/piccante/include filter_gaussian_2d_test.cpp -lGL -lGLEW -lGLU -lglut -lz


#include <GL/glew.h>
#include <piccante.hpp>

int main()
{
    pic::Image imgIn("finalbout.png",pic::LDR_type::LT_NOR);

    pic::Image imgOut = pic::FilterGaussian2D::execute(&imgIn, &imgOut, 16.12);

    imgOut.Write("filtered.png");
}