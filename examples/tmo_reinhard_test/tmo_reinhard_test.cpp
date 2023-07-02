// compile with: clang++ -std=c++17 -I/usr/include/GL -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include tmo_reinhard_test.cpp -lGL -lGLEW 

#define PIC_DISABLE_OPENGL
#include "piccante.hpp"

int main()
{
    pic::Image img;
    img.Read("bottles.hdr");
    pic::Image imgOut;
    
    imgOut = pic::ReinhardTMO::executeGlobal1(&img, NULL);
    imgOut.Write("reinhard_gtmo1.png");

    imgOut = pic::ReinhardTMO::executeGlobal2(&img, NULL);
    imgOut.Write("reinhard_gtmo2.png");

    imgOut = pic::ReinhardTMO::executeLocal1(&img, NULL);
    imgOut.Write("reinhard_ltmo1.png");

    imgOut = pic::ReinhardTMO::executeLocal2(&img, NULL);
    imgOut.Write("reinhard_ltmo2.png");
}