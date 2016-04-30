//
//  Mask.cpp
//  Student Support
//
//  Created by Seth Johnson on 2/9/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#include "Mask.h"
#include <cmath>
#include <iostream>

using std::fill;

Mask::Mask()
{
}
Mask::~Mask()
{
    
}
Mask::Mask(float radius, float opacity) : m_opacity(opacity), m_radius(radius), FloatMatrix((ceil(radius)*2+1),(ceil(radius)*2+1))
{
	fill(m_floatArray, m_floatArray+m_width*m_height, 1.f);
}

Mask::Mask(int width, int height, float opacity) : m_opacity(opacity), m_radius(0), FloatMatrix(width, height)
{
    fill(m_floatArray, m_floatArray+m_width*m_height, 1.f);
}



void Mask::generateMask() {
	for (int j = 0; j < getHeight(); j++) 
	{
		for (int i = 0; i < getWidth(); i++) 
		{
			int x = i-getWidth()/2;
			int y = j-getHeight()/2;
			float intensity = m_opacity*getIntensity(x,y,m_radius);
			setValue(i, j, intensity);
		}
	}
}

float Mask::getIntensity(int x, int y, float radius)
{
    return m_opacity;
}
