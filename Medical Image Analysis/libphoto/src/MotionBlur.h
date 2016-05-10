#ifndef MOTIONBLUR_H
#define MOTIONBLUR_H

#include "Convolution.h"

///This is the motionBlur filter that blurs in the specified direction. It inherits from the Convolution class
class MotionBlur : public Convolution
{
public:

  ///initialize the kernel with the repetition value, the radius value, as well as the direction
  MotionBlur(int rep, int radius, int direction);
  ///returns the name of the filter
  std::string getName();

protected:
  ///stores the direction of this filter
  int direction;
  ///called by the constructor enerate the motion blur kernel with the specified direction
  void generateKernel();

};

#endif
