//
//  starship.h
//  StarTroupial
//
//  Created by Jenny Valdez on 27/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#ifndef __StarTroupial__starship__
#define __StarTroupial__starship__

#include <iostream>
#include <stdlib.h>
#include "glm.h"

class ship {
    float x;
    float y;
    GLMmodel* mesh;
    
    void color(float r, float g, float b);
    
public:
    
    ship();
    
    void move(float dx, float dy);
    
    void draw();
};

#endif /* defined(__StarTroupial__starship__) */
