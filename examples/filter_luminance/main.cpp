// This program test the FilterLuminance of Piccante



//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

#define EIGEN_DONT_VECTORIZE

#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT

#include "piccante.hpp"

int main(int argc, char *argv[])
{
    std::string img0_str = "../_data/input/balcony_0.png";
    
    printf("Reading LDR images...");
    pic::Image img0;
    img0.Read(img0_str, pic::LT_NOR);
    
    printf("Ok\n");

    printf("Is it valid? ");
    if(img0.isValid()) 
    {
        printf("OK\n");

        //compute the luminance images
        printf("Applying FilterLuminance\n");
        pic::Image *L0 = pic::FilterLuminance::execute(&img0, NULL, pic::LT_CIE_LUMINANCE);
        L0->Write("../_data/output/filter_luminance.png", pic::LDR_type::LT_NOR);

        printf("OK\n");
    } 
    else 
    {
        printf("No, it is not valid!\n");
    }

    return 0;
}
