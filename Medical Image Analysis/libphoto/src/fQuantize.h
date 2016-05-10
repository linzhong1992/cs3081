#ifndef FQUANTIZE_H
#define FQUANTIZE_H

#include "Filter.h"


///This is the quantize filter. It inherits from the Filter class since it is an algorithm filter
class fQuantize : public Filter
{
public:
  ///default constructor
  fQuantize();
  ///initilize the quantize kernel with the number of bins specified
  fQuantize(int bins);
  ///apply the quantize filter to the inputted pixelbuffer
  void applyToBuffer(PixelBuffer* buf);
  ///return the name of this filter
  std::string getName();

  ///this function is not used in this class
  void generateKernel();

protected:
  ///number of bins input by the user
  int m_bins;
};

#endif
