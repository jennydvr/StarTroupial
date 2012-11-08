//
//  star.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 28/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "star.h"

star::star() : object(10, -10) {}

void star::update(float dx, float dy, float dz) {
    object::update(0, 0, SPEED);
}

void star::draw(GLenum mode, int ident) {
    glPushMatrix();
        glTranslatef(x, y, z);
    
        // Scale the radius so the star is always a single dot
        luminosity(1, 1, 1);
        glutSolidSphere((0.5 - z / 100) * 0.3, 16, 16);
        luminosity();
    glPopMatrix();
}
