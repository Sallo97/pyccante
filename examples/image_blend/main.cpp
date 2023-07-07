// This program test Image::blend feature of Piccante


// This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

#include "piccante.hpp"

int main(int argc, char *argv[])
{
    std::string img_str = "../_data/input/venice.png";
    std::string blend_str = "../_data/input/blend/flower_to_blend.png";
    std::string weight_str = "../_data/input/blend/blend_mask.png";


    printf("Reading image...");
    pic::Image img;
    img.Read(img_str, pic::LT_NOR_GAMMA);

    pic::Image blend;
    blend.Read(blend_str, pic::LT_NOR_GAMMA);

    pic::Image weight;
    weight.Read(weight_str, pic::LT_NOR_GAMMA);
    printf("Ok\n");

    printf("Is it valid?\n");
    if (img.isValid())
    {
        printf("Ok\n");

        // Applying FilterMax
        printf("Applying blend...\n");
        img.blend(&blend, &weight);
        img.Write("../_data/output/blend.png", pic::LDR_type::LT_NOR_GAMMA);
        printf("Ok!\n");

    }
    else
    {
        printf("No, the image is not valid!");
    }

}