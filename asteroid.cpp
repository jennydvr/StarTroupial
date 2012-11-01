//
//  asteroid.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 29/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "asteroid.h"

asteroid::asteroid() : interactiveObject() {
    init();
}

asteroid::asteroid(float a, float b, float c) : interactiveObject(a, b, c) {
    init();
}

void asteroid::init() {
    // Init the bounding box with this position
    box = boundingBox(x, y, z, 1);
    
    // Set drawing variables
    col[0] = 0; col[1] = 1; col[2] = 1;
    angle = 0;
    sides = rand() % 4 + 6;
    
    factor = -1;
    interactiveObject::init();
}

void asteroid::action() {
    dead = true;
}

void asteroid::randomColor() {
    switch (rand() % 3) {
        case 0:
            col[0] = 0; col[1] = 1; col[2] = 1;
            break;
        case 1:
            col[0] = 0.1f; col[1] = 0.75f; col[2] = 0.1f;
            break;
        case 2:
            col[0] = 0.5f; col[1] = 0.1f; col[2] = 0.5f;
            break;
    }
}

void asteroid::shininess(bool on) {
    // For more about this numbers, check documentation
    GLfloat color[] = {col[0], col[1], col[2], 1};
    GLfloat specular[] = {0.75f, 0.75f, 0.75f, 1};
    GLfloat shininess = 10;
    
    // If the shininess is desired to be turned off, set everything to 0
    if (!on) {
        color[0] = color[1] = color[2] = 0;
        specular[0] = specular[1] = specular[2] = 0;
        shininess = 0;
    }
    
    // Give a little light for the rings
    GLfloat light[] = {color[0] * 0.75f, color[1] * 0.75f, color[2] * 0.75f, 1};
    
    // Set specular, shininess and the internal light
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, light);
}

void asteroid::draw() {
    glPushMatrix();
        //glRotatef(angle, x, y, z);
    glRotatef(angle, x, y, z);
        glTranslatef(x, y, z);
    
        shininess(true);
        glColor4f(col[0], col[1], col[2], 0.75f);
        glutSolidSphere(1, sides, sides);
        glColor4f(1, 1, 1, 1);
        shininess(false);
    glPopMatrix();
    
    object::draw();
}

void asteroid::update(float dx, float dy, float dz) {
    angle += 1;
    angle = (angle == 360) ? 0 : angle;
    interactiveObject::update(0, 0, 0.25);
}
