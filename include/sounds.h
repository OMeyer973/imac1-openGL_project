#ifndef SOUNDS_H_
#define SOUNDS_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>
#include <dirent.h>
#include <time.h> 

#define NBSOUNDS 6

//Game options 
extern int currLevelId;
extern int gameOver;
extern int gameWin;
extern int reachedEndOfLevel;
extern int gameIsRunning;
extern Mix_Chunk* sounds[NBSOUNDS];

void initSounds();
void loadMusics();
void playMusic(int canal, int musique);



#endif
