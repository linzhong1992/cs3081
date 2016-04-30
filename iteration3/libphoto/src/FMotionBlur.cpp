//
//  FMotionBlur.cpp
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/4/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#include "FMotionBlur.h"
#include "KMotionBlur.h"

FMotionBlur::FMotionBlur(float amount, int direction) {
    m_convolveAlpha = true;
    m_kernel = new KMotionBlur(amount, direction);
}
