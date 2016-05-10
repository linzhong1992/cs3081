#ifndef SPECIALFILTER_H
#define SPECIALFILTER_H

#include "Convolution.h"

///This is the special filter that does a cool thing :). It inherits from the Convolution class
class SpecialFilter : public Convolution
{
public:

  ///initialize the specialfilter. Calls generateKernel to instantiate kernel
  SpecialFilter();
  ///return the name of this filter
  std::string getName();
  ///override the parent apply to buffer function to apply the kernel to the filter in a special way
  void applyToBuffer(PixelBuffer *buf);

protected:
  ///called by the constructor to generate the kernel for the special filter
  void generateKernel();

};

#endif
