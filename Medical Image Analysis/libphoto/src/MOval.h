//
//  MOval.h
//  Student Support
//
//  Created by Seth Johnson on 2/9/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//
///  MOval is a Mask in the shape of an ellipse with an orientation.  It takes an angle in degrees, and a ratio between height and width.  It is of constant fill.
#ifndef MOVAL_H
#define MOVAL_H

#include "Mask.h"

class MOval : public Mask
{
public:
	///initialize the mask with the specified radius, opacity, angle, ratio
	MOval(float radius, float opacity, float angle, float ratio);
protected:
	/// It returns multiplier of a pointer on mask.
	float getIntensity(int x, int y, float radius);
	///angle of the mask
	float m_angle;
	///the ratio fall off of the mask
	float m_ratio;
};

#endif
