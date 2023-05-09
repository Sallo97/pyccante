 /*

PICCANTE Examples
The hottest examples of Piccante:
http://vcg.isti.cnr.it/piccante

Copyright (C) 2014
Visual Computing Laboratory - ISTI CNR
http://vcg.isti.cnr.it
First author: Francesco Banterle

This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3.0 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    See the GNU Lesser General Public License
    ( http://www.gnu.org/licenses/lgpl-3.0.html ) for more details.
*/

//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

#include "piccante.hpp"

int main(int argc, char *argv[])
{
    std::string img_str;

    if(argc == 2) {
        img_str = argv[1];
    } else {
        img_str = "../data/input/bottles.hdr";
    }

    printf("Reading an HDR file...");

    pic::Image img;
    img.Read(img_str, pic::LT_NOR);

    printf("Ok\n");

    printf("Is it valid? ");
    if(img.isValid()) {
        printf("OK\n");

        printf("Tone mapping using Exposure Fusion...");

        pic::Image *img_ef = pic::ExposureFusion::execute(&img, NULL);
        printf("Ok\n");

        printf("Writing the tone mapped image to disk...\n");

        std::string name = pic::removeLocalPath(img_str);

        bool bWritten = img_ef->Write("../data/output/"+ pic::removeExtension(name)  + "_ef.png", pic::LT_NOR);

        if(bWritten) {
            printf("Ok\n");
        } else {
            printf("Writing had some issues!\n");
        }

        printf("Tone mapping using Raman Fusion Operator...");

        pic::Image *img_rf = pic::RamanTMO::execute(&img, NULL);

        bWritten = img_rf->Write("../data/output/"+ pic::removeExtension(name)  + "_rf.png", pic::LT_NOR);

        if(bWritten) {
            printf("Ok\n");
        } else {
            printf("Writing had some issues!\n");
        }
    } else {
        printf("No it is not a valid file!\n");
    }

    return 0;
}
