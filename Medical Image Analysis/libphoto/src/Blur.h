#ifndef BLUR_H
#define BLUR_H

#include "Convolution.h"
#include "PixelBuffer.h"

///This is the blur class. It inherits from the Convolution class
class Blur : public Convolution
{
public:

  ///initializes the blur filter with the number of repetition and the kernel radius. calls generateKernel to generate the kernel according to the inputs
  Blur(int rep, int radius);
  ///returns the filter name
  std::string getName();

protected:
  ///called by the constructor to generate the filter kernel with the inputs and calls the setValue function of the kernel class
  void generateKernel();
};

#endif
