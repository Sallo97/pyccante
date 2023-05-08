#include <GL/glew.h>
#include <piccante.hpp>

int main(){

    pic::Image hello_kitty("test.png", pic::LDR_type::LT_LDR);
    pic::Histogram histogram(&hello_kitty,pic::VALUE_SPACE::VS_LDR,3,3);
    histogram.write("histogram.png", true);
}