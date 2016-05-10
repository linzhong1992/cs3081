//
//  TPen.h
//  Student Support
//
//  Created by Seth Johnson on 2/6/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#ifndef TPEN_H
#define TPEN_H

#include "Tool.h"
///  This tool simulates the usage of a Pen. It has a MConstant mask with a radius of 1.0 (diameter of 3) and an opacity of 1.0
class TPen : public Tool
{
public:

	///the constructor initializes the mask with only the center 5 pixels at 1 (100% opaque)
	TPen();
	///Simple return the name of "pen".
	std::string getName() ;
};

#endif
