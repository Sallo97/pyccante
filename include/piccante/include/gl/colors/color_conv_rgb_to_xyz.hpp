/*

PICCANTE
The hottest HDR imaging library!
http://vcg.isti.cnr.it/piccante

Copyright (C) 2014
Visual Computing Laboratory - ISTI CNR
http://vcg.isti.cnr.it
First author: Francesco Banterle

This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.

*/

#ifndef PIC_GL_COLORS_COLOR_CONV_RGB_TO_XYZ_HPP
#define PIC_GL_COLORS_COLOR_CONV_RGB_TO_XYZ_HPP

#include "../../colors/color_conv_rgb_to_xyz.hpp"

#include "../../gl/colors/color_conv_linear.hpp"

namespace pic {

/**
 * @brief The ColorConvGLRGBtoXYZ class
 */
class ColorConvGLRGBtoXYZ: public ColorConvGLLinear
{
public:

    /**
     * @brief ColorConvGLRGBtoXYZ
     */
    ColorConvGLRGBtoXYZ(bool direct = true) : ColorConvGLLinear(direct)
    {
        memcpy(mtx, mtxRGBtoXYZ, 9 * sizeof(float));
        memcpy(mtx_inv, mtxXYZtoRGB, 9 * sizeof(float));
    }
};

} // end namespace pic

#endif /* PIC_GL_COLORS_COLOR_CONV_RGB_TO_XYZ_HPP */

