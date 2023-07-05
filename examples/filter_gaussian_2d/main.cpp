// This program test the FilterGaussian2D of Piccante


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

#include "piccante.hpp"

int main(int argc, char *argv[])
{
    std::string name_str = "../_data/input/balcony_0.png";
    
    printf("Reading an HDR file...");

    pic::Image img;
    img.Read(name_str);

    printf("Ok\n");

    printf("Is it valid? ");
    if(img.isValid()) {
        printf("Ok\n");

        printf("Filtering the image with a Gaussian filter with sigma = 4.0...");
        pic::Image *output = pic::FilterGaussian2D::execute(&img, NULL, 4.0f);

        printf("Ok!\n");

        printf("Writing the file to disk...");
        bool bWritten = output->Write("../_data/output/filter_gaussian_2d.png");
    }
}