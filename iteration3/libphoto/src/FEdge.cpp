//
//  FEdge.cpp
//  PhotoShop Proj
//
//  Created by Seth Johnson on 4/3/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#include "FEdge.h"
#include "KEdge.h"

FEdge::FEdge() {
    m_kernel = new KEdge();
}
