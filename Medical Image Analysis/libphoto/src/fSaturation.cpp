#include "fSaturation.h"
#include "PixelBuffer.h"
#include "ColorData.h"

//default constructor
fSaturation::fSaturation()
{
	m_satAmount = 1;
}

fSaturation::fSaturation(float saturation)
{
	m_satAmount = saturation;
}

void fSaturation::generateKernel(){};

std::string fSaturation::getName()
{
  return "Saturation Filter";
}

void fSaturation::applyToBuffer(PixelBuffer* buf)
{
	int width = buf->getWidth();
	int height = buf->getHeight();
	//iterate through the buffer
	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			ColorData current = buf->getPixel(x,y);
			//multiple the luminance by the saturation which is shifted down by one so that 0 satAmount is greyscale
			float lumXsat = current.getLuminance()*(m_satAmount-1);
			
			//update the color based upon that calculation
			current.setRed(current.getRed()*m_satAmount-lumXsat);
			current.setGreen(current.getGreen()*m_satAmount-lumXsat);
			current.setBlue(current.getBlue()*m_satAmount-lumXsat);
			
			//update the pixel in the buffer
			buf->setPixel(x, y, current.clampedColor());
		}
	}
}
