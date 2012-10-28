//
//  star.h
//  StarTroupial
//
//  Created by Jenny Valdez on 28/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#ifndef __StarTroupial__star__
#define __StarTroupial__star__

#include <iostream>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "glm.h"

class star {
    float x;
    float y;
    float z;
    
    void color(float r, float g, float b);
public:
    star();
    
    static bool isDead(star s);
    
    void draw();
    void update();
};

#endif /* defined(__StarTroupial__star__) */
