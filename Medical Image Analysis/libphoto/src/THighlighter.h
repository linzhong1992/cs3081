//
//  THighlighter.h
//  Student Support
//
//  Created by Seth Johnson on 2/6/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//
//

#ifndef THIGHLIGHTER_H
#define THIGHLIGHTER_H

#include "Tool.h"
///This tool simulates the usage of a Highlighter. It has a MOval mask with a radius of 7.0 (diameter of 15), an opacity of 0.4 (semi-transparent), an angle of 90 degrees counter-clockwise from the x-axis, and an elongation ratio of 0.3
class THighlighter : public Tool
{
public:
	THighlighter();

	/// overrides super's implementation and generates the corresponding mask
	ColorData colorBlendMath(float mask, ColorData toolColor, ColorData canvasColor, ColorData backgroundColor);

	///returns the name "Highligher"
	std::string getName();
};

#endif
