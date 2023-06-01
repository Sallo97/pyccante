// compile with: clang++ -std=c++17 -I/usr/include/GL -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include main.cpp

#define PIC_DISABLE_OPENGL
#include "piccante.hpp"

int main()
{
    pic::Image img; 
    img.Read("ward_tmo.png", pic::LDR_type::LT_NONE);
    img.Write("/home/deck/Desktop/copy.png", pic::LDR_type::LT_NONE);

}