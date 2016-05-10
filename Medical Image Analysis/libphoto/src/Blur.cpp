#include "Blur.h"
#include "Kernel.h"
#include "PixelBuffer.h"
#include "ColorData.h"


Blur::Blur(int rep,int radius)
{
  k_kernel = new Kernel(rep,radius);
  generateKernel();
}

std::string Blur::getName()
{
  return "Blur Filter";
}

//create the kernel w the correct values for this filter
void Blur::generateKernel()
{
  /*
  010
  111
  010
  */
  //for now it is 3x3
  k_kernel->setValue(1,0,1.f);
  k_kernel->setValue(0,1,1.f);
  k_kernel->setValue(1,1,1.f);
  k_kernel->setValue(2,1,1.f);
  k_kernel->setValue(1,2,1.f);

  k_kernel->setFactor(5.f);
}
