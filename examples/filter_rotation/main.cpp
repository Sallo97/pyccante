// This program test the FilterRotation of Piccante

//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

#include "piccante.hpp"

int main(int argc, char *argv[])
{
    std::string img_str;

    img_str = "../_data/input/cs_warwick.hdr";
    

    printf("Reading a 360 panoramic image file...");

    pic::Image img(img_str);

    printf("Ok\n");

    printf("Is it valid? ");
    if(img.isValid()) {
        printf("OK\n");

        bool bWritten;
        std::string name = pic::getFileNameOnly(img_str);

        pic::Image *img_rot_simple = pic::FilterRotation::execute(&img, NULL, pic::Deg2Rad(0.0f), pic::Deg2Rad(90.0f), 0.0f);
        img_rot_simple->Write("../_data/output/rotation.hdr");
        pic::Image *img_tone_map = pic::DragoTMO::execute(img_rot_simple, NULL);
        img_tone_map->Write("../_data/output/rotation_tone_map.png");

    } else {
        printf("No, the file is not valid!\n");
    }

    return 0;
}
