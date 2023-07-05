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

// This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

#include "piccante.hpp"

int main(int argc, char *argv[])
{
    std::string img_str;

    if (argc == 2)
    {
        img_str = argv[1];
    }
    else
    {
        img_str = "../data/input/tommaseo_statue.png";
    }

    printf("Reading an image...");
    pic::Image img;
    img.Read(img_str, pic::LT_NOR_GAMMA);
    printf("Ok\n");

    printf("Is it valid? ");
    if (img.isValid())
    {
        printf("Ok\n");

        printf("Estimated noise:\n");
        float *noise = pic::FilterNoiseEstimation::getNoiseEstimation(&img, NULL);
        for (int i = 0; i < img.channels; i++)
        {
            printf("Channel i-th: %f\n", noise[i]);
        }

        // the median filter
        printf("Filtering the image with the Median filter (radius of 3);\n");

        pic::Image output = pic::FilterMax::execute(&img, NULL, 7);
        output.Write("Med.png", pic::LDR_type::LT_NOR_GAMMA);
        printf("Ok!\n");

        output = pic::FilterMin::execute(&img, NULL, 7);
        output.Write("Min.png", pic::LDR_type::LT_NOR_GAMMA);

        output = pic::FilterMean::execute(&img, NULL, 7);
        output.Write("Mean.png", pic::LDR_type::LT_NOR_GAMMA);

        output = pic::FilterMed::execute(&img, NULL, 7);
        output.Write("Med.png", pic::LDR_type::LT_NOR_GAMMA);
        
        printf("Ok!\n");

    }

}
