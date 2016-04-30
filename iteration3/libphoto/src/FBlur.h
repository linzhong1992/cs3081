//
//  FBlur.h
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/2/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//
//  For educational purposes only.  Please do not post online.

#ifndef FBLUR_H
#define FBLUR_H

#include <stdio.h>
#include "FilterConvolve.h"

class Kernel;

class FBlur : public FilterConvolve {
public:
    FBlur(float amount);
};

#endif
