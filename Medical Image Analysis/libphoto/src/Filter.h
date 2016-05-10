#ifndef FILTER_H
#define FILTER_H

#include <string>

class PixelBuffer;
class ColorData;
class Kernel;

///the overarching filter class that all filters inherit from
class Filter{
public:

  ///this is the default constructor
  Filter();
  ///destructor to remove any unused memory after Flashphoto exits
  virtual ~Filter();

  ///pure virtual function to apply a filter to a pixel buffer
  virtual void applyToBuffer(PixelBuffer* buf)=0;
  ///pure virtual function to return the name of the filter
  virtual std::string getName() = 0;
  ///pure virtual function to generate the kernel of the filter
  virtual void generateKernel() = 0;

protected:

///stores the kernel of the filter. It is a one dimensional representation of a two dimensional array
  Kernel *k_kernel;
};

#endif
