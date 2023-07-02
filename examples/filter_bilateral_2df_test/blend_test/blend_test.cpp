// compile with: g++ -std=c++17 -I/usr/include/GL -Iusr/include/GLFW -Iusr/include/GLEW -I../../include/stb -I../../../include/piccante/include blend_test.cpp -lGL -lGLEW -lGLU -lglut -lz

#include <GL/glew.h>
#include <piccante.hpp>

int main(){

    pic::Image blend("blend.png", pic::LDR_type::LT_NONE);
    pic::Image to_blend("to_blend.png", pic::LDR_type::LT_NONE);
    pic::Image weight("weight.png", pic::LDR_type::LT_NONE);

    blend.blend(&to_blend, &weight);
    blend.Write("blended.png", pic::LDR_type::LT_NONE);

}