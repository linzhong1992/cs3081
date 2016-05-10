#ifndef EDGEDETECT_H
#define EDGEDETECT_H

#include "Convolution.h"

///This is the edge detect fulter. It inherits from the Convolution class
class EdgeDetect : public Convolution
{
public:
  ///default constructor. initialize the kernel with specific radius and repetition. Calls generateKernel to instantiate kernel
  EdgeDetect();

  ///returns the name of this filter
  std::string getName();

protected:
  ///called by the constructor to generate the kernel
  void generateKernel();
};
#endif
