//
//  TChalk.h
//  PaintShopTester
//
//  Created by Seth Johnson on 2/26/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//
//  For educational purposes only.  Please do not post online.

#ifndef TCHALK_H
#define TCHALK_H

#include "Tool.h"

class TChalk : public Tool 
{
public:
	TChalk();
	
	// overrides super's implementation
	ColorData colorBlendMath(float mask, ColorData toolColor, ColorData canvasColor, ColorData backgroundColor);

	std::string getName() ;
};

#endif
