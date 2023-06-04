// compile with: clang++ -std=c++17 -I../../../include/stb -I../../../include/piccante/include filter_mosaic_test.cpp 


#define PIC_DISABLE_OPENGL

#include <piccante.hpp>
#include <Eigen/Dense>


int main()
{
    pic::Image imgIn("image.png", pic::LDR_type::LT_NONE);

    pic::Image imgOut = pic::FilterMosaic::execute(&imgIn, NULL);
    
    imgOut.Write("filtered.png");
}