//
//  ring.h
//  StarTroupial
//
//  Created by Jenny Valdez on 27/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#ifndef __StarTroupial__ring__
#define __StarTroupial__ring__

#include "interactiveObject.h"

class ring : public interactiveObject {
    
protected:
    
    // Activates ring rotation
    bool rotate;
    
    // Emission factor
    float emission;
    
    // Sets the shininess for a material
    void shininess(bool on);
    
    // Initializes a ring
    void init();
    
public:
    
    // Random-position constructor
    ring();
    
    // Given-position constructor
    ring(float a, float b, float c = 0);
    
    // Activated when hits something
    void action(int factor = 0);
    
    // Updates the ring's position
    void update(float dx = 0, float dy = 0, float dz = 0);
    
    // Draws the ring
    void draw(GLenum mode = GL_RENDER, int ident = 0);
    
};

#endif /* defined(__StarTroupial__ring__) */
