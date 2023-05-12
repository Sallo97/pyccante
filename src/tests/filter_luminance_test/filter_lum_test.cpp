// compile with: g++ -std=c++11 -I/usr/include/GL -Iusr/include/GLFW -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include filter_lum_test.cpp -lGL -lGLEW -lGLU -lglut -lz


#include <GL/glew.h>
#include <piccante.hpp>

int main(){
    // Load image
    pic::Image imgIn1 ("./img1.png",pic::LDR_type::LT_NOR);
    pic::Image imgIn2 ("./img2.png", pic::LDR_type::LT_NOR);
    pic::Image imgOut1;
    pic::Image imgOut2;

    // Create filter
    pic::FilterLuminance filter;
    imgOut1 = filter.execute(&imgIn1, &imgOut2);
    imgOut2 = pic::FilterLuminance::execute(&imgIn2, &imgOut2,
                                        pic::LUMINANCE_TYPE::LT_CIE_LUMINANCE);

    // Write image
    imgOut1.Write("./luminance1.png");
    imgOut2.Write("./luminance2.png");
}