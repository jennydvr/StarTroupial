//
//  starship.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 27/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "starship.h"

ship::ship() : x(0), y(0) { }

void ship::move(float dx, float dy) {
    x += dx;
    y += dy;
}

void ship::color(float r, float g, float b) {
    GLfloat color[] = {r, g, b, 1.0};
    GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);
}

void ship::draw() {
    color(0, 0, 1);
    glPushMatrix();
    glTranslatef(x, y, 40);
    glutSolidSphere(1, 16, 40);
    glPopMatrix();
    color(0, 0, 0);
}