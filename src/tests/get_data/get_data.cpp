// compile with: clang++ -std=c++17 -I/usr/include/GL -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include get_data.cpp -lGL -lGLEW 

#define PIC_DISABLE_OPENGL
#include "piccante.hpp"

int main()
{
    pic::Image img("img.png", pic::LDR_type::LT_NONE);
    float* data = img.data;
    std::cout<<*data<<"\n";
    
}