// compile with: clang++ -std=c++17 -I/usr/include/GL -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include tmo_drago_test.cpp -lGL -lGLEW 

#define PIC_DISABLE_OPENGL
#include "piccante.hpp"

int main()
{
    pic::Image img;
    img.Read("bottles.hdr");

    pic::Image imgOut = pic::DragoTMO::execute(&img, NULL);
    imgOut.Write("drago_tmo.png");
}