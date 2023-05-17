// compile with: clang++ -std=c++11 -I/usr/include/GL -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include algo_grow_cut_test.cpp -lGL -lGLEW 


#include <GL/glew.h>
#include <piccante.hpp>

int main()
{
    // Load images
    pic::ImageGL img;
    img.Read("img.png", pic::LDR_type::LT_NOR_GAMMA);
    img.generateTextureGL(GL_TEXTURE_2D, GL_FLOAT, false);


    pic::ImageGL seeds;
    seeds.Read("seeds.png", pic::LDR_type::LT_NOR_GAMMA);
    seeds.generateTextureGL(GL_TEXTURE_2D, GL_FLOAT, false);

    // Execute the algorithm
    pic::Image imgOut = pic::GrowCut::execute(&img, &seeds, NULL);
    imgOut.Write("result.png");

}