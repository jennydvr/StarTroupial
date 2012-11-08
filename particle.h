//
//  particle.h
//  StarTroupial
//
//  Created by Jenny Valdez on 02/11/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#ifndef __StarTroupial__particle__
#define __StarTroupial__particle__

#include "object.h"

class particle : public object {
    
protected:
    
    // Initial point
    float ini[3];
    
    // Direction
    float dir[3];
    
    // Angle
    float angle;
    
    // Size of the particle
    float scale;
    
public:
    
    // Constructor
    particle(float a, float b, float c, float color[], float direction[]);
    
    // Updates star
    void update(float dx = 0, float dy = 0, float dz = 0);
    
    // Draws star
    void draw(GLenum mode = GL_RENDER, int ident = 0);
    
};

#endif /* defined(__StarTroupial__particle__) */
