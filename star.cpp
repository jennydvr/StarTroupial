//
//  star.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 28/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "star.h"

star::star() : object(15, -11) {}

void star::update(float dx, float dy, float dz) {
    object::update(0, 0, SPEED);
}

void star::draw(GLenum mode, int ident) {
    glPushMatrix();
        glTranslatef(x, y, z);
        luminosity(1, 1, 1);
        glutSolidSphere(z * 0.05 / 190 + (190 - z) * 0.0015625, 16, 16);
        luminosity();
    glPopMatrix();
}