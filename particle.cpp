//
//  particle.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 02/11/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "particle.h"

particle::particle(float a, float b, float c, float direction[]) : object(a, b, c) {
    ini[0] = a;
    ini[1] = b;
    ini[2] = c;
    
    dir[0] = direction[0];
    dir[1] = direction[1];
    dir[2] = direction[2];
    
    angle = (float)rand()/((float)RAND_MAX/359);
    scale = (float)rand()/((float)RAND_MAX/(0.4f)) + 0.1f;
}

void particle::update(float dx, float dy, float dz) {
    if (dead) return;
    
    object::update(SPEED * dir[0], SPEED * dir[1], SPEED * dir[2]);
    
    // Dead if distance equals 20 (I think...)
    float max = (x - ini[0]) * (x - ini[0]);
    max += (y - ini[1]) * (y - ini[1]);
    max += (z - ini[2]) * (z - ini[2]);
    
    dead = max >= 400;
}

void particle::draw(GLenum mode, int ident) {
    if (dead) return;
    
    col[0] = (float)rand()/(float)RAND_MAX;
    col[1] = (float)rand()/(float)RAND_MAX;
    col[2] = (float)rand()/(float)RAND_MAX;
    
    glPushMatrix();
        glTranslatef(x, y, z);
        glScalef(scale, scale, scale);
        glRotatef(angle, x, y, z);
    
        // Scale the radius so the star is always a single dot
        glColor4f(col[0], col[1], col[2], 0.75f);
        glutSolidTetrahedron();
        glColor4f(1, 1, 1, 1);
    glPopMatrix();
}
