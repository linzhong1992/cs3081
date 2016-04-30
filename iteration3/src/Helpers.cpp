//
//  Helpers.cpp
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/1/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#include "Helpers.h"
#include "ColorData.h"
#include <cmath>

float Helpers::lerp(float a, float b, float r) {
    return a + (b-a) * r;
}

ColorData Helpers::lerp(ColorData a, ColorData b, float r) {
    return a + (b-a) * r;
}

float Helpers::clamp(float x, float low, float high) {
    return fmin(fmax(x,low),high);
}


int Helpers::clamp(int x, int low, int high) {
    return fmin(fmax(x,low),high);
}

float Helpers::gaussian(float x, float sigma) {
    return exp(-(pow(x,2)/(2*pow(sigma,2))+pow(0,2)/(2*pow(sigma,2))));
}