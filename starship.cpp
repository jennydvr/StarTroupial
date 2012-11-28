//
//  starship.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 27/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "starship.h"

starship::starship() : interactiveObject(0, 0, 40) {
    box = boundingBox(x, y, z, 1, true);
    previousInv = -2000;        // Not invulnerable at the beginning
    previousShooting = previousText = score = 0;
    texturize = true;
    velocity[0] = velocity[1] = 0;
}

bullet starship::shoot(float xf, float yf, float zf) {
    // Add bullet every half-a-second
    if (glutGet(GLUT_ELAPSED_TIME) - previousShooting < 500)
        return bullet(0, 0, xf, yf, zf, true);
    
    previousShooting = glutGet(GLUT_ELAPSED_TIME);
    
    if (xf == -1 && yf == -1 && zf == -1) {
        xf = x;
        yf = y;
        zf = z - 10;
    }
    
    playShootingSong();
    return bullet(x, y, xf, yf, zf);
}

void starship::action(int factor) {
    if (factor < 0) {
        if (glutGet(GLUT_ELAPSED_TIME) - previousInv < 2000)
            return;
        
        previousInv = glutGet(GLUT_ELAPSED_TIME);
    }
    
    score += factor;
    score = (score < 0) ? 0 : score;
}

void starship::changeVelocity(int dx, int dy) {
    if ( (-11 < 0.1 * dx + x && 0.1 * dx + x < 11)  // Ship between bounds
      || (-11 >= 0.1 * dx + x && dx == 1)           // Ship stuck on left - but you're moving it right
      || (0.1 * dx + x >= 11 && dx == -1))          // Ship stuck on right - but you're moving it left
        velocity[0] = 0.1 * dx;
    else
        velocity[0] = 0;
    
    if ( (-7 < 0.1 * dy + y && 0.1 * dy + y < 7)     // Ship between bounds
        || (-7 >= 0.1 * dy + x && dy == 1)           // Ship stuck on left - but you're moving it right
        || (0.1 * dy + y >= 7 && dy == -1))          // Ship stuck on right - but you're moving it left
        velocity[1] = 0.1 * dy;
    else
        velocity[1] = 0;
}

void starship::update(float dx, float dy, float dz) {
    object::update(velocity[0], velocity[1]);
}

void starship::drawModel(bool withoutTexture) {
    glDisable(GL_COLOR_MATERIAL);
    if (!model) {
        char filename[32] = "resources/ship.obj";
        model = glmReadOBJ(filename);
        
        if (!model)
            exit(0);
        
        glmUnitize(model);
        glmFacetNormals(model);
        glmVertexNormals(model, 90);
    }
    
    if (withoutTexture)
        glmDraw(model, GLM_SMOOTH);
    else
        glmDraw(model, GLM_SMOOTH | GLM_MATERIAL);
    glEnable(GL_COLOR_MATERIAL);
}

void starship::draw(GLenum mode, int ident) {
    if (glutGet(GLUT_ELAPSED_TIME) - previousText >= 50) {
        previousText = glutGet(GLUT_ELAPSED_TIME);
        texturize = !texturize;
    }
    
    glPushMatrix();
        glTranslatef(x, y, z);
    
        glColor3f(1, 0, 0);
        drawModel(glutGet(GLUT_ELAPSED_TIME) - previousInv < 2000 && !texturize);
        glColor3f(0, 0, 0);
    
    glPopMatrix();
    
    object::draw();
}

void starship::reset() {
    x = y = 0;
    box = boundingBox(x, y, z, 1, true);
    previousInv = previousShooting = score = 0;
}
