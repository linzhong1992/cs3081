#ifndef FTHRESHOLD_H
#define FTHRESHOLD_H

#include "Filter.h"


///This is the threshold filter. It inherits from the Filter class since it is an algorithm filter
class fThreshold : public Filter
{
public:
  ///default constructor
  fThreshold();
  ///initialize the filter with the threshold level specified
  fThreshold(float level);
  ///apply the threshold filter to the inputted pixelbuffer
  void applyToBuffer(PixelBuffer* buf);
  ///return the name of this filter
  std::string getName();
  ///this function is not utilized in this filter
  void generateKernel();

protected:
  ///level selected in the gui
  float m_level;
};

#endif
