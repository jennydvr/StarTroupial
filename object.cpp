//
//  object.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 31/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "object.h"

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

void object::loadTexture(char *name) {
    
    // In case of error, keep calm and keep going
    if (!LoadTGA(texture, name)) {
        std::cout << "Error: No ha podido cargarse la textura \"" << name << "\".\n";
        texture.created = false;
    }
    
    // Create the texture
    glGenTextures(1, &(texture.texID));
    glBindTexture(GL_TEXTURE_2D, texture.texID);
    glTexImage2D(GL_TEXTURE_2D, 0, texture.bpp / 8, texture.width,
                 texture.height, 0, texture.type, GL_UNSIGNED_BYTE, texture.imageData);
        
    // Set some parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        
    // Free the image - already used
    if (texture.imageData)
        free(texture.imageData);
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

void object::draw(GLenum mode, int ident) {
    if (dead) return;
    
    if (debug)
        box.draw();
}
