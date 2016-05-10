#include "../../../FlashPhoto/src/FlashPhotoApp.h"

#include "ToolTest.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include "ToolFactory.h"
#include "Tool.h"
#include "Blur.h"
#include "Sharpen.h"
#include "MotionBlur.h"
#include "EdgeDetect.h"
#include "SpecialFilter.h"
#include "ImageHandler.h"

#include "fChannel.h"
#include "fQuantize.h"
#include "fThreshold.h"
#include "fSaturation.h"

#include <cmath>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "TPen.h"
#include "TEraser.h"
#include "TCalligraphyPen.h"
#include "THighlighter.h"
#include "TSprayCan.h"
#include "TChalk.h"
#include "TStamp.h"
#include "TBlur.h"


using std::cout;
using std::endl;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
using namespace std;

int main(int argc, char* argv[]) {
	cout<<"_____TESTING FLASHPHOTO TOOLS_____\n";
	ToolTest();
	exit(0);
}


ToolTest::ToolTest()
{
	testBuffer = new PixelBuffer(800,600, ColorData(1,1,0.95));
	if (penTest())
		cout<< "PEN SUCCESS\n";
	else
		cout<< "PEN FAIL\n";
	testBuffer = new PixelBuffer(800,600, ColorData(1,1,0.95));
	if (eraserTest())
		cout<< "ERASER SUCCESS\n";
	else
		cout<< "ERASER FAIL\n";
	testBuffer = new PixelBuffer(800,600, ColorData(1,1,0.95));
	if (sprayTest())
		cout<< "SPRAYCAN SUCCESS\n";
	else
		cout<< "SPRAYCAN FAIL\n";
	testBuffer = new PixelBuffer(800,600, ColorData(1,1,0.95));
	if (calligraphyTest())
		cout<< "CALLIGRAPHY SUCCESS\n";
	else
		cout<< "CALLIGRAPHY FAIL\n";
	testBuffer = new PixelBuffer(800,600, ColorData(1,1,0.95));
	if (highlighterTest())
		cout<< "HIGHLLIGHTER SUCCESS\n";
	else
		cout<< "HIGHLIGHTER FAIL\n";
	testBuffer = new PixelBuffer(800,600, ColorData(1,1,0.95));
	if (chalkTest())
		cout<< "CHALK SUCCESS\n";
	else
		cout<< "CHALK FAIL\n";
	testBuffer = new PixelBuffer(800,600, ColorData(1,1,0.95));
	if (stampTest())
		cout<< "STAMP SUCCESS\n";
	else
		cout<< "STAMP FAIL\n";
	testBuffer = new PixelBuffer(800,600, ColorData(1,1,0.95));
	if (blurTest())
		cout<< "BLUR SUCCESS\n";
	else
		cout<< "BLUR FAIL\n";
}

bool ToolTest::penTest()
{
	fillXYArray("coordinates/pencoordinates.txt");
	TPen *penTool = new TPen();
	for(int counter = 0; counter < numlines/2; counter++)
	{
		penTool->applyToBuffer(xArr[counter],yArr[counter], ColorData(0,0,0),testBuffer);
	}
	ImageHandler::saveImage("test_output/penTest.png", testBuffer);

	resultBuffer = ImageHandler::loadImage("results/pen_result.png");
	testBuffer = ImageHandler::loadImage("test_output/penTest.png");
	return compare(resultBuffer,testBuffer);
}

bool ToolTest::eraserTest()
{
	fillXYArray("coordinates/erasercoordinates.txt");
	TEraser *eraserTool = new TEraser();
	for(int counter = 0; counter < numlines/2; counter++)
	{
		eraserTool->applyToBuffer(xArr[counter],yArr[counter], ColorData(0,0,0),testBuffer);
	}
	ImageHandler::saveImage("test_output/eraserTest.png", testBuffer);

	resultBuffer = ImageHandler::loadImage("results/eraser_result.png");
	testBuffer = ImageHandler::loadImage("test_output/eraserTest.png");
	return compare(resultBuffer,testBuffer);
}

bool ToolTest::sprayTest()
{
	fillXYArray("coordinates/spraycoordinates.txt");
	TSprayCan *sprayTool = new TSprayCan();
	for(int counter = 0; counter < numlines/2; counter++)
	{
		sprayTool->applyToBuffer(xArr[counter],yArr[counter], ColorData(0,0,0),testBuffer);
	}
	ImageHandler::saveImage("test_output/sprayTest.png", testBuffer);

	resultBuffer = ImageHandler::loadImage("results/spray_result.png");
	testBuffer = ImageHandler::loadImage("test_output/sprayTest.png");
	return compare(resultBuffer,testBuffer);
}

