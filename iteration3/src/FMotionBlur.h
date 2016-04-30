//
//  FMotionBlur.h
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/4/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//
//  For educational purposes only.  Please do not post online.

#ifndef FMOTIONBLUR_H
#define FMOTIONBLUR_H

#include "FilterConvolve.h"

class Kernel;

class FMotionBlur : public FilterConvolve {
public:
    FMotionBlur(float amount, int direction);
};

#endif
