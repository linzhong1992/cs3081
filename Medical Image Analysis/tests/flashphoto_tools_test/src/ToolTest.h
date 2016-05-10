//
//  ToolTest.h
//  Originally created by the CSci-3081W TAs.
//

#ifndef TOOLTEST_H
#define TOOLTEST_H

//#include "BaseGfxApp.h"
#include "../../../FlashPhoto/src/FlashPhotoApp.h"
//#include <stack>
//#include <zlib.h>

class ColorData;
class PixelBuffer;
class Tool;

class ToolTest {
public:

  ToolTest();
  virtual ~ToolTest();

  bool compare(PixelBuffer* buf,PixelBuffer* buf2);
  bool penTest();
  bool eraserTest();
  bool sprayTest();
  bool calligraphyTest();
  bool highlighterTest();
  bool chalkTest();
  bool stampTest();
  bool blurTest();


private:
  PixelBuffer* testBuffer;
  PixelBuffer* resultBuffer;
  int *xArr;
  int *yArr;
  int numlines;
  void fillXYArray(char* s);

};


#endif
