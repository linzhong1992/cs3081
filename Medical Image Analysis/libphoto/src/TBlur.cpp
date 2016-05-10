#include "TBlur.h"
#include "MLinear.h"
#include "Kernel.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include <cmath>


TBlur::TBlur()
{
  int radius =1;
  int rep = 1;
  t_kernel = new Kernel(rep,radius);
  generateKernel();
}

std::string TBlur::getName()
{
	return "Blur";
}

void TBlur::generateKernel()
{
  /*
  010
  111
  010
  */
  //for now it is 3x3
  t_kernel->setValue(1,0,1.f);
  t_kernel->setValue(0,1,1.f);
  t_kernel->setValue(1,1,1.f);
  t_kernel->setValue(2,1,1.f);
  t_kernel->setValue(1,2,1.f);
  t_kernel->setFactor(5.f);
}

void TBlur::applyToBuffer(int toolX, int toolY, ColorData toolColor, PixelBuffer* buf)
{
  int left_bound = toolX-15;
  int right_bound = toolX+15;
  int lower_bound = toolY-15;
  int upper_bound = toolY+15;

  int x;
  int y;

  int width = right_bound - left_bound;
  int height = upper_bound - lower_bound;

  ColorData *colorArray = new ColorData[width*height];

  for(x = left_bound; x < right_bound; x++)
  for(y = lower_bound; y < upper_bound; y++)
  {
    int filterY;
    int filterX;
    float red = 0.f;
    float green = 0.f;
    float blue = 0.f;
    //multiply every value of the filter with corresponding image pixel
    for(filterX = 0; filterX < t_kernel->getWidth(); filterX++)
    for(filterY = 0; filterY < t_kernel->getHeight(); filterY++)
    {
      float multiplier = t_kernel->getValue(filterX,filterY)/t_kernel->getFactor();
      int offsetX = x-1+filterX;
      int offsetY = y-1+filterY;

      ColorData oldColor;
      if (offsetX>=0 && offsetX < buf->getWidth() && offsetY>=0 && offsetY < buf->getHeight())
        oldColor = buf->getPixel(offsetX,offsetY);

      red = red + oldColor.getRed() * multiplier;
      green = green + oldColor.getGreen() * multiplier;
      blue = blue + oldColor.getBlue() * multiplier;

    }
    //truncate
    if (red < 0) red = 0;
    if (green <0) green = 0;
    if (blue <0 ) blue = 0;
    if (red >1) red = 1;
    if (green >1) green =1;
    if (blue >1) blue = 1;

    //store the value
    colorArray[width*(y-lower_bound)+(x-left_bound)] = ColorData(red,green,blue);
  }

  for(int x = left_bound; x < right_bound; x++)
  for(int y = lower_bound; y < upper_bound; y++)
  {
    if (x>=0 && x < buf->getWidth() && y >=0 && y < buf->getHeight())
      buf->setPixel(x, y, colorArray[width*(y-lower_bound)+(x-left_bound)]);
  }
}
