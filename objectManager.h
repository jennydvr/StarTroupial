//
//  objectManager.h
//  StarTroupial
//
//  Created by Jenny Valdez on 28/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#ifndef __StarTroupial__objectManager__
#define __StarTroupial__objectManager__

#include <vector>
#include <algorithm>
#include "starship.h"
#include "ring.h"
#include "star.h"

using namespace std;

// Game objects
extern vector<ring> rings;
extern vector<star> stars;
extern ship player;

void addRings(int n);

#endif /* defined(__StarTroupial__objectManager__) */
