//
//  FSaturate.cpp
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/1/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#include "FSaturate.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include "Helpers.h"

ColorData FSaturate::generatePixel(const PixelBuffer &buffer, int x, int y) const {
    ColorData c = buffer.getPixel(x, y);
    float lum = c.getLuminance();
    ColorData gray(lum,lum,lum);
    
    ColorData output = Helpers::lerp(gray, c, m_amount);
    
    return output;
}