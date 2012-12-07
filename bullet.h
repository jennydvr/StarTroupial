//
//  bullet.h
//  StarTroupial
//
//  Created by Jenny Valdez on 31/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#ifndef __StarTroupial__bullet__
#define __StarTroupial__bullet__

#define BULLET_SPEED 0.1f

#include <iostream>
#include "interactiveObject.h"

using namespace std;

// Lights
static unsigned int BLIGHTS[3] = {GL_LIGHT1, GL_LIGHT2, GL_LIGHT3};

// Available lights
static bool BUSING[3] = {false, false, false};

class bullet : public interactiveObject {
    
protected:
    
    // Initial point
    float xi;
    float yi;
    float zi;
    
    // Target
    float xf;
    float yf;
    float zf;
    
    // Light ID
    int n;
    
    // Initializes the bullet
    void init();
    
public:
    
    // Given-position constructor
    bullet(float a, float b, float ta = 0, float tb = 0, float tc = 30, bool kill = false);
    
    // Activated when hits something
    void action(int factor = 0);
    
    // Disable lights
    static void disable(bullet &b);
    
    // Updates the bullet's position
    void update(float dx = 0, float dy = 0, float dz = 0);
    
    // Draws the ring
    void draw(GLenum mode = GL_RENDER, int ident = 0, vector<float> shadowPlane = vector<float>());
    
};

#endif /* defined(__StarTroupial__bullet__) */
