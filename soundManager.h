//
//  soundManager.h
//  StarTroupial
//
//  Created by Jenny Valdez on 07/11/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#ifndef __StarTroupial__soundManager__
#define __StarTroupial__soundManager__

#if defined(__APPLE__) || defined(MACOSX)
#include <OpenAL/al.h>
#else
#include <AL/alut.h>
#endif

#include <cstring>
#include <iostream>

void initSounds();
void playBackgroundSong();
void playRingsSong();

#endif /* defined(__StarTroupial__soundManager__) */
