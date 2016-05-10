//  This tool stamps a selected image onto the other image.

#ifndef TSTAMP_H
#define TSTAMP_H

#include "Tool.h"
#include "PixelBuffer.h"

///This tool stamps a selected image onto the canvas where it is clicked. It inherits teh Tool class
class TStamp : public Tool
{
public:
	TStamp();
	/// override applyToBuffer. The stamp image is stored in Sbuffer so that it can be applied
	void applyToBuffer(int toolX, int toolY, ColorData toolColor, PixelBuffer* buffer, PixelBuffer* Sbuffer);
	///Simple return the name of "stamp".
	std::string getName();
};

#endif
