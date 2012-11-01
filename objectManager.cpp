//
//  objectManager.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 28/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "objectManager.h"

vector<ring> rings;
vector<asteroid> asteroids;
vector<star> stars;
vector<bullet> bullets;
starship player;

int score = 0;

int currentTime = 0;
int high = 3000, low = 2000;

int ringsPrevTime = 0;
int ringsRate = 3000;

int asteroidsPrevTime = 0;
int asteroidsRate = 3000;

int n = 8;

bool notVisible(object object) {
    return !object.visible();
}

template <class T>
void updatePoints(T &obj) {
    score += obj.updateScore(player);  // ALWAYS EXECUTE THIS
    score = (score < 0) ? 0 : score;   // CHECK THE SCORE LATER
    obj.update();
}

void updateHits(bullet &obj) {
    for (int i = 0; i != asteroids.size(); ++i)
        if ((obj.dead = asteroids[i].hits(obj))) {
            break;
        }
    
    obj.update();
}

void update(star &obj) {
    obj.update();
}

template <class T>
void draw(T obj) {
    if (obj.visible())
        obj.draw();
}

template <class T>
void removeObjects(vector<T> &v) {
    // Put all the dead objects on the back
    partition(v.begin(), v.end(), notVisible);
    
    // Delete them
    while (v.size() != 0 && !v.back().visible())
        v.pop_back();
}

void addRings() {
    // Add rings every 5 seconds
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    if (currentTime - ringsPrevTime < ringsRate)
        return;
    
    if (n == 0) {           // Cross
        rings.push_back(ring(0, 2));
        rings.push_back(ring(0, -2));
        rings.push_back(ring(-2.5, 0));
        rings.push_back(ring(2.5, 0));
    } else if (n == 1) {     // Tunnel
        int x = (float)rand() / ((float)RAND_MAX / 8) - 4;
        int y = (float)rand() / ((float)RAND_MAX / 8) - 4;
        
        rings.push_back(ring(x, y, 0));
        rings.push_back(ring(x, y, -5));
        rings.push_back(ring(x, y, -10));
        rings.push_back(ring(x, y, -15));
        rings.push_back(ring(x, y, -20));
        
    } else if (n == 2) {     // Triforce
        rings.push_back(ring(0, 1.75));
        rings.push_back(ring(2, -1.75));
        rings.push_back(ring(-2, -1.75));
        
    } else if (n == 3) {     // 4 things on side
        rings.push_back(ring(5, 1));
        rings.push_back(ring(2.75, -1));
        rings.push_back(ring(-5, 1));
        rings.push_back(ring(-2.75, -1));
        
    } else if (n == 4) {     // Loop tunnel
        rings.push_back(ring(0, 0, 0));
        rings.push_back(ring(-1.5, 1.25, -5));
        rings.push_back(ring(1.25, 1.25, -10));
        rings.push_back(ring(1.25, -1.25, -15));
        rings.push_back(ring(-1.25, -1.25, -20));
        rings.push_back(ring(0, 0, -25));
        
    } else {     // 1 ring
        rings.push_back(ring());
    }
    
    // Choose next configuration and set time
    n = 8;
    ringsRate = rand() % (high - low) + low;
    ringsPrevTime = currentTime;
}

void addAsteroids() {
    // Add rings every 5 seconds
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    if (currentTime - asteroidsPrevTime < asteroidsRate)
        return;
    
    asteroids.push_back(asteroid());
    
    // Choose next configuration and set time
    asteroidsRate = rand() % (high - low) + low;
    asteroidsPrevTime = currentTime;
    high -= (high > low + 100) ? 1 : 0;
}

void updateObjects() {
    // Update stuff
    for_each(bullets.begin(), bullets.end(), updateHits);
    for_each(rings.begin(), rings.end(), updatePoints<ring>);
    for_each(asteroids.begin(), asteroids.end(), updatePoints<asteroid>);
    for_each(stars.begin(), stars.end(), update);
    
    // Remove dead objects (bizarre way that works)
    removeObjects(rings);
    removeObjects(asteroids);
    removeObjects(stars);
    removeObjects(bullets);
}

void addObjects() {
    // Add stars
    if (rand() % 100 + 1 > 80)
        stars.push_back(star());
    
    // Add rings
    addRings();
    
    // Add asteroids
    addAsteroids();
}

void drawObjects() {
    // Draw player
    player.draw();
    
    // Update stars
    for_each(stars.begin(), stars.end(), draw<star>);
    
    // Update bullets
    for_each(bullets.begin(), bullets.end(), draw<bullet>);
    
    // Update rings
    for_each(rings.begin(), rings.end(), draw<ring>);
    
    // Update asteroids
    for_each(asteroids.begin(), asteroids.end(), draw<asteroid>);
}
