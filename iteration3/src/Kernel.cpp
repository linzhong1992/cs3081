//
//  Kernel.cpp
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/1/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#include "Kernel.h"
#include <stdio.h>


Kernel::Kernel() {
    initKernel(0);
    
}


Kernel::~Kernel() {
    delete [] m_floatArray;
    
}

void Kernel::initKernel(int rad) {
    m_radius = rad;
    m_height = m_width = m_radius*2+1;
    
    m_floatArray = new float[m_height*m_width];
}

float Kernel::sum() {
    float s = 0;
    for (int i = 0; i < m_width; i++) {
        for (int j = 0; j < m_height; j++) {
            s += getValue(i, j);
        }
    }
    return s;
}

void  Kernel::print() {
    for (int j = 0; j < m_height; j++) {
        for (int i = 0; i < m_width; i++) {
            
            printf("%.3f ",getValue(i, j));
        }
        putchar('\n');
    }
}

void Kernel::normalize() {
    float s = sum();
    if (s == 0) {
        return;
    }
    float v;
    
    for (int i = 0; i < m_width; i++) {
        for (int j = 0; j < m_height; j++) {
            v = getValue(i, j);
            setValue(i, j, v/s);
        }
    }
}

void Kernel::generateKernel() {
    for (int j = 0; j < getHeight(); j++)
    {
        for (int i = 0; i < getWidth(); i++)
        {
            int x = i-getWidth()/2;
            int y = j-getHeight()/2;
            float intensity = getIntensity(x,y,m_radius);
            
            setValue(i, j, intensity);
        }
    }
}

float Kernel::getIntensity(int x, int y, float m_radius) {
    return 1;
}
