//
//  explosionLight.h
//  StarTroupial
//
//  Created by Jenny Valdez on 05/11/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#ifndef __StarTroupial__explosionLight__
#define __StarTroupial__explosionLight__

#include "object.h"

// Lights
static unsigned int LIGHTS[7] = {GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};

// Available lights
static bool USING[7] = {false, false, false, false, false, false, false};

class light : public object {
    
protected:
    
    // Previous time
    float initialTime;
    
    // Light ID
    int n;
    
public:
    
    // Constructor
    light(float a, float b, float c);
    
    // Updates timer
    void update(float dx = 0, float dy = 0, float dz = 0);
    
    // Disables this light
    static void disable(light &l);
    
};

#endif /* defined(__StarTroupial__explosionLight__) */
