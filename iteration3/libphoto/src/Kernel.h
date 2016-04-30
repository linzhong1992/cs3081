//
//  Kernel.h
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/1/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//
//  For educational purposes only.  Please do not post online.

#ifndef KERNEL_H
#define KERNEL_H

#include "FloatMatrix.h"

class Kernel : public FloatMatrix {
protected:
    void normalize();
    virtual void initKernel(int rad);
    virtual void generateKernel() ;
    float getIntensity(int x, int y, float m_radius) ;
    int m_radius;
public:
    Kernel();
    int getRadius() {
        return m_radius;
    }
    ~Kernel();
    float sum();
    void print();

};
#endif
