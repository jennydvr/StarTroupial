//
//  starship.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 27/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "starship.h"

starship::starship() : interactiveObject(0, 0, 190) {
    box = boundingBox(x, y, z, 1, true);
    previousInv = -2000;        // Not invulnerable at the beginning
    previousShooting = previousText = score = 0;
    texturize = true;
    velocity[0] = velocity[1] = 0;
    texture.created = false;
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
    velocity[0] = 0.1 * dx;
    velocity[1] = 0.1 * dy;
}

void starship::update(float dx, float dy, float dz) {
    object::update(velocity[0], velocity[1]);
    
    // Check horizontal bounds
    int cx = 0, cy = 0;
    
    if (x < -11.5) {
        x = -11.5;
        cx = 1;
    } else if (x > 11.5) {
        x = 11.5;
        cx = 1;
    }
    
    // Check vertical bounds
    if (y < -8.5) {
        y = -8.5;
        cy = 1;
    } else if (y > 8.5) {
        y = 8.5;
        cy = 1;
    }
    
    // Update box in case of bound violation
    box.update(-velocity[0] * cx, -velocity[1] * cy, 0);
}

void starship::brightness(float r, float g, float b) {
    // For more about this numbers, check documentation
    GLfloat color[] = {r, g, b, 1};
    GLfloat emission[] = {0.1, 0.1, 0.1, 1};
    GLfloat specular[] = {0.774597, 0.774597, 0.774597, 1};
    GLfloat shininess = 76.8;
    
    // If the shininess is desired to be turned off, set everything to 0
    if (r + g + b == 0) {
        color[0] = color[1] = color[2] = 0;
        emission[0] = emission[1] = emission[2] = 0;
        specular[0] = specular[1] = specular[2] = 0;
        shininess = 0;
    }
    
    // Set specular, shininess and the internal light
    glColor3f(color[0], color[1], color[2]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
}

void starship::drawModel(bool withoutTexture) {
    // Lazy texture creation - only when neccessary
    if (!texture.created) {
        char name[32] = "resources/s_1024_C.tga";
        loadTexture(name);
    }
    
    // Lazy model creation
    if (!model) {
        char filename[32] = "resources/shipA_OBJ.obj";
        model = glmReadOBJ(filename);
        
        if (!model)
            exit(0);
        
        glmUnitize(model);
        glmFacetNormals(model);
        glmVertexNormals(model, 90);
    }
    
    // If the texture doesn't exists or draw without texture
    if (!texture.created || withoutTexture) {
        brightness(0.75, 0, 0);
        glmDraw(model, GLM_SMOOTH);
        
    // If texture exists and draw with texture
    } else {
        brightness(0.6, 0.6, 0.4);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture.texID);
        glmDraw(model, GLM_SMOOTH | GLM_TEXTURE);
        glDisable(GL_TEXTURE_2D);
    }
    
    brightness();
}

void starship::draw(GLenum mode, int ident) {
    // Every 50 miliseconds update texturize
    if (glutGet(GLUT_ELAPSED_TIME) - previousText >= 50) {
        previousText = glutGet(GLUT_ELAPSED_TIME);
        texturize = !texturize;
    }
    
    glPushMatrix();
        glTranslatef(x, y, z);
        drawModel(glutGet(GLUT_ELAPSED_TIME) - previousInv < 2000 && !texturize);
    glPopMatrix();
    
    object::draw();
}

void starship::reset() {
    x = y = velocity[0] = velocity[1] = 0;
    box = boundingBox(x, y, z, 1, true);
    previousInv = previousShooting = score = 0;
    texturize = true;
}
