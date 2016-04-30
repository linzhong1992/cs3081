//
//  FSpecial.cpp
//  PhotoShop
//
//  Created by Sarit Ghildayal on 4/7/15.
//  Copyright (c) 2015 Sarit Ghildayal. All rights reserved.
//

#include "FSpecial.h"
#include "ColorData.h"
#include "PixelBuffer.h"

#include "FilterFactory.h"
#include "FBlur.h"

#include <cmath>

ColorData FSpecial::generatePixel(const PixelBuffer & buffer, const PixelBuffer & blurredBuffer, int x, int y) const
{
    
    const float blurredLuminance = blurredBuffer.getPixel(x, y).getLuminance();
    
    const ColorData & p = buffer.getPixel(x, y);
    
    ColorData output(
                     pow(blurredLuminance,7.0),
                     p.getRed(),
                     pow(blurredLuminance,7.0),
                     p.getAlpha());
    
    
    return output;
}

PixelBuffer * FSpecial::generateFilteredBuffer(const PixelBuffer & input_buffer) {
    
    PixelBuffer* blurredBuffer = PixelBuffer::duplicatePixelBuffer(&input_buffer);
    
    for (int y = 0; y < blurredBuffer->getHeight(); y++) {
        for (int x = 0; x < blurredBuffer->getWidth(); x++) {
            blurredBuffer->setPixel(x,y, blurredBuffer->getPixel(x,y)*1.2);
        }
    }
    
    Filter* f = FilterFactory::getFilter(FilterFactory::FILTER_BLUR, 1, 3.5);
    FilterFactory::applyFilter(f, blurredBuffer);
    
    
    for (int y = 0; y < blurredBuffer->getHeight(); y++) {
        for (int x = 0; x < blurredBuffer->getWidth(); x++) {
            blurredBuffer->setPixel(x,y, blurredBuffer->getPixel(x,y).clampedColor());
        }
    }
    
    
    delete f;
    
    PixelBuffer * output_buffer = new PixelBuffer(input_buffer.getWidth(), input_buffer.getHeight(), input_buffer.getBackground());
    for (int i = 0; i < input_buffer.getWidth(); i++) {
        for (int j = 0; j < input_buffer.getHeight(); j++) {
            ColorData p = generatePixel(input_buffer, *blurredBuffer, i, j);
            output_buffer->setPixel(i, j, p.clampedColor());
        }
    }
    
    delete blurredBuffer;
    
    return output_buffer;
}
