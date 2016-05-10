#include "EdgeDetect.h"
#include "Kernel.h"
#include "PixelBuffer.h"
#include "ColorData.h"

EdgeDetect::EdgeDetect()
{
  int rep = 1;
  int radius = 1;
  k_kernel = new Kernel(rep,radius);
  generateKernel();
}

std::string EdgeDetect::getName()
{
  return "Edge Detect Filter";
}

//create the kernel w the correct values for this filter
void EdgeDetect::generateKernel()
{
  /*
  -1 -1 -1
  -1  8 -1
  -1 -1 -1
  */
  //we will implement one where the generatekernel depends on the size
  //for now it is 3x3
  int i;
  int j;

  for (i=0;i<k_kernel->getWidth();i++)
  {
    for (j =0;j<k_kernel->getHeight();j++)
    {
      if (i ==1 && j == 1)
        continue;
      k_kernel->setValue(i,j,-1.0);
    }
  }
  k_kernel->setValue(1,1,8.0);
  k_kernel->setFactor(1.f);
}
