#ifndef TBLUR_H
#define TBLUR_H

#include "Tool.h"
#include "Kernel.h"

///This is the blur tool that Blurs in the vincinity of the mouse click. It inherits the Tool class
class TBlur : public Tool
{
public:
  TBlur();
  /// Simple return the name of "blur".
  std::string getName();
  /// override applyToBuffer.
  void applyToBuffer(int toolX, int toolY, ColorData toolColor, PixelBuffer* buffer);

protected:
  /// Generate the kernel for blur tool. Similar to the way the Blur filter works.
  void generateKernel();
  ///stores the array representation of the kernel
  Kernel *t_kernel;
};

#endif
