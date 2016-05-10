#ifndef FSATURATION_H
#define FSATURATION_H

#include "Filter.h"

///This is the saturation filter. It inherits from the Filter class since it is a algorithm filter
class fSaturation : public Filter
{
public:

  ///default constructor for the saturation filter
  fSaturation();
  ///initilize the saturation filter with the input saturation value
  fSaturation(float saturation);
  ///apply the saturation filter to the inputted pixelbuffer
  void applyToBuffer(PixelBuffer* buf);
  ///return the name of this filter
  std::string getName();
  ///this function is not used in this filter
  void generateKernel();

protected:
  ///gui identified saturation level
  float m_satAmount;
};

#endif
