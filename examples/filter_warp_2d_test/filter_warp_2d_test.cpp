// compile with: clang++ -std=c++11 -I/usr/include/GL -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include filter_warp_2d_test.cpp -lGL -lGLEW 


#include <GL/glew.h>
#include <piccante.hpp>
#include <Eigen/Dense>

int main()
{
    pic::Image imgIn("Wart.jpg", pic::LDR_type::LT_NONE);
    
    float a[9];
    a[0] = 1;   a[1] = 0;   a[2] = 0;
    a[3] = 2;   a[4] = 1;   a[5] = 0;
    a[6] = 2;   a[7] = 3;   a[8] = 1;
        
    pic::Matrix3x3 mtx(a);
    mtx.print();

    pic::Image imgOut = pic::FilterWarp2D::execute(&imgIn, &imgOut, mtx, true, false);
    
    imgOut.Write("filtered.png");
}