//
//  grassfloor.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 30/11/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "grassfloor.h"

grassfloor::grassfloor() : object(1, -1) {}

void grassfloor::draw(GLenum mode, int ident) {
    
    glEnable(GL_TEXTURE_2D);
    
    // Lazy texture creation
    if (!texture.created) {
        char name[32] = "resources/sky.tga";
        loadTexture(name);
    }
    
    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, texture.texID);
    
    // Create the grass plane
    glPushMatrix();
        glBegin(GL_QUADS);
            glColor3f(1.0,1.0,1.0); glTexCoord2f(0.0, 0.0); glVertex3f(-275.0, -10.0 , -10.0);
            glColor3f(1.0,1.0,1.0); glTexCoord2f(0.0, 1.0); glVertex3f(-275.0, -50.0, 150.0);
            glColor3f(1.0,1.0,1.0); glTexCoord2f(1.0, 1.0); glVertex3f(275.0, -50.0, 150.0);
            glColor3f(1.0,1.0,1.0); glTexCoord2f(1.0, 0.0); glVertex3f(275.0, -10.0, -10.0);
        glEnd();
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
}
