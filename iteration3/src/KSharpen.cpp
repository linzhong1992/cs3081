//
//  KSharpen.cpp
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/3/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#include "KSharpen.h"
#include <cmath>
#include <iostream>
#include "Helpers.h"
KSharpen::KSharpen() : KGaussian(0) {
    initKernel((int)ceil(m_sigma*3));
    generateKernel();
    normalize();
}
KSharpen::KSharpen(float sigma) : KGaussian(sigma) {
    initKernel((int)ceil(sigma));
    generateKernel();
    normalize();
    
    // Negate all the values
    (*this)*-1;
    // Add two to the middle
    float middle_value = getValue(m_width/2, m_height/2);
    setValue(m_width/2, m_height/2, middle_value+2);
}
