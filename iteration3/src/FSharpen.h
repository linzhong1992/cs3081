//
//  FSharpen.h
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/3/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//
//  For educational purposes only.  Please do not post online.

#ifndef FSHARPEN_H
#define FSHARPEN_H

#include "FilterConvolve.h"

class Kernel;

class FSharpen : public FilterConvolve {
public:
    FSharpen(float amount);
};
#endif
