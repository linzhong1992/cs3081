//
//  MLinear.h
//  Student Support
//
//  Created by Seth Johnson on 2/9/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//
//  MLinear is a Mask that is round, with a linear fall-off
//  from full intensity at the center to no intensity at the
//  extremity.

#ifndef MLINEAR_H
#define MLINEAR_H

#include "Mask.h"

///This is the linear mask where the float values depend linearly on the distance from the center. It inherits from the Mask class
class MLinear : public Mask
{
public:
	///initializes the kernel with the specified radius and opacity
	MLinear(float radius, float opacity);
protected:
	/// It returns multiplier of a pointer on mask.
	float getIntensity(int x, int y, float radius);
};

#endif
