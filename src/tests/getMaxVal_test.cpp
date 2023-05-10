// compile with: g++ -std=c++11 -I/usr/include/GL -Iusr/include/GLFW -Iusr/include/GLEW -I../../include/stb -I../../include/piccante/include getMaxVal_test.cpp -lGL -lGLEW -lGLU -lglut -lz

#include <GL/glew.h>
#include <piccante.hpp>

int main(){

    // Setting the empty objs
    std::cout<<"creating the empty Image obj\n";
    pic::Image empty;
    float* empty_array = NULL;
    pic::BBox empty_box ();

    // call getMaxVal
    empty.getMaxVal(empty_box, empty_array);
    

}