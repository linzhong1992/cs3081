#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "Filter.h"

///This is the overarching convolution class that all the convolution filters such as blur, sharpen, etc.
class Convolution : public Filter
{
public:

  ///this fuction applys the kernel to the inputted buffer. applying the kernel to every single pixel in the buffer
  virtual void applyToBuffer(PixelBuffer *buf);
  ///virtual function that is to be overridden by child classes
  virtual std::string getName() = 0;

protected:
  ///virtual function that is to be overridden by child classes
  virtual void generateKernel() = 0;

  //ColorData getNewColor(int x,int y,PixelBuffer *buf);


};

#endif
