// This program test the FilterConv2D of Piccante


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

#include "piccante.hpp"

int main(int argc, char *argv[])
{
    std::string img_str, psf_str;

    img_str = "../_data/input/yellow_flowers.png";
    psf_str = "../_data/input/kernel_psf.png";

    printf("Reading images...");

    pic::Image img;
    img.Read(img_str);

    pic::Image psf;
    psf.Read(psf_str);

    printf("Ok\n");

    printf("Is it valid? ");
    if(img.isValid() && psf.isValid()) {
        printf("Ok\n");

        // Normalization of the PSF
        psf /= psf.getSumVal(NULL, NULL)[0];

        // Applying FilterConv2D 
        pic::Image *conv = pic::FilterConv2D::execute(&img, &psf, NULL);
        conv->Write("../_data/output/filter_conv2d.png");

        printf("Ok!\n");
    }
    else
    {
        printf("No, the image is not valid!");    
    }

    return 0;
}