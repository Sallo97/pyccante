// compile with: // compile with: g++ -std=c++11 -I/usr/include/GL -Iusr/include/GLFW -Iusr/include/GLEW -I../../include/stb -I../../include/piccante/include rotates_test.cpp -lGL -lGLEW -lGLU -lglut -lz


#include <GL/glew.h>
#include <piccante.hpp>


int main(){
    // create the Image obj
    std::cout<<"creating the empty and full Image obj\n";
    pic::Image empty;
    
    // call rotate90CCW;
    empty.rotate90CCW();

    // read the nonsensical value of empty assigned by allocateAux
    std::cout << "empty.width = " << empty.width << "\n";
    std::cout << "empty.height = " << empty.height << "\n";
    std::cout << "empty.width1f = " << empty.width1f << "\n";
    std::cout << "empty.height1f = " << empty.width1f << "\n";
    std::cout << "empty.channelsf = " << empty.width1f << "\n";
    std::cout << "empty.framesf = " << empty.width1f << "\n";
    std::cout << "empty.frames1f = " << empty.width1f << "\n";
    std::cout << "empty.width1f = " << empty.width1f << "\n";
    std::cout << "empty.tstride = " << empty.tstride << "\n";
    std::cout << "empty.ystride = " << empty.ystride << "\n";
    std::cout << "empty.xstride = " << empty.xstride << "\n";
    std::cout << "empty.getFullBox = " << empty.getFullBox().toString() << "\n";

}