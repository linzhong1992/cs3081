//
//  IJPGHandler.h
//  PhotoShop
//
//  Created by Sarit Ghildayal on 4/2/15.
//  Copyright (c) 2015 Sarit Ghildayal. All rights reserved.
//
//  For educational purposes only.  Please do not post online.

#ifndef __PhotoShop__IJPGHandler__
#define __PhotoShop__IJPGHandler__

#include <stdio.h>
#include <string>

#include <jpeglib.h>
#include <setjmp.h>

#include "ImageHandler.h"

class PixelBuffer;

///This is the JPG handler class that inherits from the ImageHandler class. Copyright (c) 2015 Sarit Ghildayal. All rights reserved.
class IJPGHandler : public ImageHandler {
public:
	/// Override loadImage() in ImageHandler.
    static PixelBuffer* loadImage(const std::string fileName);
    /// Override saveImage() in ImageHandler.
    static bool saveImage(const std::string fileName, const PixelBuffer* bufferToSave);
private:
    struct my_error_mgr {
        jpeg_error_mgr pub;	/* "public" fields */
        jmp_buf setjmp_buffer;	/* for return to caller */
    };
};

#endif
