// compile with: clang++ -std=c++11 -I/usr/include/GL -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include filter_med_vec_test.cpp -lGL -lGLEW 


#include <GL/glew.h>
#include <piccante.hpp>
int main()
{
    pic::Image imgIn("crash.bmp", pic::LDR_type::LT_NONE);

    pic::Image imgOut = pic::FilterMedVec::execute(&imgIn, NULL, 1);
    
    imgOut.Write("filtered.png");
}