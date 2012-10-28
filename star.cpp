//
//  star.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 28/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "star.h"

star::star() {
    x = rand() % 40 - 20;
    y = rand() % 40 - 20;
    z = 0;
}

void star::color(float r, float g, float b) {
    GLfloat color[] = {r, g, b, 1};
    glMaterialfv(GL_FRONT, GL_EMISSION, color);
}

bool star::isDead(star s) {
    return s.z >= 50;
}

void star::draw() {
    color(1, 1, 1);
    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidSphere((0.5 - z / 100) * 0.3, 16, 16);
    glPopMatrix();
    color(0, 0, 0);
}

void star::update() {
    z += 0.25;
}