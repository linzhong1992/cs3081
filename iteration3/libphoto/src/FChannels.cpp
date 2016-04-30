//
//  FChannels.cpp
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/4/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#include "FChannels.h"
#include "ColorData.h"
#include "PixelBuffer.h"

ColorData FChannels::generatePixel(const PixelBuffer & buffer, int x, int y) const
{
    const ColorData & p = buffer.getPixel(x, y);
    ColorData output(p.getRed()*m_red, p.getGreen()*m_green, p.getBlue()*m_blue,p.getAlpha());
    return output;
}
