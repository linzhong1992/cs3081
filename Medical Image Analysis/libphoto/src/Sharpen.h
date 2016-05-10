#ifndef SHARPEN_H
#define SHARPEN_H

#include "Convolution.h"

///This is the sharpen filter that sharpens the whole canvas. It inherits from the Convolution class
class Sharpen : public Convolution
{
public:

  ///initialize the filter with the specified repetition and radius value. Calls generateKernel to instantiate kernel
  Sharpen(int rep, int radius);
  ///return the name of this filter
  std::string getName();

protected:
  ///called by the constructor to generate the kernel according to the input repetition and radius values
  void generateKernel();
};

#endif
