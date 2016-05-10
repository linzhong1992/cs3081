#include "Filter.h"
#include <cmath>
#include <iostream>
#include "ColorData.h"
#include "Kernel.h"
#include "PixelBuffer.h"

Filter::Filter()
{
  k_kernel = NULL;
}

Filter::~Filter()
{
  delete k_kernel;
}
