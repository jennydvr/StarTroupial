//
//  soundManager.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 07/11/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "soundManager.h"

using namespace std;

unsigned int buffer[4];
unsigned int source[4];

void readWAVFile(const char *filename, int &format, unsigned char *&data, int &dataSize, int &frequency) {
#ifdef USE_SOUNDS
    FILE *file = fopen(filename, "rb");
    
    if (!file) {
        cout << "Error: Archivo de sonido inexistente.\n";
        exit(0);
    }
    
    // Variables to store info about the WAVE file (all of them is not needed for OpenAL)
    char type[4];
    ALsizei size, chunkSize;
    short formatType, channels;
    ALsizei avgBytesPerSec;
    short bytesPerSample, bitsPerSample;
    
    // Check that the WAVE file is OK
    
    // First bytes in file should read RIFF
    fread(type, sizeof(char), 4, file);
    if (type[0] != 'R' || type[1] != 'I' || type[2] != 'F' || type[3] != 'F') {
        cout << "Error: No leo RIFF.\n";
        exit(0);
    }
    
    fread(&size, sizeof(unsigned int), 1, file);
    
    // Here we should read WAVE
    fread(type, sizeof(char), 4, file);
    if (type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E') {
        cout << "Error: No leo WAVE.\n";
        exit(0);
    }
    
    // Here, read "fmt "
    fread(type, sizeof(char), 4, file);
    if (type[0] != 'f' || type[1]!='m' || type[2]!='t' || type[3]!=' ') {
        cout << "Error: No leo \"fmt \".\n";
        exit(0);
    }
    
    // Now we know that the file is a acceptable WAVE file
    // Info about the WAVE data is now read and stored
    fread(&chunkSize, sizeof(unsigned int), 1, file);
    fread(&formatType, sizeof(short), 1, file);
    fread(&channels, sizeof(short), 1, file);
    fread(&frequency, sizeof(unsigned int), 1, file);
    fread(&avgBytesPerSec, sizeof(unsigned int), 1, file);
    fread(&bytesPerSample, sizeof(short), 1, file);
    fread(&bitsPerSample, sizeof(short), 1, file);
    
    // Here, read "data"
    fread(type, sizeof(char), 4, file);
    
    if (type[0]!='d' || type[1]!='a' || type[2]!='t' || type[3]!='a') {
        cout << "Error: No leo data.\n";
        exit(0);
    }
    
    // Size of the sound data
    fread(&dataSize, sizeof(unsigned int), 1, file);
    
    // Read data
    data = new unsigned char[dataSize];                // Allocate memory for the sound data
    fread(data, sizeof(unsigned char), dataSize, file);  // Read the sound data
    
    // Figure out the format
    if (bitsPerSample == 8) {
        if (channels == 1)
            format = AL_FORMAT_MONO8;
        else if (channels == 2)
            format = AL_FORMAT_STEREO8;
    } else if (bitsPerSample == 16) {
        if (channels == 1)
            format = AL_FORMAT_MONO16;
        else if (channels == 2)
            format = AL_FORMAT_STEREO16;
    }
    
    fclose(file);
#endif
}

void fillSource(int i, int loop = 0) {
#ifdef USE_SOUNDS
    float pos[] = {0, 0, 0};
    float vel[] = {0, 0, 0};
    
    alSourcef(source[i], AL_PITCH, 1);
    alSourcef(source[i], AL_GAIN, 1);
    alSourcefv(source[i], AL_POSITION, pos);
    alSourcefv(source[i], AL_VELOCITY, vel);
    alSourcei(source[i], AL_BUFFER, buffer[i]);
    alSourcei(source[i], AL_LOOPING, loop);
#endif
}

void initSounds() {
#ifdef USE_SOUNDS
    
    // Initialize sounds
    ALCdevice *device = alcOpenDevice(NULL);
    ALCcontext *context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);
    
    // Music position (kind of)
    ALfloat listenerPos[] = {0, 0, 0};
    ALfloat listenerVel[] = {0, 0, 0};
    ALfloat	listenerOri[] = {0, 0, -1, 0, 1, 0};
    
    alListenerfv(AL_POSITION, listenerPos);
    alListenerfv(AL_VELOCITY, listenerVel);
    alListenerfv(AL_ORIENTATION, listenerOri);
    
    // Generate buffers, or else no sound will happen
    alGenBuffers(4, buffer);
    
    ALsizei size, freq;
    ALenum format;
    unsigned char *data;
    
    readWAVFile("resources/ring.wav", format, data, size, freq);
    alBufferData(buffer[0], format, data, size, freq);
    free(data);
    
    readWAVFile("resources/shoot.wav", format, data, size, freq);
    alBufferData(buffer[1], format, data, size, freq);
    free(data);
    
    readWAVFile("resources/explode.wav", format, data, size, freq);
    alBufferData(buffer[2], format, data, size, freq);
    free(data);
    
    readWAVFile("resources/background.wav", format, data, size, freq);
    alBufferData(buffer[3], format, data, size, freq);
    free(data);
    
    // Create sources
    alGenSources(4, source);
    
    fillSource(0);
    fillSource(1);
    fillSource(2);
    fillSource(3, AL_TRUE);
    
    playBackgroundSong();
#endif
}

void playRingsSong() {
#ifdef USE_SOUNDS
    alSourcePlay(source[0]);
#endif
}

void playShootingSong() {
#ifdef USE_SOUNDS
    alSourcePlay(source[1]);
#endif
}

void playExplosionSong() {
#ifdef USE_SOUNDS
    alSourcePlay(source[2]);
#endif
}

void playBackgroundSong() {
#ifdef USE_SOUNDS
    alSourcePlay(source[3]);
#endif
}
