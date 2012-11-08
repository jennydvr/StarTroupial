//
//  soundManager.h
//  StarTroupial
//
//  Created by Jenny Valdez on 07/11/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#ifndef __StarTroupial__soundManager__
#define __StarTroupial__soundManager__

#include "config.h"

#ifdef USE_SOUNDS

#if defined(__APPLE__) || defined(MACOSX)
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif

#include <cstring>
#include <cstdio>
#include <iostream>

void initSounds();
void playShootingSong();
void playRingsSong();
void playExplosionSong();
void playBackgroundSong();

#endif
#endif /* defined(__StarTroupial__soundManager__) */
