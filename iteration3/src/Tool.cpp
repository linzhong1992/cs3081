//
//  Tool.cpp
//  Student Support
//
//  Created by Seth Johnson on 2/6/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#include "Tool.h"
#include "ColorData.h"
#include "Mask.h"
#include "PixelBuffer.h"
#include <cmath>

Tool::Tool() 
{
	m_mask = NULL;
    m_keep_buffer_constant = false;
    m_maxSmear = 30;
}

Tool::~Tool() 
{
    if (m_mask) {
        delete m_mask;
    }
}

void Tool::applyToBuffer(int toolX, int toolY, ColorData toolColor, PixelBuffer* buffer)
{

	int leftBound = std::max(toolX-getWidth()/2, 0);
	int rightBound = std::min(toolX+getWidth()/2, buffer->getWidth()-1);
	int lowerBound = std::max(toolY-getHeight()/2, 0);
	int upperBound = std::min(toolY+getHeight()/2, buffer->getHeight()-1);
    
    PixelBuffer* tempBuffer = buffer;
    
    if (m_keep_buffer_constant) {
        tempBuffer = PixelBuffer::duplicatePixelBuffer(buffer);
        //std::swap(tempBuffer, buffer);
    }
    
	for (int y = lowerBound; y < upperBound; y++)
	{
		for (int x = leftBound; x < rightBound; x++)
		{
			int maskX = x - (toolX-getWidth() /2);
			int maskY = y - (toolY-getHeight() /2);
			
            ColorData c = processPixel(maskX, maskY, toolColor, tempBuffer, x, y);
			
			buffer->setPixel(x, y, c);
		}
	}
    
    if (m_keep_buffer_constant) {
        //std::swap(tempBuffer, buffer);
        delete tempBuffer;
    }
}

ColorData Tool::colorBlendMath(float mask, ColorData toolColor, ColorData canvasColor, ColorData backgroundColor)
{
    return toolColor*mask + canvasColor*(1.0-mask);
}

ColorData Tool::processPixel(int maskX, int maskY, ColorData toolColor, PixelBuffer* buffer, int bufferX, int bufferY)
{
    // Because we interpolate the pixels, colors overlap
    // and increase intensity quickly. We found that cubing
    // the mask intensity compensated for this.
    ColorData result = buffer->getPixel(bufferX, bufferY);
    if (m_mask) {
        float slimmedMaskValue = powf(m_mask->getValue(maskX, maskY),3);
        result = colorBlendMath(slimmedMaskValue,toolColor, buffer->getPixel(bufferX, bufferY), buffer->getBackground());
    }
    
    return result;
}