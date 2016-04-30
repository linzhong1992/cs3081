//
//  FloatMatrix.h
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/1/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//
//  For educational purposes only.  Please do not post online.

#ifndef __PhotoShop_Proj__FloatMatrix__
#define __PhotoShop_Proj__FloatMatrix__

class FloatMatrix
{
public:
    FloatMatrix();
    FloatMatrix(int w, int h);
    ~FloatMatrix();
    float const *getFloatArray() const { return m_floatArray; }
    int getWidth() const { return m_width;}
    int getHeight() const {return m_height;}
    float getValue(int x, int y) const;
protected:
    int m_height;
    int m_width;
    
    float *m_floatArray;
    void setValue(int x, int y, float v);
    void generateMask();
    virtual float getIntensity(int x, int y, float radius) = 0;
    
    void operator*(const float c);
};

#endif 
