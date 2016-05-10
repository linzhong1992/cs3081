#include "Kernel.h"
#include <cmath>
#include <iostream>

using std::fill;

Kernel::Kernel()
{
  k_kernelArray = NULL;
  radius =0;
  height = 0;
  width = 0;
  factor= 0;
}

//radius does not include center
Kernel::Kernel(int rep,int rad) : repetition(rep), radius(rad), height(2*radius +1) , width (2*radius+1)
{
  k_kernelArray = new float[height*width];
  //default is all 0
  fill(k_kernelArray, k_kernelArray+height*width, 0.f);
  factor = 0;
}

Kernel::~Kernel()
{
    delete [] k_kernelArray;
}

float Kernel::getValue(int x, int y) const
{
	if (k_kernelArray == NULL || x < 0 || x > width || y < 0 || y > height) {
		return 0.f;
	}
	else
	{
		return k_kernelArray[y*height + x];
	}

}

void Kernel::setValue(int x, int y, float v)
{
	if (k_kernelArray == NULL || x < 0 || x > width || y < 0 || y > height)
	{
		return;
	}
	else
	{
    factor +=v;
		k_kernelArray[y*height + x] = v;
	}
}


//debug function
void Kernel::setFactor(float f)
{
  factor = f;
}
