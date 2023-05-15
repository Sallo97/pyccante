// compile with: g++ -std=c++11 -I/usr/include/GL -Iusr/include/GLEW -I../../include/stb -I../../include/piccante/include jpg_test.cpp -lGL -lGLEW
// otherwise use: clang++ -std=c++11 -I/usr/include/GL -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include jpg_test.cpp -lGL -lGLEW 

#include <GL/glew.h>
#include <piccante.hpp>


int main(){
    // Load the .jpg image
    pic::Image img("cat.jpg", pic::LDR_type::LT_NONE);

    // Save the .jpg image
    img.Write("copy.jpg");
}

