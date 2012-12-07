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
vector<building> buildings;
vector<star> stars;
vector<particle> particles;
vector<bullet> bullets;
vector<light> lights;
starship player;
grassfloor grass;
skyroof sky;

int gametime = 60;
int score = 0;

int ringsPrevTime = 0;
int ringsRate = 2000;

int asteroidsPrevTime = 0;
int asteroidsRate = 3500;

int buildingsPrevTime = 0;
int buildingsRate = 3000;

int initialGametime = 0;
int pausedTime = 0;

bool infinite = false;
int prevShooting = 0;

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

template <class T>
void checkBuildingsHit(T &obj) {
    for (int i = 0; i != buildings.size(); ++i) {
        if (collision(buildings[i].box, obj.box)) {
            obj.dead = true;
            return;
        }
    }
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

void addRing(ring r) {
    checkBuildingsHit(r);
    if (!r.dead)
        rings.push_back(r);
}

void addAsteroid(asteroid a) {
    checkBuildingsHit(a);
    if (!a.dead)
        asteroids.push_back(a);
}

bool checkGametime() {
    if (!paused || !infinite) {
        int t = (glutGet(GLUT_ELAPSED_TIME) - initialGametime) / 1000;
        gametime = gametime <= 0 ? 0 : 60 - t;
    }
    
    return gametime == 0;
}

void addBuildings() {
    if (glutGet(GLUT_ELAPSED_TIME) - buildingsPrevTime < buildingsRate)
        return;
    
    int x = rand() % (30 - 15) + 15;
    
    switch (rand() % 4) {
        case 1:
            buildings.push_back(building(-x, -10));
            buildings.push_back(building(x, -10));
            break;
            
        default:
            buildings.push_back(building());
            break;
    }
            
    // Choose next configuration and set time
    buildingsRate = rand() % 1000 + 2000;
    buildingsPrevTime = glutGet(GLUT_ELAPSED_TIME);
}

void addRings() {
    if (glutGet(GLUT_ELAPSED_TIME) - ringsPrevTime < ringsRate)
        return;
    
    int x, y, dx, dy;
    
    switch (rand() % 10) {
        case 0:             // Cross
            addRing(ring(0, 2));
            addRing(ring(0, -2));
            addRing(ring(-2.5, 0));
            addRing(ring(2.5, 0));
            break;
            
        case 1:             // Triforce
            addRing(ring(0, 1.75));
            addRing(ring(2, -1.75));
            addRing(ring(-2, -1.75));
            break;
            
        case 2:             // 4 things on side
            addRing(ring(5, 1));
            addRing(ring(2.75, -1));
            addRing(ring(-5, 1));
            addRing(ring(-2.75, -1));
            break;
	    
        case 3: case 4:     // Tunnels
            x = (float)rand() / ((float)RAND_MAX / 8) - 4;
            y = (float)rand() / ((float)RAND_MAX / 8) - 4;
            
            dx = rand() % 2 - 1;
            dy = rand() % 2 - 1;
            
            addRing(ring(x, y, 0));
            addRing(ring(x + 0.5f * dx, y + 0.5f * dy, -2));
            addRing(ring(x + 1.0f * dx, y + 1.0f * dy, -4));
            addRing(ring(x + 1.5f * dx, y + 1.5f * dy, -6));
            addRing(ring(x + 2.0f * dx, y + 2.0f * dy, -8));
            break;
	    
        default:            // 1 ring
            addRing(ring());
            break;
    }
    
    // Choose next configuration and set time
    ringsRate = rand() % 2000 + 2000;
    ringsPrevTime = glutGet(GLUT_ELAPSED_TIME);
}

void addAsteroids() {
    if (glutGet(GLUT_ELAPSED_TIME) - asteroidsPrevTime < asteroidsRate)
        return;
    
    switch (rand() % 6) {
        case 0:         // Line
            addAsteroid(asteroid(-6, 0));
            addAsteroid(asteroid(-2, 0));
            addAsteroid(asteroid(2, 0));
            addAsteroid(asteroid(6, 0));
            break;
            
        case 1:         // Triforce
            addAsteroid(asteroid(0, 2));
            addAsteroid(asteroid(2.5, -2));
            addAsteroid(asteroid(-2.5, -2));
            break;
            
        case 2:         // V-shaped
            addAsteroid(asteroid(6, 2.5));
            addAsteroid(asteroid(3, 0));
            addAsteroid(asteroid(0, -2.5));
            addAsteroid(asteroid(-3, 0));
            addAsteroid(asteroid(-6, 2.5));
            break;
            
        case 3:         // X-shaped
            addAsteroid(asteroid(6, 6));
            addAsteroid(asteroid(3, 3));
            addAsteroid(asteroid(6, -6));
            addAsteroid(asteroid(3, -3));
            addAsteroid(asteroid(0, 0));
            addAsteroid(asteroid(-3, 3));
            addAsteroid(asteroid(-6, 6));
            addAsteroid(asteroid(-3, -3));
            addAsteroid(asteroid(-6, -6));
            break;
            
        default:        // 1 ring
            addAsteroid(asteroid());
            break;
    }
    
    // Choose next configuration and set time
    asteroidsRate = rand() % 2000 + 2000;
    asteroidsPrevTime = glutGet(GLUT_ELAPSED_TIME);
}

void updateObjects() {
    // Update stuff
    for_each(bullets.begin(), bullets.end(), updateHits);
    for_each(rings.begin(), rings.end(), updatePoints<ring>);
    for_each(asteroids.begin(), asteroids.end(), updatePoints<asteroid>);
    for_each(buildings.begin(), buildings.end(), updatePoints<building>);
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
    if (rand() % 100 > 80)
        stars.push_back(star());
    
    // Add buildings
    addBuildings();
    
    // Add rings
    addRings();
    
    // Add asteroids
    addAsteroids();
}

void drawObjects(GLenum mode) {
    // Draw player
    player.draw();
    
    // Draw grass
    grass.draw();
    
    // Draw sky
    sky.draw();
    
    // Draw stars
    for_each(stars.begin(), stars.end(), draw<star>);
    
    // Draw particles
    for_each(particles.begin(), particles.end(), draw<particle>);
    
    // Draw bullets
    for_each(bullets.begin(), bullets.end(), draw<bullet>);
    
    // Draw rings
    for_each(rings.begin(), rings.end(), draw<ring>);
    
    // Draw buildings
    for_each(buildings.begin(), buildings.end(), draw<building>);
    
    // Draw asteroids
    for (int i = 0; i != asteroids.size(); ++i)
        drawAsteroid(asteroids[i], i, mode);
}

void drawShadows() {
    // Draw ground shadows
    player.draw(GL_RENDER, 0, groundPlane());
    
    for (int i = 0; i != asteroids.size(); ++i)
        asteroids[i].draw(GL_RENDER, 0, groundPlane());
    
    for (int i = 0; i != rings.size(); ++i)
        rings[i].draw(GL_RENDER, 0, groundPlane());
    
    for (int i = 0; i != bullets.size(); ++i)
        bullets[i].draw(GL_RENDER, 0, groundPlane());
    
    for (int i = 0; i != buildings.size(); ++i)
        buildings[i].draw(GL_RENDER, 0, groundPlane());
}

void resetGame() {
    // DISABLE ALL LIGHTS!!
    for_each(lights.begin(), lights.end(), light::disable);
    for_each(bullets.begin(), bullets.end(), bullet::disable);
    
    // Clear all
    particles.clear();
    stars.clear();
    bullets.clear();
    rings.clear();
    asteroids.clear();
    buildings.clear();
    lights.clear();
    
    prevShooting = score = 0;
    player.reset();
    
    ringsPrevTime = glutGet(GLUT_ELAPSED_TIME);
    ringsRate = 2000;
    
    asteroidsPrevTime = glutGet(GLUT_ELAPSED_TIME);
    asteroidsRate = 3500;
    
    buildingsPrevTime = glutGet(GLUT_ELAPSED_TIME);
    buildingsRate = 3000;
    
    initialGametime = glutGet(GLUT_ELAPSED_TIME);
    gametime = 60;
}
