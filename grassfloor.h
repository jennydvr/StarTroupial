//
//  grassfloor.h
//  StarTroupial
//
//  Created by Jenny Valdez on 30/11/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#ifndef __StarTroupial__grassfloor__
#define __StarTroupial__grassfloor__

#include <iostream>
#include "object.h"

class grassfloor : public object {
    
public:
    // Constructor
    grassfloor();
    
    // Draws grass
    void draw(GLenum mode = GL_RENDER, int ident = 0);
    
};

#endif /* defined(__StarTroupial__grassfloor__) */
