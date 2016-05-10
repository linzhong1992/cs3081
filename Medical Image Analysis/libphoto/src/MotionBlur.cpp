#include "MotionBlur.h"
#include "Kernel.h"
#include "PixelBuffer.h"
#include "ColorData.h"

#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using std::cout;
using std::endl;

MotionBlur::MotionBlur(int rep, int radius, int dir)
{
  k_kernel = new Kernel(rep,radius);
  direction = dir;
  generateKernel();
}

std::string MotionBlur::getName()
{
  return "Motion Blur Filter";
}

void MotionBlur::generateKernel()
{
  switch (direction)
  {
    case 0:
      k_kernel->setValue(1,0,1.f);
      k_kernel->setValue(1,1,1.f);
      k_kernel->setValue(1,2,1.f);
      break;
    case 1:
      k_kernel->setValue(0,1,1.f);
      k_kernel->setValue(1,1,1.f);
      k_kernel->setValue(2,1,1.f);
      break;
    case 2:
      k_kernel->setValue(0,0,1.f);
      k_kernel->setValue(1,1,1.f);
      k_kernel->setValue(2,2,1.f);
      break;
    case 3:
      k_kernel->setValue(2,0,1.f);
      k_kernel->setValue(1,1,1.f);
      k_kernel->setValue(0,2,1.f);
      break;
  }
  k_kernel->setFactor(3.f);
}
