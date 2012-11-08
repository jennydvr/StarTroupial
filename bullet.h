//
//  bullet.h
//  StarTroupial
//
//  Created by Jenny Valdez on 31/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#ifndef __StarTroupial__bullet__
#define __StarTroupial__bullet__

#define BULLET_SPEED 0.1f

#include <iostream>
#include "interactiveObject.h"

class bullet : public interactiveObject {
    
protected:
    
    // Initial point
    float xi;
    float yi;
    float zi;
    
    // Target
    float xf;
    float yf;
    float zf;
    
    // Initializes the bullet
    void init();
    
    // Activated when hits something
    void action();
    
public:
    
    // Given-position constructor
    bullet(float a, float b, float ta = 0, float tb = 0, float tc = 30, bool kill = false);
    
    // Updates the bullet's position
    void update(float dx = 0, float dy = 0, float dz = 0);
    
    // Draws the ring
    void draw(GLenum mode = GL_RENDER, int ident = 0);
    
};

#endif /* defined(__StarTroupial__bullet__) */
