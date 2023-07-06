//This program test the computePoissonImageEditing of Piccante


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

#include "piccante.hpp"

int main(int argc, char *argv[])
{
    std::string img0_str, img1_str, img2_str;

    img0_str = "../_data/input/poisson/target.png";
    img1_str = "../_data/input/poisson/source.png";
    img2_str = "../_data/input/poisson/mask.png";

    printf("Reading images...");

    pic::Image img_target, img_source, mask_source;
    img_target.Read(img0_str,pic::LT_NOR);
    img_source.Read(img1_str, pic::LT_NOR);
    mask_source.Read(img2_str, pic::LT_NOR);

    printf("Ok\n");

    printf("Are images valid? ");
    if( img_target.isValid() && img_source.isValid() && mask_source.isValid()) {
        printf("OK\n");

        float color[] = {1.0f, 1.0f, 1.0f};
        bool *mask = mask_source.convertToMask(color, 0.1f, false, NULL);

        pic::Image *imgOut = pic::computePoissonImageEditing(&img_source, &img_target, mask);

        imgOut->Write("../_data/output/poisson_blending_result.png", pic::LT_NOR);
    } else {
        printf("Images are not valid!\n");
    }

    return 0;
}
