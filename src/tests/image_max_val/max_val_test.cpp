// compile with: clang++ -std=c++17 -I/usr/include/GL -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include max_val_test.cpp -lGL -lGLEW 

#define PIC_DISABLE_OPENGL
#include "piccante.hpp"

int main()
{
    pic::Image img("./test.hdr", pic::LDR_type::LT_NONE);
    float* array = img.getMaxVal();
    std::cout<<"[";
    for (int i = 0; i < 3; ++i)
    {
        std::cout<<array[i]<<" ";
    }
    std::cout<<"]";

}