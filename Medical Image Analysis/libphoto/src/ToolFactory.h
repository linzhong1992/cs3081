//
//  ToolFactory.h
//  Student Support
//
//  Created by Seth Johnson on 2/6/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#ifndef TOOLFACTORY_H
#define TOOLFACTORY_H

#include <vector>

class Tool;
///Use a factory class to manage all our tools
/**We decided to use a factory class to manage all our tools. Each tool is inherited from a Tool
class, and the only place these tools are explicitly included is the ToolFactory class. The
ToolFactory even communicates the names of each tool to the BrushWork class for creating the
UI. We chose this pattern in order to minimize the impact of tool change and the addition of new
tools.*/
class ToolFactory
{
public:

	///These are all the tools and the value assigned to them so that we can easily choose what tool to use
	enum TOOLS
	{
		TOOL_PEN = 0,
		TOOL_ERASER = 1,
		TOOL_SPRAYCAN = 2,
		TOOL_CALLIGRAPHYPEN = 3,
		TOOL_HIGHLIGHTER = 4,
		TOOL_CHALK = 5,
		TOOL_STAMP = 6,
		TOOL_BLUR = 7,
		NUMTOOLS = 8
	};

///return the number of tools in the Flashphoto app
	static int getNumTools();

	///create the tool from the input toolID which is one of the TOOLS enum
	static Tool* createTool(int toolID);
};

#endif
