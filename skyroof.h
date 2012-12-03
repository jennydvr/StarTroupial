//
//  skyroof.h
//  StarTroupial
//
//  Created by Jenny Valdez on 03/12/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#ifndef __StarTroupial__skyroof__
#define __StarTroupial__skyroof__

#include <iostream>
#include "object.h"

class skyroof : public object {
    
public:
    // Constructor
    skyroof();
    
    // Draws grass
    void draw(GLenum mode = GL_RENDER, int ident = 0);
    
};

#endif /* defined(__StarTroupial__skyroof__) */
