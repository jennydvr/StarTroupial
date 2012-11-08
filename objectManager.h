//
//  objectManager.h
//  StarTroupial
//
//  Created by Jenny Valdez on 28/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#ifndef __StarTroupial__objectManager__
#define __StarTroupial__objectManager__

#include <time.h>
#include <algorithm>
#include <string.h>
#include "starship.h"
#include "ring.h"
#include "star.h"
#include "asteroid.h"
#include "particle.h"
#include "explosionLight.h"

using namespace std;

// Game objects
extern vector<ring> rings;
extern vector<asteroid> asteroids;
extern vector<star> stars;
extern vector<bullet> bullets;
extern vector<particle> particles;
extern vector<light> lights;
extern starship player;
extern int score;

extern int gametime;
extern int initialGametime;
extern int pausedTime;
extern bool paused;

void drawText(float pos[], char *text);
void updateObjects();
void addObjects();
void drawObjects(GLenum mode = GL_RENDER);
void resetGame();
bool checkGametime();

#endif /* defined(__StarTroupial__objectManager__) */
