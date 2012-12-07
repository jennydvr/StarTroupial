//
//  building.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 04/12/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "building.h"

using namespace std;

building::building() : interactiveObject() {
    x = rand() % (20 + 20) - 20;
    init();
}

building::building(float a, float c) : interactiveObject(a, -10, c) {
    init();
}

void building::init() {
    width = rand() % (15 - 5) + 5;
    height = rand() % (20 - 10) + 10;
    depth = rand() % (30 - 5) + 5;
    
    // Update the coordinates
    y = -10 + height / 2;
    
    // Init the bounding box with this position
    box = boundingBox(x, y, z, width, height, depth);
    
    factor = -5;
    touched = false;
}

void building::action(int factor) {
    if (factor == 0)
        playExplosionSong();
    else
        touched = false;
}

void building::drawBuilding(bool shadow) {
    // Create building
    if (buildingTexture.created && !shadow) {
        float emission[4] = {0.25f, 0.25f, 0.25f, 1};
        glMaterialfv(GL_FRONT, GL_EMISSION, emission);
        
        glColor4f(1, 1, 1, 1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, buildingTexture.texID);
    } else {
        glDisable(GL_LIGHTING);
        glDisable(GL_FOG);
        glColor4f(0.3f, 0.3f, 0.3f, 0.9f);
    }
    
    glBegin(GL_QUADS);      // Back
        glTexCoord2f(0.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
        glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
        glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
        glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
    glEnd();
    
    glBegin(GL_QUADS);      // Right
        glTexCoord2f(0.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
        glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
        glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
        glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
    glEnd();
    
    glBegin(GL_QUADS);      // Left
        glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
        glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
        glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.5, -0.5);
        glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
    glEnd();
    
    glBegin(GL_QUADS);      // Top
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, 0.5);
    glEnd();
    
    if (buildingTexture.created && !shadow) {
        glDisable(GL_TEXTURE_2D);
        float emission[4] = {0, 0, 0, 1};
        glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    } else {
        glEnable(GL_LIGHTING);
        glEnable(GL_FOG);
    }
    
    glColor4f(0, 0, 0, 1);
}

void building::draw(GLenum mode, int ident, vector<float> shadowPlane) {
    // Draw shadow
    if (shadowPlane.size() != 0) {
        glPushMatrix();
            shadowMatrix(shadowPlane);
            glTranslatef(x, y, z);
            glScalef(width, height, depth);
            drawBuilding(true);
        glPopMatrix();
        
        return;
    }
    
    // Draw building
    glPushMatrix();
        glTranslatef(x, y, z);
        glScalef(width, height, depth);
        drawBuilding();
    glPopMatrix();
    
    object::draw();
}

void building::updatePlanes() {
    // Finding points for planes
    float v0[3] = {box.xmin, box.ymin, box.zmin};
    float v1[3] = {box.xmin, box.ymax, box.zmax};
    float v2[3] = {box.xmin, box.ymin, box.zmax};
    float v3[3] = {box.xmax, box.ymax, box.zmax};
    
    // Planes
    left = findPlane(v0, v1, v2);
    front = findPlane(v1, v2, v3);
}

void building::update(float dx, float dy, float dz) {
    object::update(0, 0, SPEED);
    updatePlanes();
}

