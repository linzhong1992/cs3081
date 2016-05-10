#ifndef KERNEL_H
#define KERNEL_H

///This is the Kernel class used by the Convolution filters. It stores a 2D float array representing the kernel to be applies to the pixelbuffer
class Kernel
{
public:
  ///initialize the kernel with the specified repetition and radius
  Kernel(int rep,int rad);
  ///default constructor
  Kernel();
  ///destructor
  ~Kernel();
  ///returns the one dimensional representation of the two dimensional kernel float array
  float const *getFloatArray() const {return k_kernelArray; }
  ///returns the repetition value
  int getRepetition() {return repetition; }
  ///return the kernel float value at the input coordinates
  float getValue(int x, int y) const;
  ///set the value in the kernel float array at the input coordinates
  void setValue(int x, int y, float v);
  ///returns the radisu value
  int getRadius(){return radius;}
  ///return the height of the kernel
  int getHeight(){return height;}
  ///return the width of the kernel
  int getWidth(){return width;}
  ///return the multiplication factor of the kernel
  int getFactor(){return factor;}
  ///set the multiplication factor of the kernel
  void setFactor(float fac);

protected:
  ///the float array of the kernel
  float *k_kernelArray;
  ///repetition value
  int repetition;
  ///multiplication factor value
  float factor;
  ///radius of the Kernel
  int radius;
  ///height of the kernel
  int height;
  ///width of the kernel
  int width;

};

#endif
