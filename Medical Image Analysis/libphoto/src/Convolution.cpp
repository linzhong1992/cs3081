#include "Convolution.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include "Kernel.h"
#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

void Convolution::applyToBuffer(PixelBuffer *buf)
{
  //applyToBuffer
  int x;
  int y;
  int width = buf->getWidth();
  int height = buf->getHeight();
  int filterHeight = k_kernel->getHeight();
  int filterWidth = k_kernel->getWidth();

  //result array
  ColorData *colorArray = new ColorData[width*height];

  int repetition = k_kernel->getRepetition();

  for(int times = 0; times < repetition ; times++)
  {
    for(x = 0; x < width; x++)
    for(y = 0; y < height; y++)
    {
      int filterY;
      int filterX;
      float red = 0.f;
      float green = 0.f;
      float blue = 0.f;
      float alpha = 1.f;

      if (buf->getPixel(x,y).getAlpha() ==0) alpha = 0.f;
      //multiply every value of the filter with corresponding image pixel
      for(filterX = 0; filterX < filterWidth; filterX++)
      for(filterY = 0; filterY < filterHeight; filterY++)
      {
        int imageX = (x - filterWidth / 2 + filterX + width) % width;
        int imageY = (y - filterHeight / 2 + filterY + height) % height;

        float multiplier = k_kernel->getValue(filterX,filterY)/k_kernel->getFactor();
        ColorData oldColor = buf->getPixel(imageX,imageY);

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
      colorArray[width*y+x] = ColorData(red,green,blue,alpha);
    }

    for(int x = 0; x < width; x++)
    for(int y = 0; y < height; y++)
    {
      buf->setPixel(x, y, colorArray[width*y+x]);
    }
  }


}
