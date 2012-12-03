//
//  explosionLight.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 05/11/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "explosionLight.h"

light::light(float a, float b, float c) : object(a, b, c) {
    GLfloat white[] = {0.5f, 0.5f, 0.5f, 1};
    GLfloat position[] = {a, b, c, 1};
    
    // Choose light - from LIGHT1 to LIGHT7
    for (n = 0; n != 6 && USING[n]; ++n);
    
    if (n == 6) // No available lights (should never happen)
        return;
    
    USING[n] = true;
    
    // Set up light
    glLightfv(LIGHTS[n], GL_AMBIENT, white);
    glLightfv(LIGHTS[n], GL_DIFFUSE, white);
    glLightfv(LIGHTS[n], GL_SPECULAR, white);
    glLightfv(LIGHTS[n], GL_POSITION, position);
    
    // Set up attenuation
    glLightf(LIGHTS[n], GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(LIGHTS[n], GL_LINEAR_ATTENUATION, 0.1f);
    glLightf(LIGHTS[n], GL_QUADRATIC_ATTENUATION, 0.05f);
    
    glEnable(LIGHTS[n]);
    initialTime = glutGet(GLUT_ELAPSED_TIME);
}

void light::update(float dx, float dy, float dz) {
    // Check time
    if (glutGet(GLUT_ELAPSED_TIME) - initialTime < 1000)
        return;
    
    // Kill the light
    dead = true;
    USING[n] = false;
    glDisable(LIGHTS[n]);
}

void light::disable(light &l) {
    USING[l.n] = false;
    glDisable(LIGHTS[l.n]);
}
