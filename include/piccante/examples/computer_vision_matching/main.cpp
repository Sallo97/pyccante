// This program test the FilterWarp2D of Piccante


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

#include "piccante.hpp"

int main(int argc, char *argv[])
{
    std::string img0_str, img1_str;
    img0_str = "../_data/input/balcony_0.png";
    
    pic::Image img0;
    img0.Read(img0_str, pic::LT_NOR);
    
    printf("Ok\n");

    printf("Is it valid? ");
    if(img0.isValid()) {
        printf("OK\n");

        float* mtx_data [1, 1, 1, 1, 1, 1, 0, 0, 0];
        auto H = pic::Matrix3x3(mtx_data);
        
        printf("matrix:\n");
        pic::printfMat(H);

        printf("Applying H to the image..");
        pic::Image *img0_H = pic::FilterWarp2D::execute(&img0, NULL, pic::MatrixConvert(H), true, false);
        img0_H->Write("../_data/output/filter_warp_2d.png", pic::LT_NOR);
        printf("Ok.\n");
    } else {
        printf("No it is an invalid file!\n");
    }

    return 0;
}
