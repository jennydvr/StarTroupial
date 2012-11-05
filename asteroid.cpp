//
//  asteroid.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 29/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "asteroid.h"

asteroid::asteroid() : interactiveObject() {
    init();
}

asteroid::asteroid(float a, float b, float c) : interactiveObject(a, b, c) {
    init();
}

void asteroid::init() {
    // Init the bounding box with this position
    box = boundingBox(x, y, z, 1.25f);
    
    // Set drawing variables
    randomColor();
    angle = 0;
    sides = rand() % 4 + 6;
    
    // Other stuff
    factor = -1;
    everExploded = false;
    interactiveObject::init();
}

std::vector<particle> asteroid::explode() {
    std::vector<particle> ans;
    
    if (everExploded || !dead)
        return ans;
    
    for (int i = 0; i != 26; ++i) {
        float ax = (float)rand()/((float)RAND_MAX/(2)) -2 + x;
        float ay = (float)rand()/((float)RAND_MAX/(2)) -2 + y;
        float az = (float)rand()/((float)RAND_MAX/(2)) -2 + z;
        
        ans.push_back(particle(ax, ay, az, col, DEXP[i]));
        
        ax = (float)rand()/((float)RAND_MAX/(2)) -2 + x;
        ay = (float)rand()/((float)RAND_MAX/(2)) -2 + y;
        az = (float)rand()/((float)RAND_MAX/(2)) -2 + z;
        ans.push_back(particle(ax, ay, az, col, DEXP[i]));
        
        ax = (float)rand()/((float)RAND_MAX/(2)) -2 + x;
        ay = (float)rand()/((float)RAND_MAX/(2)) -2 + y;
        az = (float)rand()/((float)RAND_MAX/(2)) -2 + z;
        ans.push_back(particle(ax, ay, az, col, DEXP[i]));
    }
        
    everExploded = true;
    return ans;
}

light asteroid::createLight() {
    return light(x, y, z);
}

void asteroid::action() {
    dead = true;
}

void asteroid::randomColor() {
    switch (rand() % 8) {
        case 0: case 1: case 2:
            col[0] = 0.1; col[1] = 0.544; col[2] = 0.544;
            break;
        case 3: case 4:
            col[0] = 0.5745f; col[1] = 0.1175f; col[2] = 0.1175f;
            break;
        case 5:
            col[0] = 0.215f; col[1] = 0.5174f; col[2] = 0.215f;
            break;
        default:
            col[0] = 0.55f; col[1] = 0.50725f; col[2] = 0.50725f;
            break;
    }
}

void asteroid::shininess(bool on) {
    // For more about this numbers, check documentation
    GLfloat color[] = {col[0], col[1], col[2], 1};
    GLfloat specular[] = {0.297254, 0.30829, 0.306678, 1};
    GLfloat shininess = 12.8;
    
    // If the shininess is desired to be turned off, set everything to 0
    if (!on) {
        color[0] = color[1] = color[2] = 0;
        specular[0] = specular[1] = specular[2] = 0;
        shininess = 0;
    }
    
    // Give a little light for the rings
    GLfloat light[] = {color[0] * 0.9f, color[1] * 0.9f, color[2] * 0.9f, 1};
    
    // Set specular, shininess and the internal light
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, light);
}

void asteroid::draw() {
    if (dead) return;
    
    glPushMatrix();
        glRotatef(angle, x, y, z);
        glTranslatef(x, y, z);
    
        shininess(true);
        glColor4f(col[0], col[1], col[2], 0.75f);
        glutSolidDodecahedron();
        glColor4f(1, 1, 1, 1);
        shininess(false);
    glPopMatrix();
    
    object::draw();
}

void asteroid::update(float dx, float dy, float dz) {
    if (dead) return;
    
    angle += 1;
    angle = (angle == 360) ? 0 : angle;
    interactiveObject::update(0, 0, SPEED);
}
