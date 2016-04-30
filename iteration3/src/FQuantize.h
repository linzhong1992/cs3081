//
//  FQuantize.h
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/3/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//
//  For educational purposes only.  Please do not post online.

#ifndef FQUANTIZE_H
#define FQUANTIZE_H

#include "Filter.h"

class FQuantize : public Filter {
    virtual ColorData generatePixel(const PixelBuffer & buffer, int x, int y) const;
    
    int m_bins;
public:
    FQuantize(int bins) : m_bins(bins) {}
};

#endif 
