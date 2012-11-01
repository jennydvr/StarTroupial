//
//  interactiveObject.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 31/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "interactiveObject.h"

interactiveObject::interactiveObject() : object(5, -5) {}

interactiveObject::interactiveObject(float a, float b, float c) : object(a, b, c) {}

void interactiveObject::init() {
    touched = false;
}

void interactiveObject::action() {}

int interactiveObject::updateScore(object player) {
    // If already touched, nothing to update
    if (touched)
        return 0;
    
    // If hits, return factor
    return hits(player) ? factor : 0;
}

bool interactiveObject::hits(object obj) {
    // If it has already been touched, can't hit again
    if (touched)
        return false;
    
    // Check if there is a collision - if it does, take action
    if ((touched = collision(obj.box, box))) {
        action();
        obj.dead = true;
    }
    
    // Return the result of the checking
    return touched;
}