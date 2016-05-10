#include "TStamp.h"
#include "ColorData.h"
#include "MOval.h"
#include <cstdio>
TStamp::TStamp() 
{
}

void TStamp::applyToBuffer(int toolX, int toolY, ColorData toolColor, PixelBuffer* buffer, PixelBuffer* Sbuffer){
	
	if(Sbuffer->getWidth()==0 || Sbuffer->getHeight()==0)
	{
		printf("You have tried to stamp without a stamp loaded or loaded a stamp with 0 height or width. Please load an eligible stamp. \n");
		return;
	}
	
	//calculate the bounds for the stamping.
	int right_bound = Sbuffer->getWidth()/2;
	int left_bound = -right_bound;
	int upper_bound = Sbuffer->getHeight()/2;
	int lower_bound = -upper_bound;
	
	//iterate from the top left of the stamp buffer to the bottom right, centered at toolX, toolY.
	for (int y = lower_bound; y < upper_bound; y++) 
	{
		for (int x = left_bound; x < right_bound; x++) 
		{
			//if the intended pixel to draw is in the window continue. Else dont attempt to draw
			if(toolX+x>=0 && toolX+x<buffer->getWidth() && toolY+y>=0 && toolY+y<buffer->getHeight())
			{	
				ColorData c = Sbuffer->getPixel(x+right_bound, y+upper_bound);
				//only draw if there is 0 alpha
				if(c.getAlpha()!=0)
				{
					buffer->setPixel(toolX+x, toolY+y, c);
				}
			}
		}
	}
}

std::string TStamp::getName() 
{
	return "Stamp";
}


