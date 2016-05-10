#include "fQuantize.h"
#include "PixelBuffer.h"
#include "ColorData.h"
#include <cmath>
//default constructor
fQuantize::fQuantize()
{
	m_bins = 0;
}

fQuantize::fQuantize(int bins)
{
	m_bins = bins;
}

void fQuantize::generateKernel(){};

std::string fQuantize::getName()
{
  return "Quantize Filter";
}

void fQuantize::applyToBuffer(PixelBuffer* buf)
{
	int width = buf->getWidth();
	int height = buf->getHeight();
	//iterate through each pixel in the display
	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			ColorData c = buf->getPixel(x, y);
		    float red = c.getRed();
		    float blue = c.getBlue();
		    float green = c.getGreen();
		    int steps = m_bins-1;
		    red = round(red*steps)/steps;
		    green = round(green*steps)/steps;
		    blue = round(blue*steps)/steps;
		    c.setRed(red);
		    c.setGreen(green);
		    c.setBlue(blue);
			buf->setPixel(x, y, c);
		}
	}
}
