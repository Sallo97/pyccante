// This program test the GrowCut algorithm of Piccante

//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

#include "piccante.hpp"

int main(int argc, char *argv[])
{
    printf("Reading an image...");

    pic::Image img, strokes;

    std::string img_str, strokes_str;

    img_str = "../_data/input/yellow_flowers.png";
    strokes_str = "../_data/input/yellow_flowers_segmentation_strokes.png";
    
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

            gc_seg->Write("../_data/output/" + name + "_status.pfm");

            pic::Image *gc_mask = pic::GrowCut::getMaskAsImage(gc_seg, NULL);

            gc_mask->Write("../_data/output/" + name + "_mask.png");
        }
    } else {
        printf("No, the file is not valid!\n");
    }

    return 0;
}