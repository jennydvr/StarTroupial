//
//  collisionManager.h
//  StarTroupial
//
//  Created by Jenny Valdez on 28/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#ifndef __StarTroupial__collisionManager__
#define __StarTroupial__collisionManager__

#include <iostream>
#include <vector>
#include "glm.h"

// Checks whether the debug is on or off
extern bool debug;

// Class for collision checking - Bounding Box Method
class boundingBox {
    
    // Minimum box point
    float xmin, ymin, zmin;
    
    // Maximum box point
    float xmax, ymax, zmax;
    
public:
    
    // Empty constructor
    boundingBox();
    
    // Constructor for torus
    boundingBox(float xi, float yi, float zi, float innerRadius, float outerRadius);
    
    // Constructor for sphere
    boundingBox(float xi, float yi, float zi, float radius);
    
    // Gets minimum point
    std::vector<float> getMin();
    
    // Gets maximum point
    std::vector<float> getMax();
    
    // Updates the position
    void update(float nx, float ny, float nz);
    
    // Draws the box
    void draw();
    
};

// Checks if two boxes intersect
bool collision(boundingBox a, boundingBox b);

#endif /* defined(__StarTroupial__collisionManager__) */
