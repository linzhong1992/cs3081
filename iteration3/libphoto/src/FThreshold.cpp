//
//  FTheshold.cpp
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/4/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#include "FThreshold.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include "Helpers.h"

ColorData FThreshold::generatePixel(const PixelBuffer &buffer, int x, int y) const
{
    ColorData c = buffer.getPixel(x, y);
    
    ColorData output;
    output.setRed(c.getRed() < m_amount? 0 : 1);
    output.setGreen(c.getGreen() < m_amount ? 0 : 1);
    output.setBlue(c.getBlue() < m_amount ? 0 : 1);
    
    return output;
}