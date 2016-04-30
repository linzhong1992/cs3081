//
//  Helpers.h
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/1/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//
//  For educational purposes only.  Please do not post online.

#ifndef __PhotoShop_Proj__Helpers__
#define __PhotoShop_Proj__Helpers__

class ColorData;

namespace Helpers {
    float lerp(float a, float b, float r);
    ColorData lerp(ColorData a, ColorData b, float r);
    float clamp(float x, float low, float high);
    int clamp(int x, int low, int high);
    ColorData clamp(ColorData x, ColorData low, ColorData high);

    float gaussian(float x, float sigma);
}

#endif
