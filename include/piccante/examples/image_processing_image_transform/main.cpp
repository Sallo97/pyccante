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

//This means that we disable Eigen; some functionalities cannot be used.
//For example, estimating the camera response function
#define PIC_DISABLE_EIGEN

//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

//This means we do not use QT for I/O
#define PIC_DISABLE_QT

#include "piccante.hpp"

#include<chrono>
#include<ctime>

int main(int argc, char *argv[])
{
    printf("Reading an HDR file...");

    pic::Image img;
    img.Read("../data/input/tommaseo_statue.png");

    printf("Ok\n");

    printf("Is it valid? ");
    if(img.isValid()) {
        printf("OK\n");

        bool bSameSize = true; //the output image is going to be the sames size of the input one

        //setting up a (64,64) pixels translation matrix
        printf("\nTranslating the image of 64,64 pixels...");
        pic::Matrix3x3 h;
        h.setTranslationMatrix(64.0f, 64.0f);

        pic::Image *imgOut_tra = pic::FilterWarp2D::execute(&img, NULL, h, bSameSize);
        printf("Ok\n");

        printf("Writing the output...");
        bool bWritten = imgOut_tra->Write("../data/output/ip_translated_64_64_pixels.bmp");

        if(bWritten) {
            printf("Ok\n");
        } else {
            printf("Writing had some issues!\n");
        }

        //set up a 45 degree rotation matrix
        printf("\nRotating the image of 45 degrees...");
        h.setRotationMatrix(pic::Deg2Rad(45.0f));

        pic::Image *imgOut_rot = pic::FilterWarp2D::execute(&img, NULL, h, bSameSize, true);
        printf("Ok\n");

        printf("Writing the output...");
        bWritten = imgOut_rot->Write("../data/output/ip_rotated_45_degrees.bmp");

        if(bWritten) {
            printf("Ok\n");
        } else {
            printf("Writing had some issues!\n");
        }

        //set up a shear degree rotation matrix
        printf("\nApplying shear transform to the image...");
        h.setShearMatrix(0.2f, 0.1f);
        pic::Image *imgOut_sheared = pic::FilterWarp2D::execute(&img, NULL, h, bSameSize, true);

        printf("Ok\n");

        printf("Writing the output...");
        bWritten = imgOut_sheared->Write("../data/output/ip_shear_transform.bmp");

        if(bWritten) {
            printf("Ok\n");
        } else {
            printf("Writing had some issues!\n");
        }

        //set up a scaling matrix
        printf("\nApplying a scaling transform to the image...");
        h.setScaleMatrix(0.5f, 0.75f);
        pic::Image *imgOut_scaled = pic::FilterWarp2D::execute(&img, NULL, h, bSameSize, true);

        printf("Ok\n");

        printf("Writing the output...");
        bWritten = imgOut_scaled->Write("../data/output/ip_scaled.bmp");

        if(bWritten) {
            printf("Ok\n");
        } else {
            printf("Writing had some issues!\n");
        }
    } else {
        printf("No, the file is not valid!\n");
    }

    return 0;
}
