//
//  TBlur.cpp
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/4/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#include "TBlur.h"
#include "FilterFactory.h"
#include "MLinear.h"
#include "MConstant.h"
#include "Filter.h"
#include "ColorData.h"
#include "Helpers.h"
#include "PixelBuffer.h"

TBlur::TBlur()
{
    m_keep_buffer_constant = true;
    m_size = 10;
    m_mask = new MConstant(m_size, 1);
    m_filter = FilterFactory::getFilter(FilterFactory::FILTER_BLUR, 1, (float)0.5);
    m_maxSmear = 3;
}

std::string TBlur::getName()
{
    return "Blur";
}

TBlur::~TBlur()
{
    if (m_filter){
        delete m_filter;
    }
}

ColorData TBlur::processPixel(int maskX, int maskY, ColorData toolColor, PixelBuffer *buffer, int bufferX, int bufferY)
{
    ColorData c = buffer->getPixel(bufferX, bufferY);
    if (m_mask->getValue(maskX, maskY) > 0.01) {
        c = m_filter->generatePixel(*buffer, bufferX, bufferY);
    }
    return c;
}
