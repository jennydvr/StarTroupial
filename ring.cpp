//
//  ring.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 27/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "ring.h"

ring::ring() {
    x = (float)rand() / ((float)RAND_MAX / 10) - 5;
    y = (float)rand() / ((float)RAND_MAX / 10) - 5;
    z = 0;
}

ring::ring(float a, float b, float c) {
    x = a;
    y = b;
    z = c;
}

void ring::color(float r, float g, float b) {
    GLfloat color[] = {r, g, b, 1.0};
    GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);
}

bool ring::isDead(ring r) {
    return r.z >= 50;
}

void ring::draw() {
    color(0.65, 0.5, 0.0);
    glPushMatrix();
    glScalef(1, 1.5, 1);
    glTranslatef(x, y, z);
    glutSolidTorus(0.1, 0.85, 16, 40);
    glPopMatrix();
    color(0, 0, 0);
}

void ring::update() {
    z += 0.25;
}