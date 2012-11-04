//
//  starship.h
//  StarTroupial
//
//  Created by Jenny Valdez on 27/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#ifndef __StarTroupial__starship__
#define __StarTroupial__starship__

#include "bullet.h"

class starship : public object {
    
    // Mesh of the starship
    GLMmodel* model;
    
    // Time for shooting
    int current, previous;
    
    // Draw the model
    void drawModel();
    
public:
    
    // Constructor
    starship();
    
    // Shoots
    bullet shoot();
    
    // Updates the ship's position
    void update(float dx, float dy, float dz = 0);
    
    // Draws the ship
    void draw();
    
};

#endif /* defined(__StarTroupial__starship__) */
