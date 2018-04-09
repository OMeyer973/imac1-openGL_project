#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>
#include <dirent.h>
#include <time.h> 

#define NBTEXTURES 10

extern unsigned int WINDOW_WIDTH;
extern unsigned int WINDOW_HEIGHT;
extern const unsigned int BIT_PER_PIXEL;
extern const Uint32 FRAMERATE_MILLISECONDS;

void resizeViewport();
int isLoaded (SDL_Surface* image);
void drawTexturedSquare(GLuint textureID);




#endif
