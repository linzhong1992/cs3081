//
//  KMotionBlur.cpp
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/4/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#include "KMotionBlur.h"
#include <cmath>
#include <iostream>
#include "Helpers.h"


KMotionBlur::KMotionBlur(float amount, int direction) : m_amount(amount), m_direction(direction) {
    initKernel((int)ceil(m_amount));
    generateKernel();
    normalize();
}

float KMotionBlur::getIntensity(int x, int y, float radius)
{
    float element = 0.0;
    switch (m_direction) {
        case 0:
            element = (x==0)? 1:0;
            break;
        case 1:
            element = (y==0)? 1:0;
            break;
        case 2:
            element = (y == x)? 1:0;
            break;
        case 3:
            element = ( y == -x)? 1:0;
            break;
        default:
            break;
    }
    return element;
}
