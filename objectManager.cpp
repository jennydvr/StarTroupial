//
//  objectManager.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 28/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "objectManager.h"

vector<ring> rings;
vector<star> stars;
ship player;

int currentTime = 0, previousTime = 0;
int rate = 3000;
int high = 3000, low = 1000;

void addRings(int n) {
    // Add rings every 5 seconds
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    if (currentTime - previousTime < rate)
        return;
    
    switch (n) {
        case 0:
            rings.push_back(ring(0, 2));
            rings.push_back(ring(0, -2));
            rings.push_back(ring(-2.5, 0));
            rings.push_back(ring(2.5, 0));
            break;
            
        case 1:
            rings.push_back(ring(0, 0, 0));
            rings.push_back(ring(0, 0, -5));
            rings.push_back(ring(0, 0, -10));
            rings.push_back(ring(0, 0, -15));
            rings.push_back(ring(0, 0, -20));
            break;
            
        case 2:
            rings.push_back(ring(0, 1));
            rings.push_back(ring(1.5, -1.1));
            rings.push_back(ring(-1.5, -1.1));
            break;
            
        case 3:
            rings.push_back(ring(5, 1));
            rings.push_back(ring(2.75, -1));
            rings.push_back(ring(-5, 1));
            rings.push_back(ring(-2.75, -1));
            break;
            
        case 4:
            rings.push_back(ring(0, 0, 0));
            rings.push_back(ring(-1, 1, -5));
            rings.push_back(ring(1, 1, -10));
            rings.push_back(ring(1, -1, -15));
            rings.push_back(ring(-1, -1, -20));
            rings.push_back(ring(0, 0, -25));
            break;
            
        default:
            rings.push_back(ring());
            break;
    }

    // Reset time
    previousTime = currentTime;
    rate = rand() % (high - low) + low;
    high -= (high > low + 100) ? 1 : 0;
}