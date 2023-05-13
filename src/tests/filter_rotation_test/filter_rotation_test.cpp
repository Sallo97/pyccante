// compile with: clang++ -std=c++11 -I/usr/include/GL -Iusr/include/GLFW -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include filter_rotation_test.cpp -lGL -lGLEW -lGLU -lglut -lz


#include <GL/glew.h>
#include <piccante.hpp>
#include <Eigen/Dense>

int main()
{
    pic::Image imgIn_1("yosh.png",pic::LDR_type::LT_NOR);
    pic::Image imgIn_2("rabbit.png", pic::LDR_type::LT_NOR);

    Eigen::Matrix3f mtx;
    mtx << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;


    pic::Image imgOut_1 = pic::FilterRotation::execute(&imgIn_1, &imgOut_1,
                                                    10, 25.5, 10.9);
    pic::Image imgOut_2 = pic::FilterRotation::execute(&imgIn_2, &imgOut_2,
                                                        mtx);

    imgOut_1.Write("filtered1.png");
    imgOut_2.Write("filtered2.png");
}