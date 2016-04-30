//
//  KGaussian.h
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/2/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//
//  For educational purposes only.  Please do not post online.

#ifndef KGAUSSAIN_H
#define KGAUSSAIN_H

#include "Kernel.h"

class KGaussian : public Kernel {
protected:
    
    float m_sigma;
    float getIntensity(int x, int y, float radius);

public:
    KGaussian(float sigma);
    KGaussian();

};
#endif
