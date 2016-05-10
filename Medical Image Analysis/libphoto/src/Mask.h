//
//  Mask.h
//  Student Support
//
//  Created by Seth Johnson on 2/9/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//


#ifndef MASK_H
#define MASK_H
/// Mask is a wrapper for the array of floats representing the shape of a tool. It is purly virtual.
/**  Mask is a wrapper for the array of floats representing the shape of
 a tool. It is pure virtual, because a mask does not inherently have
 a shape. Shapes are defined implicitly with getIntensity(). */
class Mask
{
public:

	///constructor to initialize the mask array with the specified radius and opacity
	Mask(float radius, float opacity);
	///default constructor
	Mask();
	///destructor to remove any unused memory after Flashphoto exits
	~Mask();
	/// It returns the member variable m_maskArray, which is the array of tool mask.
	float const *getFloatArray() const { return m_maskArray; }
	/// It returns the member variable m_width, which is the width of tool mask.
	int getWidth() const { return m_width;}
	/// It returns the member variable m_height, which is the height of tool mask.
	int getHeight() const {return m_height;}
	/// It returns the value of a point on the mask.
	float getValue(int x, int y) const;
protected:
	///stores the radius of the mask
	float m_radius;
	///stores the opacity of the mask
	float m_opacity;
	///stores the height of the mask
	int m_height;
	///stores the width of the mask
	int m_width;
	///stores the float array representing the mask
	float *m_maskArray;
	///sets the value at the specified coordinates with the specified value
	void setValue(int x, int y, float v);
	///generate the mask. Overridden by child classes
	void generateMask();
	///gets the intensity at the specified coordinates
	virtual float getIntensity(int x, int y, float radius) = 0;
};

#endif
