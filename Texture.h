/*
      Texture.h
      Tudor Carean - April 2008
      http://nehe.gamedev.net/data/lessons/lesson.asp?lesson=33

      TGA files loader.
*/

#ifndef __StarTroupial__loader__
#define __StarTroupial__loader__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>

#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

typedef	struct									
{
	GLubyte	* imageData;									// Image Data (Up To 32 Bits)
	GLuint	bpp;											// Image Color Depth In Bits Per Pixel
	GLuint	width;											// Image Width
	GLuint	height;											// Image Height
	GLuint	texID;											// Texture ID Used To Select A Texture
	GLuint	type;											// Image Type (GL_RGB, GL_RGBA)
    bool    created;                                        // Checks if the texture is initialized or not
} Texture;	

typedef struct
{
	GLubyte Header[12];									// TGA File Header
} TGAHeader;


typedef struct
{
	GLubyte		header[6];								// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;							// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;								// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;									// Temporary Variable
	GLuint		type;	
	GLuint		Height;									//Height of Image
	GLuint		Width;									//Width ofImage
	GLuint		Bpp;									// Bits Per Pixel
} TGA;

bool LoadTGA(Texture &texture, char * filename);
bool LoadCompressedTGA(Texture &texture, char * filename, FILE * fTGA);
bool LoadUncompressedTGA(Texture &texture, char * filename, FILE * fTGA);

#endif /* defined(__StarTroupial__loader__) */
