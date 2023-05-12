// compile with: // compile with: g++ -std=c++11 -I/usr/include/GL -Iusr/include/GLFW -Iusr/include/GLEW -I../../include/stb -I../../include/piccante/include getDiagonalSize_test.cpp -lGL -lGLEW -lGLU -lglut -lz


#include <GL/glew.h>
#include <piccante.hpp>


int main(){
    std::cout<<"creating the empty Image obj\n";
    pic::Image empty;
    
    // getDiagonalSize returns sqrtf( (-1 * -1) + (-1 * -1)) = sqrtf(2) = 1.4
    std::cout << "getDiagonalSize = " << empty.getDiagonalSize() << "\n";

}