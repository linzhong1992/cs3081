//
//  FilterConvolve.cpp
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/3/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#include <stdio.h>

#include "FilterConvolve.h"
#include "PixelBuffer.h"
#include "ColorData.h"
#include "Kernel.h"
#include "Helpers.h"

ColorData FilterConvolve::generatePixel(const PixelBuffer &buffer, int x, int y) const {
    if (m_kernel == NULL) {
        return buffer.getPixel(x, y);
    } else {
        int half_width = m_kernel->getWidth()/2;
        int half_height = m_kernel->getHeight()/2;
        int buffer_width = buffer.getWidth();
        int buffer_height = buffer.getHeight();
        //printf("=============\n");
        ColorData result(0,0,0,0);
        for (int i = 0; i < m_kernel->getWidth(); i++) {
            for (int j = 0; j < m_kernel->getHeight(); j++) {
                int c_x = x+i-half_width;
                int c_y = y+j-half_height;
                c_y = Helpers::clamp(c_y, 0, buffer_height-1);
                c_x = Helpers::clamp(c_x, 0, buffer_width-1);
                
                ColorData original = buffer.getPixel(c_x, c_y);
                float a = original.getAlpha();
                ColorData premult = original*a;
                premult.setAlpha(a);
                
                ColorData weight = premult*m_kernel->getValue(i, j);
                if (!m_convolveAlpha) {
                    weight.setAlpha(a);
                }
                result = result + weight;
                
            }
        }
        
        return result;
        

    }
}

FilterConvolve::FilterConvolve() {
    m_kernel = NULL;
    m_convolveAlpha = false;
}

FilterConvolve::~FilterConvolve()
{
    delete m_kernel;
}
