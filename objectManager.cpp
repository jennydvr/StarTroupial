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
vector<particle> particles;
vector<bullet> bullets;
vector<light> lights;
starship player;

int gametime = 60;
int score = 0;

int currentTime = 0;

int ringsPrevTime = 0;
int ringsRate = 3000;

int asteroidsPrevTime = 0;
int asteroidsRate = 3000;

int initialGametime = 0;
int pausedTime = 0;

bool notVisible(object object) {
    return !object.visible();
}

template <class T>
void draw(T obj) {
    if (obj.visible())
        obj.draw();
}

void drawAsteroid(asteroid obj, int ident, GLenum mode) {
    if (obj.visible())
        obj.draw(mode, ident);
}

template <class T>
void update(T &obj) {
    obj.update();
}

template <class T>
void updatePoints(T &obj) {
    obj.hits(player);
    score = player.score;
    obj.update();
}

void updateHits(bullet &obj) {
    for (int i = 0; i != asteroids.size(); ++i) {
        asteroids[i].hits(obj);
        if (obj.dead)
            break;
    }
    
    obj.update();
}

void updateParticles(asteroid &obj) {   // ADDS EXPLOSION LIGHT TOO
    if (!obj.dead)
        return;
    
    vector<particle> ans = obj.explode();
    
    // Only create light if there are particles - explosion
    if (!ans.empty())
        lights.push_back(obj.createLight());
    
    while (!ans.empty()) {
        particles.push_back(ans.back());
        ans.pop_back();
    }
}

template <class T>
void removeObjects(vector<T> &v) {
    // Put all the dead objects on the back
    partition(v.begin(), v.end(), notVisible);
    
    // Delete them
    while (v.size() != 0 && !v.back().visible())
        v.pop_back();
}

bool checkGametime() {
    if (!paused) {
        int t = (glutGet(GLUT_ELAPSED_TIME) - initialGametime) / 1000;
        gametime = gametime <= 0 ? 0 : 60 - t;
    }
    
    return gametime == 0;
}

void addRings() {
    // Add rings every 5 seconds
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    if (currentTime - ringsPrevTime < ringsRate)
        return;
    
    int x, y;
    
    switch (rand() % 10) {
        case 0:           // Cross
            rings.push_back(ring(0, 2));
            rings.push_back(ring(0, -2));
            rings.push_back(ring(-2.5, 0));
            rings.push_back(ring(2.5, 0));
            break;
            
        case 1:     // Tunnel
            x = (float)rand() / ((float)RAND_MAX / 8) - 4;
            y = (float)rand() / ((float)RAND_MAX / 8) - 4;
            
            rings.push_back(ring(x, y, 0));
            rings.push_back(ring(x, y, -5));
            rings.push_back(ring(x, y, -10));
            rings.push_back(ring(x, y, -15));
            rings.push_back(ring(x, y, -20));
            break;
            
        case 2:     // Triforce
            rings.push_back(ring(0, 1.75));
            rings.push_back(ring(2, -1.75));
            rings.push_back(ring(-2, -1.75));
            break;
            
        case 3:     // 4 things on side
            rings.push_back(ring(5, 1));
            rings.push_back(ring(2.75, -1));
            rings.push_back(ring(-5, 1));
            rings.push_back(ring(-2.75, -1));
            break;
	    
        case 4:     // Tunnel Diagonal I Cuadrante
            x = (float)rand() / ((float)RAND_MAX / 8) - 4;
            y = (float)rand() / ((float)RAND_MAX / 8) - 4;
            
            rings.push_back(ring(x, y, 0));
            rings.push_back(ring(x+1, y+1, -5));
            rings.push_back(ring(x+2, y+2, -7));
            rings.push_back(ring(x+3, y+3, -9));
            rings.push_back(ring(x+4, y+4, -11));
            break;
        case 5:     // Tunnel Diagonal II Cuadrante
            x = (float)rand() / ((float)RAND_MAX / 8) - 4;
            y = (float)rand() / ((float)RAND_MAX / 8) - 4;
            
            rings.push_back(ring(x, y, 0));
            rings.push_back(ring(x-1, y+1, -5));
            rings.push_back(ring(x-2, y+2, -7));
            rings.push_back(ring(x-3, y+3, -9));
            rings.push_back(ring(x-4, y+4, -11));
            break;
        case 6:     // Tunnel Diagonal III Cuadrante
            x = (float)rand() / ((float)RAND_MAX / 8) - 4;
            y = (float)rand() / ((float)RAND_MAX / 8) - 4;
            
            rings.push_back(ring(x, y, 0));
            rings.push_back(ring(x-1, y-1, -5));
            rings.push_back(ring(x-2, y-2, -7));
            rings.push_back(ring(x-3, y-3, -9));
            rings.push_back(ring(x-4, y-4, -11));
            break;
        case 7:     // Tunnel Diagonal IV Cuadrante
            x = (float)rand() / ((float)RAND_MAX / 8) - 4;
            y = (float)rand() / ((float)RAND_MAX / 8) - 4;
            
            rings.push_back(ring(x, y, 0));
            rings.push_back(ring(x+1, y-1, -5));
            rings.push_back(ring(x+2, y-2, -7));
            rings.push_back(ring(x+3, y-3, -9));
            rings.push_back(ring(x+4, y-4, -11));
            break;	    
	    
        default:     // 1 ring
            rings.push_back(ring());
            break;
    }
    
    // Choose next configuration and set time
    ringsRate = rand() % 2000 + 2000;
    ringsPrevTime = currentTime;
}

