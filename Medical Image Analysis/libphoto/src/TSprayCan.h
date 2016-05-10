//
//  TSprayCan.h
//  Student Support
//
//  Created by Seth Johnson on 2/6/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#ifndef TSPRAYCAN_H
#define TSPRAYCAN_H

#include "Tool.h"

///This is the spraycan class that simulates the uage of chalk. it extends the Tool class
class TSprayCan : public Tool
{
public:
	///initialize the mask with the correct fall off and colorBlendMath
	TSprayCan();
	///Simple return the name of "spraycan".
	std::string getName();
};

#endif
