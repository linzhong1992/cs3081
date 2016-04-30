//
//  KSharpen.h
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/3/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//
//  For educational purposes only.  Please do not post online.

#ifndef KSHARPEN_H
#define KSHARPEN_H

#include "KGaussian.h"

class KSharpen : public KGaussian {
        
public:
    KSharpen(float sigma);
    KSharpen();
};

#endif
