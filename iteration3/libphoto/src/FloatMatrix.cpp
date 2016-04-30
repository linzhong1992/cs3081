//
//  FloatMatrix.cpp
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/1/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#include "FloatMatrix.h"

#include <stdio.h>



FloatMatrix::FloatMatrix() {
    m_floatArray = NULL;
}

FloatMatrix::FloatMatrix(int w, int h) : m_width(w), m_height(h) {
    m_floatArray = new float[w*h];
}

FloatMatrix::~FloatMatrix() {
    if (m_floatArray) {
        delete[] m_floatArray;
    }
}

float FloatMatrix::getValue(int x, int y) const
{
    if (m_floatArray == NULL || x < 0 || x >= m_width || y < 0 || y >= m_height) {
        return 0.f;
    }
    else
    {
        return m_floatArray[y*m_width + x];
    }
}

void FloatMatrix::setValue(int x, int y, float v)
{
    if (m_floatArray == NULL || x < 0 || x >= m_width || y < 0 || y >= m_height)
    {
        return;
    }
    else
    {
        m_floatArray[y*m_width + x] = v;
    }
}


void FloatMatrix::operator*(const float c) {
    for (int i = getHeight()*getWidth()-1; i>=0; i--) {
        m_floatArray[i] *= c;
    }
}
