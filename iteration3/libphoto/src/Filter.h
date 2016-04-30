//
//  Filter.h
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/1/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//
//  For educational purposes only.  Please do not post online.

#ifndef FILTER_H
#define FILTER_H

class ColorData;
class PixelBuffer;

class Filter {
public:
    virtual PixelBuffer * generateFilteredBuffer(const PixelBuffer & input_buffer
                                         );

    virtual ColorData generatePixel(const PixelBuffer & buffer, int x, int y) const;
};
#endif
