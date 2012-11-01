//
//  bullet.h
//  StarTroupial
//
//  Created by Jenny Valdez on 31/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#ifndef __StarTroupial__bullet__
#define __StarTroupial__bullet__

#include <iostream>
#include "interactiveObject.h"

class bullet : public interactiveObject {
    
protected:
    
    // Initializes a ring
    void init();
    
    // Activated when hits something
    void action();
    
public:
    
    // Given-position constructor
    bullet(float a, float b, bool kill = false);
    
    // Updates the ring's position
    void update(float dx = 0, float dy = 0, float dz = 0);
    
    // Draws the ring
    void draw();
    
};

#endif /* defined(__StarTroupial__bullet__) */
