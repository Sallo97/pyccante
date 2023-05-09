#include <GL/glew.h>
#include <piccante.hpp>

int main(){

    pic::Image hello_kitty("test.png", pic::LDR_type::LT_LDR);
    pic::BBox bbox = hello_kitty.getFullBox();
    float a[3];
    float* test = hello_kitty.getMaxVal(&bbox, a);
    for(int i = 0; i < 10; ++i)
        std::cout<<test[i]<<"\n";

}