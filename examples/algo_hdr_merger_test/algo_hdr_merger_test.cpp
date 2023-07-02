// compile with: clang++ -std=c++11 -I/usr/include/GL -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include algo_hdr_merger_test.cpp -lGL -lGLEW 


#include <GL/glew.h>
#include <piccante.hpp>

int main()
{
    // Load HDRobj
    pic::HDRMerger hdr_obj;
    hdr_obj.addFile("cannon1.jpg", -2);
    hdr_obj.addFile("cannon2.jpg", 0);
    hdr_obj.addFile("cannon3.jpg", +2);

    // Execute the algorithm
    pic::Image imgOut = hdr_obj.execute(&imgOut);
    imgOut.Write("result.hdr");

}