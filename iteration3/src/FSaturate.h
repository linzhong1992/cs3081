//
//  FSaturate.h
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/1/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//
//  For educational purposes only.  Please do not post online.

#ifndef FSATURATE_H
#define FSATURATE_H

#include "Filter.h"

class PixelBuffer;
class ColorData;

class FSaturate : public Filter {
    virtual ColorData generatePixel(const PixelBuffer & buffer, int x, int y) const;
    
    float m_amount;
public:
    FSaturate(float amount) : m_amount(amount) {
        
    }
    
};

#endif
