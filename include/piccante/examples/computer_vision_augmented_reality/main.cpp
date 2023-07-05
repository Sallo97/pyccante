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

#define EIGEN_DONT_VECTORIZE

#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT

#include "piccante.hpp"

int main(int argc, char *argv[])
{
    std::string img0_str = "../_data/input/features/balcony_0.png";
    
    printf("Reading LDR images...");
    pic::Image img0;
    img0.Read(img0_str, pic::LT_NOR);
    
    printf("Ok\n");

    printf("Is it valid? ");
    if(img0.isValid()) 
    {
        printf("OK\n");

        //compute the luminance images
        printf("Applying FilterLuminance\n");
        pic::Image *L0 = pic::FilterLuminance::execute(&img0, NULL, pic::LT_CIE_LUMINANCE);
        L0->Write("../_data/output/filter_luminance.png", pic::LDR_type::LT_NOR);

        printf("OK\n");
    } 
    else 
    {
        printf("No, it is not valid!\n");
    }

    return 0;
}
