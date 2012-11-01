//
//  bullet.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 31/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "bullet.h"

bullet::bullet(float a, float b, bool kill) : interactiveObject(a, b, 40) {
    if (kill) {
        z = -1;
        dead = true;
        return;
    }
    
    init();
}

void bullet::init() {
    box = boundingBox(x, y, z, 1, 0.25f);
}

void bullet::action() {
    dead = true;
}

void bullet::update(float dx, float dy, float dz) {
    object::update(0, 0, -0.5);
    dead |= z <= 30;
}

void bullet::draw() {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(1, 1, 1);
    
        glColor3f(0, 1, 1);
        luminosity(0.5f, 1, 1);
        glutSolidSphere(0.25f, 16, 16);
        luminosity();
        glColor3f(1, 1, 1);
    glPopMatrix();
    
    object::draw();
}
