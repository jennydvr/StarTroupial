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

class asteroid : public interactiveObject {
    
protected:
    
    // Angle for rotation
    float angle;
    
    // Sides of the asteroid
    int sides;
    
    // Mesh for the asteroid
    GLMmodel* mesh;
    
    // Initializes an asteroid
    void init();
    
    // Choose a semi-random color for the asteroid
    void randomColor();
    
    // Sets material values
    void shininess(bool on);
    
public:
    
    // Random-position constructor
    asteroid();
    
    // Given-position constructor
    asteroid(float a, float b, float c = 0);
    
    // Activated when hits something
    void action();
    
    // Updates the asteroid's position
    void update(float dx = 0, float dy = 0, float dz = 0);
    
    // Draws the asteroid
    void draw();
    
};

#endif /* defined(__StarTroupial__asteroid__) */
