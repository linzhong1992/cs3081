//
//  FSpecial.h
//  PhotoShop
//
//  Created by Sarit Ghildayal on 4/7/15.
//  Copyright (c) 2015 Sarit Ghildayal. All rights reserved.
//

#ifndef __PhotoShop__FSpecial__
#define __PhotoShop__FSpecial__

#include <stdio.h>
#include "Filter.h"

class FSpecial: public Filter {
public:
    PixelBuffer * generateFilteredBuffer(const PixelBuffer & input_buffer
                                         );
    virtual ColorData generatePixel(const PixelBuffer & buffer, const PixelBuffer & blurredBuffer, int x, int y) const;
};

#endif /* defined(__PhotoShop__FSpecial__) */
