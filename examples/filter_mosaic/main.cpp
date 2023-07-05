//This program test the FilterMosaic of Piccante


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

#include "piccante.hpp"

int main(int argc, char *argv[])
{
    std::string img_str;
    
    img_str = "../_data/input/yellow_flowers.png";
    

    pic::Image img;
    img.Read(img_str, pic::LDR_type::LT_NOR_GAMMA);

    printf("Is it valid? ");
    if(img.isValid()) {

        printf("OK\n");

        printf("Applying FilterMosaic...\n");
        pic::Image out = pic::FilterMosaic::execute(&img, NULL);
        printf("Ok\n");

        out.Write("../_data/output/filter_mosaic.png");
        printf("Ok\n");
    } else {
        printf("No, the file is not valid!\n");
    }

    return 0;
}
