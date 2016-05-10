#include "Sharpen.h"
#include "Kernel.h"
#include "PixelBuffer.h"
#include "ColorData.h"

#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

Sharpen::Sharpen(int rep,int radius)
{
  k_kernel = new Kernel(rep,radius);
  generateKernel();

}

std::string Sharpen::getName()
{
  return "Sharpen Filter";
}

//create the kernel w the correct values for this filter
void Sharpen::generateKernel()
{
  //-16+16+8
  /*
  -1, -1, -1, -1, -1,
  -1,  2,  2,  2, -1,
  -1,  2,  8,  2, -1,
  -1,  2,  2,  2, -1,
  -1, -1, -1, -1, -1,
  */
  //for now it is 3x3
  int i;
  int j;

  for (i=0;i<k_kernel->getWidth();i++)
  {
    for (j =0;j<k_kernel->getHeight();j++)
    {
      // if (i ==2 && j == 2)
      //   continue;
      // if (i==0 || j==0 || i== 4 || j == 4)
      //   k_kernel->setValue(i,j,-1.0);
      // if (i==1 || j==1 || i ==3 || j== 3)
      //   k_kernel->setValue(i,j,2);
      if (i ==1 && j == 1)
        continue;
      k_kernel->setValue(i,j,-1.0);
    }
  }
  //k_kernel->setValue(2,2,8);
  //k_kernel->setFactor(8.f);
  k_kernel->setValue(1,1,9.0);
  k_kernel->setFactor(1.f);

}
