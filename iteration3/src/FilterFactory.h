//
//  FilterFactory.h
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/3/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//
//  For educational purposes only.  Please do not post online.

#ifndef FILTERFACTORY_H
#define FILTERFACTORY_H

class Filter;
class PixelBuffer;

class FilterFactory
{
public:
    enum FILTER
    {
        FILTER_BLUR,
        FILTER_MOTION_BLUR,
        FILTER_SHARPEN,
        FILTER_EDGE_DETECT,
        FILTER_SATURATION,
        FILTER_QUANTIZE,
        FILTER_THRESHOLD,
        FILTER_CHANNELS,
        FILTER_SPECIAL,
        NUMFILTERS
    };
    
    static int getNumFilters();
    static Filter* getFilter(int filterID, int param_count, ...);
    static void applyFilter(Filter* f, PixelBuffer *& buffer);
};

#endif
