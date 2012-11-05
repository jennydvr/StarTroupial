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

// Explosion - Directional vectors
static float DEXP[42][3] = {
    {0, 0, 1}, {0, 0, -1}, {0, 1, 0}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0},
    {0, 1, 1}, {0, 1, -1}, {0, -1, 1}, {0, -1, -1},
    {1, 0, 1}, {1, 0, -1}, {-1, 0, 1}, {-1, 0, -1},
    {1, 1, 0}, {1, -1, 0}, {-1, 1, 0}, {-1, -1, 0},
    {1, 1, 1}, {1, 1, -1}, {1, -1, 1}, {-1, 1, 1},
    {1, -1, -1}, {-1, 1, -1}, {-1, -1, 1}, {-1, -1, -1},
    {0, 0.75, 0.25}, {0, 0.75, -0.25}, {0, -0.75, 0.25}, {0, -0.75, -0.25},
    {0, 0.25, 0.75}, {0, 0.25, -0.75}, {0, -0.25, 0.75}, {0, -0.25, -0.75},
    {0.75, 0, 0.25}, {0.75, 0, -0.25}, {-0.75, 0, 0.25}, {-0.75, 0, -0.25},
    {0.25, 0, 0.75}, {0.25, 0, -0.75}, {-0.25, 0, 0.75}, {-0.25, 0, -0.75}
};

class asteroid : public interactiveObject {
    
protected:
    
    // Sides of the asteroid
    int sides;
    
    // Initializes an asteroid
    void init();
    
    // Choose a semi-random color for the asteroid
    void randomColor();
    
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
    void action();
    
    // Updates the asteroid's position
    void update(float dx = 0, float dy = 0, float dz = 0);
    
    // Draws the asteroid
    void draw();
    
};

#endif /* defined(__StarTroupial__asteroid__) */
