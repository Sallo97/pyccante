// compile with: g++ -std=c++11 -I/usr/include/GL -Iusr/include/GLFW -Iusr/include/GLEW -I../../include/stb -I../../include/piccante/include jpg_test.cpp -lGL -lGLEW -lGLU -lglut -lz
// otherwise use: clang++ -std=c++11 -I/usr/include/GL -Iusr/include/GLFW -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include jpg_test.cpp -lGL -lGLEW -lGLU -lglut

#include <GL/glew.h>
#include <piccante.hpp>


int main(){
    // Load the .jpg image
    pic::Image img("cat.jpg", pic::LDR_type::LT_NOR);

    // Save the .jpg image
    img.Write("copy.jpg");
}