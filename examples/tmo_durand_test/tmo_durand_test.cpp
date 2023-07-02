// compile with: clang++ -std=c++17 -I/usr/include/GL -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include tmo_durand_test.cpp -lGL -lGLEW 

#define PIC_DISABLE_OPENGL
#include "piccante.hpp"

int main()
{
    pic::Image img;
    img.Read("bottles.hdr");

    pic::Image imgOut = pic::DurandTMO::execute(&img, NULL);
    imgOut.Write("durand_tmo.png");
}