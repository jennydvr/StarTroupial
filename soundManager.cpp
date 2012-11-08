//
//  soundManager.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 07/11/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "soundManager.h"

using namespace std;

ALuint buffer[2];
ALuint source[2];

void initSounds() {
    alutInit(0, NULL);
    
    // Music position (kind of)
    ALfloat listenerPos[] = {0, 0, 50};
    ALfloat listenerVel[] = {0, 0, 0};
    ALfloat	listenerOri[] = {0, 0, 1, 0, 1, 0};
    
    alListenerfv(AL_POSITION, listenerPos);
    alListenerfv(AL_VELOCITY, listenerVel);
    alListenerfv(AL_ORIENTATION, listenerOri);
    
    alGetError();
    
    if (alGetError() != AL_NO_ERROR) {
        cout << "Error creando buffers de sonido.\n";
        exit(0);
    }
    
    // Generate buffers, or else no sound will happen
    alGenBuffers(1, buffer);
    
    ALsizei size, freq;
    ALenum format;
    ALvoid *data;
    
    alutLoadWAVFile("background.wav", &format, &data, &size, &freq);
    alBufferData(buffer[0], format, data, size, freq);
    alutUnloadWAV(format, data, size, freq);
    
    alutLoadWAVFile("ring.wav", &format, &data, &size, &freq);
    alBufferData(buffer[1], format, data, size, freq);
    alutUnloadWAV(format, data, size, freq);
    
    alGetError();
    alGenSources(1, source);
    
    if (alGetError() != AL_NO_ERROR) {
        cout << "Error creando fuentes de sonido.\n";
        exit(0);
    }
    
    ALfloat pos[] = {0, 0, 0};
    ALfloat vel[] = {0, 0, 0};
    
    alSourcef(source[0], AL_PITCH, 1);
    alSourcef(source[0], AL_GAIN, 1);
    alSourcefv(source[0], AL_POSITION, pos);
    alSourcefv(source[0], AL_VELOCITY, vel);
    alSourcei(source[0], AL_BUFFER, buffer[0]);
    alSourcei(source[0], AL_LOOPING, AL_TRUE);
    
    alSourcef(source[1], AL_PITCH, 1);
    alSourcef(source[1], AL_GAIN, 1);
    alSourcefv(source[1], AL_POSITION, pos);
    alSourcefv(source[1], AL_VELOCITY, vel);
    alSourcei(source[1], AL_BUFFER, buffer[1]);
    alSourcei(source[1], AL_LOOPING, AL_FALSE);
}

void playBackgroundSong() {
    alSourcePlay(source[0]);
}

void playRingsSong() {
    alSourcePlay(source[1]);
}
