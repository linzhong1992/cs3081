//
//  ImageHandler.h
//  PhotoShop
//
//  Created by Sarit Ghildayal on 4/2/15.
//  Copyright (c) 2015 Sarit Ghildayal. All rights reserved.
//
//  For educational purposes only.  Please do not post online.

#ifndef __PhotoShop__ImageHandler__
#define __PhotoShop__ImageHandler__

#include <string>

class PixelBuffer;
/// The super class of IPNGHandler and IJPGHandler. It handles image saving/loading.
class ImageHandler {
public:
  ///differnt tyes of image that can be handled
    enum IMAGE_TYPE {
        PNG_IMAGE,
        JPG_IMAGE,
        UNKNOWN_IMAGE
    };
    /** This static function can be used directly to load image data to m_displayBuffer.*/
    static PixelBuffer* loadImage(const std::string & fileName);
    /** This static function can be used directly to save image (from bufferToSave)
    to a file, which is indicated by the first argument.*/
    static bool saveImage(const std::string & fileName, const PixelBuffer* bufferToSave);
private:
	/// Check image's type.
    static IMAGE_TYPE getImageType(const std::string & fileName);
};

#endif
