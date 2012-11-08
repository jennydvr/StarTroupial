//
//  ring.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 27/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "ring.h"

ring::ring() : interactiveObject() {
    init();
}

ring::ring(float a, float b, float c) : interactiveObject(a, b, c) {
    init();
}

void ring::init() {
    // Set color to yellow
    col[0] = 0.65; col[1] = 0.5; col[2] = 0;
    
    // Init the bounding box with this position
    box = boundingBox(x, y, z, 0.1f, 1.0f);
    
    factor = 1;
    emission = 0.025f;
    touched = false;
    rotate = false;
}

void ring::action() {
    col[0] = 0.85; col[1] = 0.7;
    emission = 0.25f;
    rotate = true;
    
#ifdef USE_SOUNDS
    playRingsSong();
#endif
}

void ring::shininess(bool on) {
    // For more about this numbers, check documentation
    GLfloat color[] = {col[0], col[1], col[2], 1};
    GLfloat specular[] = {0.628281, 0.555802, 0.366065, 1};
    GLfloat shininess = 51.2;
    
    // If the shininess is desired to be turned off, set everything to 0
    if (!on) {
        color[0] = color[1] = color[2] = 0;
        specular[0] = specular[1] = specular[2] = 0;
        shininess = 0;
    }
    
    // Give a little light for the rings
    GLfloat light[] = {color[0] * emission, color[1]  * emission, color[2]  * emission, 1};
    
    // Set specular, shininess and the internal light
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, light);
}

void ring::draw(GLenum mode, int ident) {
    glPushMatrix();
        glScalef(1, 1.5, 1);
        glTranslatef(x, y, z);
    
        if (rotate)
            glRotatef(angle, 0, 1, 0);
    
        shininess(true);
        glColor3f(col[0], col[1], col[2]);
        glutSolidTorus(0.1, 1, 16, 32);
        glColor3f(1, 1, 1);
        shininess(false);
    glPopMatrix();
    
    object::draw();
}

void ring::update(float dx, float dy, float dz) {
    angle += 15;
    angle = (angle == 360) ? 0 : angle;
    object::update(0, 0, SPEED);
}
