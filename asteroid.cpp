//
//  asteroid.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 29/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "asteroid.h"

using namespace std;

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
    angle = 0;
    
    // Other stuff
    factor = -3;
    everExploded = false;
    interactiveObject::init();
}

std::vector<particle> asteroid::explode() {
    std::vector<particle> ans;
    
    if (everExploded || !dead)
        return ans;
    
    for (int n = rand() % 100 + 100; n != 0; --n) {
        float ax = (float)rand()/((float)RAND_MAX/(2)) -2 + x;
        float ay = (float)rand()/((float)RAND_MAX/(2)) -2 + y;
        float az = (float)rand()/((float)RAND_MAX/(2)) -2 + z;
        
        // Direction vector cannot be 0!
        float dir[3] = {0, 0, 0};
        while (dir[0] == 0 && dir[1] == 0 && dir[2] == 0) {
            dir[0] = (float)rand()/((float)RAND_MAX/4) - 2;
            dir[1] = (float)rand()/((float)RAND_MAX/4) - 2;
            dir[2] = (float)rand()/((float)RAND_MAX/4) - 2;
        }
        
        ans.push_back(particle(ax, ay, az, dir));
    }
    
    everExploded = true;
    return ans;
}

light asteroid::createLight() {
    return light(x, y, z);
}

void asteroid::action(int factor) {
    if (factor == 0) {
        playExplosionSong();
    } else {
        everExploded = true;
    }
    
    dead = true;
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

void asteroid::draw(GLenum mode, int ident, vector<float> shadowPlane) {
    if (dead) return;
    
    // Draw shadow
    if (shadowPlane.size() != 0) {
        glPushMatrix();
            shadowMatrix(shadowPlane);
            glRotatef(angle, x, y, z);
            glTranslatef(x, y, z);
        
            glDisable(GL_LIGHTING);
            glDisable(GL_FOG);
        
            glColor4f(0.3f, 0.3f, 0.3f, 0.8f);
            glutSolidDodecahedron();
            glColor4f(1, 1, 1, 1);
        
            glEnable(GL_LIGHTING);
            glEnable(GL_FOG);
        glPopMatrix();
        
        return;
    }
    
    col[0] = (float)rand()/(float)RAND_MAX;
    col[1] = (float)rand()/(float)RAND_MAX;
    col[2] = (float)rand()/(float)RAND_MAX;
    
    if (mode == GL_SELECT)
        glLoadName(ident);
    
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
