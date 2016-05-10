//
//  TChalk.h
//  PaintShopTester
//
//  Created by Seth Johnson on 2/26/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#ifndef TCHALK_H
#define TCHALK_H

#include "Tool.h"

///This is the Chalk tool class. It simulates the usage of chalk. It extends the Tool class
class TChalk : public Tool
{
public:
	TChalk();

	/// overrides super's implementation. The resulting mask has a linear fall off
	ColorData colorBlendMath(float mask, ColorData toolColor, ColorData canvasColor, ColorData backgroundColor);
	///Simple return the name of "chalk".
	std::string getName() ;
};

#endif