bool ToolTest::calligraphyTest()
{
	fillXYArray("coordinates/calligraphycoordinates.txt");
	TCalligraphyPen *calligraphyTool = new TCalligraphyPen();
	for(int counter = 0; counter < numlines/2; counter++)
	{
		calligraphyTool->applyToBuffer(xArr[counter],yArr[counter], ColorData(0,0,0),testBuffer);
	}
	ImageHandler::saveImage("test_output/calligraphyTest.png", testBuffer);

	resultBuffer = ImageHandler::loadImage("results/calligraphy_result.png");
	testBuffer = ImageHandler::loadImage("test_output/calligraphyTest.png");
	return compare(resultBuffer,testBuffer);
}

bool ToolTest::highlighterTest()
{
	fillXYArray("coordinates/highlightercoordinates.txt");
	THighlighter *highlighterTool = new THighlighter();
	for(int counter = 0; counter < numlines/2; counter++)
	{
		highlighterTool->applyToBuffer(xArr[counter],yArr[counter], ColorData(0,0,0),testBuffer);
	}
	ImageHandler::saveImage("test_output/highlighterTest.png", testBuffer);

	resultBuffer = ImageHandler::loadImage("results/highlighter_result.png");
	testBuffer = ImageHandler::loadImage("test_output/highlighterTest.png");
	return compare(resultBuffer,testBuffer);
}

bool ToolTest::chalkTest()
{
	fillXYArray("coordinates/chalkcoordinates.txt");
	TChalk *chalkTool = new TChalk();
	for(int counter = 0; counter < numlines/2; counter++)
	{
		chalkTool->applyToBuffer(xArr[counter],yArr[counter], ColorData(0,0,0),testBuffer);
	}
	ImageHandler::saveImage("test_output/chalkTest.png", testBuffer);

	resultBuffer = ImageHandler::loadImage("results/chalk_result.png");
	testBuffer = ImageHandler::loadImage("test_output/chalkTest.png");
	return compare(resultBuffer,testBuffer);
}

bool ToolTest::stampTest()
{
	fillXYArray("coordinates/stampcoordinates.txt");
	TStamp *stampTool = new TStamp();
	PixelBuffer* testStampBuffer = ImageHandler::loadImage("pepper.png");
	for(int counter = 0; counter < numlines/2; counter++)
	{
		stampTool->applyToBuffer(xArr[counter],yArr[counter], ColorData(0,0,0),testBuffer,testStampBuffer);
	}
	ImageHandler::saveImage("test_output/stampTest.png", testBuffer);

	resultBuffer = ImageHandler::loadImage("results/stamp_result.png");
	testBuffer = ImageHandler::loadImage("test_output/stampTest.png");
	return compare(resultBuffer,testBuffer);
}

bool ToolTest::blurTest()
{
	fillXYArray("coordinates/blurcoordinates.txt");
	TBlur *blurTool = new TBlur();
	testBuffer = ImageHandler::loadImage("pepper.png");
	for(int counter = 0; counter < numlines/2; counter++)
	{
		blurTool->applyToBuffer(xArr[counter],yArr[counter], ColorData(0,0,0),testBuffer);
	}
	ImageHandler::saveImage("test_output/blurTest.png", testBuffer);

	resultBuffer = ImageHandler::loadImage("results/blur_result.png");
	testBuffer = ImageHandler::loadImage("test_output/blurTest.png");
	return compare(resultBuffer,testBuffer);
}

ToolTest::~ToolTest()
{
    if (testBuffer)
        delete testBuffer;
		if (resultBuffer)
				delete resultBuffer;
}

bool ToolTest::compare(PixelBuffer* test1, PixelBuffer* test2)
{
    const ColorData* new_data_array = test2->getData();
    const ColorData* data_array = test1->getData();
    int width;
    int height;
    if((width = test2->getWidth()) != test1->getWidth() || (height = test2->getHeight()) != test1->getHeight()) {
				return false;
    }
    else {
        for(int i = 0; i < width * height; i++) {
            if(new_data_array[i].getRed() != data_array[i].getRed() || new_data_array[i].getGreen() != data_array[i].getGreen() || new_data_array[i].getBlue() != data_array[i].getBlue()) {
								return false;
            }
        }
    }
    return true;
}

void ToolTest::fillXYArray(char* str)
{
	//read from coordinate file and intput into array
	numlines=0;
  string line;
  ifstream myfile (str);

	while (getline(myfile, line)) numlines++;
	myfile.close();

	xArr = new int[numlines/2];
	yArr = new int[numlines/2];

	int i=0,j=0;
	myfile.open(str);
  if (myfile.is_open())
  {
    while (getline(myfile,line))
    {
			if ((i+j)%2 == 0)
			{
				xArr[i] = atoi(line.c_str());
				i++;
			}
			else
			{
				yArr[j] = atoi(line.c_str());
				j++;
			}
    }
    myfile.close();
  }
}
