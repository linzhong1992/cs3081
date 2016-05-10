#ifndef FCHANNEL_H
#define FCHANNEL_H

#include "Filter.h"

///This is the channel filter class. It inherits from the Filter class since it is a algorithm filter
class fChannel : public Filter
{
public:

  ///default constructor
  fChannel();
  ///set the color multipliers to the inputted colors
  fChannel(float red, float green, float blue);
  ///this function applies this filter to the inputted pixelbuffer
  void applyToBuffer(PixelBuffer* buf);
  ///returns the name of this filter
  std::string getName();
  ///this function is not utilized in this filter.
  void generateKernel();

protected:
  ///user input multipliers.
  float m_redMult;
  ///user input multipliers.
  float m_greenMult;
  ///user input multipliers.
  float m_blueMult;
};

#endif
