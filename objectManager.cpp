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
int high = 4000, low = 2000;

int ringsPrevTime = 0;
int ringsRate = 3000;

int asteroidsPrevTime = 0;
int asteroidsRate = 3000;

int initialGametime = 0;

bool notVisible(object object) {
    return !object.visible();
}

template <class T>
void draw(T obj) {
    if (obj.visible())
        obj.draw();
}

template <class T>
void update(T &obj) {
    obj.update();
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
    int t = (glutGet(GLUT_ELAPSED_TIME) - initialGametime) / 1000;
    gametime = gametime <= 0 ? 0 : 60 - t;
    return gametime == 0;
}

void addRings() {
    // Add rings every 5 seconds
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    if (currentTime - ringsPrevTime < ringsRate)
        return;
    
    int n = rand() % 6;
    
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
    } else {     // 1 ring
        rings.push_back(ring());
    }
    
    // Choose next configuration and set time
    ringsRate = rand() % (high - low) + low;
    ringsPrevTime = currentTime;
}

void addAsteroids() {
    // Add rings every 5 seconds
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    if (currentTime - asteroidsPrevTime < asteroidsRate)
        return;
    
    int n = rand() % 6;
    
    if (n == 0) {           // Line
        asteroids.push_back(asteroid(-6, 0));
        asteroids.push_back(asteroid(-2, 0));
        asteroids.push_back(asteroid(2, 0));
        asteroids.push_back(asteroid(6, 0));
    } else if (n == 1) {     // Triforce
        asteroids.push_back(asteroid(0, 2));
        asteroids.push_back(asteroid(2.5, -2));
        asteroids.push_back(asteroid(-2.5, -2));        
    } else if (n == 2) {     // V-shaped
        asteroids.push_back(asteroid(6, 2.5));
        asteroids.push_back(asteroid(3, 0));
        asteroids.push_back(asteroid(0, -2.5));
        asteroids.push_back(asteroid(-3, 0));
        asteroids.push_back(asteroid(-6, 2.5));
    } else if (n == 3) {     // X-shaped
        asteroids.push_back(asteroid(6, 6));
        asteroids.push_back(asteroid(3, 3));
        asteroids.push_back(asteroid(6, -6));
        asteroids.push_back(asteroid(3, -3));
        asteroids.push_back(asteroid(0, 0));
        asteroids.push_back(asteroid(-3, 3));
        asteroids.push_back(asteroid(-6, 6));
        asteroids.push_back(asteroid(-3, -3));
        asteroids.push_back(asteroid(-6, -6));
    } else {     // 1 ring
        asteroids.push_back(asteroid());
    }
    
    // Choose next configuration and set time
    asteroidsRate = rand() % (high - low) + low;
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

void drawObjects() {
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
    
    // Draw asteroids
    for_each(asteroids.begin(), asteroids.end(), draw<asteroid>);
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
