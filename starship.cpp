//
//  starship.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 27/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "starship.h"

starship::starship() : object(0, 0, 40) {
    box = boundingBox(x, y, z, 1);
    current = previous = 0;
}

bullet starship::shoot() {
    // Add bullet every second
    current = glutGet(GLUT_ELAPSED_TIME);
    
    if (current - previous < 500)
        return bullet(0, 0, true);
    
    previous = current;
    return bullet(x, y);
}

void starship::update(float dx, float dy, float dz) {
    object::update(dx * 4, dy * 4);
}

void starship::draw() {
    glPushMatrix();
        glTranslatef(x, y, z);
    
        glColor3f(0, 0, 1);
        glutSolidSphere(1, 16, 40);
        glColor3f(1, 1, 1);
    glPopMatrix();
    
    object::draw();
}
