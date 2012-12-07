//
//  building.h
//  StarTroupial
//
//  Created by Jenny Valdez on 04/12/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#ifndef __StarTroupial__building__
#define __StarTroupial__building__

#include "interactiveObject.h"

using namespace std;

class building : public interactiveObject {
    
protected:
    
    // Building's size
    float width, height, depth;
    
    // Sets the shininess for a material
    void shininess(bool on);
    
    // Initializes a building
    void init();
    
    // Draw building
    void drawBuilding(bool shadow = false);
    
    // Update planes
    void updatePlanes();
    
public:
    
    // Left plane of the building
    std::vector<float> left;
    
    // Frontal plane of the building
    std::vector<float> front;
    
    // Random-position constructor
    building();
    
    // Given-position constructor
    building(float a, float c = 0);
    
    // Activated when hits something
    void action(int factor = 0);
    
    // Updates the ring's position
    void update(float dx = 0, float dy = 0, float dz = 0);
    
    // Draws the ring
    void draw(GLenum mode = GL_RENDER, int ident = 0, vector<float> shadowPlane = vector<float>());
    
};

#endif /* defined(__StarTroupial__building__) */
