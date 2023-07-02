// compile with: clang++ -std=c++11 -I/usr/include/GL -Iusr/include/GLEW -I../../../include/stb -I../../../include/piccante/include algo_grow_cut_test.cpp -lGL -lGLEW 

#define PIC_DISABLE_OPENGL

#include "piccante.hpp"

int main(int argc, char *argv[])
{
    printf("Reading an image...");

    pic::Image img, strokes;

    std::string img_str, strokes_str;

    if(argc == 3) {
        img_str = argv[1];
        strokes_str = argv[2];
    } else {
        img_str = "ye_img.png";
        strokes_str = "ye_strokes.png";
    }

    img.Read(img_str);
    strokes.Read(strokes_str);

    printf("OK\n");

    printf("Are input images valid? ");
    if(img.isValid() && strokes.isValid()) {
        printf("OK\n");

        pic::GrowCut gc;

        pic::Image *seeds = pic::GrowCut::fromStrokeImageToSeeds(&strokes, NULL);

        if(seeds != NULL) {
            pic::Image *gc_seg = gc.execute(&img, seeds, NULL);

            std::string name = pic::getFileNameOnly(img_str);

            gc_seg->Write( name + "_status.pfm");

            pic::Image *gc_mask = pic::GrowCut::getMaskAsImage(gc_seg, NULL);

            gc_mask->Write( name + "_mask.png");
        }
    } else {
        printf("No, the file is not valid!\n");
    }

    return 0;
}
