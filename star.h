//
//  star.h
//  StarTroupial
//
//  Created by Jenny Valdez on 28/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#ifndef __StarTroupial__star__
#define __StarTroupial__star__

#include "object.h"

class star : public object {
    
public:
    
    // Constructor
    star();
    
    // Updates star
    void update(float dx = 0, float dy = 0, float dz = 0);
    
    // Draws star
    void draw(GLenum mode = GL_RENDER, int ident = 0);
    
};

#endif /* defined(__StarTroupial__star__) */
