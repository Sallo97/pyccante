// This program test the FilterConv2D of Piccante


//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

#include "piccante.hpp"

int main(int argc, char *argv[])
{
    printf("Adding file names to the merger...\n");
    pic::HDRMerger merger;

    for(int i = 0; i < 7; i++) {
        std::string name = "../_data/input/stack/stack_room_exp_" + pic::fromNumberToString(i) + ".jpg";
        
        pic::EXIFInfo info;
        pic::readEXIF(name, info);        
        std::cout<<name<<"\n";
        std::cout<<info.exposureTime<<"\n";

        merger.addFile(name, info.exposureTime);
    }

    printf("Ok\n");

    printf("Merging LDR images into an HDR image...");
    pic::Image *imgOut = merger.execute(NULL);
    printf("\nOk\n");

    if(imgOut != NULL) {
        if(imgOut->isValid()) {
            imgOut->Write("../_data/output/image_debevec_crf.hdr");
            pic::Image *imgTmo = pic::ReinhardTMO::executeGlobal1(imgOut, NULL);
            imgTmo->Write("../_data/output/image_debevec_crf_tmo.png", pic::LT_NOR_GAMMA);

        }
    }

    return 0;
}

