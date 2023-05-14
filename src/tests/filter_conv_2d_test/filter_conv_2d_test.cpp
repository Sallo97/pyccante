// compile with: clang++ -std=c++11 -I/usr/include/GL -Iusr/include/GLFW -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include filter_conv_2d_test.cpp -lGL -lGLEW -lGLU -lglut -lz


#include <GL/glew.h>
#include <piccante.hpp>

int main() 
{
    pic::Image imgIn ("img.png", pic::LDR_type::LT_NOR);
    pic::Image conv ("conv.png", pic::LDR_type::LT_NOR);
    
    pic::Image imgOut = pic::FilterConv2D::execute(&imgIn, &conv, &imgOut);
    imgOut.Write("filtered.png");
}