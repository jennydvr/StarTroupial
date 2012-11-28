//
//  asteroid.h
//  StarTroupial
//
//  Created by Jenny Valdez on 29/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#ifndef __StarTroupial__asteroid__
#define __StarTroupial__asteroid__

#include <stdio.h>
#include <stdlib.h>
#include "interactiveObject.h"
#include "particle.h"
#include "explosionLight.h"

class asteroid : public interactiveObject {
    
protected:
    
    // Sides of the asteroid
    int sides;
    
    // Initializes an asteroid
    void init();
    
    // Sets material values
    void shininess(bool on);
    
public:
    
    // Particles created
    bool everExploded;
    
    // Random-position constructor
    asteroid();
    
    // Given-position constructor
    asteroid(float a, float b, float c = 0);
    
    // Creates particles
    std::vector<particle> explode();
    
    // Initialize explosion light
    light createLight();
    
    // Activated when hits something
    void action(int factor = 0);
    
    // Updates the asteroid's position
    void update(float dx = 0, float dy = 0, float dz = 0);
    
    // Draws the asteroid
    void draw(GLenum mode = GL_RENDER, int ident = 0);
    
};

#endif /* defined(__StarTroupial__asteroid__) */
