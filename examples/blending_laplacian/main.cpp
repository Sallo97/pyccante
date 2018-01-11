/*

PICCANTE
The hottest HDR imaging library!
http://piccantelib.net

Copyright (C) 2014
Visual Computing Laboratory - ISTI CNR
http://vcg.isti.cnr.it
First author: Francesco Banterle

This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.

*/

//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

#include "../common_code/image_qimage_interop.hpp"

#include "piccante.hpp"

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    printf("Reading images...");

    pic::Image img_source, img_target, mask_target;
    ImageRead("../data/input/laplacian/target.png", &img_target, pic::LT_NOR);
    ImageRead("../data/input/laplacian/source.png", &img_source, pic::LT_NOR);
    ImageRead("../data/input/laplacian/mask.png", &mask_target,pic::LT_NOR);

    printf("Ok\n");

    printf("Are images valid? ");
    if( img_source.isValid() && img_target.isValid() && mask_target.isValid()) {
        printf("OK\n");

        pic::Image mask_source(mask_target.width, mask_target.height, mask_target.channels);
        mask_source = 1.0f;
        mask_source -= mask_target;

        //Creating Laplacian pyramids
        pic::Pyramid pyr_target(&img_target, true, 4);
        pic::Pyramid pyr_source(&img_source, true, 4);

        //Creating Gaussian pyramids
        pic::Pyramid pyr_mask_target(&mask_target, false, 4);
        pic::Pyramid pyr_mask_source(&mask_source, false, 4);

        //Blending
        pyr_target.mul(&pyr_mask_target);
        pyr_source.mul(&pyr_mask_source);

        pyr_target.add(&pyr_source);

        pic::Image *imgOut = pyr_target.reconstruct();

        ImageWrite(imgOut, "../data/output/laplacian_blending_result.png", pic::LT_NOR);

    } else {
        printf("All images are not valid!\n");
    }

    return 0;
}
