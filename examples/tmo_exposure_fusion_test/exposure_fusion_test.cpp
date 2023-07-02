// compile with: clang++ -std=c++17 -I/usr/include/GL -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include exposure_fusion_test.cpp -lGL -lGLEW 

#define PIC_DISABLE_OPENGL
#include "piccante.hpp"

int main(int argc, char *argv[])
{
    printf("Reading a stack of LDR images...");
    //reading images and storing them with normalized values in [0,1]
    pic::Image img[3];
    img[0].Read("IMG_4209.jpg", pic::LT_NOR);
    img[1].Read("IMG_4210.jpg", pic::LT_NOR);
    img[2].Read("IMG_4211.jpg", pic::LT_NOR);

    printf("Ok\n");

    printf("Are these images valid? ");
    if(img[0].isValid() && img[1].isValid() && img[2].isValid()) {
        printf("Ok\n");

        printf("Aligning bright and dark exposure images to the well-exposed one... ");
        pic::Vec2i shift_dark;
        pic::Image *img_dark = pic::WardAlignment::execute(&img[0], &img[1], shift_dark);
        img_dark->Write("stack_aligned_dark.png", pic::LT_NOR);

        pic::Vec2i shift_bright;
        pic::Image *img_bright = pic::WardAlignment::execute(&img[0], &img[2], shift_bright);
        img_bright->Write("stack_aligned_bright.png", pic::LT_NOR);
        printf("Ok\n");

        printf("Fusing the aligned images... ");
        auto image_vec = pic::Triple(img_bright, &img[0], img_dark);
        pic::Image *imgOut1 = pic::ExposureFusion::executeStack(image_vec, NULL);

        if(imgOut1 != NULL) {
            imgOut1->Write("stack_aligned_exposure_fusion.png", pic::LT_NOR);
        }

        pic::Image *imgOut2 = pic::RamanTMO::executeStack(image_vec, NULL);

        if(imgOut2 != NULL) {
            imgOut2->Write("stack_aligned_raman.png", pic::LT_NOR);
        }

        printf("Ok\n");

    } else {
        printf("No, the files are not valid!\n");
    }

    return 0;
}
