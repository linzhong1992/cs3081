#include "fChannel.h"
#include "PixelBuffer.h"
#include "ColorData.h"

//default constructor
fChannel::fChannel()
{
	m_redMult = 1;
	m_greenMult = 1;
	m_blueMult = 1;
}

fChannel::fChannel(float red, float green, float blue)
{
	m_redMult = red;
	m_greenMult = green;
	m_blueMult = blue;
}

void fChannel::generateKernel(){};

std::string fChannel::getName()
{
  return "Channel Filter";
}

void fChannel::applyToBuffer(PixelBuffer* buf)
{
	int width = buf->getWidth();
	int height = buf->getHeight();
	//iterate through each pixel in buffer
	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			//multiply each color by the multiplier
			ColorData current = buf->getPixel(x,y);
			current.setRed(current.getRed()*m_redMult);
			current.setGreen(current.getGreen()*m_greenMult);
			current.setBlue(current.getBlue()*m_blueMult);
			buf->setPixel(x, y, current.clampedColor());
		}
	}
}
