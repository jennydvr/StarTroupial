//
//  collisionManager.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 28/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "collisionManager.h"

bool debug = false;

bool collision(boundingBox a, boundingBox b) {
    std::vector<float> amin = a.getMin();
    std::vector<float> bmin = b.getMin();
    std::vector<float> amax = a.getMax();
    std::vector<float> bmax = b.getMax();
    
    return amax[0] >= bmin[0] && bmax[0] >= amin[0]
        && amax[1] >= bmin[1] && bmax[1] >= amin[1]
        && amax[2] >= bmin[2] && bmax[2] >= amin[2];
}

boundingBox::boundingBox(): xmin(0), ymin(0), zmin(0), xmax(0), ymax(0), zmax(0) {}

boundingBox::boundingBox(float xi, float yi, float zi, float innerRadius, float outerRadius) {
    xmin = ymin = -outerRadius + 3 * innerRadius;
    zmin = -innerRadius;
    
    xmax = ymax = outerRadius - 3 * innerRadius;
    zmax = innerRadius;
    
    update(xi, yi, zi);
    
    ymin *= 1.5f;
    ymax *= 1.5f;
}

boundingBox::boundingBox(float xi, float yi, float zi, float radius, bool isShip) {
    xmin = ymin = zmin = -radius;
    xmax = ymax = zmax = radius;
    
    update(xi, yi, zi);
    
    if (isShip) {
        ymin *= 0.65f;
        ymax *= 0.65f;
    }
}

boundingBox::boundingBox(float xi, float yi, float zi, float width, float height, float depth) {
    xmin = -width / 2;
    ymin = -height / 2;
    zmin = -depth / 2;
    
    xmax = -xmin;
    ymax = -ymin;
    zmax = -zmin;
    
    update(xi, yi, zi);
}

std::vector<float> boundingBox::getMin() {
    float ans[3] = {xmin, ymin, zmin};
    return std::vector<float>(ans, ans + 3);
}

std::vector<float> boundingBox::getMax() {
    float ans[3] = {xmax, ymax, zmax};
    return std::vector<float>(ans, ans + 3);
}

void boundingBox::update(float nx, float ny, float nz) {
    xmin += nx; xmax += nx;
    ymin += ny; ymax += ny;
    zmin += nz; zmax += nz;
}

void boundingBox::draw() {
    // Back face
    glBegin(GL_LINE_LOOP);
        glVertex3f(xmin, ymin, zmin);
        glVertex3f(xmin, ymax, zmin);
        glVertex3f(xmax, ymax, zmin);
        glVertex3f(xmax, ymin, zmin);
    glEnd();
    
    // Front face
    glBegin(GL_LINE_LOOP);
        glVertex3f(xmin, ymin, zmax);
        glVertex3f(xmin, ymax, zmax);
        glVertex3f(xmax, ymax, zmax);
        glVertex3f(xmax, ymin, zmax);
    glEnd();
    
    // Sides
    glBegin(GL_LINES);
        glVertex3f(xmin, ymin, zmax);
        glVertex3f(xmin, ymin, zmin);
    
        glVertex3f(xmin, ymax, zmax);
        glVertex3f(xmin, ymax, zmin);
    
        glVertex3f(xmax, ymax, zmax);
        glVertex3f(xmax, ymax, zmin);
    
        glVertex3f(xmax, ymin, zmax);
        glVertex3f(xmax, ymin, zmin);
    glEnd();
}
