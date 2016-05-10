#include "fThreshold.h"
#include "PixelBuffer.h"
#include "ColorData.h"
#include <cmath>
//default constructor
fThreshold::fThreshold()
{
	m_level = 1.0;
}

fThreshold::fThreshold(float level)
{
	m_level = level;
}

void fThreshold::generateKernel(){};

std::string fThreshold::getName()
{
  return "Threshold Filter";
}

void fThreshold::applyToBuffer(PixelBuffer* buf)
{
	int width = buf->getWidth();
	int height = buf->getHeight();
	//iterate through each pixel in the display
	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			ColorData current = buf->getPixel(x,y);
			float red = current.getRed();
			float green = current.getGreen();
			float blue = current.getBlue();
			//go through each color and check threshold, RGB
			if(red>=m_level)
			{
				current.setRed(1.0);
			}
			else
			{
				current.setRed(0.0);
			}
			if(green>=m_level)
			{
				current.setGreen(1.0);
			}
			else
			{
				current.setGreen(0.0);
			}
			if(blue>=m_level)
			{
				current.setBlue(1.0);
			}
			else
			{
				current.setBlue(0.0);
			}
			//update the display with the new colors
			buf->setPixel(x,y,current);
		}
	}
}
