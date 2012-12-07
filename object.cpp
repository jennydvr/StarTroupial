//
//  object.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 31/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "object.h"

using namespace std;

object::object(int high, int low) {
    x = rand() % (high - low) + low;
    y = rand() % (high - low) + low;
    z = 0;
    
    dead = false;
}

object::object(float a, float b, float c) : x(a), y(b), z(c) {
    dead = false;
}

bool object::visible() {
    return !dead && z <= 200;     // Camera bounds
}

void object::luminosity(float r, float g, float b) {
    GLfloat color[] = {r, g, b, 1};
    glMaterialfv(GL_FRONT, GL_EMISSION, color);
}

void object::update(float dx, float dy, float dz) {
    if (dead) return;
    
    // Update position
    x += dx;
    y += dy;
    z += dz;
    
    // Update box's position
    box.update(dx, dy, dz);
}

void object::draw(GLenum mode, int ident, vector<float> shadowPlane) {
    if (dead) return;
    
    if (debug)
        box.draw();
}
