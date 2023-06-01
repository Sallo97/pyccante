// compile with: clang++ -std=c++17 -I/usr/include/GL -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include main.cpp

#define PIC_DISABLE_OPENGL
#include "piccante.hpp"

int main()
{
    pic::Image img; 
    img.Read("bottles.hdr", pic::LDR_type::LT_NONE);
    img.Write("LT_NONE.png", pic::LDR_type::LT_NONE);

    img.Read("bottles.hdr", pic::LDR_type::LT_NOR);
    img.Write("LT_NOR.png", pic::LDR_type::LT_NOR);

    img.Read("bottles.hdr", pic::LDR_type::LT_NOR_GAMMA);
    img.Write("LT_NOR_GAMMA.png", pic::LDR_type::LT_NOR_GAMMA);

    img.Read("bottles.hdr", pic::LDR_type::LT_LDR);
    img.Write("LT_LDR.png", pic::LDR_type::LT_LDR);


}