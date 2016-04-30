//
//  FBlur.cpp
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/2/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#include "FBlur.h"
#include "KGaussian.h"

FBlur::FBlur(float amount) {
    m_convolveAlpha = true;
    m_kernel = new KGaussian(amount);
}
