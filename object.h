//
//  object.h
//  StarTroupial
//
//  Created by Jenny Valdez on 31/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#ifndef __StarTroupial__glObject__
#define __StarTroupial__glObject__

#define SPEED 0.5f

#include <stdlib.h>
#include "collisionManager.h"
#include "soundManager.h"

// Base class for any OpenGL object
class object {
    
protected:
    
    // Limits for the randomness
    int high;
    int low;
    
    // Current color of the object
    float col[3];
    
    // Activates star luminosity
    void luminosity(float r = 0, float g = 0, float b = 0);
    
public:
    
    // Position of the object
    float x;
    float y;
    float z;
    
    // Indicates whether this object is dead or not
    bool dead;
    
    // Bounding box of the object
    boundingBox box;
    
    // Random-position constructor
    object(int high, int low);
    
    // Given-position constructor
    object(float a, float b, float c = 0);
    
    // Checks whether the object is visible
    virtual bool visible();
    
    // Updates the object
    virtual void update(float dx = 0, float dy = 0, float dz = 0);
    
    // Draws the object
    virtual void draw(GLenum mode = GL_RENDER, int ident = 0);
};

#endif /* defined(__StarTroupial__glObject__) */
