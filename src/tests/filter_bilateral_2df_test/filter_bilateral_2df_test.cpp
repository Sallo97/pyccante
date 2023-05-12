#include <GL/glew.h>
#include <piccante.hpp>

int main()
{
    pic::Image imgIn("pacman.png",pic::LDR_type::LT_NOR);

    pic::Image imgOut = pic::FilterBilateral2DF::execute(&imgIn, &imgOut, 1.5, 100.6);

    imgOut.Write("filtered.png");
}