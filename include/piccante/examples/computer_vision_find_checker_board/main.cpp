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
        img_str = "../data/input/features/checker_board_photo.png";
    }

    printf("Reading images...");
    pic::Image img(img_str, pic::LT_NOR_GAMMA);
    printf("Is the image valid? ");

    if(img.isValid()) {
        printf("OK\n");

        std::vector< Eigen::Vector2f > corners;
        pic::findCheckerBoard(&img, corners);

        Eigen::Vector2f p0, p1;
        float length = pic::estimateLengthOfCheckers(corners, p0, p1);

        printf("The checkers' length is %3.3f pixels.\n", length);

        float *color = pic::estimateWhitePointFromCheckerBoard(&img, corners);

        pic::Image *img_wb = pic::FilterWhiteBalance::execute(&img, color, NULL);

        std::string name = pic::removeExtension(img_str);
        name = pic::removeLocalPath(name);
        img_wb->Write("../data/output/" + name + "_wb.png");


    } else {
        printf("No there is at least an invalid file!\n");
    }

    return 0;
}
