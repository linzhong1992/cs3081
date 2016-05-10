//
//  Tool.h
//  Student Support
//
//  Created by Seth Johnson on 2/6/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//



#ifndef TOOL_H
#define TOOL_H

#include <string>

class PixelBuffer;
class ColorData;
class Mask;
/// Super class for all tools.
/** This is the superclass for Tools.
 Tool is the representation of a particular PaintShop tool.
 This baseclass is abstract and does not provide a default mask.
 Tools inherited from this class should provide a name and a mask.
 Inherited classes may optionally override the default colorBlendMath. */
class Tool
{
public:
	Tool();
	virtual ~Tool();
	/// Apply the tool's effect to m_displayBuffer.
	virtual void applyToBuffer(int toolX, int toolY, ColorData toolColor, PixelBuffer* buffer);
	/// Apply the tool's effect to m_displayBuffer.
	virtual void applyToBuffer(int toolX, int toolY, ColorData toolColor, PixelBuffer* buffer, PixelBuffer* Sbuffer);
	/// Return the name of the tool.
	virtual std::string getName() = 0;

protected:
	/**We choose to abstract a Tool's color blending math in this way in order to minimize the amount
	of added code and to keep the logic consistent between the Tools.*/
	virtual ColorData colorBlendMath(float mask, ColorData toolColor, ColorData canvasColor, ColorData backgroundColor);
	///This stores the mask instantiated by each individual tool. It is read by the FlashPhoto program to be applied to canvas everytime it is clicked
	Mask *m_mask;
};

#endif
