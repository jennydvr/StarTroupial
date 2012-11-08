//
//  bullet.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 31/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "bullet.h"

bullet::bullet(float a, float b, float ta, float tb, float tc, bool kill) : interactiveObject(a, b, 35) {
    // Empty bullet
    if (kill) {
        z = -1;
        dead = true;
        return;
    }
    
    // Initialize target and initial point
    xi = a; yi = b; zi = 35;
    xf = ta; yf = tb; zf = tc;
    
    init();
}

void bullet::init() {
    box = boundingBox(x, y, z, 0.25f);
    
    GLfloat red[] = {1, 0, 0, 1};
    GLfloat position[] = {x, y, z, 1};
    
    // Set up light
    glLightfv(GL_LIGHT1, GL_AMBIENT, red);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, red);
    glLightfv(GL_LIGHT1, GL_POSITION, position);
    
    glEnable(GL_LIGHT1);
}

void bullet::action() {
    dead = true;
    glDisable(GL_LIGHT1);
}

void bullet::update(float dx, float dy, float dz) {
    // Dead if distance equals 5
    float max = (x - xi) * (x - xi);
    max += (y - yi) * (y - yi);
    max += (z - zi) * (z - zi);
    
    dead |= max >= 200;
    
    object::update(BULLET_SPEED * (xf - xi), BULLET_SPEED * (yf - yi), BULLET_SPEED * (zf - zi));
    
    // If not dead, update light's position
    if (!dead) {
        GLfloat position[] = {x, y, z, 1};
        glLightfv(GL_LIGHT1, GL_POSITION, position);
        
    // Else, disable the light
    } else {
        glDisable(GL_LIGHT1);
    }
}

void bullet::draw(GLenum mode, int ident) {
    if (dead)
        return;
    
    glPushMatrix();
    glTranslatef(x, y, z);
    
        // Red laser
        glColor3f(0.25f, 0.15f, 0.15f);
        luminosity(1, 0, 0);
        glutSolidSphere(0.25f, 16, 16);
        luminosity();
        glColor3f(1, 1, 1);
    glPopMatrix();
    
    object::draw();
}
