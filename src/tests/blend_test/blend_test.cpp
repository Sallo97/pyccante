// compile with: g++ -std=c++11 -I/usr/include/GL -Iusr/include/GLFW -Iusr/include/GLEW -I../../include/stb -I../../include/piccante/include blend_test.cpp -lGL -lGLEW -lGLU -lglut -lz

#include <GL/glew.h>
#include <piccante.hpp>

int main(){

    pic::Image hello_kitty("../../test_2.png");
    pic::Image weight("../../w.png");
    pic::Image blend("../../test_1.png");
    blend.blend(&hello_kitty, &weight);
    blend.Write("../../blend.png");


}