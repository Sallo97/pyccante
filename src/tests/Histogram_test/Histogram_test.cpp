// compile with: g++ -std=c++11 -I/usr/include/GL -Iusr/include/GLFW -Iusr/include/GLEW -I../../include/stb -I../../include/piccante/include Histogram_test.cpp -lGL -lGLEW -lGLU -lglut -lz

#include <GL/glew.h>
#include <piccante.hpp>

int main(){

    pic::Image img = pic::Image("../../blend.png", pic::LDR_type::LT_NOR);
    pic::Histogram hist = pic::Histogram(&img, pic::VALUE_SPACE::VS_LDR, 32, 0);
    hist.write("../../histogram.png", false);
}