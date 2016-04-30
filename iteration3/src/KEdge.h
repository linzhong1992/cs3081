//
//  KEdge.h
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/3/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//
//  For educational purposes only.  Please do not post online.

#ifndef KEDGE_H
#define KEDGE_H

#include "Kernel.h"

class KEdge : public Kernel {
protected:
    float getIntensity(int x, int y, float radius);

public:
    KEdge();
};

#endif
