//
//  FSharpen.cpp
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/3/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#include "FSharpen.h"
#include "KSharpen.h"

FSharpen::FSharpen(float amount) {
    m_convolveAlpha = true;
    m_kernel = new KSharpen(amount);
}
