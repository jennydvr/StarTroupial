//
//  interactiveObject.h
//  StarTroupial
//
//  Created by Jenny Valdez on 31/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#ifndef __StarTroupial__interactiveObject__
#define __StarTroupial__interactiveObject__

#include "object.h"

class interactiveObject : public object {

protected:
    
    // Shows if the object has ever been touched by the ship
    bool touched;
    
    // Auments or decrements the player's score
    int factor;
    
    // Current color of the object
    float col[3];
    
    // Initializes parameters
    virtual void init();
    
public:
    
    // Random-position constructor
    interactiveObject();
    
    // Given-position constructor
    interactiveObject(float a, float b, float c = 0);
    
    // Activates when there is a collision
    virtual void action();
    
    // Checks collision with certain object
    bool hits(object obj);
    
    // Calculates if the score is affected or not
    int updateScore(object player);
    
};

#endif /* defined(__StarTroupial__interactiveObject__) */