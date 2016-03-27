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
}

Tool::~Tool() 
{
	delete m_mask;
}

ColorData Tool::colorBlendMath(float mask, ColorData toolColor, ColorData canvasColor, ColorData backgroundColor) 
{
	return toolColor*mask + canvasColor*(1.0-mask);
}

void Tool::applyToBuffer(int toolX, int toolY, ColorData toolColor, PixelBuffer* buffer)
{
	if (m_mask == NULL) 
	{
		return;
	}

	int left_bound = std::max(toolX-m_mask->getWidth()/2, 0);
	int right_bound = std::min(toolX+m_mask->getWidth()/2, buffer->getWidth()-1);
	int lower_bound = std::max(toolY-m_mask->getHeight()/2, 0);
	int upper_bound = std::min(toolY+m_mask->getHeight()/2, buffer->getHeight()-1);

	for (int y = lower_bound; y <= upper_bound; y++) 
	{
		for (int x = left_bound; x <= right_bound; x++) 
		{
			int mask_x = x - (toolX-m_mask->getWidth()/2);
			int mask_y = y - (toolY-m_mask->getHeight()/2);
			float mask_value = m_mask->getValue(mask_x, mask_y);
			ColorData current = buffer->getPixel(x, y);
			
			// Because we interpolate the pixels, colors overlap
			// and increase intensity quickly. We found that cubing
			// the mask intensity compensated for this.
			float slimmed_mask_value = powf(mask_value,3);
			
			ColorData c = colorBlendMath(slimmed_mask_value, toolColor, current, buffer->getBackgroundColor());
			
			buffer->setPixel(x, y, c);
		}
	}
}
