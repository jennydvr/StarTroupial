//
//  starship.h
//  StarTroupial
//
//  Created by Jenny Valdez on 27/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#ifndef __StarTroupial__starship__
#define __StarTroupial__starship__

#include "bullet.h"

class starship : public interactiveObject {
    
    // Mesh of the starship
    GLMmodel* model;
    
    // Time for shooting
    int currentShooting, previousShooting;
    
    // Draw the model
    void drawModel(bool withoutTexture = true);
    
    // Invulnerability
    int currentInv, previousInv, previousText;
    bool texturize;
    
public:
    
    // Player's score
    int score;
    
    // Player's velocity
    float velocity[2];
    
    // Constructor
    starship();
    
    // Changes the ship's velocity
    void changeVelocity(int dx, int dy);
    
    // Shoots
    bullet shoot(float xf = -1, float yf = -1, float zf = -1);
    
    // Activated when hitted by something
    void action(int factor = 0);
    
    // Updates the ship's position
    void update(float dx = 0, float dy = 0, float dz = 0);
    
    // Draws the ship
    void draw(GLenum mode = GL_RENDER, int ident = 0);
    
    // Resets the ship
    void reset();
    
};

#endif /* defined(__StarTroupial__starship__) */
