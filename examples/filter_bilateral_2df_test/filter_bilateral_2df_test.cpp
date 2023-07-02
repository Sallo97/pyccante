#include <GL/glew.h>
#include <piccante.hpp>

int main()
{
    
    pic::Image imgIn;
    imgIn.Read("tommaseo_statue.png");

    pic::Image imgOut = pic::FilterBilateral2DF::execute(&imgIn, &imgOut, 4.0f, 0.05f);

    imgOut.Write("filtered.png");
}