void addAsteroids() {
    // Add rings every 5 seconds
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    if (currentTime - asteroidsPrevTime < asteroidsRate)
        return;
    
    switch (rand() % 6) {
        case 0:           // Line
            asteroids.push_back(asteroid(-6, 0));
            asteroids.push_back(asteroid(-2, 0));
            asteroids.push_back(asteroid(2, 0));
            asteroids.push_back(asteroid(6, 0));
            break;
            
        case 1:     // Triforce
            asteroids.push_back(asteroid(0, 2));
            asteroids.push_back(asteroid(2.5, -2));
            asteroids.push_back(asteroid(-2.5, -2));
            break;
            
        case 2:     // V-shaped
            asteroids.push_back(asteroid(6, 2.5));
            asteroids.push_back(asteroid(3, 0));
            asteroids.push_back(asteroid(0, -2.5));
            asteroids.push_back(asteroid(-3, 0));
            asteroids.push_back(asteroid(-6, 2.5));
            break;
            
        case 3:     // X-shaped
            asteroids.push_back(asteroid(6, 6));
            asteroids.push_back(asteroid(3, 3));
            asteroids.push_back(asteroid(6, -6));
            asteroids.push_back(asteroid(3, -3));
            asteroids.push_back(asteroid(0, 0));
            asteroids.push_back(asteroid(-3, 3));
            asteroids.push_back(asteroid(-6, 6));
            asteroids.push_back(asteroid(-3, -3));
            asteroids.push_back(asteroid(-6, -6));
            break;
            
        default:     // 1 ring
            asteroids.push_back(asteroid());
            break;
    }
    
    // Choose next configuration and set time
    asteroidsRate = rand() % 2000 + 2000;
    asteroidsPrevTime = currentTime;
}

void updateObjects() {
    // Update stuff
    for_each(bullets.begin(), bullets.end(), updateHits);
    for_each(rings.begin(), rings.end(), updatePoints<ring>);
    for_each(asteroids.begin(), asteroids.end(), updatePoints<asteroid>);
    for_each(stars.begin(), stars.end(), update<star>);
    for_each(particles.begin(), particles.end(), update<particle>);
    for_each(lights.begin(), lights.end(), update<light>);
    player.update();
    
    // Add particles
    for_each(asteroids.begin(), asteroids.end(), updateParticles);
    
    // Remove dead objects (bizarre way that works)
    removeObjects(rings);
    removeObjects(asteroids);
    removeObjects(stars);
    removeObjects(particles);
    removeObjects(bullets);
    removeObjects(lights);
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

void drawObjects(GLenum mode) {
    // Draw player
    player.draw();
    
    // Draw stars
    for_each(stars.begin(), stars.end(), draw<star>);
    
    // Draw particles
    for_each(particles.begin(), particles.end(), draw<particle>);
    
    // Draw bullets
    for_each(bullets.begin(), bullets.end(), draw<bullet>);
    
    // Draw rings
    for_each(rings.begin(), rings.end(), draw<ring>);
    
    for (int i = 0; i != asteroids.size(); ++i)
        drawAsteroid(asteroids[i], i, mode);
}

void resetGame() {
    particles.clear();
    stars.clear();
    bullets.clear();
    rings.clear();
    asteroids.clear();
    
    // DISABLE ALL LIGHTS!!
    for_each(lights.begin(), lights.end(), light::disable);
    lights.clear();
    glDisable(GL_LIGHT1);
    
    score = 0;
    player.reset();
    
    currentTime = 0;
    
    ringsPrevTime = glutGet(GLUT_ELAPSED_TIME);
    ringsRate = 3000;
    
    asteroidsPrevTime = glutGet(GLUT_ELAPSED_TIME);
    asteroidsRate = 3000;
    initialGametime = glutGet(GLUT_ELAPSED_TIME);
    gametime = 60;
}
