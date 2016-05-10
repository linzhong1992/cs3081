//
//  TEraser.h
//  Student Support
//
//  Created by Seth Johnson on 2/6/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#ifndef TERASER_H
#define TERASER_H

#include "Tool.h"
///  This tool simulates the usage of an Eraser. It has a MConstant mask with a radius of 10.0 (diameter of 21) and an opacity of 1.0  Eraser overrides the colorBlendMath() function to provide its special eraser functionality
class TEraser : public Tool
{
public:
	///The consturctior to initialize the eraser tool. Calls generateKernel to instantiate kernel
	TEraser();

	/// overrides super's implementation. Generates the corresponding mask
	ColorData colorBlendMath(float mask, ColorData toolColor, ColorData canvasColor, ColorData backgroundColor);
	///Simple return the name of "eraser".
	std::string getName();
};

#endif
