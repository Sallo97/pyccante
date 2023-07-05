// This program test the FilterMax, FilterMin, FilterMean, and FilterMed of Piccante

// This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

#include "piccante.hpp"

int main(int argc, char *argv[])
{
    std::string img_str = "../_data/input/tommaseo_statue.png";

    printf("Reading image...");
    pic::Image img;
    img.Read(img_str, pic::LT_NOR_GAMMA);
    printf("Ok\n");

    printf("Is it valid? ");
    if (img.isValid())
    {
        printf("Ok\n");

        // Applying FilterMax
        printf("Filtering the image with the Max filter (radius of 3);\n");
        pic::Image output = pic::FilterMax::execute(&img, NULL, 7);
        output.Write("../_data/output/Filter_Max.png", pic::LDR_type::LT_NOR_GAMMA);
        printf("Ok!\n");

        // Applying FilterMin
        printf("Filtering the image with the Min filter (radius of 3);\n");
        output = pic::FilterMin::execute(&img, NULL, 7);
        output.Write("../_data/output/Filter_Min.png", pic::LDR_type::LT_NOR_GAMMA);
        printf("Ok!\n");
        
        // Applying FilterMean
        printf("Filtering the image with the Mean filter (radius of 3);\n");
        output = pic::FilterMean::execute(&img, NULL, 7);
        output.Write("../_data/output/Filter_Mean.png", pic::LDR_type::LT_NOR_GAMMA);
        printf("Ok!\n");
        
        // Applying FilterMed
        printf("Filtering the image with the Median filter (radius of 3);\n");
        output = pic::FilterMed::execute(&img, NULL, 7);
        output.Write("../_data/output/Filter_Med.png", pic::LDR_type::LT_NOR_GAMMA);
        printf("Ok!\n");
        
    }
    else
    {
        printf("No, the image is not valid!");
    }

}