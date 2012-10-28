//
//  ring.h
//  StarTroupial
//
//  Created by Jenny Valdez on 27/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#ifndef __StarTroupial__ring__
#define __StarTroupial__ring__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "glm.h"

class ring {
    float x;
    float y;
    float z;
    
    void color(float r, float g, float b);
public:
    ring();
    ring(float a, float b, float c = 0);
    
    static bool isDead(ring r);
    
    void draw();
    void update();
};

#endif /* defined(__StarTroupial__ring__) */
