//
//  grassfloor.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 30/11/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "grassfloor.h"

using namespace std;

grassfloor::grassfloor() : object(1, -1) {}

void grassfloor::draw(GLenum mode, int ident, vector<float> shadowPlane) {
    // Bind the texture
    if (skyTexture.created) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, skyTexture.texID);
    }
    
    // Create the grass plane
    glPushMatrix();
        glBegin(GL_QUADS);
            glColor3f(1.0,1.0,1.0); glTexCoord2f(0.0, 0.0); glVertex3f(-250.0, -10.0 , 0.0);
            glColor3f(1.0,1.0,1.0); glTexCoord2f(0.0, 1.0); glVertex3f(-250.0, -10.0, 300.0);
            glColor3f(1.0,1.0,1.0); glTexCoord2f(1.0, 1.0); glVertex3f(250.0, -10.0, 300.0);
            glColor3f(1.0,1.0,1.0); glTexCoord2f(1.0, 0.0); glVertex3f(250.0, -10.0, 0.0);
        glEnd();
    glPopMatrix();
    
    if (skyTexture.created)
        glDisable(GL_TEXTURE_2D);
}
