// This program test the FilterBilatera2DF and FilterBilateral2DS of Piccante


// This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

#include "piccante.hpp"
int main(int argc, char *argv[])
{
    std::string img_str = "../_data/input/tommaseo_statue.png";

    printf("Reading an image...");
    pic::Image img;
    img.Read(img_str);

    printf("Ok\n");

    if(img.isValid()) {
    
        pic::Image*  out_1 = pic::FilterBilateral2DF::execute(&img, NULL, 4.0f, 0.05f);
        pic::Image*  out_2 = pic::FilterBilateral2DS::execute(&img, 4.0f, 0.05f);
        out_1->Write("../_data/output/filter_bilateral_2df.png");
        out_2->Write("../_data/output/filter_bilateral_2ds.png");

        printf("Ok\n");
    }
    else{
        printf("The image is not valid!");
    }
    return 0;
}
