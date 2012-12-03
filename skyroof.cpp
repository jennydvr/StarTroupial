//
//  skyroof.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 03/12/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "skyroof.h"

skyroof::skyroof() : object(1, -1) {}

void skyroof::draw(GLenum mode, int ident) {
    glEnable(GL_TEXTURE_2D);
    
    // Lazy texture creation
    if (!texture.created) {
        char name[32] = "resources/sky.tga";
        loadTexture(name);
    }
    
    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, texture.texID);
    
    // Create the sky plane
    glPushMatrix();
        glBegin(GL_QUADS);
            glColor3f(1.0,1.0,1.0); glTexCoord2f(0.0, 0.0); glVertex3f(-275.0, -26.0 , -10.0);
            glColor3f(1.0,1.0,1.0); glTexCoord2f(0.0, 1.0); glVertex3f(-275.0, 180.0, 150.0);
            glColor3f(1.0,1.0,1.0); glTexCoord2f(1.0, 1.0); glVertex3f(275.0, 180.0, 150.0);
            glColor3f(1.0,1.0,1.0); glTexCoord2f(1.0, 0.0); glVertex3f(275.0, -26.0, -10.0);
        glEnd();
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
}