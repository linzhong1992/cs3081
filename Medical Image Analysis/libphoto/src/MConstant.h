//
//  MConstant.h
//  Student Support
//
//  Created by Seth Johnson on 2/9/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//
//  MConstant is a Mask that is round, with a constant fill
//  value.


#ifndef MCONSTANT_H
#define MCONSTANT_H

#include "Mask.h"

///This is the Constant mask where the value is constant inside the array. It inherits from the Mask class
class MConstant : public Mask
{
public:
	///the constructor that specifies the radius and opacity for the mask
	MConstant(float radius, float opacity);
protected:
	///gets the intensity at the specified coordinates
	float getIntensity(int x, int y, float radius);
};

#endif
