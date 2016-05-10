#include "SpecialFilter.h"
#include "Kernel.h"
#include "PixelBuffer.h"
#include "ColorData.h"

#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using std::cout;
using std::endl;

SpecialFilter::SpecialFilter()
{
  int rep = 1;
  int radius = 1;
  k_kernel = new Kernel(rep,radius);
  generateKernel();

}

std::string SpecialFilter::getName()
{
  return "Special Filter";
}

//create the kernel w the correct values for this filter
void SpecialFilter::generateKernel()
{
  /*
  -1 -1 -1
  -1  9 -1
  -1 -1 -1
  */
  //we will implement one where the generatekernel depends on the size
  //for now it is 3x3
  int i;
  int j;

  for (i=0;i<k_kernel->getWidth();i++)
  {
    for (j =0;j<k_kernel->getHeight();j++)
    {
      if (i ==1 && j == 1)
        continue;
      k_kernel->setValue(i,j,-1.0);
    }
  }
  k_kernel->setValue(1,1,9);

  k_kernel->setFactor(1.f);

}

void SpecialFilter::applyToBuffer(PixelBuffer *buf)
{
  /*print out kernel
  int i;
  int j;
  for (i=0;i<k_kernel->getWidth();i++)
  {
    for (j =0;j<k_kernel->getHeight();j++)
    {
      cout << k_kernel->getValue(i,j) << endl;
    }
  }*/

  //applyToBuffer
  int x;
  int y;
  int width = buf->getWidth();
  int height = buf->getHeight();
  int filterHeight = k_kernel->getHeight();
  int filterWidth = k_kernel->getWidth();

  //result array
  //ColorData *colorArray = new ColorData[width*height];

  for(x = 0; x < width; x++)
  for(y = 0; y < height; y++)
  {
    int filterY;
    int filterX;
    float red = 0.f;
    float green = 0.f;
    float blue = 0.f;
    float alpha = 1.f;
    //if alpha is zero set alpha to 0
    if (buf->getPixel(x,y).getAlpha()==0) alpha = 0.f;
    //multiply every value of the filter with corresponding image pixel
    for(filterX = 0; filterX < filterWidth; filterX++)
    for(filterY = 0; filterY < filterHeight; filterY++)
    {
      int imageX = (x - filterWidth / 2 + filterX + width) % width;
      int imageY = (y - filterHeight / 2 + filterY + height) % height;

      float multiplier = k_kernel->getValue(filterY,filterX)/k_kernel->getFactor();
      ColorData oldColor = buf->getPixel(imageX,imageY);

      red = red + oldColor.getGreen() * multiplier;
      green = green + oldColor.getBlue() * multiplier;
      blue = blue + oldColor.getRed() * multiplier;

    }
    //truncate
    if (red < 0) red = 0;
    if (green <0) green = 0;
    if (blue <0 ) blue = 0;
    if (red >1) red = 1;
    if (green >1) green =1;
    if (blue >1) blue = 1;

    //store the value
    buf->setPixel(x,y,ColorData(red,green,blue,alpha));
  }

  // for(int x = 0; x < width; x++)
  // for(int y = 0; y < height; y++)
  // {
  //   buf->setPixel(x, y, colorArray[width*y+x]);
  // }


}
