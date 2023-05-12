// compile with: g++ -std=c++11 -I/usr/include/GL -Iusr/include/GLFW -Iusr/include/GLEW -I../../include/stb -I../../include/piccante/include isSimilar_test.cpp -lGL -lGLEW -lGLU -lglut -lz

#include <GL/glew.h>
#include <piccante.hpp>


int main(){
    std::cout<<"creating the empty and full Image obj\n";
    pic::Image empty;
    pic::Image full("../../test.png",pic::LDR_type::LT_NOR);

    std::cout<<"coping the parameters of full in empty\n";
    empty.width = full.width;
    empty.height = full.height;
    empty.frames = full.frames;
    empty.channels = full.channels;

    std::cout<<"executing isSimilarType\n";
    if( full.isSimilarType(&empty) )
        // Even if one image is empty, isSimilarType will return true
        std::cout<<"They are similar\n";
    else
        std::cout<<"They are not similar\n";
}