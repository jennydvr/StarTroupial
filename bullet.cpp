//
//  bullet.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 31/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "bullet.h"

using namespace std;

bullet::bullet(float a, float b, float ta, float tb, float tc, bool kill) : interactiveObject(a, b, 185) {
    // Empty bullet
    if (kill) {
        z = -1;
        dead = true;
        return;
    }
    
    // Initialize target and initial point
    xi = a; yi = b; zi = 185;
    xf = ta; yf = tb; zf = tc;
    
    init();
}

void bullet::init() {
    box = boundingBox(x, y, z, 0.25f);
    factor = 0;
    
    // Choose light - from LIGHT1 to LIGHT2
    for (n = 0; n != 3 && BUSING[n]; ++n);
    
    if (n == 3) // No available lights (should never happen)
        return;
    
    BUSING[n] = true;
    
    GLfloat blue[] = {0.75f, 0, 0, 1};
    GLfloat position[] = {x, y, z, 1};
    
    // Set up light
    glLightfv(BLIGHTS[n], GL_AMBIENT, blue);
    glLightfv(BLIGHTS[n], GL_DIFFUSE, blue);
    glLightfv(BLIGHTS[n], GL_POSITION, position);
    
    // Set up attenuation
    glLightf(BLIGHTS[n], GL_LINEAR_ATTENUATION, 0.1f);
    
    glEnable(BLIGHTS[n]);
}

void bullet::action(int factor) {
    dead = true;
    
    if (n == 3) return;
    
    glDisable(BLIGHTS[n]);
    BUSING[n] = false;
}

void bullet::update(float dx, float dy, float dz) {
    object::update(BULLET_SPEED * (xf - xi), BULLET_SPEED * (yf - yi), BULLET_SPEED * (zf - zi));
    
    dead |= z <= 100;
    
    if (n == 3) return;
    
    // If not dead, update light's position
    if (!dead) {
        GLfloat position[] = {x, y, z, 1};
        glLightfv(BLIGHTS[n], GL_POSITION, position);
        
    // Else, disable the light
    } else {
        glDisable(BLIGHTS[n]);
    }
}

void bullet::disable(bullet &b) {
    if (b.n == 3) return;
    
    BUSING[b.n] = false;
    glDisable(BLIGHTS[b.n]);
}

void bullet::draw(GLenum mode, int ident, vector<float> shadowPlane) {
    if (dead) return;
    
    // Draw shadow
    if (shadowPlane.size() != 0) {
        glPushMatrix();
            shadowMatrix(shadowPlane);
            glTranslatef(x, y, z);
            glScalef(0.75f, 0.75f, 2.0f);
        
            glDisable(GL_LIGHTING);
            glDisable(GL_FOG);
        
            glColor4f(0.3f, 0.3f, 0.3f, 0.7f);
            glutSolidSphere(0.25f, 16, 16);
            glColor4f(1, 1, 1, 1);
        
            glEnable(GL_LIGHTING);
            glEnable(GL_FOG);
        glPopMatrix();
        
        return;
    }
    
    glPushMatrix();
        glTranslatef(x, y, z);
        glScalef(0.75f, 0.75f, 2.0f);
    
        // Blue laser
        glColor3f(0.75f, 0.5f, 0.5f);
        luminosity(0.25f, 0, 0);
        glutSolidSphere(0.25f, 16, 16);
        luminosity();
        glColor3f(1, 1, 1);
    glPopMatrix();
    
    object::draw();
}
