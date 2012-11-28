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
    
    // Shows if the object has ever been touched by any object
    bool touched;
    
    // Auments or decrements the player's score
    int factor;
    
    // Angle for rotation
    float angle;
    
    // Initializes parameters
    virtual void init();
    
public:
    
    // Random-position constructor
    interactiveObject();
    
    // Given-position constructor
    interactiveObject(float a, float b, float c = 0);
    
    // Activates when there is a collision
    virtual void action(int factor = 0);
    
    // Checks collision with certain object
    bool hits(interactiveObject &obj);
    
};

#endif /* defined(__StarTroupial__interactiveObject__) */
